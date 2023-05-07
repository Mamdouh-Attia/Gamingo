#include "fuel.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    // Reads added value from the given json object
    void FuelComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        addedValue = data.value("addedValue", addedValue);
    }
}