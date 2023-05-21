#include "material.hpp"

#include "../asset-loader.hpp"
#include "deserialize-utils.hpp"

namespace our
{

    // This function should setup the pipeline state and set the shader to be used
    void Material::setup() const
    {
        // TODO: (Req 7) Write this function
        // calling the setup function of the pipeline state
        pipelineState.setup();
        // calling the use function of the shader program to set the shader to be used
        shader->use();
    }

    // This function read the material data from a json object
    void Material::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())
            return;

        if (data.contains("pipelineState"))
        {
            pipelineState.deserialize(data["pipelineState"]);
        }
        shader = AssetLoader<ShaderProgram>::get(data["shader"].get<std::string>());
        transparent = data.value("transparent", false);
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint
    void TintedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        // calling the setup function of the parent class Material
        Material::setup();
        // setting the "tint" uniform to the value in the member variable tint
        shader->set("tint", tint);
    }

    // This function read the material data from a json object
    void TintedMaterial::deserialize(const nlohmann::json &data)
    {
        Material::deserialize(data);
        if (!data.is_object())
            return;
        tint = data.value("tint", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    }

    // This function should call the setup of its parent and
    // set the "alphaThreshold" uniform to the value in the member variable alphaThreshold
    // Then it should bind the texture and sampler to a texture unit and send the unit number to the uniform variable "tex"
    void TexturedMaterial::setup() const
    {
        // TODO: (Req 7) Write this function
        // calling the setup function of the parent class TintedMaterial
        TintedMaterial::setup();
        // setting the "alphaThreshold" uniform to the value in the member variable alphaThreshold
        shader->set("alphaThreshold", alphaThreshold);
        // binding the texture and sampler to a texture unit and sending the unit number to the uniform variable "tex"
        if (texture)
        {
            texture->bind();
        }
        else
        {
            Texture2D::unbind();
        }
        if (sampler)
        {
            sampler->bind(0);
        }
        else
        {
            Sampler::unbind(0);
        }

        shader->set("tex", 0);
    }

    void LightMaterial::deserialize(const nlohmann::json& data) {
        TexturedMaterial::deserialize(data);
        if(!data.is_object()) return;
        albedo_map = AssetLoader<Texture2D>::get(data.value("albedo", ""));
        specular_map = AssetLoader<Texture2D>::get(data.value("specular", ""));
        emissive_map = AssetLoader<Texture2D>::get(data.value("emissive", ""));
        roughness_map = AssetLoader<Texture2D>::get(data.value("roughness", ""));
        ambient_occlusion_map =  AssetLoader<Texture2D>::get(data.value("ambient_occlusion", ""));
    }

    // This function should call the setup of its parent and
    // set the "tint" uniform to the value in the member variable tint
    void  LightMaterial::setup() const {
        TintedMaterial::setup();
        this->shader->set("alphaThreshold", this->alphaThreshold);
        this->sampler->bind(0);
        if(albedo_map != nullptr)
        {
            // select an active texture unit -> 1
            glActiveTexture(GL_TEXTURE0);
            // bind the texture to unit 1
            this->albedo_map->bind();
            // bind the sampler to unit 1
            this->sampler->bind(0);
            shader->set("material.albedo", 0);
        }
        if(specular_map != nullptr)
        {
            // select an active texture unit -> 1
            glActiveTexture(GL_TEXTURE1);
            // bind the texture to unit 1
            this->specular_map->bind();
            // bind the sampler to unit 1
            this->sampler->bind(1);
            shader->set("material.specular", 1);
        }
        if(emissive_map != nullptr)
        {
            // select an active texture unit -> 1
            glActiveTexture(GL_TEXTURE2);
            // bind the texture to unit 1
            this->emissive_map->bind();
            // bind the sampler to unit 1
            this->sampler->bind(2);
            shader->set("material.emissive", 2);
        }
        if(ambient_occlusion_map != nullptr)
        {
            // select an active texture unit -> 1
            glActiveTexture(GL_TEXTURE3);
            // bind the texture to unit 1
            this->ambient_occlusion_map->bind();
            // bind the sampler to unit 1
            this->sampler->bind(3);
            shader->set("material.ambient_occlusion", 3);
        }
        if(roughness_map != nullptr)
        {
            // select an active texture unit -> 1
            glActiveTexture(GL_TEXTURE4);
            // bind the texture to unit 1
            this->roughness_map->bind();
            // bind the sampler to unit 1
            this->sampler->bind(4);
            shader->set("material.roughness", 4);
        }

        glActiveTexture(GL_TEXTURE0);
    }


    // This function read the material data from a json object
    void TexturedMaterial::deserialize(const nlohmann::json &data)
    {
        TintedMaterial::deserialize(data);
        if (!data.is_object())
            return;
        alphaThreshold = data.value("alphaThreshold", 0.0f);
        texture = AssetLoader<Texture2D>::get(data.value("texture", ""));
        sampler = AssetLoader<Sampler>::get(data.value("sampler", ""));
    }

}