#pragma once


#include <lib/nlohmann/json.hpp>
#include <TINS2026/GameProgressAndStateInfo.hpp>


namespace TINS2026
{
  void to_json(nlohmann::json& j, const GameProgressAndStateInfo& object);
  void from_json(const nlohmann::json& j, GameProgressAndStateInfo& object);
}


