#include "light.hpp"
#include "../deserialize-utils.hpp"
#include "../ecs/entity.hpp"
#include <iostream>
namespace our {

    // Reads linearVelocity & angularVelocity from the given json object
    void LightComponent::deserialize(const nlohmann::json& data) {
        if(!data.is_object()) return;

        glm::vec3 read_attenuation;

        std::string typeLocal = data.value("typeLight", "");
        enabled = data.value("enabled", true);
        color = data.value("color", glm::vec3(1.0));
        if(typeLocal == "directional") {
            typeLight = LightType::DIRECTIONAL;
            direction = data.value("direction", direction);
            read_attenuation = data.value("attenuation", glm::vec3(1.0));
            attenuation.constant = read_attenuation[0];
            attenuation.linear = read_attenuation[1];
            attenuation.quadratic = read_attenuation[2];

        } else if(typeLocal == "point") {
            typeLight  = LightType::POINT;
            read_attenuation = data.value("attenuation", glm::vec3(1.0));
            direction = data.value("direction", direction);
            attenuation.constant = read_attenuation[2];
            attenuation.linear = read_attenuation[1];
            attenuation.quadratic = read_attenuation[0];
        } else if(typeLocal == "spot") {
            typeLight  = LightType::SPOT;
            direction  = data.value("direction", glm::vec3(0.0));
            read_attenuation = data.value("attenuation", glm::vec3(1.0));
            attenuation.constant = read_attenuation[0];
            attenuation.linear = read_attenuation[1];
            attenuation.quadratic = read_attenuation[2];
            glm::vec2 cone_angles = data.value("cone_angles", glm::vec2(0.0));
            spot_angle.inner = cone_angles[0];
            spot_angle.outer = cone_angles[1];
        } else if(typeLocal == "sky") {
            typeLight = LightType::SKY;
            direction  = data.value("direction", glm::vec3(0.0));
            sky_light.top_color  = data.value("sky_light_top", glm::vec3(0.0));
            sky_light.bottom_color = data.value("sky_light_bottom", glm::vec3(0.0));
            sky_light.middle_color = data.value("sky_light_middle", glm::vec3(0.0));
        } else {
            throw std::runtime_error("Unknown light type " + typeLocal);
        }

        std::cout << "PASSED\n";

    }
}