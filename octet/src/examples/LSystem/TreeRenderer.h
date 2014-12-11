#pragma once
#include "../../octet.h"

namespace LSS{

   /*
      void render(color_shader &shader, mat4t &cameraToWorld) {

      mat4t modelToProjection = mat4t::build_projection_matrix(modelToWorld, cameraToWorld);
      shader.render(modelToProjection, colour);

      float points[] = {
        0, 0, 0,
        0, lineSize, 0,
      };

      glVertexAttribPointer(attribute_pos, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)points);
      glEnableVertexAttribArray(attribute_pos);

      glDrawArrays(GL_LINES, 0, 2);
    }
  };
   */
   
   struct my_vertex {
      octet::vec3 pos;
      //uint32_t color;
   };

   struct draw_vertex{
      octet::vec3p pos;
      uint32_t color;
   };

   class StorageBlock{
      
      public:
      
      my_vertex start;
      my_vertex end;
      int depth;
      
      StorageBlock(const my_vertex s, const my_vertex e){
         start = s;
         end = e;
         depth = 0;
      }

      StorageBlock(const my_vertex s,const my_vertex e, int d){
         start = s;
         end = e;
         depth = d;
      }

      StorageBlock(){}
                        
   };

   class TreeRenderer
   {

      
   private:

      octet::dynarray<octet::mat4t> transformStack;
      octet::dynarray<StorageBlock*> struct_stack;

      octet::ref<octet::mesh> rend_mesh;
      int precision = 3;
      float radius = 0.2f;
      octet::ref<octet::scene_node> node;
      octet::ref<octet::material> mat;
      octet::ref<octet::param_shader> shader;

      const octet::vec3 dir_ = octet::vec3(0,1,0);

      // converts floats into a RGBA 8 bit color, took from one of Andy's example
      static uint32_t make_color(float r, float g, float b) {
         return 0xff000000 + ((int)(r*255.0f) << 0) + ((int)(g*255.0f) << 8) + ((int)(b*255.0f) << 16);
      }

      void createCylinder(octet::mat4t_in mToWorld){
         
      }

      void Forward(){

         //octet::mat4t aux = transformStack.back();
         my_vertex s;
         my_vertex e;
         s.pos = transformStack.back()[3].xyz();
         transformStack.back().translate(dir_);
         e.pos = transformStack.back()[3].xyz();
         StorageBlock* b = new StorageBlock(s, e);
         struct_stack.push_back(b);

      }

      void OpenBranch(){

         octet::mat4t nextMatrix;
         nextMatrix = transformStack.back();
         transformStack.push_back(nextMatrix);

      }

      void CloseBranch(){
         transformStack.pop_back();
         struct_stack.back()->depth = 1;
      }

      void Rotate(float angle){

         transformStack.back().rotateZ(angle);

      }

   public:
      
      TreeRenderer(){
         rend_mesh = new octet::mesh();
         node = new octet::scene_node();
         shader = new octet::param_shader("shaders/default.vs", "shaders/simple_color.fs");
         //Chuck: not adding the shader to mat
         mat = new octet::material(octet::vec4(1, 0, 0, 1),shader);
      }

      void CalculateVertices(TreeContext& tree){

         if (!transformStack.empty()){
            transformStack.reset();
         }
         if (!struct_stack.empty()){
            struct_stack.reset();
         }

         octet::mat4t modelToWorld;

         modelToWorld.loadIdentity();
         transformStack.push_back(modelToWorld);
         
         unsigned step = tree.GetCurrentStep();
         int numSteps = tree.iterations[step].size();

         for (unsigned i = 0; i < numSteps; i++)
         {
            if ((tree.iterations[step])[i] == 'F'){
               Forward();
            }
            else if ((tree.iterations[step])[i] == '['){
               OpenBranch();
            }
            else if ((tree.iterations[step])[i] == ']'){
               CloseBranch();
            }
            else if ((tree.iterations[step])[i] == '+'){
               Rotate(tree.GetAngle());
            }
            else if ((tree.iterations[step])[i] == '-'){
               Rotate(-(tree.GetAngle()));
            }
         }

         GenerateTree(tree);

      }

      void GenerateTree(TreeContext& tree){
         
         //rend_mesh = new octet::mesh();

         //Reserve space for the vertexes and indices
         size_t num_vertices = struct_stack.size() * precision * 2;
         size_t num_indices = struct_stack.size() * precision * 2 * 3;
         //size_t num_indices = tree.GetStringLength() * 2;
         rend_mesh->allocate(sizeof(draw_vertex) * num_vertices, sizeof(uint32_t) * num_indices);
         rend_mesh->set_params(sizeof(draw_vertex), num_indices, num_vertices, GL_TRIANGLES, GL_UNSIGNED_INT);

         rend_mesh->clear_attributes();
         rend_mesh->add_attribute(octet::attribute::attribute_pos, 3, GL_FLOAT, 0);
         rend_mesh->add_attribute(octet::attribute::attribute_color, 4, GL_UNSIGNED_BYTE, 12, GL_TRUE);
            
         octet::gl_resource::wolock vlock(rend_mesh->get_vertices());
         draw_vertex *vtx = (draw_vertex*)vlock.u8();
         octet::gl_resource::wolock il(rend_mesh->get_indices());
         uint32_t* idx = il.u32();

         int numVtxs = 0;

         for (unsigned i = 0; i != struct_stack.size(); i++)
         {

            for (size_t j = 0; j < precision; ++j) {
               //float r = 0.0f, g = 1.0f * i / precision, b = 1.0f;
               float theta = j * 2.0f * 3.14159265f / precision;
               octet::vec3 s = (struct_stack[i]->start).pos;
               octet::vec3 e = (struct_stack[i]->end).pos;
               vtx->pos = s + octet::vec3p(cosf(theta) * radius, 0, sinf(theta) * radius);
               // printf("vtx bot %i: %f, %f, %f  ", i, vtx->pos.x(), vtx->pos.y(), vtx->pos.z());
               vtx->color = make_color(150.0f, 75.0f, 0);
               vtx++;
               vtx->pos = e + octet::vec3p(cosf(theta) * radius, 0, sinf(theta) * radius);
               // printf("vtx top %i: %f, %f, %f\n", i, vtx->pos.x(), vtx->pos.y(), vtx->pos.z());
               if (struct_stack[i]->depth == 0){
                  vtx->color = make_color(150.0f, 75.0f, 0);
               }
               else{
                  vtx->color = make_color(0.0f, 1.0f, 0);
               }
               vtx++;
            }

            // make the triangles
            uint32_t vn = 0;
            for (size_t j = 0; j != precision; ++j) {
               /*
               1---------3
               |       / |
               |    /    |
               | /       |
               0---------2
               */

               idx[0] = vn + 0 + numVtxs;
               idx[1] = ((vn + 3) % 6) + numVtxs;
               idx[2] = vn + 1 + numVtxs;
               idx += 3;
               // printf("%u,%u,%u :", idx[-3], idx[-2], idx[-1]);
               idx[0] = vn + 0 + numVtxs;
               idx[1] = ((vn + 2) % 6) + numVtxs;
               idx[2] = ((vn + 3) % 6) + numVtxs;
               idx += 3;
               // printf(" %u,%u,%u\n", idx[-3], idx[-2], idx[-1]);
               vn += 2;
            }
            // this is number of vertices added
            numVtxs += 6;

            /*vtx->pos = (struct_stack[i]->start).pos;

            if (struct_stack[i]->depth >= 0){
               vtx->color = make_color(150.0f, 75.0f, 0);
            }
            else{
               vtx->color = make_color(0.0f, 1.0f, 0);
            }
            vtx++;

            vtx->pos = (struct_stack[i]->end).pos;

            if (struct_stack[i]->depth == 0){
               vtx->color = make_color(150.0f, 75.0f, 0);
            }
            else{
               vtx->color = make_color(0.0f, 1.0f, 0);
            }
            vtx++;*/
         }

      }

      octet::scene_node* GetNode() {
         return node;
      }

      /// returns the mesh 
      octet::mesh* GetMesh() {
         return rend_mesh;
      }

      octet::material* GetMaterial(){
         return mat;
      }

      ~TreeRenderer()
      {
      }
   };


}

