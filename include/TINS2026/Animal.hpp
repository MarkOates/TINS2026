#pragma once


#include <TINS2025/Entity.hpp>
#include <TINS2026/Animal.hpp>
#include <string>
#include <vector>


namespace TINS2026
{
   class Animal
   {
   private:

   protected:


   public:
      std::string identifier;
      std::string name;
      TINS2025::Entity::Type entity_type;
      std::vector<std::string> interesting_facts_dialog_pages;
      int how_many_lines_needed_for_notetaking;
      double hype_rate_per_sec;
      double hype_aura_radius;
      Animal();
      ~Animal();

      static TINS2026::Animal build(std::string identifier="[unset-identifier]", std::string name="[unset-name]", TINS2025::Entity::Type entity_type=TINS2025::Entity::Type::ENTITY_TYPE_UNDEF, std::vector<std::string> interesting_facts_dialog_pages={}, int how_many_lines_needed_for_notetaking=3, double hype_rate_per_sec=15.0, double hype_aura_radius=5.0);
   };
}



