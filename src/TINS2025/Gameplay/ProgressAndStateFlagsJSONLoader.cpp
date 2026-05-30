

#include <TINS2025/Gameplay/ProgressAndStateFlagsJSONLoader.hpp>


namespace TINS2025::Gameplay
{


void to_json(nlohmann::json& j, const TINS2025::Gameplay::Screen::ProgressAndStateFlags& object)
{
   j = Screen::to_string(object);
}

void from_json(const nlohmann::json& j, TINS2025::Gameplay::Screen::ProgressAndStateFlags& object)
{
   object = Screen::from_string(j.get<std::string>());
}


}



