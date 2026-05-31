

#include <TINS2026/Animal.hpp>




namespace TINS2026
{


Animal::Animal()
   : identifier("[unset-identifier]")
   , name("[unset-name]")
   , interesting_facts_dialog_pages({})
   , how_many_lines_needed_for_notetaking(3)
   , hype_rate_per_sec(15.0)
{
}


Animal::~Animal()
{
}


TINS2026::Animal Animal::build(std::string identifier, std::string name, std::vector<std::string> interesting_facts_dialog_pages, int how_many_lines_needed_for_notetaking, double hype_rate_per_sec)
{
   TINS2026::Animal result;
   result.identifier = identifier;
   result.name= name;
   result.interesting_facts_dialog_pages = interesting_facts_dialog_pages;
   result.how_many_lines_needed_for_notetaking = how_many_lines_needed_for_notetaking;
   result.hype_rate_per_sec = hype_rate_per_sec;
   return result;
}


} // namespace TINS2026


