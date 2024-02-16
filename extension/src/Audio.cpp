// #include "Audio.h"
// #include <godot_cpp/classes/engine.hpp>
// #include <godot_cpp/core/class_db.hpp>
// #include <godot_cpp/classes/resource_loader.hpp>
// #include <godot_cpp/variant/utility_functions.hpp>

// #include "GameConstants.h"

// using namespace godot;

// Audio::Audio()
// {
//     if (Engine::get_singleton()->is_editor_hint())
//         set_process_mode(godot::Node::PROCESS_MODE_DISABLED);


// }

// Audio::~Audio()
// {
//     if(_queue != nullptr) memdelete(_queue);
//     if(_player != nullptr) memdelete(_player);

// }

// void Audio::_ready()
// {
//      if (Engine::get_singleton()->is_editor_hint())
//         return;
    
//     _queue = memnew(godot::Array);
    
//     for(int i = 0; i < max_players; i++)
//     {
//         _player = memnew(AudioStreamPlayer);
//         _player->set_volume_db(-10);
//         _player->set_bus(GameConstants::AUDIO_BUS);

//         add_child(_player);
//     }

//     connect("audio_play", Callable(this, "Play"));
// }


// void Audio::_process(double delta)
// {
//      if (Engine::get_singleton()->is_editor_hint())
//         return;
    
//     if(_queue == nullptr || _player == nullptr)
//         return;

//     if(_queue->is_empty() != false)
//     {
//     //     godot::String path = _queue->front();
//     //     Ref<AudioStream> stream = ResourceLoader::get_singleton()->load(path);
//     //    _player->set_stream(stream);

//         _queue->pop_front();
//     }
// }

// void Audio::Play(godot::String path)
// {
//     UtilityFunctions::print("Adding sound !");
//     if(_queue != nullptr)
//         _queue->push_back(path);
// }


// void Audio::_bind_methods()
// {
//     ClassDB::bind_method(D_METHOD("Play", "path"), &Audio::Play);
    
//     ADD_SIGNAL(MethodInfo("audio_play", PropertyInfo(Variant::STRING, "path")));

// }