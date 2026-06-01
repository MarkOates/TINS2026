

#include <TINS2026/GameplayProgress.hpp>




namespace TINS2026
{


GameplayProgress::GameplayProgress()
   : items_collected_tmj_ids({})
   , player_location(AllegroFlare::Vec2D{0, 0})
   , player_excitement(0.0)
   , player_line_capacity(0)
   , player_lines_filled(0)
   , documented_entity_types({})
   , triggered_dialog_names({})
   , progress_and_state_flags({})
   , player_freakouts(0)
{
}


GameplayProgress::~GameplayProgress()
{
}


int GameplayProgress::lines_available()
{
   return player_line_capacity - player_lines_filled;
}


} // namespace TINS2026


