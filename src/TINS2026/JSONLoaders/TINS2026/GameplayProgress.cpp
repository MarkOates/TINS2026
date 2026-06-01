

#include <TINS2026/JSONLoaders/TINS2026/GameplayProgress.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2D.hpp>
#include <TINS2025/Gameplay/ProgressAndStateFlagsJSONLoader.hpp>
#include <TINS2026/JSONLoaders/TINS2025/Entity/Type.hpp>
//#include <TINS2025/Gameplay/Screen.hpp>
#include <TINS2025/Entity.hpp>


namespace TINS2026
{


void to_json(nlohmann::json& j, const GameplayProgress& object)
{
   std::set<TINS2025::Gameplay::Screen::ProgressAndStateFlags> progress_and_state_flags;
   for (auto &f : object.progress_and_state_flags)
   {
      progress_and_state_flags.insert(
         static_cast<TINS2025::Gameplay::Screen::ProgressAndStateFlags>(f)
      );
   }

   std::set<TINS2025::Entity::Type> documented_entity_types;
   for (auto &t : object.documented_entity_types)
   {
      documented_entity_types.insert(
         static_cast<TINS2025::Entity::Type>(t)
      );
   }

   j = nlohmann::json{
      { "items_collected_tmj_ids", object.items_collected_tmj_ids },
      { "player_location", object.player_location },
      { "player_excitement", object.player_excitement },
      { "player_freakouts", object.player_freakouts },
      { "player_line_capacity", object.player_line_capacity },
      { "player_lines_filled", object.player_lines_filled },
      { "progress_and_state_flags", progress_and_state_flags },
      { "documented_entity_types", documented_entity_types },
      { "triggered_dialog_names", object.triggered_dialog_names },
   };
}

void from_json(const nlohmann::json& j, GameplayProgress& object)
{
   j.at("items_collected_tmj_ids").get_to(object.items_collected_tmj_ids);
   j.at("player_location").get_to(object.player_location);
   j.at("player_excitement").get_to(object.player_excitement);
   j.at("player_line_capacity").get_to(object.player_line_capacity);
   j.at("player_lines_filled").get_to(object.player_lines_filled);
   j.at("player_freakouts").get_to(object.player_freakouts);
   j.at("triggered_dialog_names").get_to(object.triggered_dialog_names);

   // Fill the progress_and_state_flags
   std::set<std::string> progress_and_state_flags_str;
   j.at("progress_and_state_flags").get_to(progress_and_state_flags_str);
   std::set<uint32_t> progress_and_state_flags;
   object.progress_and_state_flags.clear();
   for (auto &progress_and_state_flag_str : progress_and_state_flags_str)
   {
      object.progress_and_state_flags.insert(TINS2025::Gameplay::Screen::from_string(progress_and_state_flag_str));
   }
   for (auto &f : object.progress_and_state_flags)
   {
      progress_and_state_flags.insert(
         static_cast<TINS2025::Gameplay::Screen::ProgressAndStateFlags>(f)
      );
   }

   // Fill the documented_entity_types
   std::set<std::string> documented_entity_types_str;
   j.at("documented_entity_types").get_to(documented_entity_types_str);
   std::set<uint32_t> documented_entity_types;
   object.documented_entity_types.clear();
   for (auto &progress_and_state_flag_str : documented_entity_types_str)
   {
      object.documented_entity_types.insert(TINS2025::Entity::from_string(progress_and_state_flag_str));
   }
   for (auto &f : object.documented_entity_types)
   {
      documented_entity_types.insert(
         static_cast<TINS2025::Entity::Type>(f)
      );
   }
}


} // namespace TINS2026


