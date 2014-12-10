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
      octet::vec3p pos;
      //uint32_t color;
   };

   class StorageBlock{
      
      public:
      
      my_vertex start;
      my_vertex end;
      
      StorageBlock(const my_vertex s,const my_vertex e){
         start = s;
         end = e;
      }

      StorageBlock(){}
                        
   };

   class TreeRenderer
   {

      
   private:

      octet::dynarray<octet::mat4t> transformStack;
      octet::dynarray<StorageBlock*> struct_stack;

      octet::ref<octet::mesh> rend_mesh;
      octet::ref<octet::scene_node> node;
      octet::ref<octet::material> mat;
      octet::ref<octet::param_shader> shader;

      const octet::vec3 dir_ = octet::vec3(0,1,0);

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
         mat = new octet::material(octet::vec4(1, 0, 0, 1));
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
         size_t num_vertices = struct_stack.size() * 2; //tree.GetStringLength() * 2;
         //size_t num_indices = tree.GetStringLength() * 2;
         rend_mesh->allocate(sizeof(my_vertex) * num_vertices, 0);
         rend_mesh->set_params(sizeof(my_vertex), 0, num_vertices, GL_LINES, NULL);

         rend_mesh->clear_attributes();
         rend_mesh->add_attribute(octet::attribute::attribute_pos, 3, GL_FLOAT, 0);
         //rend_mesh->add_attribute(octet::attribute::attribute_color, 4, GL_UNSIGNED_BYTE, 12, GL_TRUE);
            
         octet::gl_resource::wolock vlock(rend_mesh->get_vertices());
         my_vertex *vtx = (my_vertex*)vlock.u8();

         for (unsigned i = 0; i != struct_stack.size(); i++)
         {
            vtx->pos = (struct_stack[i]->start).pos;
            vtx++;
            vtx->pos = (struct_stack[i]->end).pos;
            vtx++;
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

