#include "input_manager.hpp"

namespace Janus {
    std::map<std::string, int> InputManager::inputMap;

    void InputManager::Initialize() {
        inputMap.insert({"playerPlace", MOUSE_BUTTON_LEFT});
        inputMap.insert({"playerAttack", MOUSE_BUTTON_RIGHT});
        inputMap.insert({"moveRight", KEY_D});
        inputMap.insert({"moveLeft", KEY_A});
        inputMap.insert({"moveUp", KEY_W});
        inputMap.insert({"moveDown", KEY_S});
    }
}
