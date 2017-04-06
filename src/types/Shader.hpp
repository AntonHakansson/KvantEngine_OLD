#pragma once

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


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

      // Delete the shaders as they're linked into our program now and no longer necessery
      glDeleteShader(vertex);
      glDeleteShader(fragment);
    }

    // Use the program
    void use() const {
      glUseProgram(this->programId);
    }

    bool isInUse() const {
      GLint currentProgram = 0;
      glGetIntegerv(GL_CURRENT_PROGRAM, &currentProgram);
      return (currentProgram == (GLint)this->programId);
    }

    void stopUsing() const {
      assert( isInUse() );
      glUseProgram(0);
    }
    
    GLint attrib(const GLchar* attribName) const {
      if(!attribName)
        spdlog::get("console")->error("ERROR::SHADER::ATTRIB_NAME_IS_NULL");
      
      GLint attrib = glGetAttribLocation(this->programId, attribName);
      if(attrib == -1)
        spdlog::get("console")->error("ERROR::SHADER::ATTRIB_NOT_FOUND");

      return attrib;
    }

    GLint uniform(const GLchar* uniformName) const {
      if(!uniformName) 
        spdlog::get("console")->error("ERROR::SHADER::UNIFORM_NAME_IS_NULL");
      
      GLint uniform = glGetUniformLocation(this->programId, uniformName);
      if(uniform == -1)
        spdlog::get("console")->error("ERROR::SHADER::UNIFORM_NOT_FOUND {}", uniformName);
    
      return uniform;
    }


  
    #define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
    void setAttrib(const GLchar* name, OGL_TYPE v0) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (attrib(name), v0); } \
    void setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (attrib(name), v0, v1); } \
    void setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (attrib(name), v0, v1, v2); } \
    void setAttrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (attrib(name), v0, v1, v2, v3); } \
\
    void setAttrib1v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (attrib(name), v); } \
    void setAttrib2v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (attrib(name), v); } \
    void setAttrib3v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (attrib(name), v); } \
    void setAttrib4v(const GLchar* name, const OGL_TYPE* v) \
        { assert(isInUse()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (attrib(name), v); } \
\
    void setUniform(const GLchar* name, OGL_TYPE v0) \
        { assert(isInUse()); glUniform1 ## TYPE_SUFFIX (uniform(name), v0); } \
    void setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) \
        { assert(isInUse()); glUniform2 ## TYPE_SUFFIX (uniform(name), v0, v1); } \
    void setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) \
        { assert(isInUse()); glUniform3 ## TYPE_SUFFIX (uniform(name), v0, v1, v2); } \
    void setUniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) \
        { assert(isInUse()); glUniform4 ## TYPE_SUFFIX (uniform(name), v0, v1, v2, v3); } \
\
    void setUniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) \
        { assert(isInUse()); glUniform1 ## TYPE_SUFFIX ## v (uniform(name), count = 1, v); } \
    void setUniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) \
        { assert(isInUse()); glUniform2 ## TYPE_SUFFIX ## v (uniform(name), count = 1, v); } \
    void setUniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) \
        { assert(isInUse()); glUniform3 ## TYPE_SUFFIX ## v (uniform(name), count = 1, v); } \
    void setUniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) \
        { assert(isInUse()); glUniform4 ## TYPE_SUFFIX ## v (uniform(name), count = 1, v); }

ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
ATTRIB_N_UNIFORM_SETTERS(GLdouble, , d);
ATTRIB_N_UNIFORM_SETTERS(GLint, I, i);
ATTRIB_N_UNIFORM_SETTERS(GLuint, I, ui);


    void setUniformMatrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose = GL_FALSE) {
      assert(isInUse());
      glUniformMatrix2fv(uniform(name), count, transpose, v);
    }

    void setUniformMatrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose = GL_FALSE) {
      assert(isInUse());
      glUniformMatrix3fv(uniform(name), count, transpose, v);
    }

    void setUniformMatrix4(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose = GL_FALSE) {
      assert(isInUse());
      glUniformMatrix4fv(uniform(name), count, transpose, v);
    }

    void setUniform(const GLchar* name, const glm::mat2& m, GLboolean transpose = GL_FALSE) {
      assert(isInUse());
      glUniformMatrix2fv(uniform(name), 1, transpose, glm::value_ptr(m));
    }

    void setUniform(const GLchar* name, const glm::mat3& m, GLboolean transpose = GL_FALSE) {
      assert(isInUse());
      glUniformMatrix3fv(uniform(name), 1, transpose, glm::value_ptr(m));
    }

    void setUniform(const GLchar* name, const glm::mat4& m, GLboolean transpose = GL_FALSE) {
      assert(isInUse());
      glUniformMatrix4fv(uniform(name), 1, transpose, glm::value_ptr(m));
    }
    void setUniform(const GLchar* uniformName, const glm::vec3& v) {
      setUniform3v(uniformName, glm::value_ptr(v));
    }

    void setUniform(const GLchar* uniformName, const glm::vec4& v) {
      setUniform4v(uniformName, glm::value_ptr(v));
    }
  };
}
