#include "collision.hpp"
#include "../ecs/entity.hpp"

namespace our {
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
    }
}