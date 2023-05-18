#include "light.hpp"
#include "../deserialize-utils.hpp"
#include "../ecs/entity.hpp"
#include <iostream>
namespace our {
    // Reads linearVelocity & angularVelocity from the given json object
    void LightComponent::deserialize(const nlohmann::json& data) {
        if(!data.is_object()) return;
        std::string typeLocal = data.value("typeLight", "");
        enabled               = data.value("enabled", true);
        if(typeLocal == "directional") {
            typeLight = LightType::DIRECTIONAL;
            diffuse   = data["diffuse"];
            specular  = data["specular"];
        } else if(typeLocal == "point") {
            typeLight             = LightType::POINT;
            diffuse               = data["diffuse"];
            specular              = data["specular"];
            attenuation.constant  = data["attenuation"]["constant"];
            attenuation.linear    = data["attenuation"]["linear"];
            attenuation.quadratic = data["attenuation"]["quadratic"];
        } else if(typeLocal == "spot") {
            typeLight             = LightType::SPOT;
            diffuse               = data["diffuse"];
            specular              = data["specular"];
            attenuation.constant  = data["attenuation"]["constant"];
            attenuation.linear    = data["attenuation"]["linear"];
            attenuation.quadratic = data["attenuation"]["quadratic"];
            spot_angle.inner      = data["spot_angle"]["inner"];
            spot_angle.outer      = data["spot_angle"]["outer"];
        } else if(typeLocal == "sky") {
            typeLight              = LightType::SKY;
            sky_light.top_color    = data["sky_light"]["top_color"];
            sky_light.bottom_color = data["sky_light"]["bottom_color"];
            sky_light.middle_color = data["sky_light"]["middle_color"];
        } else {
            throw std::runtime_error("Unknown light type " + typeLocal);
        }

    }
} // namespace our