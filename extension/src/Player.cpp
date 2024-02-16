#include "Player.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/input.hpp>
#include "GameConstants.h"

using namespace godot;

Player::Player()
{
     if (Engine::get_singleton()->is_editor_hint()){
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);
        return;
     }

    m_moveSpeed = 200.0;
    _jumpStr = 6;
    _maxJumps = 2;
    _currentJumps = 2;
}

Player::~Player()
{
    
}

void Player::_ready()
{
    if (Engine::get_singleton()->is_editor_hint())
         return;

    UtilityFunctions::print("Player Ready");
    View = get_node<Node3D>("/root/Main/View");
    _visual = get_node<Node3D>("Character");
    _animator = get_node<AnimationPlayer>("Character/AnimationPlayer");
	_trail = get_node<CPUParticles3D>("ParticlesTrail");
	_audioSource = get_node<AudioStreamPlayer>("SoundFootsteps");

}

void Player::_physics_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
         return;

    m_input = Input::get_singleton();
    
    handleInput(delta);
    handleGravity(delta);
    handleAnimations(delta);

    Vector3 appliedVelocity = Vector3(0,0,0);
    appliedVelocity = get_velocity().lerp(_movementVelocity, delta * 10);
    appliedVelocity.y -= _gravity;
    set_velocity(appliedVelocity);

    move_and_slide();

    // apply rotation

    if(get_velocity().length() > 0)
    {
        _direction = Vector2(get_velocity().z, get_velocity().x).angle();
    }

    Vector3 rotation = Vector3(0,0,0);
    rotation.y = godot::Math::lerp_angle((float)get_rotation().y, _direction, (float)delta * 10);
    set_rotation(rotation);

    // // apply scale

    if(_visual != nullptr)
    {
        _visual->set_scale(get_scale().lerp(Vector3(1,1,1), delta * 10));

        if(is_on_floor() && _gravity > 2 && _previouslyFloored == false)
        {
            _visual->set_scale(Vector3(1.25,0.75,1.25));
        }

        _previouslyFloored = is_on_floor();
    }
    
}

void Player::handleInput(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
         return;

    if(m_input == nullptr || View == nullptr)
        return;

    Vector3 inputVec = Vector3(0,0,0);

    inputVec.x = m_input->get_axis(GameConstants::INP_AXIS_MOVE_LEFT, GameConstants::INP_AXIS_MOVE_RIGHT);
    inputVec.z = m_input->get_axis(GameConstants::INP_AXIS_MOVE_FWRD, GameConstants::INP_AXIS_MOVE_BACK);

    inputVec = inputVec.rotated(Vector3(0,1,0), View->get_rotation().y).normalized();
    _movementVelocity =  inputVec * m_moveSpeed * delta;

    if(m_input->is_action_just_pressed(GameConstants::INP_ACTION_JUMP))
    {
        UtilityFunctions::print("Trying to jump. current jumps = %d", _currentJumps);
        if(_currentJumps <= 0)
            return;
        

        jump();
        emit_signal("audio_play", GameConstants::SFX_JUMP);
    }
}

void Player::handleGravity(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
         return;

    _gravity += 25 * delta;
    if(is_on_floor())
    {
        if(_gravity > 0)
        {
            _gravity = 0;
            _currentJumps = _maxJumps;
        }
    }
    
}

void Player::handleAnimations(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
         return;

    if(_animator == nullptr)
        return;

    _trail->set_emitting(false);
    _audioSource->set_stream_paused(true);

    if(is_on_floor())
    {
        if(godot::Math::abs(get_velocity().x > 1 ||
        godot::Math::abs(get_velocity().z > 1)))
        {
            _animator->play("walk");
        } else {
            _animator->play("idle");
        }
    } else {
        _animator->play("jump");
    }
}

void Player::jump()
{
    if (Engine::get_singleton()->is_editor_hint())
         return;

    _gravity = -_jumpStr;
    
    if(_visual != nullptr)
        _visual->set_scale(godot::Vector3(0.5,1.5,0.5));
    
    _currentJumps -= 1;
}

// GETTERS AND SETTERS

Node3D* Player::GetView()
{
    UtilityFunctions::print("Calling GET VIEW");
    return View;
}

void Player::SetView(Node3D* view)
{
    UtilityFunctions::print("Calling SET VIEW");
    if(view != nullptr)
        View = view;
}


// BIND METHODS

void Player::_bind_methods()
{
    //ClassDB::bind_method(D_METHOD("SetView", "view"), &Player::SetView);
    //ClassDB::bind_method(D_METHOD("GetView"), &Player::GetView);
    //ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "View", PROPERTY_HINT_NODE_TYPE, "Node3D"),"SetView","GetView");

    // ClassDB::bind_method(D_METHOD("SetMaxJumps", "jumps"), &Player::SetMaxJumps);
    // ClassDB::bind_method(D_METHOD("GetMaxJumps"), &Player::GetMaxJumps);
    // ADD_PROPERTY(PropertyInfo(Variant::INT, "MaxJumps"),"SetMaxJumps","GetMaxJumps");

    // ClassDB::bind_method(D_METHOD("SetJumpStr", "str"), &Player::SetJumpStr);
    // ClassDB::bind_method(D_METHOD("GetJumpStr"), &Player::GetJumpStr);
    // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "JumpStr"),"SetJumpStr","GetJumpStr");

    // ClassDB::bind_method(D_METHOD("SetMoveSpeed", "speed"), &Player::SetMoveSpeed);
    // ClassDB::bind_method(D_METHOD("GetMoveSpeed"), &Player::GetMoveSpeed);
    // ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "MoveSpeed"),"SetMoveSpeed","GetMoveSpeed");

}