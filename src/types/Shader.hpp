#pragma once

// C++ Headers
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <spdlog/spdlog.h>

// OpenGL / glew Headers
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


namespace Kvant {

  struct Shader {
    
    Shader(const char* vertex_path, const char* fragment_path) {
      compile_shader(vertex_path, fragment_path);
    }

    //! Reads and build the shader, sets vertex and fragment id if successfull
    void compile_shader(const char* vertex_path, const char* fragment_path) {
      using namespace std;
      // 1. Retrieve the vertex/fragment source code from filePath
      string vertex_code;
      string fragment_code;
      ifstream v_shader_file;
      ifstream f_shader_file;
      // ensures ifstream objects can throw exceptions:
      v_shader_file.exceptions(std::ifstream::badbit);
      f_shader_file.exceptions(std::ifstream::badbit);
      try {
        // Open files
        v_shader_file.open(vertex_path);
        f_shader_file.open(fragment_path);
        std::stringstream v_shader_stream, f_shader_stream;
        // Read file's buffer contents into streams
        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();
        // close file handlers
        v_shader_file.close();
        f_shader_file.close();
        // Convert stream into GLchar array
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
      }
      catch(std::ifstream::failure e) {
        namespace spd = spdlog;
        spdlog::get("console")->error("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ  shaders: {}, {}", vertex_path, fragment_path);
      }

      const GLchar* v_shader_code = vertex_code.c_str();
      const GLchar* f_shader_code = fragment_code.c_str();

      // 2. Compile shaders
      GLint success;
      GLchar info_log[512];

      // Vertex Shader
      m_vertex_id = glCreateShader(GL_VERTEX_SHADER);
      glShaderSource(m_vertex_id, 1, &v_shader_code, NULL);
      glCompileShader(m_vertex_id);
      // Print compile errors if any
      glGetShaderiv(m_vertex_id, GL_COMPILE_STATUS, &success);
      if(!success) {
        glGetShaderInfoLog(m_vertex_id, 512, NULL, info_log);
        spdlog::get("console")->error("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n {}", info_log);
      };

      // Fragment Shader
      m_fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
      glShaderSource(m_fragment_id, 1, &f_shader_code, NULL);
      glCompileShader(m_fragment_id);
      // Print compile errors if any
      glGetShaderiv(m_fragment_id, GL_COMPILE_STATUS, &success);
      if(!success) {
        glGetShaderInfoLog(m_fragment_id, 512, NULL, info_log);
        spdlog::get("console")->error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n {}", info_log);
      };
    }

    ~Shader() {
      // Free memory from (supposedly) linked shader 
      glDeleteShader(m_vertex_id);
      glDeleteShader(m_fragment_id);
    }

    GLuint get_vertex_id() const { return m_vertex_id; }
    GLuint get_fragment_id() const { return m_fragment_id; }

  private:
    // Identifiers
    GLuint m_vertex_id, m_fragment_id;
    
  };
}
