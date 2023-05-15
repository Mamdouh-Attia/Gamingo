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
            //increment the level number
            level = (level+1) % 2;
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
        // We use the immediate GUI to show the FPS
        // ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        // world->getComponent<our::HealthComponent>()->onImmediateGui();
        ImGui::Begin("Level" ,0, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_NoMove);
        // ImGui::SetWindowFontScale(2);
        ImGui::Text("Level: %d", level + 1);
        //remove borders
        // ImGui::
        ImGui::End();
    }
};