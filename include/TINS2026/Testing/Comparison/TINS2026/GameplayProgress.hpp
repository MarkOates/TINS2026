#pragma once


#include <TINS2026/GameplayProgress.hpp>
#include <ostream>


namespace TINS2026
{
   bool operator==(const GameplayProgress& object, const GameplayProgress& other_object);
   void PrintTo(const GameplayProgress& object, ::std::ostream* os);
}


