

#include <TINS2026/AnimalDatabase.hpp>

#include <AllegroFlare/Logger.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace TINS2026
{


AnimalDatabase::AnimalDatabase()
   : animals(build_animal_database())
{
}


AnimalDatabase::~AnimalDatabase()
{
}


const TINS2026::Animal& AnimalDatabase::get_record_by_entity_type(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2026::AnimalDatabase::get_record_by_entity_type]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2026::AnimalDatabase::get_record_by_entity_type]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   if (animals.count(entity_type) == 0)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "There was no animal record for the entity type \"" + TINS2025::Entity::to_string(entity_type) + "\""
      );
   }
   return animals[entity_type];
}

std::map<TINS2025::Entity::Type, TINS2026::Animal> AnimalDatabase::build_animal_database()
{
   int LINES_OF_NOTES_NEEDED = 3;
   double HYPE_RATE = 15.0;
   double HYPE_AURA_RADIUS = 5.0;

   std::vector<TINS2026::Animal> pre_result = {

      Animal::build(
         "giraffe",
         "Giraffe",
         TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE,
         {
            "Amazing! A giraffe!",
            "They have huge long necks!",
         },
         LINES_OF_NOTES_NEEDED,
         HYPE_RATE,
         HYPE_AURA_RADIUS
      ),

      Animal::build(
         "goat",
         "Goat",
         TINS2025::Entity::Type::ENTITY_TYPE_GOAT,
         {
            "O...",
            "M...",
            "G.",
            "This goat... ",
            "IS SOOO CUUUTEE!",
            "This has to be the CUTEST GOAT in the ENTIRE WORLD!",
         },
         LINES_OF_NOTES_NEEDED,
         HYPE_RATE,
         HYPE_AURA_RADIUS
      ),

   };

   // Build a map
   std::map<TINS2025::Entity::Type, TINS2026::Animal> result;

   for (auto &pre_result_item : pre_result)
   {
      result[pre_result_item.entity_type] = pre_result_item;
   }

   // Verify the map has the same count as the vector (for safety)
   if (result.size() != pre_result.size())
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "There was a mis-match between the number of result records and the number of pre_result records, meaning "
            "there is likely a duplicate key. Please review."
      );
   }

   return result;
}


} // namespace TINS2026


