#pragma once
#include "../ecs/component.hpp"
#include "imgui.h"
#include <glm/gtx/euler_angles.hpp>

namespace our{
    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT,
        SKY
    };
    class LightComponent: public Component {
    public:
        LightType typeLight;
        bool enabled = false;
        // Note that we removed the 3 components and replaced it with color.
        // This is a bit more realistic since light color shouldn't differ between diffuse and specular.
        // But you may want to keep them separate if you want extra artistic control where you may want to ignore realism.
        // Also, we no longer have an ambient term in the  We will keep the ambient in a separate struct called "SkyLight".
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 position;  // Used for Point and Spot Lights only
        glm::vec3 direction; // Used for Directional and Spot Lights only
        struct {
            float quadratic, linear, constant;
        } attenuation; // Used for Point and Spot Lights only
        struct {
            float inner, outer;
        } spot_angle; // Used for Spot Lights only
        struct {
            glm::vec3 top_color, middle_color, bottom_color;
        } sky_light;

        // The ID of this component type is "Movement"
        static std::string getID() { return "Light"; }
        void deserialize(const nlohmann::json& data) override;

//        virtual void onImmediateGui() override {
//
//            std::string lightId = std::to_string((long long)this);
//            ImGui::Checkbox(("Light enabled##" + lightId).c_str(), &enabled);
//            if(enabled) {
//                if(typeLight == LightType::DIRECTIONAL ||
//                   typeLight == LightType::POINT ||
//                   typeLight == LightType::SPOT) {
//                    ImGui::ColorPicker3(("Diffuse##" + lightId).c_str(), &diffuse.x);
//                    ImGui::ColorPicker3(("Specular##" + lightId).c_str(), &specular.x);
//                }
//                if(typeLight == LightType::POINT ||
//                   typeLight == LightType::SPOT) {
//                    ImGui::DragFloat3(("Attenuation##"+lightId).c_str(), &attenuation.quadratic);
//                }
//
//                if (typeLight == LightType::SPOT) {
//                    ImGui::DragFloat2(("Cone angles (inner/outer)##"+lightId).c_str(), &spot_angle.inner);
//                }
//
//                if(typeLight==LightType::SKY){
//                    ImGui::ColorPicker3(("Sky top##" + lightId).c_str(), &sky_light.top_color.x);
//                    ImGui::ColorPicker3(("Sky middle##" + lightId).c_str(), &sky_light.middle_color.x);
//                    ImGui::ColorPicker3(("Sky bottom##" + lightId).c_str(), &sky_light.bottom_color.x);
//                }
//            }
//        }
    };
}