#include "perspective_cam.h"

//const float PerspectiveCamera::SCROLL_SPEED = 80;

PerspectiveCamera::PerspectiveCamera()
{
    theta       = 45;
    phi         = 5;
    radius      = 35;
    projection  = glm::perspective(45.0f, 4.0f / 3.0f, 0.1f, 1000.f);
    lookAt      = glm::lookAt(glm::vec3(calculateX(),calculateY(),calculateZ()), glm::vec3(0,0,0),glm::vec3(0,1,0));

}

PerspectiveCamera::~PerspectiveCamera()
{

}

// TODO(dybisz) CLAMP / MAX/ MIN functions in #define form
/**
 * Providing change on X and Y axis, camera will recalculate its position
 * by modifying lookAt matrix.
 */
void PerspectiveCamera::updatePosition(float deltaX, float deltaY)
{
    theta    += deltaX;
    phi      += deltaY;

    phi = (phi > 180) ? 180 : phi;
    phi = (phi < 0) ? 0 : phi;

    recalculateLookAt();
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

/**
 * The camera moves in sphere coordinates, hence due to change of one of the
 * angles (theta/phi) coordinate X must be recalculated.
 */
float PerspectiveCamera::calculateX()
{
    return radius * -sinf(theta * (M_PI/180.0f)) * cosf(phi * (M_PI/180.0f));
}

/**
 * The camera moves in sphere coordinates, hence due to change of one of the
 * angles (theta/phi) coordinate Y must be recalculated
 */
float PerspectiveCamera::calculateY()
{
    return radius * -sinf(phi * (M_PI/180.0f));
}

/**
 * The camera moves in sphere coordinates, hence due to change of one of the
 * angles (theta/phi) coordinate Z must be recalculated.
 */
float PerspectiveCamera::calculateZ()
{
    return -radius * cosf(theta * (M_PI/180.0f)) * cosf(phi * (M_PI/180.0f));
}

/**
 * Used to simulate zooming in/out.
 */
void PerspectiveCamera::updateRadius(float deltaRadius)
{
    radius += deltaRadius;
    recalculateLookAt();
}

void PerspectiveCamera::recalculateLookAt()
{
    lookAt  = glm::lookAt(glm::vec3(calculateX(),calculateY(),calculateZ()), glm::vec3(0,0,0),glm::vec3(0,1,0));
}

glm::vec3 PerspectiveCamera::getPosition()
{
    glm::vec3 position(calculateX(), calculateY(), calculateZ());
    return position;
}