#include "health.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"
namespace our {
    // Reads added value from the given json object
    void HealthComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;

    }

    //function to add health
    void HealthComponent::addHealth(int value){
        health += value;
    }
    //function to subtract health
    void HealthComponent::subtractHealth(int value){
        health -= value;
    }
    //function to get health
    int HealthComponent::getHealth(){
        return health;
    }
}