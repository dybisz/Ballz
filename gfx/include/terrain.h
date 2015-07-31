// author: dybisz
//
// Class describes terrain of the game. It is able to render itself
// as both, wireframe and fully textured. In addition there exists set
// of methods, which is able to establish whether collision occurred.
//
#ifndef GFX_INCLUDE_TERRAIN_H_
#define GFX_INCLUDE_TERRAIN_H_

#define GLM_FORCE_RADIANS
#include <vector>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "buffer_object.h"
#include "shader.h"
#include "shader_program.h"
#include <GL/gl.h>
#include <GL/glu.h>
#include <SOIL.h>

// TODO(dybisz) loading from .png/.bmp
// TODO(dybisz) default drawing from predefined mathematical functions
// TODO(dybisz) drawing using wireframe
// TODO(dybisz) drawing using texture
// TODO(dybisz) drawing based on loaded image

class Terrain {
 public:
  void setView(glm::mat4);

   void setProjection(glm::mat4);

   void setCameraPosition(glm::vec3);

   int render();

   Terrain();

  ~Terrain();

 private:
  // Path to the fragment shader
  static const string FRAGMENT_SHADER_PATH;

  // Path to the vertex shader
  static const string VERTEX_SHADER_PATH;

  // Number of indices along X axis
  static const int TERRAIN_WIDTH;

  // Number of indices along Z axis
  static const int TERRAIN_DEPTH;

  // Maximum height for scaling process
  static const float TERRAIN_MAX_HEIGHT;

  //Number of information in each vertex
  static const int DATA_PER_VERTEX;

  // Holds information about vertices on CPU
  std::vector <GLfloat> _vertices;

  // Holds information about normals on CPU
  std::vector <GLfloat> _normals;

  // Holds information about vertices order on CPU
  std::vector <GLuint> _indices;

  // Holds information about vertices in OpenGL buffer
  BufferObject _buffer_vertices;

  // Holds information about normals in OpenGL buffer
  BufferObject _buffer_normals;

  // Holds information about indices in OpenGL buffer
  BufferObject _buffer_indices;

  // Number of generated indices. Auxiliary variable.
  int _index_count;

  //
  glm::mat4 mModel;

  //
  glm::mat4 mView;

  //
  glm::mat4 mProjection;

  //
  glm::vec3 vCameraPosition;

  //
  Shader vertexShader;

  //
  Shader fragmentShader;

  //
  ShaderProgram program;
};

#endif