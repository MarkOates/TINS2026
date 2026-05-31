
#include <gtest/gtest.h>

#include <TINS2026/AnimalDatabase.hpp>


TEST(TINS2026_AnimalDatabaseTest, can_be_created_without_blowing_up)
{
   TINS2026::AnimalDatabase animal_database;
}


/*
  - name: identifier
    type: std::string
    init_with: '"[unset-identifier]"'
    exposed: true

  - name: name
    type: std::string
    init_with: '"[unset-name]"'
    exposed: true

  - name: interesting_facts_dialog_pages
    type: std::vector<std::string>
    init_with: '{}'
    exposed: true

  - name: how_many_lines_needed_for_notetaking
    type: int
    init_with: 3
    exposed: true

  - name: hype_rate_per_sec
    type: double
    init_with: 15.0
    exposed: true
*/


