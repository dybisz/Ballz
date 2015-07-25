#include "ball.h"

/* ----- STATIC VARIABLES ----- */
const int Ball::RINGS = 20;
const int Ball::SECTORS = 20;
const int Ball::DATA_PER_VERTEX = 3;
const int Ball::DATA_PER_NORMAL = 3;
const int Ball::DATA_PER_QUAD = 4;
const string Ball::FRAGMENT_SHADER_PATH = "res/ball.glfs";
const string Ball::VERTEX_SHADER_PATH = "res/ball.glvs";


Ball::Ball()
        : vertices(RINGS * SECTORS * DATA_PER_VERTEX),
          normals(RINGS * SECTORS * DATA_PER_NORMAL),
          indices(RINGS * SECTORS * DATA_PER_QUAD) {
    vertexShader.loadFromFile(VERTEX_SHADER_PATH, GL_VERTEX_SHADER);
    fragmentShader.loadFromFile(FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER);
    program.attachShaders(vertexShader.shaderID, fragmentShader.shaderID);
    mModel = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    mView = glm::mat4(1.0f);
    mProjection = glm::mat4(1.0f);
    generateVerticesAndNormals(5.0f);
    generateIndices();
    bVertices.set(GL_ARRAY_BUFFER, vertices);
    bNormals.set(GL_ARRAY_BUFFER, normals);
    bIndices.set(GL_ELEMENT_ARRAY_BUFFER, indices);
}

Ball::~Ball() {

}

// TODO(dybisz) comments!!!
void Ball::setView(glm::mat4 view) {
    mView = view;
}

void Ball::setProjection(glm::mat4 proj) {
    mProjection = proj;
}

void Ball::setCameraPosition(glm::vec3 cameraPosition) {
    vCameraPosition = cameraPosition;
}

/**
 * Core rendering function for the ball.
 */
int Ball::render() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    program.useProgram();
    program.setModelMatrix(mModel);
    program.setViewMatrix(mView);
    program.setProjectionMatrix(mProjection);
    program.setCameraPosition(vCameraPosition);

    program.setVertices(bVertices._id);
    program.setNormals(bNormals._id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bIndices._id);

    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_INT, 0);

    program.stopProgram();

    return 1;
}

/**
 * Handling inputs.
 */
int Ball::handleInput(Config * config, vector < Drawable * > states) {
    return 1;
}
// TODO(dybisz) glm::vec3 center as a member of the class
/**
     * Based on {@link #RINGS} and {@link #SECTORS}, this method will produce
     * a set of vertices needed to render a sphere (using glDrawElements{} with GL_QUADS).
     *
     * @param radius Desired radius of the sphere.
     */
void Ball::generateVerticesAndNormals(float radius) {
    glm::vec3 center(0.0f, 0.0f, 0.0f);
    float R = 1.0f / (float) (RINGS - 1);
    float S = 1.0f / (float) (SECTORS - 1);
    int v_offset = 0;
    int n_offset = 0;
    for ( float r = 0; r < RINGS; r++ ) {
        for ( float s = 0; s < SECTORS; s++ ) {
            /* -----         Determine next sector in the current ring       -----*/
            float y = (GLfloat) sin(-PI / 2.0f + PI * r * R);
            float x = (GLfloat) cos(2.0f * PI * s * S) * (float) sin(PI * r * R);
            float z = (GLfloat) sin(2.0f * PI * s * S) * (float) sin(PI * r * R);
            /* -----         -----------------------------------------       -----*/

            /* -----    VERTICES     ----- */
            vertices[v_offset++] = radius * x;
            vertices[v_offset++] = radius * y;
            vertices[v_offset++] = radius * z;
            /* -----    -------      ----- */

            /* ----- NORMALS ----- */
            normals[n_offset++] = (radius * x) - center.x;
            normals[n_offset++] = (radius * y) - center.y;
            normals[n_offset++] = (radius * z) - center.z;
        }
    }
}

/**
 * Based on {@link #RINGS} and {@link #SECTORS}, this method will produce
 * a set of indices needed to render a sphere (using glDrawElements{} with GL_QUADS).
 */
void Ball::generateIndices() {
    int offset = 0;
    for ( int r = 0; r < RINGS - 1; r++ )
        for ( int s = 0; s < SECTORS - 1; s++ ) {
            indices[offset++] = (GLuint)(r * SECTORS + s);
            indices[offset++] = (GLuint)(r * SECTORS + (s + 1));
            indices[offset++] = (GLuint)((r + 1) * SECTORS + (s + 1));
            indices[offset++] = (GLuint)((r + 1) * SECTORS + s);
        }
}

