#ifndef VIEW_CLASS
#define VIEW_CLASS

#include <godot_cpp/variant/basis.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/input.hpp>
#include "GameConstants.h"

using namespace godot;

class View : public Node3D
{
    GDCLASS(View, Node3D)

    private:
        Camera3D* _camera;
        godot::Input* m_input;
        Vector3 _cameraRotation;
        float _zoom;
        void handleInput(double delta);        

    public:
        View();
        ~View();

        Node3D* Target;
        float MinZoom;
        float MaxZoom;
        float ZoomSpeed;
        float RotationSpeed;

        void _ready() override;
        void _physics_process(double delta) override;

        Node3D* GetTarget();
        void SetTarget(Node3D* target);

        float GetMinZoom();
        void SetMinZoom(float zoom);

        float GetMaxZoom();
        void SetMaxZoom(float zoom);

        float GetZoomSpeed();
        void SetZoomSpeed(float zoom);

        float GetRotationSpeed();
        void SetRotationSpeed(float speed);
        
    protected:
        static void _bind_methods();

};


#endif