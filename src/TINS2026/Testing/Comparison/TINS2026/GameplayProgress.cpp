

#include <TINS2026/Testing/Comparison/TINS2026/GameplayProgress.hpp>


namespace TINS2026
{


bool operator==(const GameplayProgress& object, const GameplayProgress& other_object)
{
   if (object.items_collected_tmj_ids != other_object.items_collected_tmj_ids) return false;
   if (object.player_location != other_object.player_location) return false;
   if (object.player_excitement != other_object.player_excitement) return false;
   if (object.player_line_capacity != other_object.player_line_capacity) return false;
   if (object.player_lines_filled != other_object.player_lines_filled) return false;
   if (object.progress_and_state_flags != other_object.progress_and_state_flags) return false;
   return true;
}


void PrintTo(const GameplayProgress& object, ::std::ostream* os)
{
   *os << "GameplayProgress([serialization-of-values-not-implemented]"
       //<< "saturation_multiplier: \"" << object.saturation_multiplier << "\", "
       << ")";
}


}


/*
properties:


  - name: items_collected_tmj_ids
    type: std::set<uint32_t>
    init_with: '{}'
    exposed: true

  - name: player_location
    type: AllegroFlare::Vec2D
    init_with: AllegroFlare::Vec2D{0, 0}
    exposed: true

  - name: player_excitement
    type: int
    init_with: 0
    exposed: true

  - name: player_blank_lines
    type: int
    init_with: 0
    exposed: true

  - name: progress_and_state_flags
    type: std::set<TINS2025::Gameplay::Screen::ProgressAndStateFlags>
    init_with: '{}'
    exposed: true
*/


