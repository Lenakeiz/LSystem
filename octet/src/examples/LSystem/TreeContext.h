#pragma once
#include "../../octet.h"

namespace LSS{
   
   static const int DEBUG_ITERATION = 1;

   struct RuleEquation{
      char alphabet;
      std::string rule;
   };

   class TreeContext
   {
    
   
   private:

      int currentStep = 0;
      float angle = 22.7f;
   
   public:

      octet::dynarray<char> alphabet;
      octet::dynarray<char> axiom;
      
      octet::dynarray<RuleEquation> rules;

      std::vector<std::vector<char>> iterations;
      //octet::dynarray<octet::dynarray<char>> iterations;
            
      int GetCurrentStep(){
         return currentStep;
      }

      float GetAngle(){
         return angle;
      }

      void SetAngle(float ang){
         angle = ang;
      }

      void ModifyAngle(bool direction){
         angle = direction ? angle + 1.0f : angle - 1.0f;         
      }

      int GetDrawingSize(){
         int num = 0;
         for (int i = 0; i < iterations[currentStep].size(); ++i){
            if (iterations[currentStep][i] == 'F') {
               ++num;
            }
         }
         return num;
      }

      bool CheckNewIteration(){
         return currentStep >= iterations.size(); //Remember I always increase current step before this step. currentStep is the position inside the dinarray so currentStep = 0 -> size = 1      
      }

      void Initialize(){
         currentStep = 0;
         CalculateNextIteration();
      }

      /// Setting new current step for drawing the tree
      void SetCurrentStep(bool direction){

         if (direction){
            currentStep += 1;
            if (CheckNewIteration()){
               CalculateNextIteration();
            }
         }
         else{
            currentStep -= 1;
            if (currentStep <= -1)
               currentStep = 0;
         }

      }

      /// This function calculates the next step of the tree (can be an upward, downward movement), we save the last file configuration before calculating the current
      void CalculateNextIteration(){
         
         std::vector<char> nextIteration;

         if (currentStep == -1){
            assert("Impossible to calculate rule");
         }

         else if (currentStep == 0){

            for (unsigned i = 0; i < axiom.size(); i++)
            {
               nextIteration.push_back(axiom[i]);
            }

            
         }

         else{
            
            std::vector<char> lastIteration = iterations.back();

            for (unsigned  i = 0; i != lastIteration.size(); i++)
            {
               char currChar = lastIteration[i];
               bool find = false;
               std::string currentRule = "";
               
               //Looking if current simbol is in the alphabet
               for (unsigned i = 0; i < alphabet.size(); i++){
                  if (currChar == alphabet[i]){
                     find = true;
                     //getting the rule according to the letter just found
                     for (unsigned i = 0; i < rules.size(); i++){
                        if(rules[i].alphabet == currChar){
                           currentRule = rules[i].rule;
                        }
                     }
                  }
               }

               if (!find){

                  nextIteration.push_back(currChar);

               }
               else if(currentRule != ""){

                  for (std::string::iterator it = currentRule.begin(); it != currentRule.end(); ++it)
                  {
                     nextIteration.push_back(*it);
                  }

               }
               else{
                  if (DEBUG_ITERATION == 1){
                     printf("Founded %c, but not its rule\n", currChar);
                  }
               }
            }
         }

         iterations.push_back(nextIteration);

      }

      void DebugPrint(){
         printf("Current iteration is: %s \n", iterations[currentStep]);
      }

      void Reset(){
         
         if (!alphabet.empty()){
            alphabet.reset();
         }
         if (!axiom.empty()){
            axiom.reset();
         }
         if (!rules.empty()){
            rules.reset();
         }

         if (!iterations.empty()){
            for (unsigned i = 0; i < iterations.size(); i++)
            {
               if (!iterations[i].empty()){
                  iterations[i].clear();
               }
            }
            iterations.clear();
         }

      }

      TreeContext()
      {
         
      }

      ~TreeContext()
      {

      }

   };

}

