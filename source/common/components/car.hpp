#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {
    class CarComponent : public Component {
    public:
    glm::vec3 size = glm::vec3(6.0f, 9.0f, 11.0f);
    int health = 100;
        // The ID of this component type is "Car"
        static std::string getID() { return "Car"; }
    };
}