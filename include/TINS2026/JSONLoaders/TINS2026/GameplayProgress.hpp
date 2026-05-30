#pragma once


#include <lib/nlohmann/json.hpp>
#include <TINS2026/GameplayProgress.hpp>


namespace TINS2026
{
  void to_json(nlohmann::json& j, const GameplayProgress& object);
  void from_json(const nlohmann::json& j, GameplayProgress& object);
}


