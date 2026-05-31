

#include <TINS2026/AnimalDatabase.hpp>




namespace TINS2026
{


AnimalDatabase::AnimalDatabase()
   : animals(build_animal_database())
{
}


AnimalDatabase::~AnimalDatabase()
{
}


std::vector<TINS2026::Animal> AnimalDatabase::build_animal_database()
{
   int LINES_OF_NOTES_NEEDED = 3;
   double HYPE_RATE = 15.0;

   std::vector<TINS2026::Animal> result = {
      Animal::build("giraffe",
         "Giraffe", {
            "Amazing! A giraffe!",
            "They have huge long necks!",
         },
         LINES_OF_NOTES_NEEDED,
         HYPE_RATE
      )
   };
   return result;
}


} // namespace TINS2026


