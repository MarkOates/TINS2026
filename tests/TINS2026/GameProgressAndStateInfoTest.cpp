
#include <gtest/gtest.h>

#include <TINS2026/GameProgressAndStateInfo.hpp>


TEST(TINS2026_GameProgressAndStateInfoTest, can_be_created_without_blowing_up)
{
   TINS2026::GameProgressAndStateInfo game_progress_and_state_info;
}


TEST(TINS2026_GameProgressAndStateInfoTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "TINS2026/GameProgressAndStateInfo",
     TINS2026::GameProgressAndStateInfo::TYPE
   );
}


TEST(TINS2026_GameProgressAndStateInfoTest, type__has_the_expected_value_matching_TYPE)
{
   TINS2026::GameProgressAndStateInfo game_progress_and_state_info;
   EXPECT_EQ(TINS2026::GameProgressAndStateInfo::TYPE, game_progress_and_state_info.get_type());
}


