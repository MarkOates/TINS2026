

#include <TINS2025/Gameplay/Screen.hpp>

#include <AllegroFlare/DialogTree/NodeOptions/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/NodeOptions/GoToNode.hpp>
#include <AllegroFlare/DialogTree/Nodes/ExitDialog.hpp>
#include <AllegroFlare/DialogTree/Nodes/Interparsable.hpp>
#include <AllegroFlare/DialogTree/Nodes/MultipageWithOptions.hpp>
#include <AllegroFlare/Elements/HealthBars/Classic.hpp>
#include <AllegroFlare/Physics/TileMapCollisionStepper.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/PlayerInputControllers/Generic.hpp>
#include <AllegroFlare/Tiled/TMJDataLoader.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <TINS2025/Gameplay/Level.hpp>
#include <TINS2026/JSONLoaders/TINS2026/GameplayProgress.hpp>
#include <algorithm>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <filesystem>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace TINS2025
{
namespace Gameplay
{


TINS2026::AnimalDatabase Screen::animal_database = {};


Screen::Screen()
   : AllegroFlare::Screens::Gameplay()
   , data_folder_path(DEFAULT_DATA_FOLDER_PATH)
   , asset_studio_database(nullptr)
   , event_emitter(nullptr)
   , bitmap_bin(nullptr)
   , font_bin(nullptr)
   , model_bin(nullptr)
   , dialog_system(nullptr)
   , gameplay_progress({})
   , progress_file_filename("save.json")
   , items_collected_tmj_ids(gameplay_progress.items_collected_tmj_ids)
   , view_motion_studio({})
   , hide_view_motion_studio_hud(false)
   , current_level_identifier("[unset-current_level]")
   , current_level(nullptr)
   , animal_aura_collision_observer({})
   , player_is_accumulating_hype(true)
   , total_cumulative_hype_aura(0.0)
   , collision_observer({})
   , collision_tile_map({})
   , environment_overlay_placement()
   , entities({})
   , environment_model(nullptr)
   , player_entity(nullptr)
   , input_mode(0)
   , QUEST__collected_apple(false)
   , QUEST__collected_carrot(false)
   , QUEST__collected_red_carrot(false)
   , QUEST__dialog_1_triggered(false)
   , QUEST__dialog_2_triggered(false)
   , QUEST__dialog_3_triggered(false)
   , QUEST__friend_1_requirements_asked(false)
   , QUEST__friend_2_requirements_asked(false)
   , QUEST__friend_3_requirements_asked(false)
   , current_chapter_number(1)
   , dip_to_black_overlay_opacity(0.0f)
   , dip_to_black_rate(0.02f)
   , dip_to_black_color(ALLEGRO_COLOR{0, 0, 0, 1})
   , dipping_to_black(false)
   , in_test_or_development_mode(true)
   , camera_is_tracking_player(true)
   , flag__showing_plant_now(false)
   , lottie__num_notebook_pages__DEP(0)
   , lottie__num_lines_written__DEP(0)
   , lottie__excitement__DEP(0)
   , initialized(false)
{
}


Screen::~Screen()
{
}


void Screen::set_data_folder_path(std::string data_folder_path)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_data_folder_path]: error: guard \"get_initialized()\" not met.");
   this->data_folder_path = data_folder_path;
}


void Screen::set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_asset_studio_database]: error: guard \"get_initialized()\" not met.");
   this->asset_studio_database = asset_studio_database;
}


void Screen::set_event_emitter(AllegroFlare::EventEmitter* event_emitter)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_event_emitter]: error: guard \"get_initialized()\" not met.");
   this->event_emitter = event_emitter;
}


void Screen::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_bitmap_bin]: error: guard \"get_initialized()\" not met.");
   this->bitmap_bin = bitmap_bin;
}


void Screen::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_font_bin]: error: guard \"get_initialized()\" not met.");
   this->font_bin = font_bin;
}


void Screen::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_model_bin]: error: guard \"get_initialized()\" not met.");
   this->model_bin = model_bin;
}


void Screen::set_dialog_system(AllegroFlare::DialogSystem::DialogSystem* dialog_system)
{
   if (get_initialized()) throw std::runtime_error("[Screen::set_dialog_system]: error: guard \"get_initialized()\" not met.");
   this->dialog_system = dialog_system;
}


void Screen::set_in_test_or_development_mode(bool in_test_or_development_mode)
{
   this->in_test_or_development_mode = in_test_or_development_mode;
}


std::string Screen::get_data_folder_path() const
{
   return data_folder_path;
}


AllegroFlare::EventEmitter* Screen::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* Screen::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Screen::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::ModelBin* Screen::get_model_bin() const
{
   return model_bin;
}


AllegroFlare::DialogSystem::DialogSystem* Screen::get_dialog_system() const
{
   return dialog_system;
}


TINS2026::GameplayProgress Screen::get_gameplay_progress() const
{
   return gameplay_progress;
}


std::string Screen::get_progress_file_filename() const
{
   return progress_file_filename;
}


std::set<uint32_t>& Screen::get_items_collected_tmj_ids() const
{
   return items_collected_tmj_ids;
}


bool Screen::get_QUEST__collected_apple() const
{
   return QUEST__collected_apple;
}


bool Screen::get_QUEST__collected_carrot() const
{
   return QUEST__collected_carrot;
}


bool Screen::get_QUEST__collected_red_carrot() const
{
   return QUEST__collected_red_carrot;
}


bool Screen::get_QUEST__dialog_1_triggered() const
{
   return QUEST__dialog_1_triggered;
}


bool Screen::get_QUEST__dialog_2_triggered() const
{
   return QUEST__dialog_2_triggered;
}


bool Screen::get_QUEST__dialog_3_triggered() const
{
   return QUEST__dialog_3_triggered;
}


bool Screen::get_QUEST__friend_1_requirements_asked() const
{
   return QUEST__friend_1_requirements_asked;
}


bool Screen::get_QUEST__friend_2_requirements_asked() const
{
   return QUEST__friend_2_requirements_asked;
}


bool Screen::get_QUEST__friend_3_requirements_asked() const
{
   return QUEST__friend_3_requirements_asked;
}


int Screen::get_current_chapter_number() const
{
   return current_chapter_number;
}


float Screen::get_dip_to_black_overlay_opacity() const
{
   return dip_to_black_overlay_opacity;
}


float Screen::get_dip_to_black_rate() const
{
   return dip_to_black_rate;
}


ALLEGRO_COLOR Screen::get_dip_to_black_color() const
{
   return dip_to_black_color;
}


bool Screen::get_dipping_to_black() const
{
   return dipping_to_black;
}


bool Screen::get_in_test_or_development_mode() const
{
   return in_test_or_development_mode;
}


bool Screen::get_camera_is_tracking_player() const
{
   return camera_is_tracking_player;
}


bool Screen::get_flag__showing_plant_now() const
{
   return flag__showing_plant_now;
}


bool Screen::get_initialized() const
{
   return initialized;
}


AllegroFlare::AssetStudio::Database* &Screen::get_asset_studio_database_ref()
{
   return asset_studio_database;
}


std::string Screen::to_string(InputMode value, bool throw_on_error)
{
   if (value == InputMode::INPUT_MODE_NONE) return "input_mode_none";
   if (value == InputMode::INPUT_MODE_PLAYING) return "input_mode_playing";
   if (value == InputMode::INPUT_MODE_EDITING) return "input_mode_editing";
   // TODO: Implement "throw_on_error" argument
   return "";
}


std::string Screen::to_string(ProgressAndStateFlags value, bool throw_on_error)
{
   if (value == ProgressAndStateFlags::NONE) return "none";
   if (value == ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_1) return "flag_foo_test_flag_1";
   if (value == ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_2) return "flag_foo_test_flag_2";
   // TODO: Implement "throw_on_error" argument
   return "";
}


Screen::ProgressAndStateFlags Screen::from_string(std::string value, bool throw_on_error)
{
   if (value == "none") return ProgressAndStateFlags::NONE;
   if (value == "flag_foo_test_flag_1") return ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_1;
   if (value == "flag_foo_test_flag_2") return ProgressAndStateFlags::FLAG_FOO_TEST_FLAG_2;
   throw std::runtime_error("Blast/Cpp/EnumClass: ERROR: Could not find enum for \" + value + \"");
}


void Screen::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"model_bin\" not met");
   }
   if (!(dialog_system))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"dialog_system\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"dialog_system\" not met");
   }
   if (!((data_folder_path != DEFAULT_DATA_FOLDER_PATH)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::initialize]: error: guard \"(data_folder_path != DEFAULT_DATA_FOLDER_PATH)\" not met");
   }
   set_update_strategy(AllegroFlare::Screens::Base::UpdateStrategy::SEPARATE_UPDATE_AND_RENDER_FUNCS);

   // Setup the dialog
   dialog_system->set_dialog_node_bank(build_dialog_node_bank());
   dialog_system->set_standard_dialog_box_font_name("Quicksand-SemiBold.ttf");
   dialog_system->set_standard_dialog_box_font_size(-52);
   //dialog_system->set_standard_dialog_box_font_line_height(-52); // TODO: Add this feature
   dialog_system->set_standard_dialog_box_width(1920 * 0.5);
   dialog_system->set_standard_dialog_box_height(248);
   dialog_system->set_standard_dialog_box_y(1080/5*4);
   dialog_system->set_standard_dialog_box_frame_color(al_color_html("c6987e"));
   dialog_system->set_standard_dialog_box_background_color(al_color_html("fdf5e6"));
   dialog_system->set_standard_dialog_box_text_color(al_color_html("9f6b32"));
   dialog_system->set_standard_dialog_box_label_color(al_color_html("fdf5e6"));

   dialog_system->set_on_before_activating_dialog_node_by_name_callback_func([this](
      AllegroFlare::DialogSystem::DialogSystem* dialog_system,
      std::string activating_dialog_node_name,
      AllegroFlare::DialogTree::Nodes::Base* dialog_node,
      void* user_data
   ){
      if (!dialog_node) return; // consider throwing error

      std::string speaker = LOTTIE;

      if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::MultipageWithOptions::TYPE))
      {
         AllegroFlare::DialogTree::Nodes::MultipageWithOptions *as =
            static_cast<AllegroFlare::DialogTree::Nodes::MultipageWithOptions*>(dialog_node);
         speaker = as->get_speaker();
      }
      else if (dialog_node->is_type(AllegroFlare::DialogTree::Nodes::Interparsable::TYPE))
      {
         auto *as = static_cast<AllegroFlare::DialogTree::Nodes::Interparsable*>(dialog_node);
         speaker = as->get_speaker();
      }

      if (speaker == LOTTIE) customize_dialog_for_DOTTIE();
      else if (speaker == NARRATOR) customize_dialog_for_NARRATOR();
      else if (speaker == FRIEND_1) customize_dialog_for_FRIEND_1();
      else if (speaker == FRIEND_2) customize_dialog_for_FRIEND_2();
      else if (speaker == FRIEND_3) customize_dialog_for_FRIEND_3();
      //}
   });

   //set_standard_dialog_box_label_color(al_color_html("fdf5e6"));


   load_up_world();
   initialized = true;
   return;
}

std::string Screen::build_full_progress_file_filename()
{
   return data_folder_path + PROGRESS_FILE_FOLDER + progress_file_filename;
}

void Screen::load_progress_file()
{
   std::string full_progress_file_filename = build_full_progress_file_filename();

   if (!std::filesystem::exists(full_progress_file_filename))
   {
      std::cout << "NOTICE: A save file does not exist, and thus cannot be loaded." << std::endl;
      return;
   }

   try
   {
      //if (!std::filesystem::exists(full_progress_file_filename))
      //{
         //throw std::runtime_error("The json file does not exist");
      //}

      std::string content = AllegroFlare::php::file_get_contents(full_progress_file_filename);

      //nlohmann::json j;
      //j.parse(content);
      nlohmann::json j = nlohmann::json::parse(content);

      gameplay_progress = j;
   }
   catch (std::exception& e)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         std::string("Could not load the progress json file... for reasons: ") + e.what()
      );
   }

   // TODO: What to do after the content is loaded?

   return;
}

void Screen::save_progress_file()
{
   // Refresh some of our critical pieces of data
   //player_entity->aabb2d.set_x(
   gameplay_progress.player_location.x = player_entity->aabb2d.get_x();
   gameplay_progress.player_location.y = player_entity->aabb2d.get_y();

   //std::set<uint32_t> items_collected_tmj_ids;

   //for (auto &entity : entities)
   //{
      //if ((entity.flags & TINS2025::Entity::FLAG_COLLECTED) == 0)
      //{
         //items_collected_tmj_ids
      //}
   //}

   //gameplay_progress.player_location.y = player_entity->aabb2d.get_y();


   std::string full_progress_file_filename = build_full_progress_file_filename();

   try
   {
      //if (!std::filesystem::exists(full_progress_file_filename))
      //{
         //throw std::runtime_error("The json file does not exist");
      //}

      //std::string content = AllegroFlare::php::file_get_contents(full_progress_file_filename);

      nlohmann::json j;
      j = gameplay_progress;

      AllegroFlare::php::file_put_contents(full_progress_file_filename, j.dump(2));
   }
   catch (std::exception& e)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         std::string("Could not save the progress json file... for reasons: ") + e.what()
      );
   }


   return;
}

void Screen::customize_dialog_for_DOTTIE()
{
   dialog_system->set_standard_dialog_box_frame_color(al_color_html("c6987e"));
   dialog_system->set_standard_dialog_box_background_color(al_color_html("fdf5e6"));
   dialog_system->set_standard_dialog_box_text_color(al_color_html("9f6b32"));
   dialog_system->set_standard_dialog_box_label_color(al_color_html("fdf5e6"));
   dialog_system->set_standard_dialog_box_y(1080/5*4);

   //dialog_system->set_standard_dialog_box_frame_color(al_color_html("c4b067"));
   //dialog_system->set_standard_dialog_box_background_color(al_color_html("c4b067"));
   //dialog_system->set_standard_dialog_box_text_color(al_color_html("60541f"));
   //dialog_system->set_standard_dialog_box_label_color(al_color_html("60541f"));
   return;
}

void Screen::customize_dialog_for_NARRATOR()
{
   dialog_system->set_standard_dialog_box_frame_color(al_color_html("6dbacc"));
   dialog_system->set_standard_dialog_box_background_color(al_color_html("6dbacc"));
   dialog_system->set_standard_dialog_box_text_color(al_color_html("4270a2"));
   dialog_system->set_standard_dialog_box_label_color(al_color_html("4270a2"));
   dialog_system->set_standard_dialog_box_y(1080/2);
   //dialog_system->set_standard_dialog_box_frame_color(al_color_html("c6987e"));
   //dialog_system->set_standard_dialog_box_background_color(al_color_html("fdf5e6"));
   //dialog_system->set_standard_dialog_box_text_color(al_color_html("9f6b32"));
   //dialog_system->set_standard_dialog_box_label_color(al_color_html("fdf5e6"));
   //dialog_system->set_standard_dialog_box_frame_color(al_color_html("c4b067"));
   //dialog_system->set_standard_dialog_box_background_color(al_color_html("c4b067"));
   //dialog_system->set_standard_dialog_box_text_color(al_color_html("60541f"));
   //dialog_system->set_standard_dialog_box_label_color(al_color_html("60541f"));
   return;
}

void Screen::customize_dialog_for_FRIEND_1()
{
   //dialog_system->set_standard_dialog_box_frame_color(al_color_html("de923c"));
   //dialog_system->set_standard_dialog_box_background_color(al_color_html("de923c"));
   //dialog_system->set_standard_dialog_box_text_color(al_color_html("60541f"));
   //dialog_system->set_standard_dialog_box_label_color(al_color_html("60541f"));
   std::string bg = "c2905b";
   std::string fg = "e6e3dd";
   dialog_system->set_standard_dialog_box_frame_color(al_color_html(bg.c_str()));
   dialog_system->set_standard_dialog_box_background_color(al_color_html(bg.c_str()));
   dialog_system->set_standard_dialog_box_text_color(al_color_html(fg.c_str()));
   dialog_system->set_standard_dialog_box_label_color(al_color_html(fg.c_str()));
   if (current_chapter_number == 1) view_motion_studio.set_current_camera_to_camera_at_index(2);
   return;
}

void Screen::customize_dialog_for_FRIEND_2()
{
   dialog_system->set_standard_dialog_box_frame_color(al_color_html("d2698a"));
   dialog_system->set_standard_dialog_box_background_color(al_color_html("d2698a"));
   dialog_system->set_standard_dialog_box_text_color(al_color_html("e4d4bb"));
   dialog_system->set_standard_dialog_box_label_color(al_color_html("e4d4bb"));
   if (current_chapter_number == 1) view_motion_studio.set_current_camera_to_camera_at_index(4);

   //dialog_system->set_standard_dialog_box_frame_color(al_color_html("6dbacc"));
   //dialog_system->set_standard_dialog_box_background_color(al_color_html("6dbacc"));
   //dialog_system->set_standard_dialog_box_text_color(al_color_html("000000"));
   //dialog_system->set_standard_dialog_box_label_color(al_color_html("000000"));
   return;
}

void Screen::customize_dialog_for_FRIEND_3()
{
   dialog_system->set_standard_dialog_box_frame_color(al_color_html("6dbacc"));
   dialog_system->set_standard_dialog_box_background_color(al_color_html("6dbacc"));
   dialog_system->set_standard_dialog_box_text_color(al_color_html("4270a2"));
   dialog_system->set_standard_dialog_box_label_color(al_color_html("4270a2"));
   if (current_chapter_number == 1) view_motion_studio.set_current_camera_to_camera_at_index(5);

   return;
}

void Screen::gameplay_suspend_func()
{

   // Function that is called immediately after the gameplay is suspended.
   //AllegroFlare::Logger::warn_from_once(
      //"AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      //"Not implemented in the base class. This method should be implemented in the derived class. Take into account "
         //"the AllegroFlare/Screens/Gameplay class has a suspend_gameplay func"
   //);
   return;
}

void Screen::gameplay_resume_func()
{
   if (current_chapter_number == 1) view_motion_studio.set_current_camera_to_camera_at_index(1); // ???
   // Function that is called immediately after the gameplay is resumed.
   //AllegroFlare::Logger::warn_from_once(
      //"AllegroFlare::Screens::Gameplay::gameplay_suspend_func",
      //"Not implemented in the base class. This method should be implemented in the derived class. Take into account "
         //"the AllegroFlare/Screens/Gameplay class has a resume_gameplay func"
   //);
   return;
}

void Screen::load_up_world()
{
   collision_observer.clear();
   animal_aura_collision_observer.clear();


   // Load up the world model
   collision_tile_map.initialize();

   //environment_model = model_bin->auto_get("simple_scene-03.obj");
   //environment_model->texture = bitmap_bin->auto_get("simple_scene-03.png");

   environment_overlay_placement.rotation.x = 0.25;
   environment_overlay_placement.position.y = 0.25;



   // Setup the entities
   entities.reserve(256);



   { // create teh player character
      Entity e;
      e.aabb2d.set_x(9.0);
      e.aabb2d.set_y(5.0);
      e.aabb2d.set_w(0.75);
      e.aabb2d.set_h(0.25);
      //e.sprite = bitmap_bin->auto_get("character_a-01.png");
      e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_TILEMAP;
      e.type = TINS2025::Entity::ENTITY_TYPE_PLAYER;
      //e.model = model_bin->auto_get("character_model-01.obj");
      //e.sprite = bitmap_bin->auto_get("player_character.png");
      e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
      e.model = model_bin->auto_get("hello_zoo-entities-0x-lottie.obj");
      e.model->texture = e.sprite;
      entities.push_back(e);
   }

   player_entity = &entities.back();



   refresh_environment_and_world(true);


   // Setup view_motion_studio
   view_motion_studio.set_font_bin(font_bin);
   view_motion_studio.set_data_folder_path(data_folder_path);
   view_motion_studio.initialize();
   //view_motion_studio.load_json(cameras_json_string); // Load some test data
   // TODO: Fix these paths
   std::string filename_load = data_folder_path + "animations/camera_move_1-0n.txt";
   //std::string filename_save = "tests/fixtures/animations/camera_move_1-0n_output.txt";
   //std::cout << "loading json" << std::endl;
   std::string file_content = AllegroFlare::php::file_get_contents(filename_load);
   view_motion_studio.load_json(file_content);


   view_motion_studio.set_current_camera_to_camera_at_index(1); // Set camera to 1 by default


   input_mode = INPUT_MODE_PLAYING;


   // Hide the view motion studio
   hide_view_motion_studio_hud = true;



   // Setup the player_input_controller
   auto generic_player_input_controller = new AllegroFlare::PlayerInputControllers::Generic();
   generic_player_input_controller->set_on_time_step_update(
      [this](AllegroFlare::Vec2D value, double time_now, double time_step) {
         /*
         float threshold = 0.1f;
         float max_velocity = 0.2f;
         float acceleration = 1.0f; // units per second squared
         float deceleration = 2.0f; // units per second squared

         // Get current velocity
         AllegroFlare::Vec2D current_velocity = {
            player_entity->aabb2d.get_velocity_x(),
            player_entity->aabb2d.get_velocity_y()
         };

         AllegroFlare::Vec2D target_direction = value;
         if (target_direction.get_magnitude() > 1.0f)
         {
            target_direction = target_direction.normalized();
         }

         AllegroFlare::Vec2D desired_velocity = target_direction * max_velocity;

         AllegroFlare::Vec2D velocity_diff = desired_velocity - current_velocity;

         // Calculate acceleration or deceleration based on input presence
         float applied_accel = (std::abs(value.x) > threshold || std::abs(value.y) > threshold)
            ? acceleration
            : deceleration;

         AllegroFlare::Vec2D velocity_change = velocity_diff.normalized() * applied_accel * time_step;

         // Clamp the change if it's going to overshoot
         if (velocity_change.get_magnitude() > velocity_diff.get_magnitude())
         {
            velocity_change = velocity_diff;
         }

         AllegroFlare::Vec2D new_velocity = current_velocity + velocity_change;

         player_entity->aabb2d.set_velocity_x(new_velocity.x);
         player_entity->aabb2d.set_velocity_y(new_velocity.y);

         if (std::abs(value.x) > threshold || std::abs(value.y) > threshold)
         {
            player_entity->animation_mode = TINS2025::Entity::ANIMATION_MODE_WALKING_WOBBLY;
         }
         else
         {
            player_entity->animation_mode = TINS2025::Entity::ANIMATION_MODE_STANDING;
         }
         */
         //throw std::runtime_error("asdfasf");

         //player_entity->
         //auto player_box = frustum_viewer.find_first_box("player_box");
         //AllegroFlare::Camera3D &camera = frustum_viewer.get_camera_ref();

         // Simple:
         //player_box->position.x += value.x * 0.02;
         //player_box->position.z += value.y * 0.02;
         //player_entity->aabb2d.set_velocity_x(value.x * 0.02);
         //player_entity->aabb2d.set_velocity_y(value.y * 0.02);
         //player_entity->aabb2d.set_velocity_x(value.x * 0.01625 * 3);
         //player_entity->aabb2d.set_velocity_y(value.y * 0.01625 * 3);



         bool relative_to_camera = true;
         if (relative_to_camera)
         {
            // Relative to camera:
            AllegroFlare::Camera3D &camera = view_motion_studio.get_camera_studio_ref().get_live_camera_ref();
            //float angle = camera.spin;
            //float x_prime = value.x * std::cos(angle) - value.y * std::sin(angle);
            //float y_prime = value.x * std::sin(angle) + value.y * std::cos(angle);

            // Convert unit spin (0.0 to 1.0) to radians (0.0 to 2*PI)
            // Using a constant for TAU (2 * PI)
            constexpr float TAU = 6.28318530718f; 
            float angle_in_radians = camera.spin * TAU;

            // Apply rotation matrix
            float x_prime = value.x * std::cos(angle_in_radians) - value.y * std::sin(angle_in_radians);
            float y_prime = value.x * std::sin(angle_in_radians) + value.y * std::cos(angle_in_radians);

            player_entity->aabb2d.set_velocity_x(x_prime * 0.05); // Values?
            player_entity->aabb2d.set_velocity_y(y_prime * 0.05);
         }
         else
         {
            player_entity->aabb2d.set_velocity_x(value.x * 0.01625 * 3.5);
            player_entity->aabb2d.set_velocity_y(value.y * 0.01625 * 3.5);
         }
        

         float threshold = 0.1f; // example threshold
         if (std::abs(value.x) > threshold || std::abs(value.y) > threshold)
         {
         //if (value.x > 0.01
            player_entity->animation_mode = TINS2025::Entity::ANIMATION_MODE_WALKING_WOBBLY;
         }
         else
         {
            player_entity->animation_mode = TINS2025::Entity::ANIMATION_MODE_STANDING;
         }

         // Relative to camera:
         //float angle = camera.spin;
         //float x_prime = value.x * std::cos(angle) - value.y * std::sin(angle);
         //float y_prime = value.x * std::sin(angle) + value.y * std::cos(angle);

         //player_entity->velocity.x = x_prime * 0.05;
         //player_box->velocity.z = y_prime * 0.05;
      }
   );
   set_player_input_controller(generic_player_input_controller);


   event_emitter->emit_play_music_track_event("theme");


   return;
}

bool Screen::load_level_by_identifier(std::string level_identifier)
{
   return false;
}

void Screen::on_activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::on_activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::on_activate]: error: guard \"initialized\" not met");
   }
   std::vector<std::string> tokens = {
      "W", "%SPACE", "A", "%SPACE", "S", "%SPACE", "D", "%SPACER", "LABEL>>", "Move", 
      "%SEPARATOR",
      "ENTER", "%SPACER", "LABEL>>", "Advance dialog", 
      "%SEPARATOR",
      "9", "%SPACER", "LABEL>>", "Quick save", 
      "%SEPARATOR",
      "0", "%SPACER", "LABEL>>", "Quick load", 
      //"%SEPARATOR",
      //"P", "%SPACER", "LABEL>>", "Pause", 
      //"%SEPARATOR",
      //"SHIFT", "%SPACE", "%PLUS", "%SPACE", "ESC", "%SPACER", "LABEL>>", "Exit program", 
   };
   //std::vector<std::string> tokens = {
      //"ESC", "%SPACER", "LABEL>>", "Exit test",
      //"%SEPARATOR",
      //"N", "%SPACER", "LABEL>>", "Post a notification"
      //"%SEPARATOR",
      //"F", "%SPACER", "LABEL>>", "Toggle fullscreen"
   //};
   event_emitter->emit_set_input_hints_bar_event(tokens);
   event_emitter->emit_show_input_hints_bar_event();
   event_emitter->emit_set_input_hints_bar_text_opacity_event(0.75);
   //emit_event_to_update_input_hints_bar();
   //emit_show_and_size_input_hints_bar_event();
   return;
}

void Screen::on_deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::on_deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::on_deactivate]: error: guard \"initialized\" not met");
   }
   event_emitter->emit_hide_input_hints_bar_event();
   //emit_hide_and_restore_size_input_hints_bar_event();
   return;
}

void Screen::mark_entity_collected(TINS2025::Entity* entity)
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::mark_entity_collected]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::mark_entity_collected]: error: guard \"entity\" not met");
   }
   entity->flags |= TINS2025::Entity::FLAG_HIDDEN;
   entity->flags |= TINS2025::Entity::FLAG_INACTIVE;
   entity->flags |= TINS2025::Entity::FLAG_COLLECTED;
   return;
}

void Screen::time_step_player_excitement(double time_step)
{
   static int MAX_ALLOWED_HYPE = 100;

   if (!player_is_accumulating_hype) return;
   if (gameplay_progress.player_excitement >= MAX_ALLOWED_HYPE) // Player is already overstimulated
   {
      gameplay_progress.player_excitement = MAX_ALLOWED_HYPE;
      return;
   }

   // Increment our hype
   gameplay_progress.player_excitement += total_cumulative_hype_aura * 2 * time_step;
   if (gameplay_progress.player_excitement >= MAX_ALLOWED_HYPE)
   {
      gameplay_progress.player_excitement = MAX_ALLOWED_HYPE;
      //event_emitter->emit_game_event(AllegroFlare::GameEvent("player_became_overhyped"));
      //event_emitter->emit_activate_dialog_node_by_name_event("became_overhyped"); // HERE
      view_motion_studio.set_current_camera_to_camera_at_index(2);
      gameplay_progress.player_freakouts++;
      event_emitter->emit_activate_dialog_node_by_name_event("became_overhyped"); // DEVELOPMENT, for now
   }

   return;
}

bool Screen::is_only_once_dialog_already_triggered(std::string dialog_identifier)
{
   return (gameplay_progress.triggered_dialog_names.count(dialog_identifier) > 0);
}

void Screen::mark_dialog_as_triggered(std::string dialog_identifier)
{
   gameplay_progress.triggered_dialog_names.insert(dialog_identifier);
   // TODO: HERE

   //gameplay_progress.triggered_dialogs.insert(entity_type);
   //review_documented_animals_for_win_condition(); // DEVELOPMENT
   return;
}

void Screen::document_animal_type(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::document_animal_type]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::document_animal_type]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   gameplay_progress.documented_entity_types.insert(entity_type);
   review_documented_animals_for_win_condition(); // DEVELOPMENT

   // TODO: Find all en
   //gameplay_progress.documented_entity_types.insert(TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE);
   return;
}

void Screen::review_documented_animals_for_win_condition()
{
   // TODO: Expand what happens here. Probably a new scene?
   int total_animals = animal_database.total_number_of_animals();
   if (gameplay_progress.documented_entity_types.size() >= total_animals) // DEVELOPMENT
   {
      //event_emitter->emit_activate_dialog_node_by_name_event("emit_win_game");
      event_emitter->emit_play_music_track_event("closer");
      event_emitter->emit_game_event(AllegroFlare::GameEvent("win_game"));
   }
   return;
}

bool Screen::is_documented(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::is_documented]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::is_documented]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   return (gameplay_progress.documented_entity_types.count(entity_type) > 0);
}

void Screen::update()
{
   auto &lottie__total_lines_available = gameplay_progress.player_line_capacity;

   if (!get_gameplay_suspended())
   {
      // Observe aabb2d <-> tile steps
      AllegroFlare::Physics::TileMapCollisionStepper tile_map_collision_stepper(
         &collision_tile_map,
         nullptr,
         1.0f,
         1.0f
      );
      for (auto &entity : entities)
      {
         if ((entity.flags & TINS2025::Entity::FLAG_COLLIDES_WITH_TILEMAP) == 0) continue;
         tile_map_collision_stepper.set_aabb2d(&entity.aabb2d);
         tile_map_collision_stepper.step();
      }

      // Update the "distance to player"
      for (auto &entity : entities)
      {
         if (entity.flags & TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER)
         {
            entity.distance_to_player = entity.aabb2d.fast_distance_to_center(player_entity->aabb2d.get_center());
         }
      }

      // Observe changes in bounding box collisions
      collision_observer.set_subject(player_entity);
      std::set<void*> collidables;
      for (auto &entity : entities)
      {
         if (entity.flags & TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER) collidables.insert((void*)&entity);
      }
      collision_observer.set_collidables(collidables);
      collision_observer.set_on_test_collide([](void* subject_v, void* collidable_v) -> bool {
         TINS2025::Entity &subject = *static_cast<TINS2025::Entity*>(subject_v);
         TINS2025::Entity &collidable = *static_cast<TINS2025::Entity*>(collidable_v);

         return (subject.aabb2d.collides(&collidable.aabb2d));
      });

      collision_observer.process();

      for (auto &entered : collision_observer.get_entered())
      {
         TINS2025::Entity &entity = *static_cast<TINS2025::Entity*>(entered);
         if (entity.flags & TINS2025::Entity::FLAG_INACTIVE) continue;

     

         switch (entity.type)
         {
            case TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER: {
               bool is_only_once = entity.has_flag(Entity::FLAG_DIALOG_TRIGGERS_ONLY_ONCE);
               if (is_only_once && !is_only_once_dialog_already_triggered(entity.name))
               {
                  event_emitter->emit_activate_dialog_node_by_name_event(entity.name); // HERE
                  if (is_only_once) mark_dialog_as_triggered(entity.name);
               }
            } break;

            case TINS2025::Entity::ENTITY_TYPE_INFO_SIGN: {
               event_emitter->emit_activate_dialog_node_by_name_event("meet_" + entity.name);
               //entity.name
               //bool is_only_once = entity.has_flag(Entity::FLAG_DIALOG_TRIGGERS_ONLY_ONCE);
               //if (is_only_once && !is_only_once_dialog_already_triggered(entity.name))
               //{
                  //event_emitter->emit_activate_dialog_node_by_name_event(entity.name); // HERE
                  //if (is_only_once) mark_dialog_as_triggered(entity.name);
               //}
            } break;

            case TINS2025::Entity::ENTITY_TYPE_NOTEBOOK_PAGE: {
               //entity.flags |= TINS2025::Entity::FLAG_HIDDEN;
               //entity.flags |= TINS2025::Entity::FLAG_INACTIVE;
               //entity.flags |= TINS2025::Entity::FLAG_COLLECTED;

               lottie__total_lines_available += LINES_PER_PAGE;
               items_collected_tmj_ids.insert(entity.tmj_id);

               mark_entity_collected(&entity);

               event_emitter->emit_activate_dialog_node_by_name_event("#collect_notebook_paper");
            } break;

            case TINS2025::Entity::ENTITY_TYPE_GIRAFFE: {
               event_emitter->emit_activate_dialog_node_by_name_event("meet_giraffe");

               //event_emitter->emit_activate_dialog_node_by_name_event("celebrate_won_game");
            } break;

            case TINS2025::Entity::ENTITY_TYPE_GOAT: {
               event_emitter->emit_activate_dialog_node_by_name_event("meet_goat");
            } break;
         }
      }


      //
      // Update the animal_aura_collision_observer
      //
      {
         total_cumulative_hype_aura = 0.0;

         animal_aura_collision_observer.set_subject(player_entity);
         std::set<void*> collidables;
         for (auto &entity : entities)
         {
            // If it does not track distance to player, don't include
            if (!(entity.flags & TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER)) continue;

            // If it does not emit a hype aura, don't include
            if (!(entity.flags & TINS2025::Entity::FLAG_EMITS_HYPE_AURA)) continue;

            // If it's already been documented, don't include
            if (is_documented(entity.type)) continue;
            //if (entity.flags & TINS2025::Entity::FLAG_DOCUMENTED) continue;

            collidables.insert((void*)&entity);
         }
         animal_aura_collision_observer.set_collidables(collidables);
         animal_aura_collision_observer.set_on_test_collide([](void* subject_v, void* collidable_v) -> bool {
            TINS2025::Entity &subject = *static_cast<TINS2025::Entity*>(subject_v);
            TINS2025::Entity &collidable = *static_cast<TINS2025::Entity*>(collidable_v);

            int HARD_CODED_AURA_RADIUS = 10; // DEVELOPMENT, TODO: Use value from database for this animal
            return (collidable.distance_to_player <= HARD_CODED_AURA_RADIUS);
         });

         animal_aura_collision_observer.process();

         for (auto &currently_colliding_animal : animal_aura_collision_observer.get_currently_colliding())
         {
            int HARD_CODED_AURA_HYPE = 5; // DEVELOPMENT, TODO: Use value from database for this animal
            total_cumulative_hype_aura += HARD_CODED_AURA_HYPE;
         }
      }


      //
      // Update the hype meter
      //
      time_step_player_excitement(1.0/60); // NOTE: HACK: hard-coded step rate
   }

   // Update the view motion
   view_motion_studio.update();

   // Update the current camera to track the current player position
   if (camera_is_tracking_player)
   {
      view_motion_studio.get_camera_studio_ref().get_live_camera_ref().position.x = player_entity->aabb2d.get_x();
      view_motion_studio.get_camera_studio_ref().get_live_camera_ref().position.z = player_entity->aabb2d.get_y();
   }

   // Update dipping to black
   if (dipping_to_black)
   {
      dip_to_black_overlay_opacity += dip_to_black_rate;
      if (dip_to_black_overlay_opacity > 1.0)
      {
         dip_to_black_overlay_opacity = 1.0f;
         if (current_chapter_number == 1) event_emitter->emit_game_event(AllegroFlare::GameEvent("start_chapter_2"));
         if (current_chapter_number == 2) event_emitter->emit_game_event(AllegroFlare::GameEvent("start_chapter_3"));
      }
   }
   else
   {
      dip_to_black_overlay_opacity -= dip_to_black_rate;
      if (dip_to_black_overlay_opacity < 0.0) dip_to_black_overlay_opacity = 0.0f;
   }


   return;
}

void Screen::white_flash()
{
   dip_to_black_rate = 0.03125;
   dip_to_black_overlay_opacity = 1.0;
   dip_to_black_color = ALLEGRO_COLOR{1, 1, 1, 1};
   dipping_to_black = false;
   return;
}

void Screen::black_dip_out()
{
   dip_to_black_rate = 0.015625;
   dip_to_black_overlay_opacity = 1.0;
   dip_to_black_color = ALLEGRO_COLOR{0, 0, 0, 1};
   dipping_to_black = false;
   return;
}

void Screen::render_game_hud()
{
   auto &lottie__num_lines_written = gameplay_progress.player_lines_filled;
   auto &lottie__total_lines_available = gameplay_progress.player_line_capacity;

   AllegroFlare::Camera2D hud_camera;
   hud_camera.setup_dimensional_projection(al_get_target_bitmap());
   al_clear_depth_buffer(1);

   //al_draw_filled_circle(100, 100, 30, ALLEGRO_COLOR{1, 1, 1, 1});

   ALLEGRO_FONT *font = font_bin->auto_get("Quicksand-SemiBold.ttf -42");
   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{1, 1, 1, 1};
   ALLEGRO_COLOR fill_color = ALLEGRO_COLOR{0, 0, 0, 0.2};

   double &lottie__excitement = gameplay_progress.player_excitement;


   //- name: lottie__num_notebook_pages
     //type: int
     //init_with: 0

   //- name: lottie__excitement
     //type: int
     //init_with: 0


   { // Draw the meters
      //float off_y = -30;
      al_draw_filled_rounded_rectangle(94, 380, 326, 696, 16, 16, fill_color);

      { // Draw the "Excitement meter"
         int bar_x = 170;
         int bar_y = 1080/2;
         int bar_height = 8;
         int bar_margin = 4;
         int bar_width = 48;
         int text_offset_y = -42;
         //int lottie_excitement = gameplay_progress.player_excitement;
         {
            // Draw the excitement meter
            AllegroFlare::Placement2D bar_place;
            bar_place.rotation = -3.1415 * 0.5;
            bar_place.position.x = bar_x;
            bar_place.position.y = bar_y;
            bar_place.align.y = 0.5;
            bar_place.align.x = 0.5;
            //bar_place.start_transform();
            AllegroFlare::Elements::HealthBars::Classic bar;
            bar.set_max(20);
            bar.set_value((lottie__excitement / 100.0) * bar.get_max());
            // NOTE: These values are switched around because 
            bar.set_bar_width(bar_height);
            bar.set_bar_height(bar_width);
            bar.set_bar_spacing(bar_height + bar_margin);
            bar.set_fill_color(al_color_name("pink"));

            bar_place.size.y = bar.get_bar_height();
            bar_place.size.x = bar.get_max() * bar.get_bar_spacing();
            bar_place.start_transform();
            bar.render();

            //al_draw_text(font, text_color, 0, text_offset_y, 0, "OVERSTIMULATION");
            al_draw_text(font, text_color, 0, text_offset_y, 0, "EXCITEMENT");

            bar_place.restore_transform();
         }


         bar_x = 275;
         {
            // Draw the excitement meter
            AllegroFlare::Placement2D bar_place;
            bar_place.rotation = -3.1415 * 0.5;
            bar_place.position.x = bar_x;
            bar_place.position.y = bar_y+116;
            bar_place.align.y = 0.5;
            bar_place.align.x = 0.0;
            //bar_place.start_transform();
            AllegroFlare::Elements::HealthBars::Classic bar;
            //bar.set_max(20);
            //bar.set_value(10);
            bar.set_max(gameplay_progress.player_line_capacity); // HERE
            //bar.set_max(20); // HERE
            /*
              - name: player_line_capacity
                type: int
                init_with: 0
                exposed: true

              - name: player_lines_filled
                type: int
                init_with: 0
                exposed: true
            */

            bar.set_value(gameplay_progress.player_lines_filled);
            //bar.set_value((lottie__num_lines_written * (lottie__total_lines_available) / 100.0) * bar.get_max());
            // NOTE: These values are switched around because 
            bar.set_bar_width(bar_height);
            bar.set_bar_height(bar_width);
            bar.set_bar_spacing(bar_height + bar_margin);
            bar.set_fill_color(al_color_name("pink"));

            bar_place.size.y = bar.get_bar_height();
            bar_place.size.x = bar.get_max() * bar.get_bar_spacing();
            //bar_place.position.x 
            bar_place.start_transform();
            bar.render();

            al_draw_text(font, text_color, 0, text_offset_y, 0, "BLANK LINES");

            bar_place.restore_transform();
         }
      }
   }

   // Draw the animals distance list
   {
      float box_y = 352;
      al_draw_filled_rounded_rectangle(94, 380+box_y, 326, 696+box_y-40, 16, 16, fill_color);

      static std::vector<TINS2025::Entity*> distance_entities;
      distance_entities.reserve(32);
      distance_entities.clear();
      float max_distance = 50;
      for (auto &entity : entities)
      {
         if (entity.flags & TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER)
         {
            if (entity.distance_to_player >= max_distance) continue;
            // Modify the value here
            entity.distance_to_player = (float)(int)(entity.distance_to_player / 5);
            distance_entities.push_back(&entity);
         }
      }
      std::sort(distance_entities.begin(), distance_entities.end(),
         [](const TINS2025::Entity* a, const TINS2025::Entity* b)
         {
            //return (int)(a->distance_to_player / 5) < (int)(b->distance_to_player / 5);
            return a->distance_to_player < b->distance_to_player;
         });
      float xx = 100 + 15;
      float yy = 1080/7*5;
      int line = 0;
      int line_height = al_get_font_line_height(font);
      int limit = 4;
      int count = 0;
      float y = yy + line * line_height;
      if (distance_entities.empty())
      {
         // TODO: test this
         float lh = al_get_font_line_height(font);
         al_draw_multiline_text(font, text_color, xx+91, y+58, 999, lh, ALLEGRO_ALIGN_CENTER, "NOTHING\nIN RANGE");
      }
      else
      {
         for (auto &entity : distance_entities)
         {
            // entity name
            float y = yy + line * line_height;
            al_draw_text(font, text_color, xx, y, 0, entity->type_to_string().c_str());
            al_draw_textf(font, text_color, xx+184, y, ALLEGRO_ALIGN_RIGHT, "%d", (int)entity->distance_to_player);
            line++;
            count++;
            if (count > limit) break;
         }
      }
   }


   if (false)
   { // DEVELOPMENT
      float l=0;
      float lh = 40;
      al_draw_textf(font, text_color, 20, 20+l++*40, 0, "num_pages: %d", lottie__total_lines_available / LINES_PER_PAGE);
      al_draw_textf(font, text_color, 20, 20+l++*40, 0, "num_total_lines: %d", lottie__total_lines_available);
      al_draw_textf(font, text_color, 20, 20+l++*40, 0, "num_lines_written: %d", lottie__num_lines_written);
      al_draw_textf(font, text_color, 20, 20+l++*40, 0, "excitement: %.2f", lottie__excitement);
      al_draw_textf(font, text_color, 20, 20+l++*40, 0, "total_hype_aura: %.2f", total_cumulative_hype_aura);
   }


   return;
}

void Screen::render()
{
   view_motion_studio.setup_camera_projection_on_live_camera();

   AllegroFlare::Placement3D environment_model_displacement;
   //environment_model_displacement.position.x = 0.5;
   //environment_model_displacement.position.z = 0.5;
   environment_model_displacement.start_transform();
   environment_model->draw();
   environment_model_displacement.restore_transform();

   if (!hide_view_motion_studio_hud) DEVELOPMENT__render_tile_map();


   std::vector<TINS2025::Entity> sorted_entities = entities;
   std::sort(
      sorted_entities.begin(),
      sorted_entities.end(),
      [](const TINS2025::Entity &a, const TINS2025::Entity &b)
      {
         float a_center_y = a.aabb2d.get_y() + a.aabb2d.get_h() * 0.5f;
         float b_center_y = b.aabb2d.get_y() + b.aabb2d.get_h() * 0.5f;
         return a_center_y < b_center_y; // back to front
         //return a.aabb2d.get_y() < b.aabb2d.get_y(); // back to front
      }
   );

   AllegroFlare::Camera3D &camera = view_motion_studio.get_camera_studio_ref().get_live_camera_ref();

   AllegroFlare::Placement3D placement;
   //for (auto &entity : entities)
   for (auto &entity : sorted_entities)
   {
      if (entity.flags & TINS2025::Entity::FLAG_INACTIVE) continue;
      if (entity.flags & TINS2025::Entity::FLAG_HIDDEN) continue;

      float animation_y_offset = 0.0f;
      if (entity.animation_mode == TINS2025::Entity::ANIMATION_MODE_JUMPING_IN_EXCITEMENT)
      {
         //float bounce_counter = sin(time_now*34)*0.5 + 0.5;
         //get_bitmap_placement_ref().anchor = { 0, -(bounce_counter * 3.0f) };
         animation_y_offset = std::sin(al_get_time()*34)*0.4 + 0.5;
      }
      else if (entity.animation_mode == TINS2025::Entity::ANIMATION_MODE_WALKING_WOBBLY)
      {
         float i = 0.125 * 0.5; // intensity
         animation_y_offset = std::sin(al_get_time()*34)*i + i;
      }


      float item_y_offset = 0;
      if (entity.type == TINS2025::Entity::ENTITY_TYPE_CAKE_1
       || entity.type == TINS2025::Entity::ENTITY_TYPE_CAKE_2
       || entity.type == TINS2025::Entity::ENTITY_TYPE_CAKE_3
      )
      {
         item_y_offset = 0.45;
      }
      else if (entity.type == TINS2025::Entity::ENTITY_TYPE_COMPOSITE_CAKE)
      {
         item_y_offset = 0.35;
      }
      //else if (entity.type == TINS2025::Entity::ENTITY_TYPE_RED_CARROT)
      //{
         //item_y_offset = -0.25;
      //}
      

      //entity.draw();
      float entity_center_x = entity.aabb2d.get_x() + entity.aabb2d.get_w() * 0.5f;
      float entity_center_y = entity.aabb2d.get_y() + entity.aabb2d.get_h() * 0.5f;
      placement.position.x = entity_center_x; //entity.aabb2d.get_x() + ; // + entity.aabb2d.get_w() * 0.5f;
      placement.position.z = entity_center_y; //entity.aabb2d.get_y(); // + entity.aabb2d.get_h() * 0.5;
      placement.position.y = animation_y_offset + item_y_offset;
      placement.scale.x = 1.0; // + entity.aabb2d.get_w() * 0.5f;
      placement.scale.y = 1.0; // + entity.aabb2d.get_w() * 0.5f;







      // --- BILLBOARDING LOGIC START (Gemini, after reviwing my code from another project) ---
      
      // TODO: Swap these booleans with your actual entity flag checks when ready
      bool renders_with_billboarding = true; // e.g., (entity.flags & TINS2025::Entity::FLAG_RENDERS_WITH_BILLBOARDING)
      bool renders_with_y_only = false;      // e.g., (entity.flags & TINS2025::Entity::FLAG_RENDERS_WITH_BILLBOARDING_Y_ONLY)

      // Reset rotations to default (Crucial because 'placement' is reused!)
      placement.rotation.x = 0;
      placement.rotation.y = 0;
      placement.rotation.z = 0;

      if (renders_with_billboarding || renders_with_y_only)
      {
         placement.rotation_order = AllegroFlare::Placement3D::RotationOrder::XZY;

         // Note: If your older Camera3D doesn't have the `_in_unit_values` booleans, 
         // you can just remove the ternary checks and use `-camera.tilt`, `-camera.spin`, etc.
         float cam_rot_x = -(camera.tilt_in_unit_values ? camera.tilt : camera.tilt / AllegroFlare::TAU);
         float cam_rot_y = -(camera.spin_in_unit_values ? camera.spin : camera.spin / AllegroFlare::TAU);
         float cam_rot_z = -(camera.roll_in_unit_values ? camera.roll : camera.roll / AllegroFlare::TAU);

         if (renders_with_y_only)
         {
            placement.rotation.y = cam_rot_y;
         }
         else
         {
            placement.rotation.x = cam_rot_x;
            placement.rotation.y = cam_rot_y;
            placement.rotation.z = cam_rot_z;
         }
      }
      // --- BILLBOARDING LOGIC END ---







      //placement.size.x = entity.aabb2d.get_w(); // + entity.aabb2d.get_w() * 0.5f;
      //placement.size.z = entity.aabb2d.get_h(); // + entity.aabb2d.get_h() * 0.5;
      /*
      //placement.size.x = entity.aabb2d.get_w(); // + entity.aabb2d.get_w() * 0.5f;
      //placement.size.z = entity.aabb2d.get_h(); // + entity.aabb2d.get_h() * 0.5;
      placement.size.y = 0;
      placement.align.x = 0.5;
      placement.align.z = 0.5;
      placement.align.y = 0;
      */

      placement.start_transform();
      entity.model->set_texture(entity.sprite);
      entity.model->draw();
      if (!hide_view_motion_studio_hud)
      {
         al_draw_rectangle(0, 0, entity.aabb2d.get_w(), entity.aabb2d.get_h(), ALLEGRO_COLOR{1, 1, 1, 1}, 0.01);
      }
      placement.restore_transform();
   }



   render_game_hud();



   if (dip_to_black_overlay_opacity > 0.0001)
   {
      view_motion_studio.get_camera_studio_ref().setup_projection_on_hud_camera();
      float o = dip_to_black_overlay_opacity;
      ALLEGRO_COLOR c = dip_to_black_color;
      c.r *= o;
      c.g *= o;
      c.b *= o;
      c.a = o;
      al_draw_filled_rectangle(0, 0, 1920, 1080, c);
   }


   //view_motion_studio.setup_camera_projection_on_live_camera();

   // Render the view motion hud
   if (!hide_view_motion_studio_hud) view_motion_studio.render_hud();
   //DEVELOPMENT__render_tile_map();
   //for (auto &entity : entities)
   //{
      //if ((entity.flags & TINS2025::Entity::FLAG_HIDDEN) == 0) entity.draw_bbox();
   //}
   return;
}

TINS2025::Entity* Screen::find_last_activated_safe_point()
{
   TINS2025::Entity* result = nullptr;
   for (auto &entity : entities)
   {
      if (entity.type == TINS2025::Entity::ENTITY_TYPE_LOCATION_POINT) return &entity;
   }
   AllegroFlare::Logger::throw_error(
      THIS_CLASS_AND_METHOD_NAME,
      "Could not find any location point."
   );
   return nullptr;
}

void Screen::move_player_to_last_safe_point()
{
   TINS2025::Entity* safe_point = find_last_activated_safe_point();
   player_entity->aabb2d.set_x(safe_point->aabb2d.get_x());
   player_entity->aabb2d.set_y(safe_point->aabb2d.get_y());
   return;
}

void Screen::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::game_event_func]: error: guard \"game_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::game_event_func]: error: guard \"game_event\" not met");
   }
   auto &lottie__num_lines_written = gameplay_progress.player_lines_filled;
   //if (scripting) scripting->game_event_func(game_event);

   //if (game_event->is_type("trigger_central_core_cinematic"))
   //{
      //start_cinematic_camera("central_core_cinematic");
   //}
   if (game_event->is_type("show_bunbucks_cake"))
   {
      auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            return e.type == TINS2025::Entity::ENTITY_TYPE_BUNBUCKS_CAKE;
      });
      if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      else { } // Not found
   }
   //else if (game_event->is_type("player_became_overhyped"))
   //{
      // TODO: Consider what consequences are due here
      // TODO: Note that there could be a race condition
      //event_emitter->emit_activate_dialog_node_by_name_event("became_overhyped");
   //}




   else if (game_event->is_type("document_giraffe_event"))
   {
      auto type = TINS2025::Entity::Type::ENTITY_TYPE_GIRAFFE;
      double &lottie__excitement = gameplay_progress.player_excitement;
      const TINS2026::Animal& record = animal_database.get_record_by_entity_type(type);
      int num_lines = record.how_many_lines_needed_for_notetaking;
      if (gameplay_progress.lines_available() >= num_lines)
      {
         lottie__num_lines_written += num_lines;
         lottie__excitement -= num_lines * 5;
         document_animal_type(type);
         // TODO: Emit "done!" dialog // HERE
         event_emitter->emit_activate_dialog_node_by_name_event("documented_the_animal");
      }
      else
      {
         event_emitter->emit_activate_dialog_node_by_name_event("unable_to_document_the_animal");
      }
   }
   else if (game_event->is_type("document_goat_event"))
   {
      auto type = TINS2025::Entity::Type::ENTITY_TYPE_GOAT;
      double &lottie__excitement = gameplay_progress.player_excitement;
      const TINS2026::Animal& record = animal_database.get_record_by_entity_type(type);
      int num_lines = record.how_many_lines_needed_for_notetaking;
      if (gameplay_progress.lines_available() >= num_lines)
      {
         lottie__num_lines_written += num_lines;
         lottie__excitement -= num_lines * 5;
         document_animal_type(type);
         // TODO: Emit "done!" dialog // HERE
         event_emitter->emit_activate_dialog_node_by_name_event("documented_the_animal");
      }
      else
      {
         event_emitter->emit_activate_dialog_node_by_name_event("unable_to_document_the_animal");
      }
   }
   else if (game_event->is_type("document_zebra_event"))
   {
      auto type = TINS2025::Entity::Type::ENTITY_TYPE_ZEBRA;
      double &lottie__excitement = gameplay_progress.player_excitement;
      const TINS2026::Animal& record = animal_database.get_record_by_entity_type(type);
      int num_lines = record.how_many_lines_needed_for_notetaking;
      if (gameplay_progress.lines_available() >= num_lines)
      {
         lottie__num_lines_written += num_lines;
         lottie__excitement -= num_lines * 5;
         document_animal_type(type);
         // TODO: Emit "done!" dialog // HERE
         event_emitter->emit_activate_dialog_node_by_name_event("documented_the_animal");
      }
      else
      {
         event_emitter->emit_activate_dialog_node_by_name_event("unable_to_document_the_animal");
      }
   }
   else if (game_event->is_type("document_tiger_event"))
   {
      auto type = TINS2025::Entity::Type::ENTITY_TYPE_TIGER;
      double &lottie__excitement = gameplay_progress.player_excitement;
      const TINS2026::Animal& record = animal_database.get_record_by_entity_type(type);
      int num_lines = record.how_many_lines_needed_for_notetaking;
      if (gameplay_progress.lines_available() >= num_lines)
      {
         lottie__num_lines_written += num_lines;
         lottie__excitement -= num_lines * 5;
         document_animal_type(type);
         // TODO: Emit "done!" dialog // HERE
         event_emitter->emit_activate_dialog_node_by_name_event("documented_the_animal");
      }
      else
      {
         event_emitter->emit_activate_dialog_node_by_name_event("unable_to_document_the_animal");
      }
   }
   else if (game_event->is_type("document_leopard_event"))
   {
      auto type = TINS2025::Entity::Type::ENTITY_TYPE_LEOPARD;
      double &lottie__excitement = gameplay_progress.player_excitement;
      const TINS2026::Animal& record = animal_database.get_record_by_entity_type(type);
      int num_lines = record.how_many_lines_needed_for_notetaking;
      if (gameplay_progress.lines_available() >= num_lines)
      {
         lottie__num_lines_written += num_lines;
         lottie__excitement -= num_lines * 5;
         document_animal_type(type);
         // TODO: Emit "done!" dialog // HERE
         event_emitter->emit_activate_dialog_node_by_name_event("documented_the_animal");
      }
      else
      {
         event_emitter->emit_activate_dialog_node_by_name_event("unable_to_document_the_animal");
      }
   }



   else if (game_event->is_type("show_cake_1"))
   {
      event_emitter->emit_play_music_track_event("sad_theme");
      // TODO: Sound effect, "poof" or "tada"
      auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            return e.type == TINS2025::Entity::ENTITY_TYPE_CAKE_1;
      });
      if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      else { } // Not found
   }
   else if (game_event->is_type("show_cake_2"))
   {
      // TODO: Sound effect, "poof" or "tada"
      auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            return e.type == TINS2025::Entity::ENTITY_TYPE_CAKE_2;
      });
      if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      else { } // Not found
   }
   else if (game_event->is_type("show_cake_3"))
   {
      // TODO: Sound effect, "poof" or "tada"
      auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            return e.type == TINS2025::Entity::ENTITY_TYPE_CAKE_3;
      });
      if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      else { } // Not found
   }
   else if (game_event->is_type("show_composite_cake"))
   {
      // TODO: Sound effect, "poof" or "tada"
      auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            return e.type == TINS2025::Entity::ENTITY_TYPE_COMPOSITE_CAKE;
      });
      if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      else { } // Not found
   }
   else if (game_event->is_type("wind_blow"))
   {
      reveal_all_notebook_pages_not_collected();
   }
   else if (game_event->is_type("bakeoff_begins"))
   {
      //event_emitter->emit_play_music_track_event("sad_theme");
      //{ "theme", { "hello_friend-theme-01.ogg", true, "ignore" } },
      //{ "sad_theme", { "hello_friend-sad_theme-01.ogg", true, "ignore" } },
      //{ "chipper_tune", { "hello_friend-chipper_tune-01.ogg", true, "ignore" } },
      // Start reveal music here

      // TODO: Sound effect, "poof" or "tada"
      //auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            //return e.type == TINS2025::Entity::ENTITY_TYPE_THE_PLANT;
      //});
      //if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      //else { } // Not found
   }
   else if (game_event->is_type("plant_begins"))
   {
      event_emitter->emit_play_music_track_event("theme");
      // Start reveal music here

      // TODO: Sound effect, "poof" or "tada"
      //auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            //return e.type == TINS2025::Entity::ENTITY_TYPE_THE_PLANT;
      //});
      //if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      //else { } // Not found
   }
   else if (game_event->is_type("show_the_plant"))
   {
      // TODO: Sound effect, "poof" or "tada"
      auto it = std::find_if(entities.begin(), entities.end(), [](const TINS2025::Entity &e) {
            return e.type == TINS2025::Entity::ENTITY_TYPE_THE_PLANT;
      });
      if (it != entities.end()) { (*it).flags &= ~TINS2025::Entity::FLAG_HIDDEN; }
      else { } // Not found

      camera_is_tracking_player = false;
      flag__showing_plant_now = true;
      view_motion_studio.set_current_camera_to_camera_at_index(0);
      view_motion_studio.get_motion_studio_ref().set_playhead_position(0);
      //view_motion_studio.get_motion_studio_ref().start_animation();
      view_motion_studio.get_motion_studio_ref().set_playing(true);
      event_emitter->emit_play_music_track_event("closer");
      //view_motion_studio.get_motion_studio_ref().set_playback_speed(true);
      //amera_is_tracking_player = false;
   }
   else if (game_event->is_type("restart_to_safe_point"))
   {
      black_dip_out();
      move_player_to_last_safe_point();
      gameplay_progress.player_excitement = 0;
      //view_motion_studio.set_current_camera_to_camera_at_index(2);
      //gameplay_progress.player_freakouts++;
      //black_dip_out();
      //dipping_to_black = false;
      //suspend_gameplay();
   }
   else if (game_event->is_type("end_chapter_1"))
   {
      dipping_to_black = true;
      suspend_gameplay();
   }
   else if (game_event->is_type("character_realizes"))
   {
      event_emitter->emit_play_music_track_event("idea");
      // TODO: Start camera move here;
   }
   else if (game_event->is_type("end_chapter_2"))
   {
      //current_chapter_number = 3; // HACK
      dipping_to_black = true;
      suspend_gameplay();
   }
   else if (game_event->is_type("start_chapter_2"))
   {
      current_chapter_number = 2;
      refresh_environment_and_world(true);
      dipping_to_black = false;
      //resume_suspended_gameplay();
      //event_emitter->emit_activate_dialog_node_by_name_event("friend_3_requirements"); //
      //event_emitter->emit_play_music_track_event("chipper_tune");
      event_emitter->emit_play_music_track_event("chipper_tune");
      //event_emitter->emit_activate_dialog_node_by_name_event("character_starts_bakeoff");
      //event_emitter->emit_activate_dialog_node_by_name_event("");
   }
   else if (game_event->is_type("start_chapter_3"))
   {
      current_chapter_number = 3;
      refresh_environment_and_world(true);
      dipping_to_black = false;
      resume_suspended_gameplay();
      event_emitter->emit_play_music_track_event("theme");
      view_motion_studio.set_current_camera_to_camera_at_index(7);
   }
   else if (game_event->is_type("win_game"))
   {
      //throw std::runtime_error("AAAAAAAAAAA");
      call_on_finished_callback_func(); // Consider technique to exit
      
      //game_is_won();
      //toggle_player_input_controller_between_robot_and_player_if_available();
   }

   // game_configuration->handle_game_event(game_event);
   return;
   return;
}

void Screen::refresh_environment_and_world(bool set_player_position)
{
   // TODO: Take in to account (current_chapter_number = 2) case

   // Clear out all the entities (non-character)
   entities.erase(
      std::remove_if(entities.begin(), entities.end(),
         [](const TINS2025::Entity &entity)
         {
            return entity.type != TINS2025::Entity::ENTITY_TYPE_PLAYER;
         }),
      entities.end()
   );


   // Clear the bitmap bin, except, restore the player entities sprite
   bitmap_bin->clear();
   player_entity->sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
   //player_entity->sprite = bitmap_bin->auto_get("player_character.png");
      //e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");


   // Relad the TMJ and refill the tile layer data
   AllegroFlare::Tiled::TMJDataLoader tmj_data_loader;
   tmj_data_loader.set_filename(data_folder_path + "maps/hello_zoo-world_map-0n.tmj");
   tmj_data_loader.load();

   auto data = tmj_data_loader.get_tilelayer_data_by_name_as_2d_vector("collision");

   collision_tile_map.resize(tmj_data_loader.get_num_columns(), tmj_data_loader.get_num_rows());
   collision_tile_map.fill_with_data(data);


   tmj_data_loader.for_each_object([this, set_player_position]
         (AllegroFlare::Tiled::TMJObject* object, void* user_data) {
      int tile_width = 16;
      int tile_height = 16;
      float object_x = object->x / (float)tile_width;
      int tmj_id = object->id;
      std::string tmj_name = object->name;

      float object_y = object->y / (float)tile_height;
      float object_w = object->width / (float)tile_width;
      float object_h = object->height / (float)tile_height;

      if (current_chapter_number == 3 && object->object_layer_name != "entities_chapter_3") return;
      if (current_chapter_number == 2 && object->object_layer_name != "entities_chapter_2") return;
      if (current_chapter_number == 1 && object->object_layer_name != "entities_chapter_1") return;


      if (object->name == "player_character")
      {
         if (set_player_position)
         {
            player_entity->aabb2d.set_x(object_x);
            player_entity->aabb2d.set_y(object_y);
         }
         return;
      }

      Entity e;
      e.aabb2d.set_x(object_x);
      e.aabb2d.set_y(object_y);
      e.aabb2d.set_w(1.0);
      e.aabb2d.set_h(1.0);
      e.tmj_id = tmj_id;
      e.name = tmj_name;
      e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;


      e.model = model_bin->auto_get("character_model-01.obj");

      // BY TYPE
      int dialog_trigger_count = 0;
      if (object->type == "dialog_trigger")
      {
         auto &custom_properties = object->custom_properties;
         if (custom_properties.exists("play_only_once"))
         {
            if (!custom_properties.is_bool("play_only_once"))
            {
               throw std::runtime_error("####!!!!!! play_only_once is not bool.");
            }
            if (custom_properties.get_bool("play_only_once") == true)
            {
               e.flags |= TINS2025::Entity::FLAG_DIALOG_TRIGGERS_ONLY_ONCE;
            }
         }
         //bool triggered_once = true;
         //if (custom_
         //object->name; //custom_properties.exists("");
         // HERE
         e.sprite = nullptr;
         e.model = nullptr;
         e.type = TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER;
         e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
         dialog_trigger_count++;
      }
      else if (object->type == "info_sign")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_INFO_SIGN;
         e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         e.model = model_bin->auto_get("hello_zoo-entities-0x-info_sign.obj");
         e.flags |= TINS2025::Entity::FLAG_COLLIDES_WITH_PLAYER;
         //continue;
         //e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         //e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      }

      //std::cout << "DIALOG TRIGGERS ACCUMULATED: " << dialog_trigger_count << std::endl;



      // BY NAME
      //e.model = model_bin->auto_get("character_model-01.obj");
      else if (object->name == "friend_1")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_FRIEND_1;
         e.sprite = bitmap_bin->auto_get("friend_1.png");
      }
      else if (object->type == "location")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_LOCATION_POINT;
         e.sprite = nullptr;
         e.model = nullptr;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.flags |= TINS2025::Entity::FLAG_INACTIVE;
      }
      //else if (object->name == "player_character")
      //{
         //e.type = TINS2025::Entity::ENTITY_TYPE_GIRAFFE;
         //e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         //e.model = model_bin->auto_get("hello_zoo-entities-0x-lottie.obj");
         //e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         //e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      //}
      else if (object->name == "giraffe")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_GIRAFFE;
         e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         e.model = model_bin->auto_get("hello_zoo-entities-0x-giraffe.obj");
         e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      }
      else if (object->name == "goat")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_GOAT;
         e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         e.model = model_bin->auto_get("hello_zoo-entities-0x-goat.obj");
         e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      }
      else if (object->name == "leopard")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_LEOPARD;
         e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         e.model = model_bin->auto_get("hello_zoo-entities-0x-leopard.obj");
         e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      }
      else if (object->name == "tiger")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_TIGER;
         e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         e.model = model_bin->auto_get("hello_zoo-entities-0x-tiger.obj");
         e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      }
      else if (object->name == "zebra")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_ZEBRA;
         e.sprite = bitmap_bin->auto_get("hello_zoo-animals-0x-2x.png");
         e.model = model_bin->auto_get("hello_zoo-entities-0x-zebrah.obj");
         e.flags |= TINS2025::Entity::FLAG_TRACKS_DISTANCE_TO_PLAYER;
         e.flags |= TINS2025::Entity::FLAG_EMITS_HYPE_AURA;
      }
      else if (object->name == "notebook_page")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_NOTEBOOK_PAGE;
         e.sprite = bitmap_bin->auto_get("notebook_paper_item_feature-01.png");
         e.flags |= TINS2025::Entity::FLAG_HIDDEN; // HIDE Notebook pages by default
         e.flags |= TINS2025::Entity::FLAG_INACTIVE; // make them inactive by default too
         //entity.flags &= ~TINS2025::Entity::FLAG_HIDDEN; // Remove the flag
      }
      else if (object->name == "friend_2")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_FRIEND_2;
         e.sprite = bitmap_bin->auto_get("friend_2.png");
      }
      else if (object->name == "friend_3")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_FRIEND_3;
         e.sprite = bitmap_bin->auto_get("friend_3.png");
      }
      else if (object->name == "apple")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_APPLE;
         e.sprite = bitmap_bin->auto_get("apple.png");
      }
      else if (object->name == "carrot")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CARROT;
         e.sprite = bitmap_bin->auto_get("carrot.png");
      }
      else if (object->name == "red_carrot")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_RED_CARROT;
         e.sprite = bitmap_bin->auto_get("red_carrot.png");
      }
      else if (object->name == "dialog_trigger_1")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER_1;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "dialog_trigger_2")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER_2;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "dialog_trigger_3")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER_3;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "dialog_trigger_4")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER_4;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "dialog_trigger_5")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_DIALOG_TRIGGER_5;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_0")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_0;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_1")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_1;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_2")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_2;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_3")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_3;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_4")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_4;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_5")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_5;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_6")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_6;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_7")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_7;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_8")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_8;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "camera_9")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAMERA_9;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.aabb2d.set_w(object_w);
         e.aabb2d.set_h(object_h);
      }
      else if (object->name == "bunbucks_cake")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_BUNBUCKS_CAKE;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         e.sprite = bitmap_bin->auto_get("bunbucks_cake.png");
         e.aabb2d.set_w(1.0);
         e.aabb2d.set_h(1.0);
      }
      else if (object->name == "cake_1")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAKE_1;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         //e.sprite = bitmap_bin->auto_get("bunbucks_cake.png");
         e.sprite = bitmap_bin->auto_get("composite_cake-01.png");
         e.model = model_bin->auto_get("cake_1.obj");
         //e.model = model_bin->auto_get("composite_cake-01.obj");
         e.aabb2d.set_w(1.0);
         e.aabb2d.set_h(1.0);
      }
      else if (object->name == "cake_2")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAKE_2;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         //e.sprite = bitmap_bin->auto_get("bunbucks_cake.png");
         e.sprite = bitmap_bin->auto_get("composite_cake-01.png");
         e.model = model_bin->auto_get("cake_2.obj");
         e.aabb2d.set_w(1.0);
         e.aabb2d.set_h(1.0);
      }
      else if (object->name == "cake_3")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_CAKE_3;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         //e.sprite = bitmap_bin->auto_get("bunbucks_cake.png");
         e.sprite = bitmap_bin->auto_get("composite_cake-01.png");
         e.model = model_bin->auto_get("cake_3.obj");
         //e.model = model_bin->auto_get("composite_cake-01.obj");
         e.aabb2d.set_w(1.0);
         e.aabb2d.set_h(1.0);
      }
      else if (object->name == "composite_cake")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_COMPOSITE_CAKE;
         //e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         //e.sprite = bitmap_bin->auto_get("bunbucks_cake.png");
         e.sprite = bitmap_bin->auto_get("composite_cake-01.png");
         //e.model = model_bin->auto_get("cake_3.obj");
         e.model = model_bin->auto_get("composite_cake-01.obj");
         e.aabb2d.set_w(1.0);
         e.aabb2d.set_h(1.0);
      }
      else if (object->name == "the_plant")
      {
         e.type = TINS2025::Entity::ENTITY_TYPE_THE_PLANT;
         e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         //e.sprite = bitmap_bin->auto_get("bunbucks_cake.png");
         e.sprite = bitmap_bin->auto_get("the_plant-01.png");
         //e.model = model_bin->auto_get("cake_3.obj");
         e.model = model_bin->auto_get("the_plant-01.obj");
         e.aabb2d.set_w(1.0);
         e.aabb2d.set_h(1.0);
      }

      entities.push_back(e);
      
      //std::function<void(AllegroFlare::Tiled::TMJObject*, void*)> function={}, void* user_data=nullptr)
   });



   // Reload the environment model
   //std::string model_filename = "hello_friend-environment-0n.obj";
   std::string model_filename = "hello_zoo-world-0x-Scene-visual.obj";
   std::string image_filename = "hello_friend-environment-0n.png";

   model_bin->destroy(model_filename);
   bitmap_bin->destroy(image_filename);
   environment_model = model_bin->auto_get(model_filename);
   environment_model->texture = bitmap_bin->auto_get(image_filename);

   return;
}

void Screen::display_switch_in_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::display_switch_in_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::display_switch_in_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Screens::Gameplay::display_switch_in_func();

   if (in_test_or_development_mode)
   {
      refresh_environment_and_world(true);
   }

   return;
}

void Screen::primary_update_func(double time_now, double delta_time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::primary_update_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::primary_update_func]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Screens::Gameplay::primary_update_func(time_now, delta_time);

   if (flag__showing_plant_now)
   {
      if (view_motion_studio.get_motion_studio_ref().get_playhead() > 23.53)
      {
         flag__showing_plant_now = false;
         event_emitter->emit_game_event(AllegroFlare::GameEvent("win_game"));
      }
   }

   update();
   return;
}

void Screen::reveal_all_notebook_pages_not_collected()
{
   for (auto &entity : entities)
   {
      if (entity.type == TINS2025::Entity::ENTITY_TYPE_NOTEBOOK_PAGE)
      {
         // HERE
         //e.type = TINS2025::Entity::ENTITY_TYPE_NOTEBOOK_PAGE;
         //e.sprite = bitmap_bin->auto_get("notebook_paper_item_feature-01.png");
         //e.flags |= TINS2025::Entity::FLAG_HIDDEN;
         //entity.tmj_id; // HERE
         if (items_collected_tmj_ids.count(entity.tmj_id) > 0) continue; // Already collected

         //entity.flags &= ~TINS2025::Entity::FLAG_HIDDEN; // Remove the flag
         entity.flags &= ~TINS2025::Entity::FLAG_INACTIVE; // Remove the flag
         entity.flags &= ~TINS2025::Entity::FLAG_HIDDEN; // Remove the flag
      }
   }
   return;
}

void Screen::primary_render_func()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::primary_render_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::primary_render_func]: error: guard \"initialized\" not met");
   }
   // Render stuff here
   al_clear_to_color(al_color_html("d3e7ea"));
   render();
   return;
}

void Screen::mouse_axes_func(ALLEGRO_EVENT* ev)
{
   AllegroFlare::Screens::Gameplay::mouse_axes_func(ev);
   return;
}

void Screen::mouse_down_func(ALLEGRO_EVENT* ev)
{
   AllegroFlare::Screens::Gameplay::mouse_down_func(ev);
   return;
}

void Screen::action__save_progress()
{
   save_progress_file();
   white_flash();
   return;
}

void Screen::action__load_progress()
{
   load_progress_file();
   refresh_environment_and_world();

   // Set the player location
   player_entity->aabb2d.set_x(gameplay_progress.player_location.x);
   player_entity->aabb2d.set_y(gameplay_progress.player_location.y);

   // mark collected items as collected
   for (auto &entity : entities)
   {
      if (items_collected_tmj_ids.count(entity.tmj_id) == 0) continue;
      mark_entity_collected(&entity);
   }

   white_flash();
   return;
}

void Screen::key_down_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"initialized\" not met");
   }
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::key_down_func]: error: guard \"ev\" not met");
   }
   // Process standard gameplay screen controls, which includes whatever active player_input_controller is
   // assigned to the Screens/Gameplay
   AllegroFlare::Screens::Gameplay::key_down_func(ev);

   bool shift = ev->keyboard.modifiers & ALLEGRO_KEYMOD_SHIFT;
   bool ctrl = ev->keyboard.modifiers & ALLEGRO_KEYMOD_COMMAND;



   switch(ev->keyboard.keycode)
   {
      case ALLEGRO_KEY_9: {
         action__save_progress();
      } break;

      case ALLEGRO_KEY_0: {
         action__load_progress();
         load_progress_file();
         refresh_environment_and_world();

         // Set the player location
         player_entity->aabb2d.set_x(gameplay_progress.player_location.x);
         player_entity->aabb2d.set_y(gameplay_progress.player_location.y);

         // mark collected items as collected
         for (auto &entity : entities)
         {
            if (items_collected_tmj_ids.count(entity.tmj_id) == 0) continue;
            mark_entity_collected(&entity);
         }

         reveal_all_notebook_pages_not_collected();

         white_flash();
         // TODO: White flash?
      } break;
   }


   if (in_test_or_development_mode)
   {
      if (ev->keyboard.keycode == ALLEGRO_KEY_BACKQUOTE)
      {
         // Toggle playmode
         if (input_mode == INPUT_MODE_PLAYING) input_mode = INPUT_MODE_EDITING;
         else if (input_mode == INPUT_MODE_EDITING) input_mode = INPUT_MODE_PLAYING;
      }
      else if (ev->keyboard.keycode == ALLEGRO_KEY_H)
      {
         hide_view_motion_studio_hud = !hide_view_motion_studio_hud;
      }
      //else if (ev->keyboard.keycode == ALLEGRO_KEY_U)
      //{
         //event_emitter->emit_game_event(AllegroFlare::GameEvent("end_chapter_1"));
      //}
      //else if (ev->keyboard.keycode == ALLEGRO_KEY_Y)
      //{
         //event_emitter->emit_game_event(AllegroFlare::GameEvent("start_chapter_2"));
      //}
      else
      {
         switch (input_mode)
         {
            case INPUT_MODE_PLAYING: {
            } break;

            case INPUT_MODE_EDITING:
               view_motion_studio.on_key_down(ev);
            break;
         }
      }
   }

   return;
}

void Screen::virtual_control_button_up_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::virtual_control_button_up_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

void Screen::virtual_control_button_down_func(AllegroFlare::Player* player, AllegroFlare::VirtualControllers::Base* virtual_controller, int virtual_controller_button_num, bool is_repeat)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::virtual_control_button_down_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   using namespace AllegroFlare;
   //if (!is_processing_user_input()) return;

   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_RIGHT)
   {
      //player_velocity.x = 1;
      //chapter_select_element.rotate_carousel_right();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_LEFT)
   {
      //player_velocity.x = -1;
      //chapter_select_element.rotate_carousel_left();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_A
      || virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_MENU
      )
   {
      //select_menu_option();
   }
   if (virtual_controller_button_num == VirtualControllers::GenericController::BUTTON_X)
   {
      //exit_screen();
   }
   //call_on_finished_callback_func(); // Consider technique to exit
   return;
}

void Screen::virtual_control_axis_change_func(ALLEGRO_EVENT* ev)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::virtual_control_axis_change_func]: error: guard \"initialized\" not met");
   }
   // TODO: this function
   return;
}

ALLEGRO_FONT* Screen::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -32");
}

void Screen::DEVELOPMENT__render_tile_map()
{
   AllegroFlare::Placement3D tile_map_placement = environment_overlay_placement;
   float o = 0.25;
   tile_map_placement.rotation.x = 0.25;
   tile_map_placement.position.y = 0.25;

   AllegroFlare::TileMaps::TileMap<int> &tile_map = collision_tile_map;
   float tile_width=1.0f;
   float tile_height=1.0f;

   tile_map_placement.start_transform();
   for (int y=0; y<tile_map.get_num_rows(); y++)
   {
      for (int x=0; x<tile_map.get_num_columns(); x++)
      {
         int tile_type = tile_map.get_tile(x, y);
         switch(tile_type)
         {
            case 0:
              //al_draw_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.2, 0.2, 0.21, 0.21}, 1.0);
            break;

            case 1:
              al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 ALLEGRO_COLOR{0.94f*o, 0.42f*o, 0.8f*o, 1.0f*o});
            break;

            default:
              //al_draw_filled_rectangle(x * tile_width, y * tile_height, (x+1) * tile_width, (y+1) * tile_height, 
                 //ALLEGRO_COLOR{0.8, 0.32, 0.4, 1.0});
            break;
         }
      }
   }
   tile_map_placement.restore_transform();
   return;
}

std::vector<std::string> Screen::build_need_to_document_dialog_pages(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_need_to_document_dialog_pages]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_need_to_document_dialog_pages]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   std::vector<std::string> result = {
      "This is such an amazing creature!",
      "For the (em)"
         + record.name
         + "(/em), I'll need to write (em)"
         + std::to_string(record.how_many_lines_needed_for_notetaking)
         + " lines of notes(/em)!",
   };
   return result;
}

std::vector<std::string> Screen::build_interesting_facts_dialog_pages(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_interesting_facts_dialog_pages]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_interesting_facts_dialog_pages]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   return record.interesting_facts_dialog_pages;
}

std::string Screen::build_emit_document_event_identifier(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_emit_document_event_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_emit_document_event_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   return "document_" + record.identifier + "_event";
}

std::string Screen::build_meet_node_identifier(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_meet_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_meet_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   return "meet_" + record.identifier;
}

std::string Screen::build_document_node_identifier(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_document_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_document_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   return "->document_" + record.identifier;
}

std::string Screen::build_emit_document_node_identifier(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_emit_document_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_emit_document_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   return "->emit_document_" + record.identifier;
}

std::string Screen::build_emit_document_event_node_identifier(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_emit_document_event_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_emit_document_event_node_identifier]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   const TINS2026::Animal& record = animal_database.get_record_by_entity_type(entity_type);
   return "->emit_document_" + record.identifier;
}

std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> Screen::build_meet_node(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_meet_node]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_meet_node]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> result = {
   //return AllegroFlare::Dialog // HERE   {
      build_meet_node_identifier(entity_type),
      new AllegroFlare::DialogTree::Nodes::Interparsable(
         LOTTIE,
         build_interesting_facts_dialog_pages(entity_type),
         //{
            //"Amazing! A giraffe!",
            //"They have huge long necks!",
            ////"Also, they hardly ever sleep, getting only 30 to 4.5 hours of sleep a day!",
         //},
         {
            { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode(
               build_document_node_identifier(entity_type)
               ), 0 }
         }
      )
   };
   return result;
}

std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> Screen::build_document_node(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_document_node]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_document_node]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }

   std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> result = {

       build_document_node_identifier(entity_type),
         new AllegroFlare::DialogTree::Nodes::Interparsable(
      //{ "->document_giraffe", new AllegroFlare::DialogTree::Nodes::Interparsable(
            LOTTIE,
            build_need_to_document_dialog_pages(entity_type),
            //{
               //"This is such an amazing creature!",
               //"For the (em)Giraffe(/em), I'll need to write (em)3 lines of notes(/em)!",
            //},
            {
               { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode(
                  build_emit_document_node_identifier(entity_type)
                           //"->emit_document_giraffe"
                  ), 0 }
            }
         )
      };
   return result;
}

std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> Screen::build_emit_document_event_node(TINS2025::Entity::Type entity_type)
{
   if (!((entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)))
   {
      std::stringstream error_message;
      error_message << "[TINS2025::Gameplay::Screen::build_emit_document_event_node]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[TINS2025::Gameplay::Screen::build_emit_document_event_node]: error: guard \"(entity_type != TINS2025::Entity::Type::ENTITY_TYPE_UNDEF)\" not met");
   }
   std::pair<std::string, AllegroFlare::DialogTree::Nodes::Base*> result = {
       build_emit_document_node_identifier(entity_type),
         new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            //"document_" _ record,
            build_emit_document_event_identifier(entity_type),
            "exit_dialog"
         )
      };
   return result;
}

AllegroFlare::DialogTree::NodeBank Screen::build_dialog_node_bank()
{
   AllegroFlare::DialogTree::NodeBank result;

   //TINS2026::AnimalDatabase animal_db;

   //std::string LOTTIE = "Lottie";
   //std::string FRIEND_1 = "Ditto";
   //std::string FRIEND_2 = "Frank";
   //std::string FRIEND_3 = "Derek";

   result.set_nodes({
      //character_enters_town
      //character_sees_plant
      { "#collect_notebook_paper", new AllegroFlare::DialogTree::Nodes::YouGotAnItemDialog(
            "Sheet of Notebook Paper",
            //"storyboard-2-01-1165x500.png"
            //"player_character.png"
            "notebook_paper_item_feature-01.png"
            //"As a botanist, I can't wait to check out the (em)mysterious flower(/em).",
            //"I came all the way to this small town just to see it!",
         //)}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "get_notebook_paper", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "A (em)Sheet of Notebook Paper(/em) increases your total number of blank lines by 4.",
         }, { { "GoToNode", new AllegroFlare::DialogTree::NodeOptions::GoToNode("#collect_notebook_paper"), 0 } }
      )},
      //{ "get_notebook_paper", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            //"A (em)Sheet of Notebook Paper(/em) increases your total number of blank lines by 4.",
         //}, { { "GoToNode", new AllegroFlare::DialogTree::NodeOptions::GoToNode("#collect_notebook_paper"), 0 } }
      //)},
      { "character_intro_dialog", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Whew!",
            "I made it!",
            "As a botanist, I don't normally get time to check out cool places like the (em)Zoo(/em)!",
            "But today is my lucky day.",
            "I've brought my notepad so I can take a bunch of notes and..."
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "character_attempts_to_leave", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "As much as I'd like to leave and get some goodies from Bunbucks, I really want to check out the flower."
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "character_enters_town", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "What a cute little town!",
            "I had no idea this place would be so small.",
            "There can't be more than...",
            "1...",
            "2...",
            "3 houses here!",
            "I bet the residents here are pretty grateful to be in the presence of one of the rarest plants...",
            "like...",
            "...ever!",
            "I bet they're pretty cool and relaxed just knowing it's nearby!",
            "Oooh! And there it is! The rare flower!",
            "And it hasn't bloomed yet. It looks like I got here just in time!",
            "I can't wait to get a closer look."
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "character_sees_plant", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "OOoooo!",
            "And! Just as I suspected.",
            "It hasn't yet bloomed. It's still a little bud.",
            "Oh my... eee!! After all the years I've studied botany!",
            "I couldn't be more excited!",
            "It's even more miraculous than I could have dreamed!",
            "And it still hasn't even bloomed yet!",
            "EEEeeee!!",
            "Maybe I should talk to the local villagers and see what their thoughts are on such a wonderful thing.",
            //"
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "character_sees_plant_again", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Maybe I should talk to the local villagers and see what their thoughts are on such a wonderful flower.",
            //"
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "character_suspicious_of_plant", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Hmmm...",
            "Something's not quite right.",
            "Normally, just around this time, the plant would start showing signs of budding.",
            "But, it's like... nothing.",
            "No worry! I read some guy's comment on PlantVids once. He said that this happens sometimes.",
            "The comment said something about how the flower needs a cake, and it will start to bloom.",
            "I came prepared!",
            "I picked up a little cake at Bunbucks on the way here.",
            "It was 50% off too!",
            "Heheh! It gets the job done!",
            "I mean, comments on the internet can't all be wrong right?",
            "...",
            "OK, here I go...",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "use bunbucks", new AllegroFlare::DialogTree::NodeOptions::GoToNode("use_bunbucks"), 0 } }
      )},
      { "use_bunbucks", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "show_bunbucks_cake",
            "->character_tries_bunbucks_cake"
         )
      },

      { "start_chapter_2", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "start_chapter_2",
            "character_starts_bakeoff"
         )
      },
      { "character_starts_bakeoff", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Yaaayy!",
            "It's now time for the big bake-off cake reveal!",
            //"Today's the big day for the bake-off!",
            "But wait, if this is a competition, how do we know who will be the winner?"
            //"Normally, just around this time, the plant would start showing signs of budding.",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_01"), 0 } }
         //}, { { "win for now", new AllegroFlare::DialogTree::NodeOptions::GoToNode("emit_win_game"), 0 } }
         //}, { { "exit for now", new AllegroFlare::DialogTree::NodeOptions::GoToNode("exit_dialog"), 0 } }
      )},
      { "bakeoff_01", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_2, {
            "Well, we each present our cakes one by one.",
            "And, whoever makes the flower bloom the most is declared the winner!",
            //"The bakeoff has begun!",
            //"But wait, if this is a competition, how do we know who will be the winner?"
            //"Normally, just around this time, the plant would start showing signs of budding.",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_02"), 0 } }
         //}, { { "win for now", new AllegroFlare::DialogTree::NodeOptions::GoToNode("emit_win_game"), 0 } }
         //}, { { "exit for now", new AllegroFlare::DialogTree::NodeOptions::GoToNode("exit_dialog"), 0 } }
      )},
      { "bakeoff_02", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Oh wow!",
            "It sure didn't like my Bunbucks cake, heh.",
            "I can see why it didn't bloom, then.",
            "I can't wait to see your cakes!",
            "Let the bake-off begin!"
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_03a"), 0 } }
      )},
      { "bakeoff_03a", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "bakeoff_begins",
            "bakeoff_03b"
         )
      },
      //{ "bakeoff_03a", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(FRIEND_1, {
            //"OK! I'll present my cake first!",
            //"It sure didn't like my Bunbucks cake.",
            //"I can see why it didn't bloom. I can't wait to see your cakes!",
            //"Let the bake-off begin!"
         //}, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_03"), 0 } }
      //)},
      { "bakeoff_03b", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_1, {
            "OK! I'll present my cake first!",
            //"It sure didn't like my Bunbucks cake.",
            //"I can see why it didn't bloom. I can't wait to see your cakes!",
            //"Let the bake-off begin!"
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_04"), 0 } }
      )},
      { "bakeoff_04", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "show_cake_1",
            "bakeoff_05"
         )
      },
      { "bakeoff_05", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_1, {
            "Wah!!",
            "...",
            "Huh?",
            "The flower didn't react at all.",
            "My cake had the perfect proportions!",
            "Oh no! I'm super disappointed in myself.",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_06"), 0 } }
      )},
      //{ "bakeoff_05", new AllegroFlare::DialogTree::Nodes::MultipageWithOptions(FRIEND_1, {
            //"Wah!!",
            //"The flower didn't react at all.",
            //"Oh no! I'm super disappointed in myself.",
         //}, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_06"), 0 } }
      //)},


      { "bakeoff_06", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_2, {
            "Yikes!",
            "Heh heh! I guess that gives me a better chance of winning the competition!",
            "Ok, I'll present my cake now!",
            //"It sure didn't like my Bunbucks cake.",
            //"I can see why it didn't bloom. I can't wait to see your cakes!",
            //"Let the bake-off begin!"
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_07"), 0 } }
      )},
      { "bakeoff_07", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "show_cake_2",
            "bakeoff_08"
         )
      },
      { "bakeoff_08", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_2, {
            "Heegh!!",
            "...", // Change
            "How?!",
            "I put my best into this one.",
            "There's no way it couldn't have worked.",
            "I measured mine to have the perfect proportions!",
            "How could this be?!",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_9"), 0 } }
      )},


      { "bakeoff_9", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_3, {
            "Oh man!",
            "The two of you made amazing cakes, and neither of them worked?!",
            "That means mine doesn't stand a chance!",
            "On the other hand, that also means I'm the one left with a chance to be the winner!",
            "Ok, here goes nothing..."
            //"It sure didn't like my Bunbucks cake.",
            //"I can see why it didn't bloom. I can't wait to see your cakes!",
            //"Let the bake-off begin!"
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_10"), 0 } }
      )},
      { "bakeoff_10", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "show_cake_3",
            "bakeoff_11"
         )
      },
      { "bakeoff_11", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_3, {
            "Yah!!", // Change
            "...", // Change
            "Wahh?!", // Change
            "But... I put my best into this one.", // Change
            //"There's no way!",
            "And I measured the perfect proportions, too!",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_12"), 0 } }
      )},




      { "bakeoff_12", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Hmm...",
            "This is indeed strange!",
            "Why would none of the cakes work for the flower.",
            //"What did my botany book have to say about this?",
            "Hmm...",
            "It's peculiar that ALL THREE of you said something about how you had the pefect propotions!",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("bakeoff_13"), 0 } }
      )},
      { "bakeoff_13", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "character_realizes",
            "bakeoff_14"
         )
      },


      { "bakeoff_14", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            //"Hmm...",
            //"This is indeed strange!",
            //"Why would none of the cakes work for the flower.",
            ////"What did my botany book have to say about this?",
            //"Hmm...",
            //"It's peculiar that *all three* of you said something about how you had the pefect propotions!",
            "Wait! THAT'S IT!",
            "I know what it is!",
            "I know what we need to do!",
            "In order to make the perfect cake... we all must...",
            "There's not time to explain!",
            "Quick, everybody!",
            "GIVE ME ALL YOUR CAKES!",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->trigger_end_chapter_2"), 0 } }
      )},
      { "->trigger_end_chapter_2", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "end_chapter_2",
            "exit_dialog"
         )
      },


      { "start_chapter_3", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "start_chapter_3",
            "cake_reveal_00"
         )
      },
      { "cake_reveal_00", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_1, {
            "Woooww!",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("cake_reveal_01"), 0 } }
      )},
      { "cake_reveal_01", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_2, {
            "Amazing!",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("cake_reveal_02"), 0 } }
      )},
      { "cake_reveal_02", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_3, {
            "It's perfect!",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("cake_reveal_03"), 0 } }
      )},
      { "cake_reveal_03", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "This is it!",
            "Making a layered cake with all our cakes combined is the answer!",
            //"The last ingredient we all needed was...",
            //"We needed to see all of our cakes combined!",
            //"It turns out the last missing ingredient we needed for the competition was...",
            //"Layers!",
            "Each of you measured the perfect ratios, but...",
            "You didn't take into account that each of you ALSO had perfect ratios with EACH OTHER!",
            "It turns out the last missing ingredient we needed for the competition was...",
            "Layers!",
            //"It turns out the last missing ingredient we needed for the competition was...",
            //"Layers!",
            //"each other's ratios, as well.",
            //"This is the layered cake with all our cakes combined!",
            //"We have to work together!",
            //"Making a layered cake with all our cakes combined is the answer!",
            //"I know it!",
            "Working TOGETHER is the answer to a perfect cake! Not against one another.",
            "This is why the flower wouldn't bloom!",
            "It's because everybody was so stressed about the competition.",
            //"This is the layered cake with all our cakes combined!",
            "When we put all of our cakes together into a single, layered cake, it's like something else entirely!",
            //"This is the layered cake with all our cakes combined!",
            //"I know it!",
            //"And, I noticed all our cakes were the perfect dimensions to stack on top of each other.",
            //"This cake is so amazing!",
            //"The ratios are just... just... perfect!",
            //"I think all our cakes deserves a... a... gold medal!",
            //"Oh wait! I can see the plant reacting!",
            //"And the flower is in full bloom!",
            //"Something's not quite right.",
            //"Normally, just around this time, the plant would start showing signs of budding.",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("cake_reveal_04"), 0 } }
      )},
      { "cake_reveal_04", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_1, {
            "This cake is so amazing!",
            //"The ratios are just... just... perfect!",
            //"I think all our cakes deserves a... a... gold medal!",
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("cake_reveal_05"), 0 } }
      )},
      { "cake_reveal_05", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_2, {
            //"This cake is so amazing!",
            "The ratios together... They are just... just... perfect for each other!",
            //"I think all our cakes deserves a... a... gold medal!",
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("cake_reveal_06"), 0 } }
      )},
      { "cake_reveal_06", new AllegroFlare::DialogTree::Nodes::Interparsable(FRIEND_3, {
            //"This cake is so amazing!",
            //"The ratios are just... just... perfect!",
            "I think all our cakes deserve a... a... gold medal!",
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("start_plant_reveal"), 0 } }
      )},
      { "start_plant_reveal", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "plant_begins",
            "show_plant_reveal_02"
         )
      },
      { "show_plant_reveal_02", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Oh wait! I can see the plant reacting!",
            //"And the flower is in full bloom!",
            //"Something's not quite right.",
            //"Normally, just around this time, the plant would start showing signs of budding.",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "plant spawn", new AllegroFlare::DialogTree::NodeOptions::GoToNode("show_plant_reveal_03"), 0 } }
      )},
      { "show_plant_reveal_03", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "show_the_plant",
            "celebrate_plant_02"
         )
      },
      { "celebrate_plant_02", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "We did it!",
            "YAAAAY!",
            //"And the flower is in full bloom!",
            //"Something's not quite right.",
            //"Normally, just around this time, the plant would start showing signs of budding.",
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         }, { { "win for now", new AllegroFlare::DialogTree::NodeOptions::GoToNode("exit_dialog"), 0 } }
      )},

      { "->character_tries_bunbucks_cake", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Heuh!",
            "...",
            "Huh.",
            "Weird.",
            "Nothing happened.",
            "Well, should be no big deal, heh.",
            "I mean, everybody's presenting cakes at the bake-a-thon so it should be fine by then.",
            "...right?"
         }, { { "End Ch1", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->trigger_end_chapter_1"), 0 } }
      )},
      { "->trigger_end_chapter_1", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "end_chapter_1",
            "exit_dialog"
         )
      },
      { "pickup_food", new AllegroFlare::DialogTree::Nodes::Interparsable(
            LOTTIE,
            {
               "Sweet! I just found an essential ingredient for a perfect cake!"
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },






      { "zoo_intro_dialog", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Whew!",
            "I made it!",
            "I may be a botanist by trade, but I like to think of myself as a bit of an amateur zoologist, too!",
            "I LOVE THE ZOO!!",
            "I can't wait to check out the mysterious animals.",
            //"I came all the way to this zoo just to see them!",
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "zoo_entrance_reaction", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "WOAH! What a nice little zoo!",
            "I had no idea this place would be so quaint.",
            "There are exactly...",
            "1... 2...",
            "3... 4...",
            "5 animals here!",
            //"I bet the zookeepers are THRILLED to be working here.",
            "And they are truly some of natures most majestic creatures...",
            //"They're in the presence of some of the most majestic creatures...",
            "like...",
            "...ever!",
            "It's a good thing I brought my (em)notebook(/em) with all of the (em)blank pages(/em) in it.",
            "With these (em)blank pages(/em), I can write down my thoughts so I don't get overwhelmed!"
            //"I bet they're pretty cool and relaxed just knowing they're nearby!",
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "zoo_mechanic_setup", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "Oooh! And there's the first exhibit! The Goat!",
            "EEEeeee!! It's so cute I can't even stand it!",
            "Wait... oh no! My notebook!",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("zoo_wind_blows_notebook"), 0 } }
      )},
      { "zoo_mechanic__after_wind", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE, {
            "AAgh! The wind just blew all of my (em)blank pages(/em) all over the zoo!",
            "Wha... what am I gonna do!?",
            "I need to find those (em)blank pages(/em). I can't possibly document all these animals without them!",
            "If I get too close to the animals without being able to write stuff down, I'll get (em)overwhelmed "
               "with excitement(/em)!",
            "Writing notes is how I keep my mind calm.",
            "Deep breaths...",
            "*pfoo* *pfoo*",
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "zoo_wind_blows_notebook", new AllegroFlare::DialogTree::Nodes::Interparsable(NARRATOR, {
            "Suddenly, an unexpected gust of wind blew through the zoo.",
            "It was so fierce, all of Lottie's blank pages soared into the air!",
            "When Lottie finally got her footing, she saw that her notebook pages had been spread out all over the zoo!",
         }, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->trigger_wind_blow"), 0 } }
         //}, { { "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("zoo_mechanic__after_wind"), 0 } }
         //}, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
      )},
      { "->trigger_wind_blow", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "wind_blow",
            "zoo_mechanic__after_wind"
         )
      },




      { "documented_the_animal", new AllegroFlare::DialogTree::Nodes::Interparsable(
            LOTTIE,
            {
               "Done!",
               "I've documented the animal.",
               "Aahh. I feel more relaxed now."
            //},
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
            //{ { "End Ch1", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->trigger_restart_to_safe_point"), 0 } }
            //{
               //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } // DEVELOPMENT
               ////{ "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->document_giraffe"), 0 }
            //}
         //)
      )},



      { "unable_to_document_the_animal", new AllegroFlare::DialogTree::Nodes::Interparsable(
            LOTTIE,
            {
               "Oh no!",
               "I don't have enough blank lines!"
            //},
         }, { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
            //{ { "End Ch1", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->trigger_restart_to_safe_point"), 0 } }
            //{
               //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } // DEVELOPMENT
               ////{ "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->document_giraffe"), 0 }
            //}
         //)
      )},




      { "became_overhyped", new AllegroFlare::DialogTree::Nodes::Interparsable(
            LOTTIE,
            {
               "Aaayeeee!!!!",
               "AAGH!",
               "This is all too overstimulating!",
               "*pfoo* *pfoo* *pfoo*",
               "I'm getting overwhelmed with excitement. I, I need to take a break."
               //"Also, they hardly ever sleep, getting only 30 to 4.5 hours of sleep a day!",
            },
            { { "End Ch1", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->trigger_restart_to_safe_point"), 0 } }
            //{
               //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } // DEVELOPMENT
               ////{ "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode("->document_giraffe"), 0 }
            //}
         )
      },
      { "->trigger_restart_to_safe_point", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            "restart_to_safe_point",
            "exit_dialog"
         )
      },



      build_meet_node(Entity::Type::ENTITY_TYPE_GIRAFFE),
      build_document_node(Entity::Type::ENTITY_TYPE_GIRAFFE),
      build_emit_document_event_node(Entity::Type::ENTITY_TYPE_GIRAFFE),


      build_meet_node(Entity::Type::ENTITY_TYPE_GOAT),
      build_document_node(Entity::Type::ENTITY_TYPE_GOAT),
      build_emit_document_event_node(Entity::Type::ENTITY_TYPE_GOAT),


      build_meet_node(Entity::Type::ENTITY_TYPE_ZEBRA),
      build_document_node(Entity::Type::ENTITY_TYPE_ZEBRA),
      build_emit_document_event_node(Entity::Type::ENTITY_TYPE_ZEBRA),


      build_meet_node(Entity::Type::ENTITY_TYPE_TIGER),
      build_document_node(Entity::Type::ENTITY_TYPE_TIGER),
      build_emit_document_event_node(Entity::Type::ENTITY_TYPE_TIGER),


      build_meet_node(Entity::Type::ENTITY_TYPE_LEOPARD),
      build_document_node(Entity::Type::ENTITY_TYPE_LEOPARD),
      build_emit_document_event_node(Entity::Type::ENTITY_TYPE_LEOPARD),


      //{ build_meet_node_identifier(Entity::Type::ENTITY_TYPE_GIRAFFE),
         //new AllegroFlare::DialogTree::Nodes::Interparsable(
            //LOTTIE,
            //build_interesting_facts_dialog_pages(Entity::Type::ENTITY_TYPE_GIRAFFE),
            ////{
               ////"Amazing! A giraffe!",
               ////"They have huge long necks!",
               //////"Also, they hardly ever sleep, getting only 30 to 4.5 hours of sleep a day!",
            ////},
            //{
               //{ "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode(
                  //build_document_node_identifier(Entity::Type::ENTITY_TYPE_GIRAFFE)
                  //), 0 }
            //}
         //)
      //},
      //{ build_document_node_identifier(Entity::Type::ENTITY_TYPE_GIRAFFE),
         //new AllegroFlare::DialogTree::Nodes::Interparsable(
      ////{ "->document_giraffe", new AllegroFlare::DialogTree::Nodes::Interparsable(
            //LOTTIE,
            //build_need_to_document_dialog_pages(Entity::Type::ENTITY_TYPE_GIRAFFE),
            ////{
               ////"This is such an amazing creature!",
               ////"For the (em)Giraffe(/em), I'll need to write (em)3 lines of notes(/em)!",
            ////},
            //{
               //{ "next", new AllegroFlare::DialogTree::NodeOptions::GoToNode(
                  //build_emit_document_node_identifier(Entity::Type::ENTITY_TYPE_GIRAFFE)
                           ////"->emit_document_giraffe"
                  //), 0 }
            //}
         //)
      //},
      //{ "->emit_document_giraffe", new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
      //{ build_emit_document_node_identifier(Entity::Type::ENTITY_TYPE_GIRAFFE),
         //new AllegroFlare::DialogTree::Nodes::EmitGameEvent(
            //"document_giraffe",
            //"exit_dialog"
         //)
      //},


      //build_meet_node(Entity::Type::ENTITY_TYPE_GOAT),
      //build_document_node(Entity::Type::ENTITY_TYPE_GOAT),
      //build_emit_document_event_node(Entity::Type::ENTITY_TYPE_GOAT),



      { "inspect_apple", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE,
            {
               "A reeeeally nice juicy apple!",
               "There's so many delicious types of apples.",
               "My favorite is the cosmic crisp.",
            },
            { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         )
      },
      { "inspect_carrot", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE,
            {
               "Ooh an orange carrot.",
               "Unlike red carrots, the orange ones are the most common cultivar of Daucus carota sativus.",
               "This carrot looks really yummy right now.",
               "I forgot to eat my snack on the way down here.",
               "Mmm... sweet, delicious beta-carotene."
            },
            { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         )
      },
      { "inspect_red_carrot", new AllegroFlare::DialogTree::Nodes::Interparsable(LOTTIE,
            {
               "Ooo this is a nice red carrot.",
               "It's a variety of Daucus carota.",
               "This is the same species as regular carrots, just bred for that deep red color.",
               "I'll take a selfie with it to show my collegues."
            },
            { { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 } }
         )
      },
      { "friend_2_requirements", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_2,
            {
               "Normally this time of year is a time for celebration!",
               "But holy cow am I stressed!",
               "I've got to bake a cake, and, I've just got to win this competition.",
               "All the stress has got me locked right up! I can't seem to do anything.",
               "Maybe if I had a carrot!",
               "Yes! That's the thing!",
               "If I had a nice juicy carrot it would make my cake into perfection.",
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      { "friend_3_requirements", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_3,
            {
               "You know, last year's bake-a-thon was so much fun!",
               "I impressed everybody with my super unique mini cake.",
               "Everyone was so happy... but...",
               "I don't think anyone will like my cake this year.",
               "Everyone will think my cake is as uninteresting as a cake could possibly be!",
               "Only because this year's bake-a-thon has been turned into a competition!",
               "The stress of all this has me...",
               "AnXiOuSs!!",
               "*pfoo* *pfoo* *pfoo*",
               "Just breathe...",
               "Maybe if I had a red carrot it might be just the trick to fix my cake."
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      { "friend_1_requirements", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_1,
            {
               "Eeks! I'm so flummoxed!",
               "The annual bake-a-thon is happening soon and my cake is going to be a disaster!",
               "It was supposed to be a glorious event, what with the flower blooming and all.",
               "But now everyone's so stressed about it...",
               "...and it's stressing ME out!!!",
               "I wanted to hang out with Derek and make cakes, but he's all mopy so we can't do that.",
               "Maybe if I put a special ingredient in my cake, it'll cheer him up.",
               "He's always loved apples."
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      { "friend_1_requirements_met", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_1,
            {
               "Amazing!",
               "This apple is exactly what I need!",
               "Well... at least I think it is.",
               "The competition still has me stressed, but at least I can move forward!",
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      { "friend_2_requirements_met", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_2,
            {
               "Woo-hoo!",
               "This carrot is perfect for my cake!",
               "Meeehg... except I'm still stressed about the compeition.",
               "Thanks to you I at least have something I can work with.",
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      { "friend_3_requirements_met", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_3,
            {
               "Yes!!",
               "This big juicy red carrot is perfecto!",
               "Except one thing...",
               "I'm still going to have to make the cake for the competition.",
               "How stressful!",
               "I guess I better get going if I'm going to make this work."
            },
            {
               { "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            }
         )
      },
      //{ "friend_1_requirements_met", new AllegroFlare::DialogTree::Nodes::Interparsable(
            //DITTO,
            //{
               //"Amazing! This should fix my pie in no time! Thank you!"
            //},
            //{
               //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
            //}
         //)
      //},
      { "celebrate_won_game", new AllegroFlare::DialogTree::Nodes::Interparsable(
            FRIEND_1,
            {
               "Thank you so much!!",
               "You've saved my new groundbreaking layered apple pie!",
            },
            {
               { "->Reply", new AllegroFlare::DialogTree::NodeOptions::GoToNode("reply_to_won_game"), 0 },
            }
         )
      },
      { "reply_to_won_game", new AllegroFlare::DialogTree::Nodes::Interparsable(
            LOTTIE,
            {
               "Yay!!",
               "I'm so glad I could help!",
               "Best of luck to you in the competition!"
            },
            {
               { "Win game", new AllegroFlare::DialogTree::NodeOptions::GoToNode("emit_win_game"), 0 },
            }
         )
      },
     //AllegroFlare::DialogTree::NodeOptions::GoToNode
      { "emit_win_game", new AllegroFlare::DialogTree::Nodes::EmitGameEvent("win_game", "exit_dialog") },
      { "exit_dialog", new AllegroFlare::DialogTree::Nodes::ExitDialog() },
            //LOTTIE,
            //{
               //"I did it! What a party!"
            //},
            //{
               //{ "Exit", new AllegroFlare::DialogTree::NodeOptions::ExitDialog(), 0 }
               //{ "Win game", new AllegroFlare::DialogTree::Nodes::EmitGameEvent("win_game", "->mission_briefing") },
            //}
         //)
      //},
   });

   return result;
}


} // namespace Gameplay
} // namespace TINS2025


