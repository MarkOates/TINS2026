#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <cstdint>
#include <set>


namespace TINS2026
{
   class GameplayProgress
   {
   private:

   protected:


   public:
      std::set<uint32_t> items_collected_tmj_ids;
      AllegroFlare::Vec2D player_location;
      int player_excitement;
      int player_line_capacity;
      int player_lines_filled;
      std::set<uint32_t> progress_and_state_flags;
      GameplayProgress();
      ~GameplayProgress();

   };
}



