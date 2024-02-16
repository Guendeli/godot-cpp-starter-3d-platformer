#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "Platform.h"
#include "GameConstants.h"

using namespace godot;

Platform::Platform()
{
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);
    
    _falling = false;
    _gravity = 0;

}

Platform::~Platform()
{

}

void Platform::_ready()
{
    _area = get_node<Area3D>("Area3D");
}

void Platform::_process(double delta)
{
    Vector3 pos = get_position();
    set_scale(get_scale().lerp(godot::Vector3(1,1,1), delta * 10));
    pos.y -= _gravity * delta;

    if(pos.y < -10)
        queue_free();

    if(_falling)
    {
        _gravity += 0.25;
    }

    set_position(pos);
}

// to be called from "body_entered" signal from the Node's inspector
void Platform::OnBodyEntered(Node3D* body)
{
    if(!_falling)
    {
        emit_signal("audio_play",GameConstants::SFX_FALL);

        set_scale(godot::Vector3(1.25,1,1.25));
    }

    _falling = true;
}

void Platform::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("OnBodyEntered", "body"), &Platform::OnBodyEntered);
}