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
            program = glCreateProgram();
        }
        ~ShaderProgram(){
            //TODO: (Req 1) Delete a shader program
            glDeleteProgram(program);
        }

        bool attach(const std::string &filename, GLenum type) const;

        bool link() const;

        void use() { 
            glUseProgram(program);
        }

        GLuint getUniformLocation(const std::string &name) {
            //TODO: (Req 1) Return the location of the uniform with the given name
            //converting name from string to char* for function parameters
            const char* name_c = name.c_str();
            //getting uniform location
            GLuint uniform_location = glGetUniformLocation(program,name_c);
            return uniform_location;
        }

        void set(const std::string &uniform, GLfloat value) {
            //TODO: (Req 1) Send the given float value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform1f(uniform_loc,value);
        }

        void set(const std::string &uniform, GLuint value) {
            //TODO: (Req 1) Send the given unsigned integer value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform1ui(uniform_loc,value);
        }

        void set(const std::string &uniform, GLint value) {
            //TODO: (Req 1) Send the given integer value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform1i(uniform_loc,value);
        }

        void set(const std::string &uniform, glm::vec2 value) {
            //TODO: (Req 1) Send the given 2D vector value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform2fv(uniform_loc,1,glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec3 value) {
            //TODO: (Req 1) Send the given 3D vector value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform3fv(uniform_loc,1,glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::vec4 value) {
            //TODO: (Req 1) Send the given 4D vector value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            glUniform4fv(uniform_loc,1,glm::value_ptr(value));
        }

        void set(const std::string &uniform, glm::mat4 matrix) {
            //TODO: (Req 1) Send the given matrix 4x4 value to the given uniform
            GLuint uniform_loc = getUniformLocation(uniform);
            // glUniformMatrix4fv(uniform_loc,1,glm::value_ptr(matri));
            glUniformMatrix4fv(uniform_loc,1,GL_FALSE,glm::value_ptr(matrix));
        }

        //TODO: (Req 1) Delete the copy constructor and assignment operator.
        ShaderProgram(const ShaderProgram &s)=delete;
        ShaderProgram operator=(ShaderProgram const &s)=delete;
        //TODO Question: Why do we delete the copy constructor and assignment operator?
        //=>to avoid shallow copy and shallow assignment
        //  and not to have 2 pointers pointing to the same object of shaderprogram
    };

}

#endif