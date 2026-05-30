#pragma once


#include <TINS2026/Animal.hpp>
#include <string>
#include <vector>


namespace TINS2026
{
   class AnimalDatabase
   {
   private:
      std::vector<TINS2026::Animal> animals;

   protected:


   public:
      AnimalDatabase();
      ~AnimalDatabase();

      std::string run();
   };
}



