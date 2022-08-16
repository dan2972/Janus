#ifndef JANUS_INPUT_MANAGER_HPP
#define JANUS_INPUT_MANAGER_HPP

#include <map>
#include <string>
#include <raylib-cpp.hpp>

namespace Janus {
    class InputManager{
    public:
        static void Initialize();
        static bool PlayerPlaceDown() {
            if(IsMouseButtonDown(inputMap.find("playerPlace")->second))
                return true;
            return false;
        }
        static bool PlayerAttackDown() {
            if(IsMouseButtonDown(inputMap.find("playerAttack")->second))
                return true;
            return false;
        }
        static bool MoveRightDown() {
            if(IsKeyDown(inputMap.find("moveRight")->second))
                return true;
            return false;
        }
        static bool MoveLeftDown() {
            if(IsKeyDown(inputMap.find("moveLeft")->second))
                return true;
            return false;
        }
        static bool MoveUpDown() {
            if(IsKeyDown(inputMap.find("moveUp")->second))
                return true;
            return false;
        }
        static bool MoveDownDown() {
            if(IsKeyDown(inputMap.find("moveDown")->second))
                return true;
            return false;
        }

    private:
        static std::map<std::string, int> inputMap;
    };
}

#endif //JANUS_INPUT_MANAGER_HPP
