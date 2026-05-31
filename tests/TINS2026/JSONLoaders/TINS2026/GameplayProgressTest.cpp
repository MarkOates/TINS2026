
#include <gtest/gtest.h>

#include <TINS2026/JSONLoaders/TINS2026/GameplayProgress.hpp>
#include <TINS2026/Testing/Comparison/TINS2026/GameplayProgress.hpp>
#include <TINS2025/Gameplay/Screen.hpp>
//TINS2025::Gameplay::Screen
//#include <TINS2026/Testing/Comparison/TINS2026/GameplayProgress.hpp>
//#include <AllegroFlare/Testing/Comparison/TINS2026/JSONLoaders/TINS2026/GameplayProgress.hpp>
//#include <[COMPONENT_NAME]].hpp>


TEST(TINS2026_JSONLoaders_TINS2026_GameplayProgressTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   TINS2026::GameplayProgress gameplay_progress;
   gameplay_progress.items_collected_tmj_ids = { 4, 32, 8 };
   gameplay_progress.player_location = AllegroFlare::Vec2D(32, -16);
   gameplay_progress.player_excitement = 42;
   gameplay_progress.player_line_capacity = 64;
   gameplay_progress.player_lines_filled = 28;
   gameplay_progress.player_freakouts = 4;
   gameplay_progress.progress_and_state_flags = {
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_1,
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_2
   };
   gameplay_progress.documented_entity_types = {
     TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE,
     TINS2025::Entity::Type::ENTITY_TYPE_GOAT,
   };


   nlohmann::json j = gameplay_progress;

    //"flag_unlocked_giraffe",
    //"flag_unlocked_goat"

   std::string expected_values =
R"({
  "documented_entity_types": [
    "entity_type_giraffe",
    "entity_type_goat"
  ],
  "items_collected_tmj_ids": [
    4,
    8,
    32
  ],
  "player_excitement": 42.0,
  "player_freakouts": 4,
  "player_line_capacity": 64,
  "player_lines_filled": 28,
  "player_location": {
    "x": 32.0,
    "y": -16.0
  },
  "progress_and_state_flags": [
    "flag_foo_test_flag_1",
    "flag_foo_test_flag_2"
  ]
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(TINS2026_JSONLoaders_TINS2026_GameplayProgressTest,
   from_json__loads_json_data_into_the_object)
{
   TINS2026::GameplayProgress gameplay_progress;
   gameplay_progress.items_collected_tmj_ids = { 4, 32, 8 };
   gameplay_progress.player_location = AllegroFlare::Vec2D(32, -16);
   gameplay_progress.player_excitement = 42.125;
   gameplay_progress.player_freakouts = 4;
   gameplay_progress.player_line_capacity = 64;
   gameplay_progress.player_lines_filled = 28;
   gameplay_progress.progress_and_state_flags = {
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_1,
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_2
   };
   gameplay_progress.documented_entity_types = {
     TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE,
     TINS2025::Entity::Type::ENTITY_TYPE_GOAT,
   };

   TINS2026::GameplayProgress actual_gameplay_progress;

   std::string json =
R"({
  "documented_entity_types": [
    "entity_type_giraffe",
    "entity_type_goat"
  ],
  "items_collected_tmj_ids": [
    4,
    8,
    32
  ],
  "player_line_capacity": 64,
  "player_lines_filled": 28,
  "player_excitement": 42.125,
  "player_freakouts": 4,
  "player_location": {
    "x": 32.0,
    "y": -16.0
  },
  "progress_and_state_flags": [
    "flag_foo_test_flag_1",
    "flag_foo_test_flag_2"
  ]
})";


   //TINS2026::GameplayProgress gameplay_progress;

   //std::string json =
//R"({
  //"position": 1.5
//})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(actual_gameplay_progress);

   //TINS2026::GameplayProgress expected;

   //// TODO: add comparison
   EXPECT_EQ(gameplay_progress, actual_gameplay_progress);
}



