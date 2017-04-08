#pragma once

// C++ Headers
#include <array>

// OpenGL / glew Headers
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// Kvant Headers
#include <types/Shader.hpp>

namespace Kvant {

  struct Program {
    
    /*! Generates program ID 
     *   
     *  Generates a program ID, shaders needs to be attached and linked seperatly
     */
    Program() {
      m_program_id = glCreateProgram();
    }

    //! Compiles, attaches and links shaders and generates a program ID
    Program(const char* vertex_path, const char* fragment_path) {
      m_program_id = glCreateProgram();
      
      Shader shader = Shader(vertex_path, fragment_path);      
      attach_shaders(shader);
      link_program();
    }

    Program(const Shader& shader) {
      
      m_program_id = glCreateProgram();

      attach_shaders(shader);
      link_program();
    }

    ~Program() {
      delete_program();
    }
    

    /*! Attaches the given shaders
     *  
     *  Calls glAttachShader for every shader Id in array
     *
     *  @param [in] shaders   Array of Shader Ids
     */
    template<typename Iterator>
    void attach_shaders(Iterator shaders_begin, Iterator shaders_end) const {
      // Attach shaders
      for (; shaders_begin != shaders_end; ++shaders_begin) {
        glAttachShader(m_program_id, *shaders_begin);
      }
    }

    /*! Attaches the given shaders
     *  
     *  Calls glAttachShader for every shader Id in array
     *
     *  @param [in] shaders   Array of Shader Ids
     */
    void attach_shaders(const Shader& shader) const {
      // Attach shaders
      glAttachShader(m_program_id, shader.get_vertex_id());
      glAttachShader(m_program_id, shader.get_fragment_id());
    }


    //! Links program, assumes shaders have been attached
    void link_program() const {
      glLinkProgram(m_program_id);
      
      // Print linkage errors if any
      GLint success;
      GLchar info_log[512];
      glGetProgramiv(m_program_id, GL_LINK_STATUS, &success);
      
      if(!success) {
        glGetProgramInfoLog(m_program_id, 512, NULL, info_log);
        spdlog::get("console")->error("ERROR::SHADER::PROGRAM::LINKING_FAILED\n {}", info_log);
      };
    }
    
    void delete_program() const {
      glDeleteProgram(m_program_id);
    }


    //! Sets program as active
    void use() const {
      glUseProgram(m_program_id);
    }
    
    /*! Checks if program is active
     *
     * @retval TRUE   Program is in use.
     * @retval FALSE  Program is NOT in use.
     */
    bool is_in_use() const {
      GLint current_program = 0;
      glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
      return (current_program == (GLint)m_program_id);
    }
    
    //! Removes program as active
    void stop_using() const {
      assert( is_in_use() );
      glUseProgram(0);
    }


    // Setters
    #define ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE, TYPE_PREFIX, TYPE_SUFFIX) \
\
    void set_attrib(const GLchar* name, OGL_TYPE v0) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX (get_attrib(name), v0); } \
    void set_attrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX (get_attrib(name), v0, v1); } \
    void set_attrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX (get_attrib(name), v0, v1, v2); } \
    void set_attrib(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX (get_attrib(name), v0, v1, v2, v3); } \
\
    void set_attrib1v(const GLchar* name, const OGL_TYPE* v) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 1 ## TYPE_SUFFIX ## v (get_attrib(name), v); } \
    void set_attrib2v(const GLchar* name, const OGL_TYPE* v) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 2 ## TYPE_SUFFIX ## v (get_attrib(name), v); } \
    void set_attrib3v(const GLchar* name, const OGL_TYPE* v) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 3 ## TYPE_SUFFIX ## v (get_attrib(name), v); } \
    void set_attrib4v(const GLchar* name, const OGL_TYPE* v) const \
        { assert(is_in_use()); glVertexAttrib ## TYPE_PREFIX ## 4 ## TYPE_SUFFIX ## v (get_attrib(name), v); } \
\
    void set_uniform(const GLchar* name, OGL_TYPE v0) const \
        { assert(is_in_use()); glUniform1 ## TYPE_SUFFIX (get_uniform(name), v0); } \
    void set_uniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1) const \
        { assert(is_in_use()); glUniform2 ## TYPE_SUFFIX (get_uniform(name), v0, v1); } \
    void set_uniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2) const \
        { assert(is_in_use()); glUniform3 ## TYPE_SUFFIX (get_uniform(name), v0, v1, v2); } \
    void set_uniform(const GLchar* name, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3) const \
        { assert(is_in_use()); glUniform4 ## TYPE_SUFFIX (get_uniform(name), v0, v1, v2, v3); } \
\
    void set_uniform1v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) const \
        { assert(is_in_use()); glUniform1 ## TYPE_SUFFIX ## v (get_uniform(name), count = 1, v); } \
    void set_uniform2v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) const \
        { assert(is_in_use()); glUniform2 ## TYPE_SUFFIX ## v (get_uniform(name), count = 1, v); } \
    void set_uniform3v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) const \
        { assert(is_in_use()); glUniform3 ## TYPE_SUFFIX ## v (get_uniform(name), count = 1, v); } \
    void set_uniform4v(const GLchar* name, const OGL_TYPE* v, GLsizei count = 1) const \
        { assert(is_in_use()); glUniform4 ## TYPE_SUFFIX ## v (get_uniform(name), count = 1, v); }

ATTRIB_N_UNIFORM_SETTERS(GLfloat, , f);
ATTRIB_N_UNIFORM_SETTERS(GLdouble, , d);
ATTRIB_N_UNIFORM_SETTERS(GLint, I, i);
ATTRIB_N_UNIFORM_SETTERS(GLuint, I, ui);

    void set_uniform_matrix2(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose = GL_FALSE) const {
      assert(is_in_use());
      glUniformMatrix2fv(get_uniform(name), count, transpose, v);
    }

    void set_uniform_matrix3(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose = GL_FALSE) const {
      assert(is_in_use());
      glUniformMatrix3fv(get_uniform(name), count, transpose, v);
    }

    void set_uniform_matrix4(const GLchar* name, const GLfloat* v, GLsizei count, GLboolean transpose = GL_FALSE) const {
      assert(is_in_use());
      glUniformMatrix4fv(get_uniform(name), count, transpose, v);
    }

    void set_uniform(const GLchar* name, const glm::mat2& m, GLboolean transpose = GL_FALSE) const {
      assert(is_in_use());
      glUniformMatrix2fv(get_uniform(name), 1, transpose, glm::value_ptr(m));
    }

    void set_uniform(const GLchar* name, const glm::mat3& m, GLboolean transpose = GL_FALSE) const {
      assert(is_in_use());
      glUniformMatrix3fv(get_uniform(name), 1, transpose, glm::value_ptr(m));
    }

    void set_uniform(const GLchar* name, const glm::mat4& m, GLboolean transpose = GL_FALSE) const {
      assert(is_in_use());
      glUniformMatrix4fv(get_uniform(name), 1, transpose, glm::value_ptr(m));
    }
    void set_uniform(const GLchar* uniformName, const glm::vec3& v) const {
      set_uniform3v(uniformName, glm::value_ptr(v));
    }

    void set_uniform(const GLchar* uniformName, const glm::vec4& v) const {
      set_uniform4v(uniformName, glm::value_ptr(v));
    }



    // Getters
    
    //! Returns Opengl generated program ID
    GLuint get_program_id() const { return m_program_id; }

    GLint get_attrib(const GLchar* attrib_name) const {
      if(!attrib_name)
        spdlog::get("console")->error("ERROR::SHADER::ATTRIB_NAME_IS_NULL");
      
      GLint attrib = glGetAttribLocation(m_program_id, attrib_name);
      if(attrib == -1)
        spdlog::get("console")->error("ERROR::SHADER::ATTRIB_NOT_FOUND");

      return attrib;
    }

    GLint get_uniform(const GLchar* uniform_name) const {
      if(!uniform_name) 
        spdlog::get("console")->error("ERROR::SHADER::UNIFORM_NAME_IS_NULL");
      
      GLint uniform = glGetUniformLocation(m_program_id, uniform_name);
      if(uniform == -1)
        spdlog::get("console")->error("ERROR::SHADER::UNIFORM_NOT_FOUND {}", uniform_name);
    
      return uniform;
    }

    private:
      GLuint m_program_id;
  };
};
