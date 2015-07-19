#include "perspective_cam.hpp"

PerspectiveCamera::PerspectiveCamera()
{
    projection  = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 100.f);
    lookAt      = glm::lookAt(glm::vec3(4,3,3), glm::vec3(0,0,0),glm::vec3(0,1,0));

}

PerspectiveCamera::~PerspectiveCamera()
{

}