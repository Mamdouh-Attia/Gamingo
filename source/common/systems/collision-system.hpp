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
    bool won = false;
    // This class handles collision in every entity that has collision component
    class CollisionSystem
    {
    public:
        //write a function 3dCollides that takes in two 3d positions , depth , width and height and returns true if they collide
        bool three_D_collides(const glm::vec4 &position, int width, int depth, const glm::vec4 &otherPosition, int otherWidth, int otherDepth)
        {
            //write the 6 conditions
            return position.x < otherPosition.x + otherWidth &&
                   position.x + width > otherPosition.x &&
                   position.z < otherPosition.z + otherDepth &&
                   position.z + depth > otherPosition.z;
        }


        bool collides(const glm::vec4 &position, int width, const glm::vec4 &otherPosition, int otherWidth)
        {
            // std::cout << "Car Position ( " << position.x << ", " << position.z << " ) AND Obstacle Position ( " << otherPosition.x << ", " << otherPosition.z << " )." << std::endl;
            //  Check if the two objects are colliding
            //  Check if first object passed second object z position
            return position.x < otherPosition.x + otherWidth &&
                   position.y + width > otherPosition.y &&
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
            int carDepth = carComponent->depth;
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
                        int fuelDepth = fuel->depth;
                        // check if car collides with collision
                        // if (collides(carPosition, carWidth, fuelPosition, fuelWidth))
                        if (three_D_collides(carPosition, carWidth,  carDepth, fuelPosition, fuelWidth,fuelDepth))
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
                        int obstacleDepth = obstacle->depth;
                        // check if car collides with collision
                        if (three_D_collides(carPosition, carWidth, carDepth, obstaclePosition, obstacleWidth,obstacleDepth))
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
                            won = true;
                        }
                    }
                }
            }
            // get car position and size
        }
    };

}
