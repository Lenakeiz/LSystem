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
      tr->ParseStructure(tc);
      tr->CloseFile();

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
