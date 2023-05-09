#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/free-camera-controller.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our {

class FreeCameraControllerSystem {
    Application* app;
    bool mouse_locked = false;

    float target_rotation;

public:
    void enter(Application* app){
        this->app = app;
    }

    void update(World* world, float deltaTime) {
        CameraComponent* camera = nullptr;
        FreeCameraControllerComponent *controller = nullptr;
        for(auto entity : world->getEntities()){
            camera = entity->getComponent<CameraComponent>();
            controller = entity->getComponent<FreeCameraControllerComponent>();
            if(camera && controller) break;
        }

        if(!(camera && controller)) return;
        Entity* entity = camera->getOwner();

        glm::vec3& position = entity->localTransform.position;
        glm::vec3& rotation = entity->localTransform.rotation;

        if(rotation.x < -glm::half_pi<float>() * 0.99f) rotation.x = -glm::half_pi<float>() * 0.99f;
        if(rotation.x >  glm::half_pi<float>() * 0.99f) rotation.x  = glm::half_pi<float>() * 0.99f;
        rotation.y = glm::wrapAngle(rotation.y);

        float fov = camera->fovY + app->getMouse().getScrollOffset().y * controller->fovSensitivity;
        fov = glm::clamp(fov, glm::pi<float>() * 0.4f, glm::pi<float>() * 0.8f);
        camera->fovY = fov;

        glm::mat4 matrix = entity->localTransform.toMat4();

        glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                  up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)), 
                  right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

        glm::vec3 current_sensitivity = controller->positionSensitivity;
        if(app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT)) current_sensitivity *= controller->speedupFactor;

        bool key_d_pressed = app->getKeyboard().isPressed(GLFW_KEY_D);
        bool key_a_pressed = app->getKeyboard().isPressed(GLFW_KEY_A);
        Entity *car = nullptr;

        for (auto entity : world->getEntities()) {
            if (entity->name == "car") {
                car = entity;
                break;
            }
        }

        if(key_d_pressed) {
            glm::vec3 new_position = position + right * ((deltaTime * 2.0f) * current_sensitivity.x);
            if (new_position.x < 12.3)
                position = new_position;

            target_rotation = -0.18f;
        } else if(key_a_pressed) {
            glm::vec3 new_position = position - right * ((deltaTime * 2.0f) * current_sensitivity.x);
            if (new_position.x > -12.3)
                position = new_position;
            target_rotation = 0.18f;
        } else {
            target_rotation = 0;
        }

        // Rotate the car with smoothness
        car->localTransform.rotation.y = glm::mix(car->localTransform.rotation.y, target_rotation, deltaTime * 2.3f);
    }

    void exit() {
        if(mouse_locked) {
            mouse_locked = false;
            app->getMouse().unlockMouse(app->getWindow());
        }
    }
};

}