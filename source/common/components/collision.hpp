#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>

namespace our {

    // This class handles data storage of collision
    class CollisionComponent : public Component {
    public:

        // The ID of this component type is "Collision"
        static std::string getID() { return "Collision"; }

    };

}