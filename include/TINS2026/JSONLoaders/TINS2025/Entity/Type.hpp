#pragma once


#include <lib/nlohmann/json.hpp>
#include <TINS2025/Entity.hpp>


namespace TINS2025
{
  void to_json(nlohmann::json& j, const Entity::Type& object);
  void from_json(const nlohmann::json& j, Entity::Type& object);
}


