#include "obstacle.hpp"
#include "../ecs/entity.hpp"

namespace our {
    // Reads added value from the given json object
    void ObstacleComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        subtractedValue = data.value("subtractedValue", subtractedValue);
        width = data.value("width", width);
        depth = data.value("depth", depth);
    }
}