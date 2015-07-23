#ifndef GFX_INCLUDE_BUFFER_OBJECT_H_
#define GFX_INCLUDE_BUFFER_OBJECT_H_
#include <GL/glew.h>
#include <stdio.h>
/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <GL/gl.h>

// TODO(dybisz) put set() functionality in the consturctor

class BufferObject
{
public:
    GLenum type;
    GLuint _id;

    ~BufferObject();
    BufferObject();
    template<typename T>
    void set(GLenum type, T list)
    {
        this->type = type;
        glGenBuffers(1, &_id);
        glBindBuffer(type, _id);
        glBufferData(type, list.size() * sizeof(glm::vec3), &list[0], GL_STATIC_DRAW);

    };


};

#endif
