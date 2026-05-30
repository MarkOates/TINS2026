
#include <gtest/gtest.h>

#include <TINS2025/Gameplay/ProgressAndStateFlagsJSONLoader.hpp>


TEST(TINS2025_Gameplay_ProgressAndStateFlagsJSONLoaderTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   std::set<TINS2025::Gameplay::Screen::ProgressAndStateFlags> flags = {
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_UNLOCKED_GIRAFFE,
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_UNLOCKED_GOAT
   };

   nlohmann::json j = flags;
    

   std::string expected_values =
R"([
  "flag_unlocked_giraffe",
  "flag_unlocked_goat"
])";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(TINS2025_Gameplay_ProgressAndStateFlagsJSONLoaderTest,
   from_json__loads_json_data_into_the_object)
{
   std::set<TINS2025::Gameplay::Screen::ProgressAndStateFlags> expected_flags = {
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_UNLOCKED_GIRAFFE,
     TINS2025::Gameplay::Screen::ProgressAndStateFlags::FLAG_UNLOCKED_GOAT
   };
   std::set<TINS2025::Gameplay::Screen::ProgressAndStateFlags> actual_flags;

   std::string json =
R"([
  "flag_unlocked_giraffe",
  "flag_unlocked_goat"
])";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(actual_flags);

   EXPECT_EQ(expected_flags, actual_flags);
}



