#include "terrain.h"

const int Terrain::kSizePerSide = 32;
const float Terrain::kMinPosition = -5.0f;
const float Terrain::kPositionRange = 10.0f;
const int Terrain::kDataPerVertex = 3;
const int Terrain::kDataPerNormal = 3;
const int Terrain::kNumberStripsRequired = kSizePerSide - 1;
const int Terrain::kNumDegensRequired = 2 * (kNumberStripsRequired - 1);
const int Terrain::kVerticesPerStrip = 2 * kSizePerSide;

// TODO(dybisz) PORZADEK I GODNOSC

void Terrain::setView(glm::mat4 view) {
    mView = view;
}

void Terrain::setProjection(glm::mat4 proj) {
    mProjection = proj;
}

void Terrain::setCameraPosition(glm::vec3 cameraPosition) {
    vCameraPosition = cameraPosition;
}

/**
 * Core rendering function for the ball.
 */
int Terrain::render() {
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_FRONT_AND_BACK);
//
    program.useProgram();
    program.setModelMatrix(mModel);
    program.setViewMatrix(mView);
    program.setProjectionMatrix(mProjection);
    program.setCameraPosition(vCameraPosition);

    program.setVertices(buffer_vertices_._id);
    program.setNormals(buffer_normals_._id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer_indices_._id);
    glDrawElements(GL_TRIANGLE_STRIP, indices_.size(), GL_UNSIGNED_INT, 0);
    program.stopProgram();

    return 1;
}

Terrain::Terrain()
    : vertices_(kDataPerVertex * kSizePerSide * kSizePerSide),
      normals_(kDataPerNormal * kSizePerSide * kSizePerSide),
      indices_((kVerticesPerStrip * kNumberStripsRequired) + kNumDegensRequired)
{
    int x_length = kSizePerSide;
    int y_length = kSizePerSide;
    int v_offset = 0;
    int n_offset = 0;
    for ( int y = 0; y < y_length; ++y) {
        for ( int x = 0; x < x_length; ++ x) {

            /* ----- FEATURES ----- */
            const float x_ratio = x / (float) (x_length - 1);
            const float y_ratio = 1.0f - (y / (float) (y_length - 1));
            const float x_position = kMinPosition + (x_ratio * kPositionRange);
            const float y_position = kMinPosition + (y_ratio * kPositionRange);
            const float x_slope = (2 * x_position) / 10.0f;
            const float y_slope = (2 * y_position) / 10.0f;
            glm::vec3 vec_plane_X(1.0f, 0.0f, x_slope);
            glm::vec3 vec_plane_Y(0.0f, 1.0f, y_slope);
            glm::vec3 normal = glm::normalize(glm::cross(vec_plane_X, vec_plane_Y));

            /* ----- VERTEX POSITION ----- */
            vertices_[v_offset++] = x_position;
            vertices_[v_offset++] = ((x_position * x_position) + (y_position * y_position)) / 10.0f;
            vertices_[v_offset++] = y_position;

            /* ----- NORMAL DATA ----- */
            normals_[n_offset++] = normal.x;
            normals_[n_offset++] = normal.y;
            normals_[n_offset++] = normal.z;

        }
    }

    int i_offset = 0;

    for ( int y = 0; y < y_length - 1; ++y ) {
        if ( y > 0 ) {
            indices_[i_offset++] = (short) (y * y_length);
        }
        for ( int x = 0; x < x_length; ++x ) {
            indices_[i_offset++] = (short) ((y * y_length) + x);
            indices_[i_offset++] = (short) (((y + 1) * y_length) + x);
        }
        if ( y < y_length - 2 ) {
            indices_[i_offset++] = (short) (((y + 1) * y_length) + (x_length - 1));
        }
    }

    vertexShader.loadFromFile("res/terrain.glvs", GL_VERTEX_SHADER);
    fragmentShader.loadFromFile("res/terrain.glfs", GL_FRAGMENT_SHADER);
    program.attachShaders(vertexShader.shaderID, fragmentShader.shaderID);
    mModel = glm::translate(glm::mat4(1.f), glm::vec3(0.f, -10.0f, 0.f));
    mView = glm::mat4(1.0f);
    mProjection = glm::mat4(1.0f);
    buffer_vertices_.set(GL_ARRAY_BUFFER, vertices_);
    buffer_normals_.set(GL_ARRAY_BUFFER, normals_);
    buffer_indices_.set(GL_ELEMENT_ARRAY_BUFFER, indices_);
}

Terrain::~Terrain()
{

}