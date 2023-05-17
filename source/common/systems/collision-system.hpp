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
    int health = 100;
    // This class handles collision in every entity that has collision component
    class CollisionSystem
    {
    public:
        // write a function 2dCollides that takes in two 2d positions, depth, and width and returns true if they collide
        bool two_d_collides(const glm::vec4 &position, int width, int depth, const glm::vec4 &otherPosition, int otherWidth, int otherDepth)
        {
            return position.x < otherPosition.x + otherWidth &&
                   position.x + width > otherPosition.x &&
                   position.z < otherPosition.z + otherDepth &&
                   position.z + depth > otherPosition.z;
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
                        // shift fuel object left because it rotates, so that it collides with the second cup of coffee
                        fuelPosition.x -= 2.5;
                        // check if car collides with fuel
                        if (two_d_collides(carPosition, carWidth,  carDepth, fuelPosition, fuel->width,fuel->depth))
                        {
                            // if car collides with fuel, add addedValue to car's health
                            carComponent->health += fuel->addedValue;
                            // if car's health is more than 100, set car's health to 100
                            if (carComponent->health > 100)
                            {
                                carComponent->health = 100;
                            }
                            health = carComponent->health;
                            // mark the fuel for removal
                            world->markForRemoval(entity);
                        }
                    }
                    else if (obstacle)
                    {
                        // get obstacle object position and size
                        glm::vec4 obstaclePosition = glm::vec4(entity->localTransform.position, 1.0);
                        // check if car collides with obstacle
                        if (two_d_collides(carPosition, carWidth, carDepth, obstaclePosition, obstacle->width,obstacle->depth))
                        {
                            // if car collides with obstacle, subtract subtractedValue from car's health
                            carComponent->health -= obstacle->subtractedValue;
                            // if car's health is less than 0, set car's health to 0
                            if (carComponent->health < 0)
                            {
                                carComponent->health = 0;
                                // TODO: GAMEOVER
                                // gameOver = true;
                            }
                            health = carComponent->health;
                            // mark obstacle for removal
                            world->markForRemoval(entity);
                        }
                    }
                    else if (goal)
                    {
                        // get goal object position and size
                        glm::vec4 goalPosition = glm::vec4(entity->localTransform.position, 1.0);
                        int goalWidth = goal->width;
                        // check if car collides with goal
                        //if z coordinates only collides, we have a collision
                        if (carPosition.z <= goalPosition.z)
                        {
                            // if car collides with goal, mark goal for removal
                            world->markForRemoval(entity);
                            std::cout << "Goal "<<std::endl;
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
