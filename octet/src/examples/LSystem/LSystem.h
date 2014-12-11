////////////////////////////////////////////////////////////////////////////////
//
// (C) Andrea Castegnaro 2014
//
//

#include "TreeContext.h"
#include "TextReader.h"
#include "TreeRenderer.h"

namespace LSS {
  /// Scene containing a box with octet.
   class LSystem : public octet::app {
   
   private:
         
      // scene for drawing box
      octet::ref<octet::visual_scene> app_scene;
      char currTree = '1';
      bool changedTree = false;

      TextReader* tr;
      TreeContext* tc;
      TreeRenderer* render;
      
      void AcquireInputs(){

         

         if (is_key_down(octet::key_esc)){
            exit(1);
         }

         if (is_key_going_down('1') && currTree != '1'){
            currTree = '1';
            tr->OpenFile("../../../lsystemassets/tree1.txt");
            changedTree = true;
         }
         else if (is_key_going_down('2') && currTree != '2'){
            currTree = '2';
            tr->OpenFile("../../../lsystemassets/tree2.txt");
            changedTree = true;
         }
         else if (is_key_going_down('3') && currTree != '3'){
            currTree = '3';
            tr->OpenFile("../../../lsystemassets/tree3.txt");
            changedTree = true;
         }
         else if (is_key_going_down('4') && currTree != '4'){
            currTree = '4';
            tr->OpenFile("../../../lsystemassets/tree4.txt");
            changedTree = true;
         }  
         else if (is_key_going_down('5') && currTree != '5'){
            currTree = '5';
            tr->OpenFile("../../../lsystemassets/tree5.txt");
            changedTree = true;
         }
         else if (is_key_going_down('6') && currTree != '6'){
            currTree = '6';
            tr->OpenFile("../../../lsystemassets/tree6.txt");
            changedTree = true;
         }
         else if (is_key_going_down('7') && currTree != '7'){
            currTree = '7';
            tr->OpenFile("../../../lsystemassets/tree7.txt");
            changedTree = true;
         }
         else if (is_key_going_down('8') && currTree != '8'){
            currTree = '8';
            tr->OpenFile("../../../lsystemassets/tree8.txt");
            changedTree = true;
         }
         else{

            if (is_key_going_down(octet::key_up)){               
               tc->SetCurrentStep(true);
               PrepareTreeMesh();
            }
            else if (is_key_going_down(octet::key_down)){
               tc->SetCurrentStep(false);
               PrepareTreeMesh();
            }

            if (is_key_down(octet::key_left)){               
               tc->ModifyAngle(false);
               PrepareTreeMesh();
            }
            else if (is_key_down(octet::key_right)){            
               tc->ModifyAngle(true);
               PrepareTreeMesh();
            }

         }

         if (changedTree){            
            changedTree = false;
            tc->Reset();
            //tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
            PrepareTreeMesh();
         }

         //WSAD control camera
         if (is_key_down('W')){
            app_scene->get_camera_instance(0)->get_node()->access_nodeToParent().translate(0, 2.5, 0);
         }
         else if (is_key_down('S')){
            app_scene->get_camera_instance(0)->get_node()->access_nodeToParent().translate(0, -2.5, 0);
         }
         else if (is_key_down('A')){
            app_scene->get_camera_instance(0)->get_node()->access_nodeToParent().translate(-2.5, 0, 0);
         }
         else if (is_key_down('D')){
            app_scene->get_camera_instance(0)->get_node()->access_nodeToParent().translate(2.5, 0, 0);
         }
         else if (is_key_down('Q')){
            app_scene->get_camera_instance(0)->get_node()->access_nodeToParent().translate(0, 0, -2.5);
         }
         else if (is_key_down('E')){
            app_scene->get_camera_instance(0)->get_node()->access_nodeToParent().translate(0, 0, 2.5);
         }

      }

  public:
    /// this is called when we construct the class before everything is initialised.
    LSystem(int argc, char **argv) : app(argc, argv) {
    }

    ~LSystem(){
      delete tc;
      delete tr;
    }

    /// this is called once OpenGL is initialized
   void app_init() {

      app_scene = new octet::visual_scene();
      app_scene->create_default_camera_and_lights();

      app_scene->get_camera_instance(0)->set_far_plane(1000000000);

      tc = new TreeContext();
      tr = new TextReader("../../../lsystemassets/tree1.txt");
      render = new TreeRenderer();
      tr->ParseStructure(*tc);
      tr->CloseFile();
      tc->Initialize();

      PrepareTreeMesh();

      app_scene->add_child(render->GetNode());
      app_scene->add_mesh_instance(new octet::mesh_instance(render->GetNode(), render->GetMesh(), render->GetMaterial()));
      
   }
   
   void PrepareTreeMesh(){
      render->CalculateVertices(*tc);
   }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) 
    {

         AcquireInputs();

         int vx = 0, vy = 0;
         get_viewport_size(vx, vy);
         app_scene->begin_render(vx, vy);

         // update matrices. assume 30 fps.
         app_scene->update(1.0f/30);

         glClearColor(0, 0, 0, 1);
         glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

         // draw the scene
         app_scene->render((float)vx / vy);

         }
      };
}
