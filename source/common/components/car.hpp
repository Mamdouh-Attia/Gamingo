#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {
    // A component that stores the size of the car and its health
    class CarComponent : public Component {
    public:
        // The size of the car in the x and z directions
        //width and depth 
        float width = 0;
        float depth = 0;
        // The health of the car
        int health = 100;

        // The ID of this component type is "Car"
        static std::string getID() { return "Car"; }
        // Reads added value from the given json object
        void deserialize(const nlohmann::json& data) override;
    };
}