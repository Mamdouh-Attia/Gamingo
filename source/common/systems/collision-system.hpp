#pragma once

#include "../ecs/world.hpp"
#include "../components/collision.hpp"
#include "../components/car.hpp"
#include "../components/fuel.hpp"
#include "../components/obstacle.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // This class handles collision in every entity that has collision component
    class CollisionSystem
    {
    public:
        bool collides(const glm::vec3 &position, const glm::vec3 &size, const glm::vec3 &other_position, const glm::vec3 &other_size)
        {
            // Check if the two boxes are colliding
            return position.x < other_position.x + other_size.x &&
                   position.x + size.x > other_position.x &&
                   position.y < other_position.y + other_size.y &&
                   position.y + size.y > other_position.y &&
                   position.z < other_position.z + other_size.z &&
                   position.z + size.z > other_position.z;
        }

        // This should be called every frame to update all entities containing a CollisionComponent.
        void update(World *world, float deltaTime)
        {
            // get car entity
            Entity *car = nullptr;
            for (auto entity : world->getEntities())
            {
                if (entity->getComponent<CarComponent>())
                {
                    car = entity;
                    break;
                }
            }
            CarComponent *carComponent = car->getComponent<CarComponent>();
            // get car position and size
            glm::vec3 carPosition = car->getLocalToWorldMatrix() * glm::vec4( car->localTransform.position,1.0);
            glm::vec3 carSize = carComponent->size;
            // For each entity in the world
            // collide car with collision
            for (auto entity : world->getEntities())
            {
                // Get the collision component if it exists
                CollisionComponent *collision = entity->getComponent<CollisionComponent>();
                // If the collision component exists
                if (collision)
                {
                    FuelComponent *fuel = entity->getComponent<FuelComponent>();
                    ObstacleComponent *obstacle = entity->getComponent<ObstacleComponent>();
                    // check if car collides with fuel
                    if (fuel) {
                        // get obstacle object position and size
                        glm::vec3 fuelPosition =
                                entity->getLocalToWorldMatrix() * glm::vec4(entity->localTransform.position, 1.0);
                        glm::vec3 fuelSize = fuel->size;
                        // check if car collides with collision
                        if (collides(carPosition, carSize, fuelPosition, fuelSize)) {
                            // if car collides with fuel, add 10 to car's health
                            carComponent->health += fuel->addedValue;
                            // if car's health is more than 100, set car's health to 100
                            if (carComponent->health > 100) {
                                carComponent->health = 100;
                            }
                            // mark the fuel for removal
                            world->markForRemoval(entity);
                        }
                    }
                    else if (obstacle) {
                        // get obstacle object position and size
                        glm::vec3 obstaclePosition =
                                entity->getLocalToWorldMatrix() * glm::vec4(entity->localTransform.position, 1.0);
                        glm::vec3 obstacleSize = obstacle->size;
                        // check if car collides with collision
                        if (collides(carPosition, carSize, obstaclePosition, obstacleSize)) {
                            // if car collides with obstacle, subtract 10 from car's health
                            carComponent->health -= obstacle->subtractedValue;
                            // if car's health is less than 0, set car's health to 0
                            if (carComponent->health < 0) {
                                carComponent->health = 0;
                                // TODO: GAMEOVER
                                // gameOver = true;
                            }
                            // mark obstacle for removal
                            world->markForRemoval(entity);
                        }
                    }
                }
            }
            // get car position and size
        }
    };

}
