#pragma once
#include "../../octet.h"
#include <iostream>
#include <fstream>
#include "TreeContext.h"

namespace LSS{
   
   class TextReader
   {

   private:

   std::ifstream file;

   void ParseAlphabet(TreeContext& tc, std::string& currString){

      std::size_t start = currString.find("{");
      std::size_t stop = currString.find("}");

      std::string sub = currString.substr(start + 1, stop - start - 1);

      for (std::string::iterator it = sub.begin(); it != sub.end(); ++it)
      {
         tc.alphabet.push_back(*it);
      }
   }

   void ParseAxiom(TreeContext& tc, std::string& currString){

      std::size_t start = currString.find("{");
      std::size_t stop = currString.find("}");

      std::string sub = currString.substr(start + 1, stop - start - 1);

      for (std::string::iterator it = sub.begin(); it != sub.end(); ++it)
      {
         tc.axiom.push_back(*it);
      }
   }

   void ParseRule(TreeContext& tc, std::string& currString){

      std::size_t first = currString.find("{");
      std::size_t med = currString.find("=");
      std::size_t last = currString.find("}");
       
      std::string subAlpha = currString.substr(first + 1, med - first - 1);
      std::string subRule = currString.substr(med + 1, last - med - 1);

      RuleEquation re;
      re.alphabet = subAlpha[0];
      re.rule = subRule;

      tc.rules.push_back(re);

   }

   public:

      TextReader(const octet::string& path)
      {
         //printf("%s",path.c_str());
         OpenFile(path);
      }

      void ParseStructure(TreeContext& tc){

         std::string line;
         while (std::getline(file, line)){

            //break as soon as we find the first break
            /*if (line.compare(";") == 0)
            break;*/

            std::size_t found;

            found = line.find("Alphabet");
            if (found != std::string::npos){
               ParseAlphabet(tc, line);
            }
            found = line.find("Axiom");
            if (found != std::string::npos){
               ParseAxiom(tc, line);
            }
            found = line.find("Rule");
            if (found != std::string::npos){
               ParseRule(tc, line);
            }
            found = line.find("Angle");
            if (found != std::string::npos){
               //ParseRule(*tc, line);
            }
         }
      }

      /*
         TreeContext* ParseStructure(){

         TreeContext* tc = new TreeContext();
         
         std::string line;
         while (std::getline(file, line)){

            //break as soon as we find the first break
            //if (line.compare(";") == 0)
               break;

            std::size_t found;
            
            found = line.find("Alphabet");
            if (found != std::string::npos){
               ParseAlphabet(*tc, line);
            }
            found = line.find("Axiom");
            if (found != std::string::npos){
               ParseAxiom(*tc, line);
            }
            found = line.find("Rule");
            if (found != std::string::npos){
               ParseRule(*tc, line);
            }
            found = line.find("Angle");
            if (found != std::string::npos){
               //ParseRule(*tc, line);
            }
         }
         
         return tc;

      }*/

      void OpenFile(const octet::string& path){

         
         file.open(path.c_str(), std::ios::in);
         if (file.is_open())
         {
            printf("File opened!");
         }
         else{
            assert("error initializing the file");
         }
      }

      void CloseFile(){
         file.close();
      }

      ~TextReader()
      {
         file.close();
      }

   };

}


