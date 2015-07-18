#include "ball.hpp"

const string Ball::FRAGMENT_SHADER_PATH = "ball.glfs";
const string Ball::VERTEX_SHADER_PATH = "ball.glvs";

Ball::Ball()
{
    vertexShader.loadFromFile(VERTEX_SHADER_PATH, GL_VERTEX_SHADER);
    fragmentShader.loadFromFile(FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER);
    program.attachShaders(vertexShader.shaderID, fragmentShader.shaderID);
}
Ball::~Ball()
{

}
/**
 * Core rendering function for the ball.
 */
int Ball::render()
{
    return 1;
}

/**
 * Handling inputs.
 */
int Ball::handleInput(Config* config, vector<Drawable*> states)
{
    return 1;
}