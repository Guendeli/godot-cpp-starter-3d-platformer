#ifndef PLAYER_CLASS
#define PLAYER_CLASS


#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/physics_body3d.hpp>
#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/classes/animation_player.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/cpu_particles3d.hpp>
#include <godot_cpp/classes/input.hpp>

using namespace godot;

class Player : public CharacterBody3D
{
    GDCLASS(Player, CharacterBody3D)

    private:

        

        int _currentJumps;

        godot::Vector3 _movementVelocity;
        float _direction;
        float _gravity;
        bool _previouslyFloored;
        int _totalCoins;

        Node3D* _visual;
        godot::AnimationPlayer* _animator;
        godot::AudioStreamPlayer* _audioSource;
        godot::CPUParticles3D* _trail;

        void handleInput(double delta);
        void handleGravity(double delta);
        void handleAnimations(double delta);
        void jump();

        godot::Input* m_input;
    public:
        Player();
        ~Player();

        Node3D* View;
        float _jumpStr;
        int _maxJumps;
        float m_moveSpeed;



        void _ready() override;
        void _physics_process(double delta) override;

        Node3D* GetView();
        void SetView(Node3D* view);

    protected:
        static void _bind_methods();
}; 


#endif