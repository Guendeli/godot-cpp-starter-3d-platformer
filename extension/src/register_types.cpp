#include "register_types.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>
#include "Cloud.h"
#include "Coin.h"
#include "Platform.h"
#include "View.h"

using namespace godot;

namespace FlecsModule
{
	void initialize(ModuleInitializationLevel p_level)
	{
		if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		{
			return;
		}
		ClassDB::register_class<Cloud>();
		ClassDB::register_class<Coin>();
		ClassDB::register_class<Platform>();
		ClassDB::register_class<View>();
	}

	void uninitialize(ModuleInitializationLevel p_level)
	{
		if (p_level != MODULE_INITIALIZATION_LEVEL_SCENE)
		{
			return;
		}
	}

	extern "C"
	{
		GDExtensionBool GDE_EXPORT game_library_init(GDExtensionInterfaceGetProcAddress p_get_proc_address, GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
		{
			GDExtensionBinding::InitObject init_obj(p_get_proc_address, p_library, r_initialization);

			init_obj.register_initializer(initialize);
			init_obj.register_terminator(uninitialize);
			init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_SCENE);

			return init_obj.init();
		}
	}
}