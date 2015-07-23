#ifndef GFX_INCLUDE_PERSPECTIVE_CAMERA_H_
#define GFX_INCLUDE_PERSPECTIVE_CAMERA_H_

#define PI 3.14159265
#include <math.h>
#include <stdio.h>

/* ----- GLM ----- */
#define GLM_FORCE_RADIANS
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class PerspectiveCamera
{
private:
//    static const float SCROLL_SPEED;
    float theta;
    float phi;
    float radius;
    glm::mat4 projection;
    glm::mat4 lookAt;
    float calculateX();
    float calculateY();
    float calculateZ();
    void recalculateLookAt();
public:
    PerspectiveCamera();
    ~PerspectiveCamera();
    glm::mat4 getProjection();
    glm::mat4 getView();
    void updatePosition(float, float);
    void updateRadius(float);
    glm::vec3 getPosition();
};

#endif