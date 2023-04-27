#pragma once

#include <glad/gl.h>
#include "vertex.hpp"

namespace our {

    // These constants define the attribute locations in the shader program for vertex data.
    #define ATTRIB_LOC_POSITION 0
    #define ATTRIB_LOC_COLOR    1
    #define ATTRIB_LOC_TEXCOORD 2
    #define ATTRIB_LOC_NORMAL   3

    // The Mesh class represents a 3D object composed of vertices and indices.
    // It is responsible for managing OpenGL buffers and rendering the object.
    class Mesh {
        // Here, we store the object names of the 3 main components of a mesh:
        // A vertex array object, A vertex buffer and an element buffer
        
        // The vertex buffer object (VBO) stores the vertex data on the GPU.
        // The element buffer object (EBO) stores the indices data on the GPU.
        unsigned int VBO, EBO;

        // The vertex array object (VAO) encapsulates the state needed for rendering the object.
        unsigned int VAO;

        // We need to remember the number of elements that will be draw by glDrawElements
        GLsizei elementCount;
    public:

        // The constructor takes two vectors:
        // - vertices which contain the vertex data.
        // - elements which contain the indices of the vertices out of which each rectangle will be constructed.
        // The mesh class does not keep a these data on the RAM. Instead, it should create
        // a vertex buffer to store the vertex data on the VRAM,
        // an element buffer to store the element data on the VRAM,
        // a vertex array object to define how to read the vertex & element buffer during rendering 
        Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& elements)
        {
            //TODO: (Req 2) Write this function
            // remember to store the number of elements in "elementCount" since you will need it for drawing
            // For the attribute locations, use the constants defined above: ATTRIB_LOC_POSITION, ATTRIB_LOC_COLOR, etc
            
            
            // Create the vertex array object (VAO) and bind it.
            glGenVertexArrays(1, &VAO);
            glBindVertexArray(VAO);


            // Create the vertex buffer object (VBO), bind it, and send the vertex data to the GPU.
            glGenBuffers(1, &VBO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);

            // Enable and define the vertex attributes for position, color, texture coordinates, and normals.
            glEnableVertexAttribArray(ATTRIB_LOC_POSITION);
            glVertexAttribPointer(ATTRIB_LOC_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

            glEnableVertexAttribArray(ATTRIB_LOC_COLOR);
            glVertexAttribPointer(ATTRIB_LOC_COLOR, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

            glEnableVertexAttribArray(ATTRIB_LOC_TEXCOORD);
            glVertexAttribPointer(ATTRIB_LOC_TEXCOORD, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tex_coord));

            glEnableVertexAttribArray(ATTRIB_LOC_NORMAL);
            glVertexAttribPointer(ATTRIB_LOC_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
            //////////////////////////////////////////////

            // Store the number of elements in "elementCount" for drawing.
            this->elementCount = elements.size();

            // Create the element buffer object (EBO), bind it, and send the indices data to the GPU.
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, elements.size() * sizeof(unsigned int), elements.data(), GL_STATIC_DRAW);
        }

        // This function renders the mesh by binding the vertex array object (VAO)
        // and issuing a glDrawElements call to draw the triangles.
        void draw() 
        {
            //TODO: (Req 2) Write this function
            // Bind the vertex array object (VAO) and draw the elements using the stored element count.
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, this->elementCount, GL_UNSIGNED_INT, 0);
        }

        // This destructor function deletes the vertex & element buffers and the vertex array object,
        // freeing up GPU resources when the mesh is no longer needed.
        ~Mesh(){
            //TODO: (Req 2) Write this function

            // Delete the vertex buffer object (VBO), element buffer object (EBO), and vertex array object (VAO).
            glDeleteBuffers(1, &VBO);
            glDeleteBuffers(1, &EBO);
            glDeleteVertexArrays(1, &VAO);
        }

        Mesh(Mesh const &) = delete;
        Mesh &operator=(Mesh const &) = delete;
    };
}
