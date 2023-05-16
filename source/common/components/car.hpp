#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {
    class CarComponent : public Component {
    public:
        float width = 0;
        float depth = 0;
        int health = 100;

        // The ID of this component type is "Car"
        static std::string getID() { return "Car"; }
        // Reads added value from the given json object
        void deserialize(const nlohmann::json& data) override;
    };
}