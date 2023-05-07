#include "car.hpp"
#include "../ecs/entity.hpp"

namespace our {
    void CarComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
    }
}