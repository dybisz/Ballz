#ifndef __CAMERA__
#define __CAMERA__

/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PerspectiveCamera
{
private:
    glm::mat4 projection;
    glm::mat4 lookAt;

public:
    PerspectiveCamera();
    ~PerspectiveCamera();

};

#endif