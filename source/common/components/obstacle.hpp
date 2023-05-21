#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>


namespace our {

    // This class handles data storage of obstacle
    class ObstacleComponent : public Component {
    public:
        // The subtracted value from the car's health when it collides with an obstacle
        int subtractedValue = 10;
        // The width of the obstacle and its depth
        float width = 0;
        float depth = 0;

        // The ID of this component type is "Obstacle"
        static std::string getID() { return "Obstacle"; }

        // Reads subtracted value from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}