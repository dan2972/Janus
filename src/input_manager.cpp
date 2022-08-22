#include "input_manager.hpp"

namespace Janus {
    std::map<std::string, int> InputManager::inputMap;

    void InputManager::Initialize() {
        inputMap.insert({"player_use", MOUSE_BUTTON_RIGHT});
        inputMap.insert({"player_attack", MOUSE_BUTTON_LEFT});
        inputMap.insert({"move_right", KEY_D});
        inputMap.insert({"move_left", KEY_A});
        inputMap.insert({"move_up", KEY_W});
        inputMap.insert({"move_down", KEY_S});
    }
}
