
#include <gtest/gtest.h>

#include <TINS2026/JSONLoaders/TINS2026/GameProgressAndStateInfo.hpp>
#include <TINS2026/Testing/Comparison/TINS2026/GameProgressAndStateInfo.hpp>


TEST(TINS2026_JSONLoaders_TINS2026_GameProgressAndStateInfoTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   TINS2026::GameProgressAndStateInfo game_progress_and_state_info;
   game_progress_and_state_info.set_player_inventory_items({ "fruit", "veggie", "fork" });
   game_progress_and_state_info.set_player_num_lives(7);

   nlohmann::json j = game_progress_and_state_info;

   std::string expected_values =
R"({
  "player_inventory_items": [
    "fruit",
    "veggie",
    "fork"
  ],
  "player_num_lives": 7
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(TINS2026_JSONLoaders_TINS2026_GameProgressAndStateInfoTest,
   from_json__loads_json_data_into_the_object)
{
   TINS2026::GameProgressAndStateInfo game_progress_and_state_info;

   std::string json =
R"({
  "player_inventory_items": [
    "fruit",
    "veggie",
    "fork"
  ],
  "player_num_lives": 7
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(game_progress_and_state_info);

   TINS2026::GameProgressAndStateInfo expected;
   expected.set_player_inventory_items({ "fruit", "veggie", "fork" });
   expected.set_player_num_lives(7);

   EXPECT_EQ(expected, game_progress_and_state_info);
}


