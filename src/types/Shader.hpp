#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>

#include <GL/glew.h>



namespace Kvant {

  struct Shader {
    // The program ID
    GLuint programId;
    // Constructor reads and build the shader
    Shader(const char* vertexPath, const char* fragmentPath) {
      using namespace std;
      // 1. Retrieve the vertex/fragment source code from filePath
      string vertexCode;
      string fragmentCode;
      ifstream vShaderFile;
      ifstream fShaderFile;
      // ensures ifstream objects can throw exceptions:
      vShaderFile.exceptions(std::ifstream::badbit);
      fShaderFile.exceptions(std::ifstream::badbit);
      try {
        // Open files
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        std::stringstream vShaderStream, fShaderStream;
        // Read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // Convert stream into GLchar array
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
      }
      catch(std::ifstream::failure e) {
        namespace spd = spdlog;
        spdlog::get("console")->error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ  shaders: {}, {}", vertexPath, fragmentPath);
      }

      const GLchar* vShaderCode = vertexCode.c_str();
      const GLchar* fShaderCode = fragmentCode.c_str();

      // 2. Compile shaders
      GLuint vertex, fragment;
      GLint success;
      GLchar infoLog[512];

      // Vertex Shader
      vertex = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(vertex, 1, &vShaderCode, NULL);
      glCompileShader(vertex);
      // Print compile errors if any
      glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
      if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        spdlog::get("console")->error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n {}", infoLog);
      };

      // Fragment Shader
      fragment = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(fragment, 1, &fShaderCode, NULL);
      glCompileShader(fragment);
      // Print compile errors if any
      glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
      if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        spdlog::get("console")->error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n {}", infoLog);
      };

      // Shader Program
      this->programId = glCreateProgram();
      glAttachShader(this->programId, vertex);
      glAttachShader(this->programId, fragment);
      glLinkProgram(this->programId);
      // Print linkage errors if any
      glGetProgramiv(this->programId, GL_LINK_STATUS, &success);
      if(!success) {
        glGetProgramInfoLog(this->programId, 512, NULL, infoLog);
        spdlog::get("console")->error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n {}", infoLog);
      };

      // Delete the shaders as theyäre linked into our program now and no longer necessery
      glDeleteShader(vertex);
      glDeleteShader(fragment);
    }
    // Use the program
    void use() { glUseProgram(this->programId); }
  };

}
