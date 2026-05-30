

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

   j = nlohmann::json{
      { "items_collected_tmj_ids", object.items_collected_tmj_ids },
      { "player_location", object.player_location },
      { "player_excitement", object.player_excitement },
      { "player_line_capacity", object.player_line_capacity },
      { "player_lines_filled", object.player_lines_filled },
      { "progress_and_state_flags", object.progress_and_state_flags },
   };
}

void from_json(const nlohmann::json& j, GameplayProgress& object)
{
   //std::set<std::string> flags_s;
   //std::std<uint32_t> flags;

   j.at("items_collected_tmj_ids").get_to(object.items_collected_tmj_ids);
   j.at("player_location").get_to(object.player_location);
   j.at("player_excitement").get_to(object.player_excitement);
   j.at("player_line_capacity").get_to(object.player_line_capacity);
   j.at("player_lines_filled").get_to(object.player_lines_filled);
   j.at("progress_and_state_flags").get_to(object.progress_and_state_flags);
}


} // namespace TINS2026


