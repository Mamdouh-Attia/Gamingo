#pragma once

#include "../ecs/component.hpp"
#include "imgui.h"
#include <glm/gtx/euler_angles.hpp>

namespace our {

    enum class LightType {
        DIRECTIONAL,
        POINT,
        SPOT,
        SKY
    };

    class LightComponent : public Component {
    public:
        LightType typeLight;
        bool enabled = false;

        glm::vec3 direction; // Used for Directional and Spot Lights only
        glm::vec3 color;
        struct {
            float quadratic, linear, constant;
        } attenuation; // Used for Point and Spot Lights only
        struct {
            float inner, outer;
        } spot_angle; // Used for Spot Lights only
        struct {
            glm::vec3 top_color, middle_color, bottom_color;
        } sky_light;

        // The ID of this component type is "Light"
        static std::string getID() { return "Light"; }

        //virtual std::string getIDPolymorphic() override { return getID(); }

        // Reads linearVelocity & angularVelocity from the given json object
        virtual void deserialize(const nlohmann::json &data) override;

    };


}