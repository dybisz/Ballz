#include "ball.hpp"

/* ----- STATIC VARIABLES ----- */
const int Ball::RINGS                       = 20;
const int Ball::SECTORS                     = 20;
const int Ball::DATA_PER_VERTEX             = 3;
const int Ball::DATA_PER_QUAD               = 4;
const string Ball::FRAGMENT_SHADER_PATH     = "ball.glfs";
const string Ball::VERTEX_SHADER_PATH       = "ball.glvs";


Ball::Ball() : vertices(RINGS * SECTORS * DATA_PER_VERTEX), indices(RINGS * SECTORS * DATA_PER_QUAD)
{
    vertexShader.loadFromFile(VERTEX_SHADER_PATH, GL_VERTEX_SHADER);
    fragmentShader.loadFromFile(FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER);
    program.attachShaders(vertexShader.shaderID, fragmentShader.shaderID);
    mModel = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    mView = glm:: mat4(1.0f);
    mProjection = glm:: mat4(1.0f);
    generateVertices(5.0f);
    generateIndices();
    vbo.set(GL_ARRAY_BUFFER, vertices);
    indices_vbo.set(GL_ELEMENT_ARRAY_BUFFER, indices);
}
Ball::~Ball()
{

}

void Ball::setView(glm:: mat4 view)
{
    mView = view;
}

void Ball::setProjection(glm:: mat4 proj)
{
    mProjection = proj;
}

/**
 * Core rendering function for the ball.
 */
int Ball::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    program.useProgram();
    program.setModelMatrix(mModel);
    program.setViewMatrix(mView);
    program.setProjectionMatrix(mProjection);
    program.setVertices(vbo._id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_vbo._id);
    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, 0);

    program.stopProgram();

    return 1;
}

/**
 * Handling inputs.
 */
int Ball::handleInput(Config* config, vector<Drawable*> states)
{
    return 1;
}

/**
     * Based on {@link #RINGS} and {@link #SECTORS}, this method will produce
     * a set of vertices needed to render a sphere (using glDrawElements{} with GL_QUADS).
     *
     * @param radius Desired radius of the sphere.
     */
void Ball::generateVertices(float radius) {
    int RINGS = 20;
    int SECTORS = 20;
    float R = 1.0f / (float) (RINGS - 1);
    float S = 1.0f / (float) (SECTORS - 1);
    int offset = 0;
    for (float r = 0; r < RINGS; r++) {
        for (float s = 0; s < SECTORS; s++) {
            /* -----         Determine next sector in the current ring       -----*/
            float y = (GLfloat) sin(-PI / 2.0f + PI * r * R);
            float x = (GLfloat) cos(2.0f * PI * s * S) * (float) sin(PI * r * R);
            float z = (GLfloat) sin(2.0f * PI * s * S) * (float) sin(PI * r * R);
            /* -----         -----------------------------------------       -----*/

            /* -----    Save it     ----- */
            vertices[offset++] = radius * x;
            vertices[offset++] = radius * y;
            vertices[offset++] = radius * z;
            /* -----    -------     ----- */
        }
    }
}

/**
 * Based on {@link #RINGS} and {@link #SECTORS}, this method will produce
 * a set of indices needed to render a sphere (using glDrawElements{} with GL_QUADS).
 */
void Ball::generateIndices() {
    int offset = 0;
    for (int r = 0; r < RINGS - 1; r++)
        for (int s = 0; s < SECTORS - 1; s++) {
            indices[offset++] = (GLuint) (r * SECTORS + s);
            indices[offset++] = (GLuint) (r * SECTORS + (s + 1));
            indices[offset++] = (GLuint) ((r + 1) * SECTORS + (s + 1));
            indices[offset++] = (GLuint) ((r + 1) * SECTORS + s);
        }
}