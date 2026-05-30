
#include <gtest/gtest.h>

#include <TINS2026/AnimalDatabase.hpp>


TEST(TINS2026_AnimalDatabaseTest, can_be_created_without_blowing_up)
{
   TINS2026::AnimalDatabase animal_database;
}


TEST(TINS2026_AnimalDatabaseTest, run__returns_the_expected_response)
{
   TINS2026::AnimalDatabase animal_database;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, animal_database.run());
}


