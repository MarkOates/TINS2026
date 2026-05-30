#pragma once


#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Physics/AABB2D.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>


namespace TINS2025
{
   class Entity
   {
   public:

      enum Flags
      {
         FLAG_NONE = 0x0000,
         FLAG_INACTIVE = 0x0001,
         FLAG_HIDDEN = 0x0002,
         FLAG_COLLIDES_WITH_PLAYER = 0x0004,
         FLAG_COLLIDES_WITH_TILEMAP = 0x0008,
         FLAG_TRACKS_DISTANCE_TO_PLAYER = 0x0010,
         FLAG_IS_COMMON_ANIMAL = 0x0020,
         FLAG_IS_UNCOMMON_ANIMAL = 0x0040,
         FLAG_IS_RARE_ANIMAL = 0x0080,
      };
      enum Type
      {
         ENTITY_TYPE_UNDEF = 0,
         ENTITY_TYPE_PLAYER,
         ENTITY_TYPE_FRIEND_1,
         ENTITY_TYPE_FRIEND_2,
         ENTITY_TYPE_FRIEND_3,
         ENTITY_TYPE_APPLE,
         ENTITY_TYPE_CARROT,
         ENTITY_TYPE_RED_CARROT,
         ENTITY_TYPE_DIALOG_TRIGGER_1,
         ENTITY_TYPE_DIALOG_TRIGGER_2,
         ENTITY_TYPE_DIALOG_TRIGGER_3,
         ENTITY_TYPE_DIALOG_TRIGGER_4,
         ENTITY_TYPE_DIALOG_TRIGGER_5,
         ENTITY_TYPE_BUNBUCKS_CAKE,
         ENTITY_TYPE_CAKE_1,
         ENTITY_TYPE_CAKE_2,
         ENTITY_TYPE_CAKE_3,
         ENTITY_TYPE_COMPOSITE_CAKE,
         ENTITY_TYPE_THE_PLANT,
         ENTITY_TYPE_CAMERA_0,
         ENTITY_TYPE_CAMERA_1,
         ENTITY_TYPE_CAMERA_2,
         ENTITY_TYPE_CAMERA_3,
         ENTITY_TYPE_CAMERA_4,
         ENTITY_TYPE_CAMERA_5,
         ENTITY_TYPE_CAMERA_6,
         ENTITY_TYPE_CAMERA_7,
         ENTITY_TYPE_CAMERA_8,
         ENTITY_TYPE_CAMERA_9,
         ENTITY_TYPE_NOTEBOOK_PAGE,
         ENTITY_TYPE_GIRAFFE,
         ENTITY_TYPE_GOAT,
         ENTITY_TYPE_LEOPARD,
         ENTITY_TYPE_TIGER,
         ENTITY_TYPE_ZEBRAH,
      };
      enum AnimationMode
      {
         ANIMATION_MODE_UNDEF = 0,
         ANIMATION_MODE_STANDING,
         ANIMATION_MODE_WALKING_WOBBLY,
         ANIMATION_MODE_JUMPING_IN_EXCITEMENT,
      };
   private:

   protected:


   public:
      ALLEGRO_BITMAP* sprite;
      AllegroFlare::Model3D* model;
      uint32_t type;
      uint32_t animation_mode;
      float distance_to_player;
      AllegroFlare::Physics::AABB2D aabb2d;
      uint32_t flags;
      Entity();
      ~Entity();

      static std::string to_string(Type value=Type::ENTITY_TYPE_UNDEF, bool throw_on_error=true);
      std::string type_to_string();
      void draw();
   };
}



