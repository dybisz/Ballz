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


  // Number of vertices per side. Used when constructing default terrain
  static const int kSizePerSide;

  //
  static const float kMinPosition;

  //
  static const float kPositionRange;

  //
  static const int kDataPerVertex;

  //
  static const int kDataPerNormal;

  //
  static const int kNumberStripsRequired;

  //
  static const int kNumDegensRequired;

  //
  static const int kVerticesPerStrip;

 // Holds information about vertices on CPU
  std::vector <GLfloat> vertices_;

  // Holds information about normals on CPU
  std::vector <GLfloat> normals_;

  // Holds information about vertices order on CPU
  std::vector <GLuint> indices_;

  // Holds information about vertices in OpenGL buffer
  BufferObject buffer_vertices_;

  // Holds information about normals in OpenGL buffer
  BufferObject buffer_normals_;

  // Holds information about indices in OpenGL buffer
  BufferObject buffer_indices_;

  // Number of generated indices. Auxiliary variable.
  int index_count_;

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