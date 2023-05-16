#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>


namespace our {

    // This class handles data storage of Goal
    class GoalComponent : public Component {
    public:
        float width = 0;
        // The ID of this component type is "Goal"
        static std::string getID() { return "Goal"; }

        // Reads subtracted value from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}