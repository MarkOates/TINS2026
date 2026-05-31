

#include <TINS2026/JSONLoaders/TINS2025/Entity/Type.hpp>


namespace TINS2025
{


void to_json(nlohmann::json& j, const Entity::Type& object)
{
   j = Entity::to_string(object);
}

void from_json(const nlohmann::json& j, Entity::Type& object)
{
   object = Entity::from_string(j.get<std::string>());
}



} // namespace TINS2025::Entity



