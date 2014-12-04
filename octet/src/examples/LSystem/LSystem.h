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

      TextReader* tr;
      TreeContext* tc;

      void AcquireInputs(){
         if (is_key_down('1') && currTree != '1'){
            currTree = '1';
            tr->OpenFile("../../../lsystemassets/tree1.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else if (is_key_down('2') && currTree != '2'){
            currTree = '2';
            tr->OpenFile("../../../lsystemassets/tree2.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else if (is_key_down('3') && currTree != '3'){
            currTree = '3';
            tr->OpenFile("../../../lsystemassets/tree3.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else if (is_key_down('4') && currTree != '4'){
            currTree = '4';
            tr->OpenFile("../../../lsystemassets/tree4.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }  
         else if (is_key_down('5') && currTree != '5'){
            currTree = '5';
            tr->OpenFile("../../../lsystemassets/tree5.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else if (is_key_down('6') && currTree != '6'){
            currTree = '6';
            tr->OpenFile("../../../lsystemassets/tree6.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else if (is_key_down('7') && currTree != '7'){
            currTree = '7';
            tr->OpenFile("../../../lsystemassets/tree7.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else if (is_key_down('8') && currTree != '8'){
            currTree = '8';
            tr->OpenFile("../../../lsystemassets/tree8.txt");
            //tc->Reset();
            tc = new TreeContext();
            tr->ParseStructure(*tc);
            tc->Initialize();
            tr->CloseFile();
         }
         else{

            if (is_key_down(octet::key_up)){
               
               tc->SetCurrentStep(true);

            }
            else if (is_key_down(octet::key_down)){

               tc->SetCurrentStep(false);

            }

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

      tc = new TreeContext();
      tr = new TextReader("../../../lsystemassets/tree1.txt");
      tr->ParseStructure(*tc);
      tr->CloseFile();
      tc->Initialize();
   }

    /// this is called to draw the world
    void draw_world(int x, int y, int w, int h) {

         AcquireInputs();

         int vx = 0, vy = 0;
         get_viewport_size(vx, vy);
         app_scene->begin_render(vx, vy);

         // update matrices. assume 30 fps.
         app_scene->update(1.0f/30);

         // draw the scene
         app_scene->render((float)vx / vy);

         }
      };
}
