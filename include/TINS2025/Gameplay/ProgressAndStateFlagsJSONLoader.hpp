#pragma once


#include <lib/nlohmann/json.hpp>
#include <TINS2025/Gameplay/Screen.hpp> // flags are here


namespace TINS2025::Gameplay
{
  // NOTE: In the future, you can automatically prepare json serialization of enums by using 
  // the NLOHMANN_JSON_SERIALIZE_ENUM! Cool!

  //NLOHMANN_JSON_SERIALIZE_ENUM( Status, {
        //{ ProgressAndStateFlags::UNDEF, "undef"},
        //{ ProgressAndStateFlags::, "pending"},
        //{Status::InProgress, "in_progress"},
        //{Status::Completed, "completed"}
    //})

  void to_json(nlohmann::json& j, const TINS2025::Gameplay::Screen::ProgressAndStateFlags& object);
  void from_json(const nlohmann::json& j, TINS2025::Gameplay::Screen::ProgressAndStateFlags& object);
}


