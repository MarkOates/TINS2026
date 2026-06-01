

#include <TINS2025/Entity.hpp>

#include <allegro5/allegro_primitives.h>
#include <map>


namespace TINS2025
{


Entity::Entity()
   : sprite(nullptr)
   , model(nullptr)
   , name("[unset-name]")
   , tmj_id(0)
   , type(TINS2025::Entity::ENTITY_TYPE_UNDEF)
   , animation_mode(TINS2025::Entity::ANIMATION_MODE_STANDING)
   , distance_to_player(9999.0f)
   , aabb2d({})
   , flags(0)
{
}


Entity::~Entity()
{
}


std::string Entity::to_string(Type value, bool throw_on_error)
{
   if (value == Type::ENTITY_TYPE_UNDEF) return "entity_type_undef";
   if (value == Type::ENTITY_TYPE_PLAYER) return "entity_type_player";
   if (value == Type::ENTITY_TYPE_FRIEND_1) return "entity_type_friend_1";
   if (value == Type::ENTITY_TYPE_FRIEND_2) return "entity_type_friend_2";
   if (value == Type::ENTITY_TYPE_FRIEND_3) return "entity_type_friend_3";
   if (value == Type::ENTITY_TYPE_APPLE) return "entity_type_apple";
   if (value == Type::ENTITY_TYPE_CARROT) return "entity_type_carrot";
   if (value == Type::ENTITY_TYPE_RED_CARROT) return "entity_type_red_carrot";
   if (value == Type::ENTITY_TYPE_DIALOG_TRIGGER) return "entity_type_dialog_trigger";
   if (value == Type::ENTITY_TYPE_DIALOG_TRIGGER_1) return "entity_type_dialog_trigger_1";
   if (value == Type::ENTITY_TYPE_DIALOG_TRIGGER_2) return "entity_type_dialog_trigger_2";
   if (value == Type::ENTITY_TYPE_DIALOG_TRIGGER_3) return "entity_type_dialog_trigger_3";
   if (value == Type::ENTITY_TYPE_DIALOG_TRIGGER_4) return "entity_type_dialog_trigger_4";
   if (value == Type::ENTITY_TYPE_DIALOG_TRIGGER_5) return "entity_type_dialog_trigger_5";
   if (value == Type::ENTITY_TYPE_BUNBUCKS_CAKE) return "entity_type_bunbucks_cake";
   if (value == Type::ENTITY_TYPE_CAKE_1) return "entity_type_cake_1";
   if (value == Type::ENTITY_TYPE_CAKE_2) return "entity_type_cake_2";
   if (value == Type::ENTITY_TYPE_CAKE_3) return "entity_type_cake_3";
   if (value == Type::ENTITY_TYPE_COMPOSITE_CAKE) return "entity_type_composite_cake";
   if (value == Type::ENTITY_TYPE_THE_PLANT) return "entity_type_the_plant";
   if (value == Type::ENTITY_TYPE_CAMERA_0) return "entity_type_camera_0";
   if (value == Type::ENTITY_TYPE_CAMERA_1) return "entity_type_camera_1";
   if (value == Type::ENTITY_TYPE_CAMERA_2) return "entity_type_camera_2";
   if (value == Type::ENTITY_TYPE_CAMERA_3) return "entity_type_camera_3";
   if (value == Type::ENTITY_TYPE_CAMERA_4) return "entity_type_camera_4";
   if (value == Type::ENTITY_TYPE_CAMERA_5) return "entity_type_camera_5";
   if (value == Type::ENTITY_TYPE_CAMERA_6) return "entity_type_camera_6";
   if (value == Type::ENTITY_TYPE_CAMERA_7) return "entity_type_camera_7";
   if (value == Type::ENTITY_TYPE_CAMERA_8) return "entity_type_camera_8";
   if (value == Type::ENTITY_TYPE_CAMERA_9) return "entity_type_camera_9";
   if (value == Type::ENTITY_TYPE_LOCATION_POINT) return "entity_type_location_point";
   if (value == Type::ENTITY_TYPE_NOTEBOOK_PAGE) return "entity_type_notebook_page";
   if (value == Type::ENTITY_TYPE_GIRAFFE) return "entity_type_giraffe";
   if (value == Type::ENTITY_TYPE_GOAT) return "entity_type_goat";
   if (value == Type::ENTITY_TYPE_LEOPARD) return "entity_type_leopard";
   if (value == Type::ENTITY_TYPE_TIGER) return "entity_type_tiger";
   if (value == Type::ENTITY_TYPE_ZEBRAH) return "entity_type_zebrah";
   // TODO: Implement "throw_on_error" argument
   return "";
}


Entity::Type Entity::from_string(std::string value, bool throw_on_error)
{
   if (value == "entity_type_undef") return Type::ENTITY_TYPE_UNDEF;
   if (value == "entity_type_player") return Type::ENTITY_TYPE_PLAYER;
   if (value == "entity_type_friend_1") return Type::ENTITY_TYPE_FRIEND_1;
   if (value == "entity_type_friend_2") return Type::ENTITY_TYPE_FRIEND_2;
   if (value == "entity_type_friend_3") return Type::ENTITY_TYPE_FRIEND_3;
   if (value == "entity_type_apple") return Type::ENTITY_TYPE_APPLE;
   if (value == "entity_type_carrot") return Type::ENTITY_TYPE_CARROT;
   if (value == "entity_type_red_carrot") return Type::ENTITY_TYPE_RED_CARROT;
   if (value == "entity_type_dialog_trigger") return Type::ENTITY_TYPE_DIALOG_TRIGGER;
   if (value == "entity_type_dialog_trigger_1") return Type::ENTITY_TYPE_DIALOG_TRIGGER_1;
   if (value == "entity_type_dialog_trigger_2") return Type::ENTITY_TYPE_DIALOG_TRIGGER_2;
   if (value == "entity_type_dialog_trigger_3") return Type::ENTITY_TYPE_DIALOG_TRIGGER_3;
   if (value == "entity_type_dialog_trigger_4") return Type::ENTITY_TYPE_DIALOG_TRIGGER_4;
   if (value == "entity_type_dialog_trigger_5") return Type::ENTITY_TYPE_DIALOG_TRIGGER_5;
   if (value == "entity_type_bunbucks_cake") return Type::ENTITY_TYPE_BUNBUCKS_CAKE;
   if (value == "entity_type_cake_1") return Type::ENTITY_TYPE_CAKE_1;
   if (value == "entity_type_cake_2") return Type::ENTITY_TYPE_CAKE_2;
   if (value == "entity_type_cake_3") return Type::ENTITY_TYPE_CAKE_3;
   if (value == "entity_type_composite_cake") return Type::ENTITY_TYPE_COMPOSITE_CAKE;
   if (value == "entity_type_the_plant") return Type::ENTITY_TYPE_THE_PLANT;
   if (value == "entity_type_camera_0") return Type::ENTITY_TYPE_CAMERA_0;
   if (value == "entity_type_camera_1") return Type::ENTITY_TYPE_CAMERA_1;
   if (value == "entity_type_camera_2") return Type::ENTITY_TYPE_CAMERA_2;
   if (value == "entity_type_camera_3") return Type::ENTITY_TYPE_CAMERA_3;
   if (value == "entity_type_camera_4") return Type::ENTITY_TYPE_CAMERA_4;
   if (value == "entity_type_camera_5") return Type::ENTITY_TYPE_CAMERA_5;
   if (value == "entity_type_camera_6") return Type::ENTITY_TYPE_CAMERA_6;
   if (value == "entity_type_camera_7") return Type::ENTITY_TYPE_CAMERA_7;
   if (value == "entity_type_camera_8") return Type::ENTITY_TYPE_CAMERA_8;
   if (value == "entity_type_camera_9") return Type::ENTITY_TYPE_CAMERA_9;
   if (value == "entity_type_location_point") return Type::ENTITY_TYPE_LOCATION_POINT;
   if (value == "entity_type_notebook_page") return Type::ENTITY_TYPE_NOTEBOOK_PAGE;
   if (value == "entity_type_giraffe") return Type::ENTITY_TYPE_GIRAFFE;
   if (value == "entity_type_goat") return Type::ENTITY_TYPE_GOAT;
   if (value == "entity_type_leopard") return Type::ENTITY_TYPE_LEOPARD;
   if (value == "entity_type_tiger") return Type::ENTITY_TYPE_TIGER;
   if (value == "entity_type_zebrah") return Type::ENTITY_TYPE_ZEBRAH;
   throw std::runtime_error("Blast/Cpp/EnumClass: ERROR: Could not find enum for \" + value + \"");
}


std::string Entity::type_to_string()
{
   static std::map<uint32_t, std::string> names = {
      { ENTITY_TYPE_GIRAFFE, "Giraffe" },
      { ENTITY_TYPE_GOAT, "Goat" },
      { ENTITY_TYPE_LEOPARD, "Leopard", },
      { ENTITY_TYPE_TIGER, "Tiger", },
      { ENTITY_TYPE_ZEBRAH, "Zebrah", },
   };
   if (names.count(type) == 0)
   {
      throw std::runtime_error("AAAAAAAAAAAAA! Entity: No name found for this entity type.");
   }
   return names[type];
}

void Entity::draw()
{
   // Draw the box
   al_draw_rectangle(
      aabb2d.get_x(),
      aabb2d.get_y(),
      aabb2d.get_x()+aabb2d.get_w(),
      aabb2d.get_y()+aabb2d.get_h(),
      ALLEGRO_COLOR{1, 1, 1, 1},
      1.0
   );

   // Draw the sprite (bottom centered)
   if (sprite)
   {
      ALLEGRO_BITMAP *bitmap = sprite;

      float center_x = aabb2d.get_x() + aabb2d.get_w() / 2.0f;
      float center_y = aabb2d.get_y() + aabb2d.get_h() / 2.0f;

      float bitmap_w = al_get_bitmap_width(bitmap);
      float bitmap_h = al_get_bitmap_height(bitmap);

      float draw_x = center_x - bitmap_w / 2.0f;
      float draw_y = center_y - bitmap_h;

      al_draw_bitmap(bitmap, draw_x, draw_y, 0);
   }
}


} // namespace TINS2025


