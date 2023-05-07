#pragma once

#include "../ecs/world.hpp"
#include "../components/collision.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // This class handles collision in every entity that has collision component
    class CollisionSystem {
    public:

        // This should be called every frame to update all entities containing a CollisionComponent.
        void update(World* world, float deltaTime) {
            // For each entity in the world
            for(auto entity : world->getEntities()){
                // Get the collision component if it exists
                CollisionComponent* collision = entity->getComponent<CollisionComponent>();
                // If the collision component exists
                if(collision){

                }
            }
        }

    };

}
