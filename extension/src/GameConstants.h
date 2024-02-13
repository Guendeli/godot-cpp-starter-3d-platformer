#ifndef GAME_CONSTS
#define GAME_CONSTS

#pragma once

#include <string>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;


struct GameConstants
{
    public:
        static inline const char* AUDIO_BUS = "bus";
        static inline const char* SFX_JUMP = "res://sounds/jump.ogg";
        static inline const char* SFX_COIN = "res://sounds/coin.ogg";
        static inline const char* SFX_FALL = "res://sounds/fall.ogg";

        static inline const char* INP_AXIS_MOVE_LEFT = "move_left";
        static inline const char* INP_AXIS_MOVE_RIGHT = "move_right";
        static inline const char* INP_AXIS_MOVE_FWRD = "move_forward";
        static inline const char* INP_AXIS_MOVE_BACK = "move_back";
        static inline const char* INP_ACTION_JUMP = "jump";

        static inline const char* INP_AXIS_CAM_LEFT = "camera_left";
        static inline const char* INP_AXIS_CAM_RIGHT = "camera_right";
        static inline const char* INP_AXIS_CAM_DOWN = "camera_down";
        static inline const char* INP_AXIS_CAM_UP = "camera_up";
    
        static inline const char* INP_AXIS_ZOOM_IN = "zoom_in";
        static inline const char* INP_AXIS_ZOOM_OUT = "zoom_out";
};

#endif