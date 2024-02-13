#ifndef PLATFORM_CLASS
#define PLATFORM_CLASS

#include <godot_cpp/variant/basis.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/area3d.hpp>

using namespace godot;

class Platform : public Node3D
{
    GDCLASS(Platform, Node3D)

    private:
        Area3D* _area;
        bool _falling;
        float _gravity;        
    public:
        Platform();
        ~Platform();

        void _ready() override;
        void _process(double delta) override;
        void OnBodyEntered(Node3D* body);

    protected:
        static void _bind_methods();
};


#endif