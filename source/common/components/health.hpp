#pragma once

#include "../ecs/component.hpp"

#include <glm/glm.hpp>
#include "imgui.h"

namespace our
{

    // This class handles data storage of Health
    class HealthComponent : public Component
    {
    public:
        int health = 100;
        // The ID of this component type is "Goal"
        static std::string getID() { return "Health"; }

        // Reads subtracted value from the given json object
        void deserialize(const nlohmann::json &data) override;
        // fuel level display using onImmediateGui
        virtual void onImmediateGui()
        {
            ImGui::Begin("Health");
            ImGui::SetWindowSize(ImVec2(400, 100));
            ImGui::SetWindowPos(ImVec2(0, 0));
            ImGui::Text("Health: %i", health);
            ImGui::SameLine();
            ImGui::ProgressBar(health / 100.0f, ImVec2(0.0f, 0.0f));
            ImGui::End();
        };
        // function to add health
        void addHealth(int value);
        // function to subtract health
        void subtractHealth(int value);
        // function to get health
        int getHealth();
    };

}