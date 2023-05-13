#pragma once

#include "../ecs/world.hpp"
#include "../components/collision.hpp"
#include "../components/car.hpp"
#include "../components/fuel.hpp"
#include "../components/obstacle.hpp"
#include "../components/goal.hpp"

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
        bool collides(const glm::vec4 &position, int width, const glm::vec4 &otherPosition, int otherWidth)
        {
            // std::cout << "Car Position ( " << position.x << ", " << position.z << " ) AND Obstacle Position ( " << otherPosition.x << ", " << otherPosition.z << " )." << std::endl;
            //  Check if the two objects are colliding
            //  Check if first object passed second object z position
            return position.x < otherPosition.x + otherWidth &&
                   position.x + width > otherPosition.x &&
                   position.z <= otherPosition.z;
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
            glm::vec4 carPosition = car->getLocalToWorldMatrix() * glm::vec4(car->localTransform.position, 1.0);
            int carWidth = carComponent->width;
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
                    GoalComponent *goal = entity->getComponent<GoalComponent>();

                    // check if car collides with fuel
                    if (fuel)
                    {
                        // get obstacle object position and size
                        glm::vec4 fuelPosition = glm::vec4(entity->localTransform.position, 1.0);
                        // fuel object has a thing that makes its image shifted 6 right in x axis and 6 into z axis
                        fuelPosition.x += 6;
                        fuelPosition.z -= 6;
                        int fuelWidth = fuel->width;
                        // check if car collides with collision
                        if (collides(carPosition, carWidth, fuelPosition, fuelWidth))
                        {
                            // if car collides with fuel, add 10 to car's health
                            carComponent->health += fuel->addedValue;
                            // if car's health is more than 100, set car's health to 100
                            if (carComponent->health > 100)
                            {
                                carComponent->health = 100;
                            }
                            std::cout << "Fuel: Health = " << carComponent->health << std::endl;
                            // mark the fuel for removal
                            world->markForRemoval(entity);
                        }
                    }
                    else if (obstacle)
                    {
                        // get obstacle object position and size
                        glm::vec4 obstaclePosition =
                            /* entity->getLocalToWorldMatrix() * */ glm::vec4(entity->localTransform.position, 1.0);
                        int obstacleWidth = obstacle->width;
                        // check if car collides with collision
                        if (collides(carPosition, carWidth, obstaclePosition, obstacleWidth))
                        {
                            // if car collides with obstacle, subtract 10 from car's health
                            carComponent->health -= obstacle->subtractedValue;
                            // if car's health is less than 0, set car's health to 0
                            if (carComponent->health < 0)
                            {
                                carComponent->health = 0;
                                // TODO: GAMEOVER
                                // gameOver = true;
                            }
                            std::cout << "Obstacle: Health = " << carComponent->health << std::endl;
                            // mark obstacle for removal
                            world->markForRemoval(entity);
                        }
                    }
                    else if (goal)
                    {
                        // get goal object position and size
                        glm::vec4 goalPosition = glm::vec4(entity->localTransform.position, 1.0);
                        int goalWidth = goal->width;
                        // check if car collides with collision
                        //if z coordinates only collides, we have a collision
                        if (carPosition.z <= goalPosition.z)
                        {
                            // if car collides with goal, mark goal for removal
                            world->markForRemoval(entity);
                            std::cout << "Goal "<<std::endl;
                            // mark obstacle for removal
                            world->markForRemoval(entity);
                            // if reached the end of the level "goal" and it was marked for removal, return to menu
                        }
                    }
                }
            }
            // get car position and size
        }
    };

}
