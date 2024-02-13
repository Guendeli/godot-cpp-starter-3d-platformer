#ifndef COIN_CLASS
#define COIN_CLASS

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/mesh_instance3d.hpp>
#include <godot_cpp/classes/cpu_particles3d.hpp>
#include <godot_cpp/classes/area3d.hpp>

using namespace godot;

class Coin : public Area3D
{
    GDCLASS(Coin, Area3D)

    private:
        double _time;
        bool _grabbed;
        MeshInstance3D* _mesh;
        CPUParticles3D* _emitter;


    public:
        Coin();
        ~Coin();

        void _ready() override;
        void _process(double delta) override;
        void OnBodyEntered(Node3D* body);

    protected:
        static void _bind_methods();
};






#endif