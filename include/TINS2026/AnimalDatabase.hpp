#pragma once


#include <TINS2025/Entity.hpp>
#include <TINS2026/Animal.hpp>
#include <map>


namespace TINS2026
{
   class AnimalDatabase
   {
   private:
      std::map<TINS2025::Entity::Type, TINS2026::Animal> animals;

   protected:


   public:
      AnimalDatabase();
      ~AnimalDatabase();

      const TINS2026::Animal& get_record_by_entity_type(TINS2025::Entity::Type entity_type=TINS2025::Entity::Type::ENTITY_TYPE_UNDEF);
      std::map<TINS2025::Entity::Type, TINS2026::Animal> build_animal_database();
   };
}



