#include "HUD.h"
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

HUD::HUD()
{
    if (Engine::get_singleton()->is_editor_hint())
        set_process_mode(godot::Node::PROCESS_MODE_DISABLED);

}

HUD::~HUD()
{

}

void HUD::_ready()
{
    if (Engine::get_singleton()->is_editor_hint())
        return;

    _coinsText = get_node<Label>("Coins");
    connect("coins_collected", Callable(this, "OnCoinCollected"));
}

void HUD::OnCoinCollected(int coins)
{
    if(_coinsText != nullptr)
        _coinsText->set_text(godot::String(Variant(coins)));

}

void HUD::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("OnCoinCollected", "coins"), &HUD::OnCoinCollected);
    ADD_SIGNAL(MethodInfo("coins_collected", PropertyInfo(Variant::INT, "coins")));

}