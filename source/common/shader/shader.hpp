#ifndef SHADER_HPP
#define SHADER_HPP

#include <string>

#include <glad/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace our {

    class ShaderProgram {

    private:
        //Shader Program Handle (OpenGL object name)
        GLuint program;

    public:
        ShaderProgram(){
            // TODO: (Req 1) Create A shader program
            //calling glCreateProgram() to create a shader program
            program = glCreateProgram();
        }
        ~ShaderProgram(){
            //TODO: (Req 1) Delete a shader program
            //calling glDeleteProgram() to delete a shader program
            glDeleteProgram(program);
        }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: (Req 1) Return the location of the uniform with the given name
            //getting uniform location by calling glGetUniformLocation()
            return glGetUniformLocation(program,&name[0]);
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: (Req 1) Send the given float value to the given uniform
            //sending float value to the given uniform by calling glUniform1f()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform1f(uniform_loc,value);
        }

        void set(const std::string &uniform, GLuint value) {
            //TODO: (Req 1) Send the given unsigned integer value to the given uniform
            //sending unsigned integer value to the given uniform by calling glUniform1ui()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform1ui(uniform_loc,value);
        }

        void set(const std::string &uniform, GLint value) {
            //TODO: (Req 1) Send the given integer value to the given uniform
            //sending integer value to the given uniform by calling glUniform1i()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform1i(uniform_loc,value);
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: (Req 1) Send the given 2D vector value to the given uniform
            //sending 2D vector value to the given uniform by calling glUniform2f()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform2f(uniform_loc,value.x,value.y);
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: (Req 1) Send the given 3D vector value to the given uniform
            //sending 3D vector value to the given uniform by calling glUniform3f()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform3f(uniform_loc,value.x,value.y,value.z);
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: (Req 1) Send the given 4D vector value to the given uniform
            //sending 4D vector value to the given uniform by calling glUniform4f()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform4f(uniform_loc,value.x,value.y,value.z,value.w);
        }

        void set(const std::string &uniform, glm::mat4 matrix) {
            //TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
            //sending matrix 4x4 value to the given uniform by calling glUniformMatrix4fv()
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniformMatrix4fv(uniform_loc,1,GL_FALSE,&matrix[0][0]);
        }

        //TODO: (Req 1) Delete the copy constructor and assignment operator.
        ShaderProgram(const ShaderProgram &s)=delete;
        ShaderProgram operator=(ShaderProgram const &s)=delete;
        //TODO Question: Why do we delete the copy constructor and assignment operator?
        // Answer: because we don't want to copy the shader program
        //  and not to have 2 pointers pointing to the same object of shaderprogram
        //also to ensure Resource Aquisition Is Initialization (RAII) 
        //which is a technique used to avoid resource leaks in C++ programs
    };

}

#endif