#ifndef JANUS_INPUT_MANAGER_HPP
#define JANUS_INPUT_MANAGER_HPP

#include <map>
#include <string>
#include <raylib.h>

namespace Janus {
    class InputManager{
    public:
        static void Initialize();
        static bool PlayerUse() {
            return IsMouseButtonDown(inputMap.find("player_use")->second);
        }
        static bool PlayerAttack() {
            return IsMouseButtonDown(inputMap.find("player_attack")->second);
        }
        static bool MoveRight() {
            return IsKeyDown(inputMap.find("move_right")->second);
        }
        static bool MoveLeft() {
            return IsKeyDown(inputMap.find("move_left")->second);
        }
        static bool MoveUp() {
            return IsKeyDown(inputMap.find("move_up")->second);
        }
        static bool MoveDown() {
            return IsKeyDown(inputMap.find("move_down")->second);
        }

    private:
        static std::map<std::string, int> inputMap;
    };
}

#endif //JANUS_INPUT_MANAGER_HPP
