
#include <gtest/gtest.h>

#include <TINS2026/JSONLoaders/TINS2025/Entity/Type.hpp>


TEST(TINS2026_JSONLoaders_TINS2025_Entity_TypeTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   nlohmann::json j = std::set<TINS2025::Entity::Type>{
      TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE,
      TINS2025::Entity::Type::ENTITY_TYPE_GOAT,
   };

   std::string expected_values =
R"([
  "entity_type_giraffe",
  "entity_type_goat"
])";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(TINS2026_JSONLoaders_TINS2025_Entity_TypeTest,
   from_json__loads_json_data_into_the_object)
{
   std::set<TINS2025::Entity::Type> actual_types;
   std::set<TINS2025::Entity::Type> expected_types = {
      TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE,
      TINS2025::Entity::Type::ENTITY_TYPE_GOAT,
   };

   std::string json =
R"([
  "entity_type_giraffe",
  "entity_type_goat"
])";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(actual_types);

   EXPECT_EQ(expected_types, actual_types);
}



