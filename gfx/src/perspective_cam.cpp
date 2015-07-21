#include "perspective_cam.hpp"

PerspectiveCamera::PerspectiveCamera()
{
    projection  = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    lookAt      = glm::lookAt(glm::vec3(4,3,25), glm::vec3(0,0,0),glm::vec3(0,1,0));

}

PerspectiveCamera::~PerspectiveCamera()
{

}

/**
 * Returns projection matrix. Useful e.g. for calculating coordinates
 * of the vertex in a shader.
 */
glm::mat4 PerspectiveCamera::getProjection()
{
    return projection;
}

/**
 * Returns view matrix. Useful e.g. for calculating coordinates
 * of the vertex in a shader.
 */
glm::mat4 PerspectiveCamera::getView()
{
    return lookAt;
}
