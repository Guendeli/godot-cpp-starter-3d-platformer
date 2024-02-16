#include <godot_cpp/variant/basis.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "Coin.h"
#include "GameConstants.h"

using namespace godot;

Coin::Coin()
{
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);

    _grabbed = false;
    _time = 0;
}

Coin::~Coin()
{

}

void Coin::_ready()
{
    if (Engine::get_singleton()->is_editor_hint())
        return;
    
    _mesh = get_node<MeshInstance3D>("Mesh");
    _emitter = get_node<CPUParticles3D>("Particles");
    //connect("body_entered", Callable(this, "OnBodyEntered"));
}

void Coin::_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
        return;
    
    Vector3 pos = get_position();

    pos.y += godot::Math::cos(_time * 5) * 1 * delta;

    set_position(pos);
    _time += delta;
}

// Called from "body_entered" signal in the Godot Node inspector
void Coin::OnBodyEntered(Node3D* body)
{
    if(!_grabbed)
    {
        // Collect Coin
        emit_signal("audio_play", GameConstants::SFX_COIN);
        _mesh->queue_free();
        _emitter->set_emitting(false);
        _grabbed = true;
    }
}

void Coin::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("OnBodyEntered", "body"), &Coin::OnBodyEntered);
}