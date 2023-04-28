#include "texture-utils.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include <iostream>

our::Texture2D* our::texture_utils::empty(GLenum format, glm::ivec2 size){
    our::Texture2D* texture = new our::Texture2D();
    //TODO: (Req 11) Finish this function to create an empty texture with the given size and format
    //we first bind the texture
    texture->bind();
    //then send a nullptr
    glTexImage2D(GL_TEXTURE_2D, 0, format, size.x, size.y, 0, format, GL_UNSIGNED_BYTE, nullptr);
    //then we unbind it
    texture->unbind();
    return texture;
}

our::Texture2D* our::texture_utils::loadImage(const std::string& filename, bool generate_mipmap) {
    glm::ivec2 size;
    int channels;
    //Since OpenGL puts the texture origin at the bottom left while images typically has the origin at the top left,
    //We need to till stb to flip images vertically after loading them
    stbi_set_flip_vertically_on_load(true);
    //Load image data and retrieve width, height and number of channels in the image
    //The last argument is the number of channels we want and it can have the following values:
    //- 0: Keep number of channels the same as in the image file
    //- 1: Grayscale only
    //- 2: Grayscale and Alpha
    //- 3: RGB
    //- 4: RGB and Alpha (RGBA)
    //Note: channels (the 4th argument) always returns the original number of channels in the file
    unsigned char* pixels = stbi_load(filename.c_str(), &size.x, &size.y, &channels, 4);
    if(pixels == nullptr){
        std::cerr << "Failed to load image: " << filename << std::endl;
        return nullptr;
    }
    // Create a texture
    our::Texture2D* texture = new our::Texture2D();
    //Bind the texture such that we upload the image data to its storage
    //TODO: (Req 5) Finish this function to fill the texture with the data found in "pixels"
    //corner case
    //first we bind the texture
    texture->bind();
    //then we upload the image data to the texture
    glPixelStorei(GL_UNPACK_ALIGNMENT,4);
    //then we call glTexImage2D() to upload the image data to the texture
    //the first argument is the target texture: GL_TEXTURE_2D
    //the second argument is the mipmap level: 0
    //the third argument is the internal format of the texture: GL_RGBA
    //the fourth and fifth arguments are the width and height of the texture: size.x and size.y
    //the sixth argument is the border width: must be 0
    //the seventh argument is the format of the pixel data: GL_RGBA
    //the eighth argument is the data type of the pixel data: GL_UNSIGNED_BYTE
    //the ninth argument is the actual pixel data : pixels
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size.x, size.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);
    //if specified in function parameters, generate mipmaps for the texture
    if(generate_mipmap){
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    //Unbinding the texture
    texture->unbind();
    stbi_image_free(pixels); //Free image data after uploading to GPU
    return texture;
}