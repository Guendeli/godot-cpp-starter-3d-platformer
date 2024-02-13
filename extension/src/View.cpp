#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>
#include <godot_cpp/classes/input.hpp>
#include "View.h"
#include "GameConstants.h"

using namespace godot;

View::View()
{
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);

    _zoom = 10.0;
    _cameraRotation = godot::Vector3(0,0,0);

    MinZoom = 4;
    MaxZoom = 16;
    ZoomSpeed = 10;
    RotationSpeed = 120;
}

View::~View()
{

}

void View::_ready()
{
    if (Engine::get_singleton()->is_editor_hint())
        return;

    _camera = get_node<Camera3D>("Camera");
    _cameraRotation = get_rotation_degrees();
    m_input = godot::Input::get_singleton();

}

void View::_physics_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint())
        return;

    if(Target == nullptr || _camera == nullptr)
        return;

    Vector3 pos = get_position().lerp(Target->get_position(), delta * 4);
    set_position(pos);

    Vector3 rotDeg = get_rotation_degrees().lerp(_cameraRotation, delta * 6);
    set_rotation_degrees(rotDeg);

    Vector3 camPos = _camera->get_position().lerp(Vector3(0,0,_zoom), delta * 8);
    _camera->set_position(camPos);

    handleInput(delta);

}

void View::handleInput( double delta)
{
    if(m_input == nullptr)
        return;
        
    Vector3 input = Vector3(0,0,0);

    input.x = m_input->get_axis(GameConstants::INP_AXIS_CAM_UP, GameConstants::INP_AXIS_CAM_DOWN);
    input.y = m_input->get_axis(GameConstants::INP_AXIS_CAM_LEFT, GameConstants::INP_AXIS_CAM_RIGHT);

    _cameraRotation += input.limit_length(1.0) * RotationSpeed * delta;

    _zoom += m_input->get_axis(GameConstants::INP_AXIS_ZOOM_IN, GameConstants::INP_AXIS_ZOOM_OUT) * ZoomSpeed * delta;

    _zoom = godot::Math::clamp(_zoom, MinZoom, MaxZoom);

}

float View::GetMinZoom()
{
    return MinZoom;
}

void View::SetMinZoom(float zoom)
{
    MinZoom = zoom;
}

float View::GetMaxZoom()
{
    return MaxZoom;
}

void View::SetMaxZoom(float zoom)
{
    MaxZoom = zoom;
}

float View::GetZoomSpeed()
{
    return ZoomSpeed;
}

void View::SetZoomSpeed(float zoom)
{
    ZoomSpeed = zoom;
}

float View::GetRotationSpeed()
{
    return RotationSpeed;
}

void View::SetRotationSpeed(float speed)
{
    RotationSpeed = speed;
}

Node3D* View::GetTarget()
{
    return Target;
}

void View::SetTarget(Node3D* target)
{
    Target = target;
}


void View::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("SetTarget", "target"), &View::SetTarget);
    ClassDB::bind_method(D_METHOD("SetRotationSpeed", "speed"), &View::SetRotationSpeed);
    ClassDB::bind_method(D_METHOD("SetZoomSpeed", "zoom"), &View::SetZoomSpeed);
    ClassDB::bind_method(D_METHOD("SetMaxZoom", "zoom"), &View::SetMaxZoom);
    ClassDB::bind_method(D_METHOD("SetMinZoom", "zoom"), &View::SetMinZoom);

    ClassDB::bind_method(D_METHOD("GetMinZoom"), &View::GetMinZoom);
    ClassDB::bind_method(D_METHOD("GetMaxZoom"), &View::GetMaxZoom);
    ClassDB::bind_method(D_METHOD("GetZoomSpeed"), &View::GetZoomSpeed);
    ClassDB::bind_method(D_METHOD("GetRotationSpeed"), &View::GetRotationSpeed);
    ClassDB::bind_method(D_METHOD("GetTarget"), &View::GetTarget);

    ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "Target", PROPERTY_HINT_NODE_TYPE, "Node3D"),"SetTarget","GetTarget");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "RotationSpeed"),"SetRotationSpeed","GetRotationSpeed");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "MinZoom"),"SetMinZoom","GetMinZoom");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "MaxZoom"),"SetMaxZoom","GetMaxZoom");
    ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "ZoomSpeed"),"SetZoomSpeed","GetZoomSpeed");

}