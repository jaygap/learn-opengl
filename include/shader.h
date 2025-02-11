#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader{
    public:
        unsigned int ID;

        Shader(const char* vert_shader_path, const char* frag_shader_path){
            //read files
            std::string vert_code;
            std::string frag_code;
            std::ifstream vert_file;
            std::ifstream frag_file;

            vert_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
            frag_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

            try{
                vert_file.open(vert_shader_path);
                frag_file.open(frag_shader_path);

                std::stringstream vert_stream, frag_stream;
                
                vert_stream << vert_file.rdbuf();
                frag_stream << frag_file.rdbuf();

                vert_file.close();
                frag_file.close();

                vert_code = vert_stream.str();
                frag_code = frag_stream.str();
            } catch(std::ifstream::failure e){
                std::cout<<"ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ"<<std::endl;
            }

            const char* vert_shader = vert_code.c_str();
            const char* frag_shader = frag_code.c_str();

            //compile shaders

            unsigned int vertex, fragment;
            int success;
            char info_log[512];

            vertex = glCreateShader(GL_VERTEX_SHADER);
            glShaderSource(vertex, 1, &vert_shader, NULL);
            glCompileShader(vertex);

            glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

            if(!success){
                glGetShaderInfoLog(vertex, 512, NULL, info_log);
                std::cout<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<info_log<<std::endl;
            }

            fragment = glCreateShader(GL_FRAGMENT_SHADER);
            glShaderSource(fragment, 1, &frag_shader, NULL);
            glCompileShader(fragment);

            glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);

            if(!success){
                glGetShaderInfoLog(fragment, 512, NULL, info_log);
                std::cout<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<info_log<<std::endl;
            }

            //link shaders to program

            ID = glCreateProgram();
            glAttachShader(ID, vertex);
            glAttachShader(ID, fragment);
            glLinkProgram(ID);

            glGetProgramiv(ID, GL_LINK_STATUS, &success);

            if(!success){
                glGetProgramInfoLog(ID, 512, NULL, info_log);
                std::cout<<"ERROR::SHADER::PROGRAM::LINKING_FALIED"<<info_log<<std::endl;
            }

            //delete shaders bc no longer necessary
            glDeleteShader(vertex);
            glDeleteShader(fragment);
        }

        void use(){
            glUseProgram(ID);
        }

        void setBool(const std::string &name, bool value){
            glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
        }

        void setInt(const std::string &name, int value){
            glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
        }
        
        void setFloat(const std::string &name, float value){
            glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
        }

        void setVec3(const std::string &name, float value_x, float value_y, float value_z){
            glUniform3f(glGetUniformLocation(ID, name.c_str()), value_x, value_y, value_z);
        }

        void setVec4(const std::string &name, float value_x, float value_y, float value_z, float value_w){
            glUniform4f(glGetUniformLocation(ID, name.c_str()), value_x, value_y, value_z, value_w);    
        }
};

#endif