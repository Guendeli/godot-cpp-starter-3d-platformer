#include <godot_cpp/variant/basis.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include "Cloud.h"

using namespace godot;

Cloud::Cloud()
{
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);
}

Cloud::~Cloud()
{
    if(_rnd != nullptr)
        memdelete(_rnd);
}

void Cloud::_ready() 
{

    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);

    _rnd = memnew(RandomNumberGenerator);
    _time = 0;
    _randomTime = _rnd->randf_range(0.1,2.0);
    _randomVelocity = _rnd->randf_range(0.1,2.0);    
}

void Cloud::_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
        return;
    godot::Vector3 pos = get_position();

    pos.y += godot::Math::cos(_time * _randomTime) * _randomVelocity * delta;

    set_position(pos);

    _time += delta;
}

void Cloud::_bind_methods()
{
    // ClassDB::bind_method(D_METHOD("_ready"), &Cloud::_ready);
    // ClassDB::bind_method(D_METHOD("_process"), &Cloud::_process);
}

