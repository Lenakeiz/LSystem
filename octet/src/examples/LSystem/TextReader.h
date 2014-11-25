#pragma once
#include "../../octet.h"
#include <fstream>

namespace LSS{
   
   class TextReader
   {

   std::ifstream file;


   public:

      TextReader(octet::string path)
      {
         file.open(path);
      }

      void ParseStructure(){
         while (!file.eof()){
            
         }
      }

      ~TextReader()
      {
         file.close();
      }

   };

}


