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
      unsigned currentStep = 0;
   
   public:

      octet::dynarray<char> alphabet;
      octet::dynarray<char> axiom;
      
      octet::dynarray<RuleEquation> rules;

      //octet::dynarray<char> lastIteration;
      octet::dynarray<char> currentIteration;

      /// This function calculates the next step of the tree (can be an upward, downward movement), we save the last file configuration before calculating the current
      void CalculateNextIteration(unsigned step = 1){
         
         int deb = 0;
         this->currentStep = step;

         if (step == 0){
            assert("Impossible to calculate rule");
         }
         else if (step == 1){
            currentIteration = axiom;            
         }
         else{
            
            octet::dynarray<char> nextIteration;

            for (octet::dynarray<char>::iterator it = currentIteration.begin(); it != currentIteration.end(); ++it)
            {
               char currChar = *it;
               bool find = false;
               std::string currentRule = "";
               //Looking if current simbol is in the alphabet
               for (unsigned i = 0; i < alphabet.size(); i++){
                  if (currChar == alphabet[i]){
                     find = true;
                     //getting the rule according to the letter just found
                     for (unsigned i = 0; i < rules.size(); i++){
                        if(rules[i].alphabet == currChar)
                        {
                           currentRule = rules[i].rule;
                        }
                     }
                  }
               }

               if (!find){

                  nextIteration.push_back(*it);

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

            currentIteration = nextIteration;

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

