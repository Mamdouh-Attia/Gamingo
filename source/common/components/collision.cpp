#include "collision.hpp"
#include "../ecs/entity.hpp"

namespace our {
    //a component to identify collision objects
    void CollisionComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
    }
}