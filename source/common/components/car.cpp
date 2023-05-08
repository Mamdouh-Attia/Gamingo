#include "car.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    void CarComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        size = data.value("size", size);
    }
}