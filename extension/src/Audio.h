// #ifndef AUDIO_CLASS
// #define AUDIO_CLASS

// #include <godot_cpp/core/defs.hpp>
// #include <godot_cpp/classes/audio_stream_player.hpp>
// #include <godot_cpp/classes/node.hpp>

// using namespace godot;

// class Audio : public Node
// {
//     GDCLASS(Audio, Node)

//     private:
//         int max_players;
//         AudioStreamPlayer* _player;
//         godot::Array* _queue;
        
//     public:
//         Audio();
//         ~Audio();

//         void _ready() override;
//         void _process(double delta) override;
//         void Play(godot::String path);
//     protected:
//         static void _bind_methods();

// };

// #endif