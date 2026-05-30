

#include <TINS2026/JSONLoaders/TINS2026/GameplayProgress.hpp>
#include <AllegroFlare/JSONLoaders/AllegroFlare/Vec2D.hpp>
#include <TINS2025/Gameplay/ProgressAndStateFlagsJSONLoader.hpp>
//#include <TINS2025/Gameplay/Screen.hpp>


namespace TINS2026
{


void to_json(nlohmann::json& j, const GameplayProgress& object)
{
   //std::set<std::string> flags_s;
   //std::set<uint32_t> flags_i;

   //for (auto &flag : object.progress_and_state_flags)
   //{
      //flags_s.push_back(to_string());
   //}
   std::set<TINS2025::Gameplay::Screen::ProgressAndStateFlags> progress_and_state_flags;
   for (auto &f : object.progress_and_state_flags)
   {
      progress_and_state_flags.insert(
         static_cast<TINS2025::Gameplay::Screen::ProgressAndStateFlags>(f)
      );
   }
//TINS2025::Gameplay::Screen::ProgressAndStateFlags

//for (uint32_t v : raw_values)
//{
   //flags.insert(static_cast<TINS2026ProgressAndStateFlags>(v));
//}

   j = nlohmann::json{
      { "items_collected_tmj_ids", object.items_collected_tmj_ids },
      { "player_location", object.player_location },
      { "player_excitement", object.player_excitement },
      { "player_line_capacity", object.player_line_capacity },
      { "player_lines_filled", object.player_lines_filled },
      { "progress_and_state_flags", progress_and_state_flags },
   };
}

void from_json(const nlohmann::json& j, GameplayProgress& object)
{
   j.at("items_collected_tmj_ids").get_to(object.items_collected_tmj_ids);
   j.at("player_location").get_to(object.player_location);
   j.at("player_excitement").get_to(object.player_excitement);
   j.at("player_line_capacity").get_to(object.player_line_capacity);
   j.at("player_lines_filled").get_to(object.player_lines_filled);

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
}


} // namespace TINS2026


