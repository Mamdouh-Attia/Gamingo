#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // This class handles data storage of fuel
    class FuelComponent : public Component {
    public:
        int addedValue = 10;
        float width;
        float depth;

        // The ID of this component type is "Fuel"
        static std::string getID() { return "Fuel"; }

        // Reads added value from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}