#ifndef CLOUD_CLASS
#define CLOUD_CLASS

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

using namespace godot;

class Cloud : public Node3D {
    GDCLASS(Cloud, Node3D)


    private:
        float _time;
        float _randomVelocity;
        float _randomTime;
        RandomNumberGenerator* _rnd;

    public:
        Cloud();
        ~Cloud();

        void _ready() override;
        void _process(double delta) override;

    protected:
        static void _bind_methods();

};

#endif