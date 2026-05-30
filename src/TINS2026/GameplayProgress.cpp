

#include <TINS2026/GameplayProgress.hpp>




namespace TINS2026
{


GameplayProgress::GameplayProgress()
   : items_collected_tmj_ids({})
   , player_location(AllegroFlare::Vec2D{0, 0})
   , player_excitement(0)
   , player_line_capacity(0)
   , player_lines_filled(0)
   , progress_and_state_flags({})
{
}


GameplayProgress::~GameplayProgress()
{
}




} // namespace TINS2026


