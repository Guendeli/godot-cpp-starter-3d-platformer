#ifndef HUD_CLASS
#define HUD_CLASS

#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/classes/canvas_layer.hpp>

using namespace godot;

class HUD : public CanvasLayer
{
    GDCLASS(HUD, CanvasLayer)

    private:
        Label* _coinsText;

    public:
        HUD();
        ~HUD();

        void _ready() override;
        void OnCoinCollected(int coins);

    protected:
        static void _bind_methods();

};

#endif