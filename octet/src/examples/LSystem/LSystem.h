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

      TextReader* tr;
      TreeContext* tc;

      void AcquireInputs(){
         if (is_key_down('1')){
         }
         else if (is_key_down('2')){

         }
         else if (is_key_down('3')){

         }
         else if (is_key_down('4')){

         }
         else if (is_key_down('5')){

         }
         else if (is_key_down('6')){

         }
         else if (is_key_down('7')){

         }
         else if (is_key_down('8')){

         }
         else{
            if (is_key_down(octet::key_up)){
               if (tc->)
            }
            else if (is_key_down(octet::key_down)){

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

      tr = new TextReader("lsystemassets/tree1.txt");
      tc = tr->ParseStructure();
      tr->CloseFile();

      tc->CalculateNextIteration();
      tc->CalculateNextIteration(2);

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
