#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/free-camera-controller.hpp>
#include <systems/collision-system.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>
#include "imgui.h"
// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{
    our::World world;
    our::ForwardRenderer renderer;
    our::FreeCameraControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::CollisionSystem collisionSystem;
    // defining a variable to store the level number
    int level = 0;
    void onInitialize() override
    {
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["levels"][level]["scene"];

        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
        // set the health to 100
        our::health = 100;
    }
    //function to load the next level
    void loadNextLevel()
    {
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["levels"][level]["scene"];

        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }
        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }
    void onDraw(double deltaTime) override
    {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        collisionSystem.update(&world, (float)deltaTime);

        // Delete all marked entities after update
        world.deleteMarkedEntities();

        // And finally we use the renderer system to draw the scene
        renderer.render(&world);

        // Get a reference to the keyboard object
        auto &keyboard = getApp()->getKeyboard();

        if (keyboard.justPressed(GLFW_KEY_ESCAPE))
        {
            // If the escape  key is pressed in this frame, go to the play state
            getApp()->changeState("menu");
        }
        // if reached the end of the level "goal" and it was marked for removal, return to menu
        if (our::won)
        {
            getApp()->changeState("level-win");
            our::won = false;
            our::health = 100;
            //increment the level number
            level = (level+1) % 3;
            //load the next level
            loadNextLevel();
        }
        // if the car reached 0 health, return to menu
        if (our::gameOver)
        {
            getApp()->changeState("game-over");
            our::gameOver = false;
        }
    }


    void onDestroy() override
    {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // Clear the world
        world.clear();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }

    virtual void onImmediateGui() override
    {
        // loading Level text
        ImVec2 levelPos(10, 10);
        ImVec2 levelSize = ImGui::CalcTextSize("LEVEL: 1", NULL, true);
        // add some padding
        levelSize.x += 15;
        levelSize.y += 15;
        // make it at the top left of window
        ImGui::SetNextWindowPos(levelPos);
        ImGui::SetNextWindowSize(levelSize);
        ImGui::Begin("LEVEL", NULL,
                     ImGuiWindowFlags_NoBackground |
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoInputs |
                     ImGuiWindowFlags_AlwaysAutoResize);
        // blue color
        ImVec4 levelColor(0.0f, 0.0f, 1.0f, 1.0f);
        ImGui::TextColored(levelColor, "LEVEL: %d", level + 1);
        ImGui::End();

        // loading Health text
        ImVec2 healthPos(1150, 650);
        ImVec2 healthSize = ImGui::CalcTextSize("HEALTH: 100", NULL, true);
        // add some padding
        healthSize.x += 25;
        healthSize.y += 25;
        // make it at the top left of window
        ImGui::SetNextWindowPos(healthPos);
        ImGui::SetNextWindowSize(healthSize);
        ImGui::Begin("HEALTH", NULL,
                     ImGuiWindowFlags_NoBackground |
                     ImGuiWindowFlags_NoTitleBar |
                     ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoMove |
                     ImGuiWindowFlags_NoScrollbar |
                     ImGuiWindowFlags_NoSavedSettings |
                     ImGuiWindowFlags_NoInputs |
                     ImGuiWindowFlags_AlwaysAutoResize);
        // green color
        ImVec4 healthColor(0.0f, 1.0f, 0.0f, 1.0f);
        // red color if health less than 50
        if (our::health < 50) healthColor = ImVec4(1.0, 0.0, 0.0, 1.0);
        ImGui::TextColored(healthColor, "HEALTH: %d", our::health);
        ImGui::End();
    }
};