#include "terrain.h"

// TODO(dybisz) PORZADEK I GODNOSC

const int Terrain::TERRAIN_WIDTH = 50;
const int Terrain::TERRAIN_DEPTH = 50;
const float Terrain::TERRAIN_MAX_HEIGHT = 10.0f;
const int Terrain::DATA_PER_VERTEX = 3;
const string Terrain::FRAGMENT_SHADER_PATH = "res/terrain.glfs";
const string Terrain::VERTEX_SHADER_PATH = "res/terrain.glvs";

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
    glDisable(GL_CULL_FACE);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    program.useProgram();
    program.setModelMatrix(mModel);
    program.setViewMatrix(mView);
    program.setProjectionMatrix(mProjection);
    program.setCameraPosition(vCameraPosition);

    program.setVertices(_buffer_vertices._id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer_indices._id);

    glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);

    program.stopProgram();

    return 1;
}

Terrain::Terrain()
    : _vertices(TERRAIN_WIDTH * TERRAIN_DEPTH * DATA_PER_VERTEX),
      _indices(TERRAIN_WIDTH * TERRAIN_DEPTH * 3 * 2)       // TODO(dybisz) ogarnac tajemnice
{
    int texture_width = 0;
    int texture_height = 0;
    int channels = 0;

    /* ----- LOAD IMAGE DATA ----- */
    GLubyte* pData = SOIL_load_image("res/default_map.png", &texture_width, &texture_height, &channels, SOIL_LOAD_L);

    /* ----- SWAP IMAGE VERTICALLY ----- */
    for ( int j = 0; j * 2 < texture_height; ++j ) {
        int index1 = j * texture_width;
        int index2 = (texture_height -1 - j) * texture_width;
        for ( int i = texture_width; i > 0; --i ) {
            GLubyte temp = pData[index1];
            pData[index1] = pData[index2];
            pData[index2] = temp;
            ++index1;
            ++index2;
        }
    }

    /* ----- PREPARE GPU TEXTURE ----- */
    GLuint heightMapTextureID;
    glGenTextures(1, &heightMapTextureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, heightMapTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, texture_width, texture_height, 0, GL_RED, GL_UNSIGNED_BYTE, pData);

    /* ----- BIND TEXTURE AS A UNIFORM ----- */
    glUniform1i(glGetUniformLocation(program.programID, "heightMapTexture"), 0);

    /* ----- FREE IMAGE DATA ----- */
    SOIL_free_image_data(pData);

    /* ----- CREATE PLANE TERRAIN ----- */
    int v_offset = 0;
    for ( int j = 0; j < TERRAIN_DEPTH; ++j ) {
        for ( int i = 0; i < TERRAIN_WIDTH; ++i ) {
            _vertices[v_offset++] = float(i) / (TERRAIN_WIDTH - 1);
            _vertices[v_offset++] = 0;
            _vertices[v_offset++] = float(j) / (TERRAIN_DEPTH - 1);
        }
    }

    /* ----- CREATE INDICES ----- */
    int i_offset = 0;
    for ( int i = 0; i < TERRAIN_DEPTH-1; ++i ) {
        for ( int j = 0; j < TERRAIN_WIDTH-1; ++j ) {

            int i0 = j+ i*TERRAIN_WIDTH;
            int i1 = i0+1;
            int i2 = i0+TERRAIN_WIDTH;
            int i3 = i2+1;

            _indices[i_offset++] = i0;
            _indices[i_offset++] = i2;
            _indices[i_offset++] = i1;
            _indices[i_offset++] = i1;
            _indices[i_offset++] = i2;
            _indices[i_offset++] = i3;
        }
    }

    /* ----- ASSIGN REST OF UNIFORMS ----- */
    glUniform1f(glGetUniformLocation(program.programID, "scale"), TERRAIN_MAX_HEIGHT);


    /* ----- INIT MEMBERS ------  */
    vertexShader.loadFromFile(VERTEX_SHADER_PATH, GL_VERTEX_SHADER);
    fragmentShader.loadFromFile(FRAGMENT_SHADER_PATH, GL_FRAGMENT_SHADER);
    program.attachShaders(vertexShader.shaderID, fragmentShader.shaderID);
    mModel = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.f));
    mView = glm::mat4(1.0f);
    mProjection = glm::mat4(1.0f);
    _buffer_vertices.set(GL_ARRAY_BUFFER, _vertices);
    _buffer_indices.set(GL_ELEMENT_ARRAY_BUFFER, _indices);
}

Terrain::~Terrain() {

}