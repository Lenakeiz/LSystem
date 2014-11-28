#pragma once
#include "../../octet.h"

namespace LSS{

   class TreeRenderer
   {

   private:

      octet::dynarray<octet::mat4t> transformStack;

   public:

      TreeRenderer()
      {
      }

      ~TreeRenderer()
      {
      }
   };


}

