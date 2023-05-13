#include "goal.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
namespace our {
    // Reads added value from the given json object
    void GoalComponent::deserialize(const nlohmann::json& data){
        // if(!data.is_object()) return;
        // width = data.value("width", width);
    }
}