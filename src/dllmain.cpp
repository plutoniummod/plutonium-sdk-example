#include "std_include.hpp"

#include <plutonium_sdk.hpp>

plutonium::sdk::iinterface* plutonium_ = nullptr;
using namespace plutonium::sdk::interfaces;
using namespace plutonium::sdk::types;

void gsc_method_test([[maybe_unused]] entref entity)
{
    plutonium_->logging()->info("GSC Method Test");
}

void gsc_function_test()
{
    plutonium_->logging()->info("GSC Function Test");
}

void client_command_function_test([[maybe_unused]] int client_num)
{
    plutonium_->logging()->info("Client Command Function Test");
}

void main_scheduler_test()
{
    plutonium_->logging()->info("Main Frame Test!");
}

scheduler::evaluation game_scheduler_test()
{
    plutonium_->logging()->info("Game Frame Test!");
    return scheduler::reschedule;
}

void on_dvar_init()
{
    plutonium_->logging()->info("Dvar System Initialized!");
}

void on_after_dvar_init()
{
    plutonium_->logging()->info("Game Dvars Finished Initializing!");
}

void on_game_init([[maybe_unused]] int level_time, [[maybe_unused]] int restart)
{
    plutonium_->logging()->info("Game Initialized!");
}

void on_game_shutdown([[maybe_unused]] int freeing_scripts)
{
    plutonium_->logging()->info("Game Shutting Down!");
}

void on_player_pre_connect([[maybe_unused]] unsigned int client_num)
{
    plutonium_->logging()->info("Player Connecting Once!");
}

void on_player_connect([[maybe_unused]] unsigned int client_num)
{
    plutonium_->logging()->info("Player Connected!");
}

void on_player_disconnect([[maybe_unused]] unsigned int client_num)
{
    plutonium_->logging()->info("Player Disconnected!");
}

void on_script_load()
{
    plutonium_->logging()->info("Scripts are loading!");
}

void on_script_execute()
{
    plutonium_->logging()->info("Scripts are executing!");
}

std::unique_ptr<plutonium::sdk::plugin> plugin_;

class plugin_impl final : public plutonium::sdk::plugin
{
public:
    const char* plugin_name() override
    {
        return "Plutonium SDK Example";
    }

    bool is_game_supported(const plutonium::sdk::game game) override
    {
        return game == plutonium::sdk::game::iw5;
    }

    void on_startup(plutonium::sdk::iinterface* interface_ptr, [[maybe_unused]] plutonium::sdk::game game) override
    {
        plutonium_ = interface_ptr;

        // Logging to the Plutonium console
        plutonium_->logging()->info("Plugin Startup Called\n");

        // Register a built-in GSC function
        plutonium_->gsc()->register_function("testPluginFunction", gsc_function_test);

        // Register a client command
        plutonium_->client_command()->register_client_command("testClientCommand", client_command_function_test);

        // Register a built-in GSC method
        plutonium_->gsc()->register_method("testPluginMethod", gsc_method_test);

        // Schedule a function to be called once on the main thread
        plutonium_->scheduler()->once(main_scheduler_test);

        // Schedule a function to be called on the game thread ever 1 second
        plutonium_->scheduler()->every(game_scheduler_test, 1000, scheduler::thread::game);

        // Add a callback when the dvar system is ready to register dvars
        plutonium_->callbacks()->on_dvar_init(on_dvar_init);

        // Add a callback when the dvar system is finished registering game dvars
        plutonium_->callbacks()->on_after_dvar_init(on_after_dvar_init);

        // Add a callback when the game server initialized
        plutonium_->callbacks()->on_game_init(on_game_init);

        // Add a callback when the game server shuts down
        plutonium_->callbacks()->on_game_shutdown(on_game_shutdown);

        // Add a callback when a player connects once
        plutonium_->callbacks()->on_player_pre_connect(on_player_pre_connect);

        // Add a callback when a player connects (including fast restarts)
        plutonium_->callbacks()->on_player_connect(on_player_connect);

        // Add a callback when a player disconnects
        plutonium_->callbacks()->on_player_disconnect(on_player_disconnect);

        // Add a callback when scripts are being loaded
        plutonium_->callbacks()->on_scripts_load(on_script_load);

        // Add a callback when scripts are being executed
        plutonium_->callbacks()->on_scripts_execute(on_script_execute);
    }

    void on_shutdown() override
    {
    }
};

PLUTONIUM_API plutonium::sdk::plugin* on_initialize()
{
    return (plugin_ = std::make_unique<plugin_impl>()).get();
}

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID)
{
    return TRUE;
}
