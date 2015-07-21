#include "shader_program.hpp"

/* ----- EXCEPTIONS ----- */
CreateProgEx        createProgEx;
DeleteProgEx        deleteProgEx;
AttachShdEx         attachShdEx;
LinkProgEx          linkShdEx;
LogProgEx           logProgEx;
UniformLocationEx   uniformLocationEx;
SetUniformMatEx     setUniformMatEx;

/* ----- STATIC VARIABLES ----- */
const GLchar* ShaderProgram::UNIFORM_MODEL_MATRIX           = "uModel";
const GLchar* ShaderProgram::UNIFORM_VIEW_MATRIX            = "uView";
const GLchar* ShaderProgram::UNIFORM_PROJECTION_MATRIX      = "uProjection";
const GLchar* ShaderProgram::ATTRIBUTE_POSITION             = "aPosition";


ShaderProgram::ShaderProgram()
{
    /* ----- CREATE PROGRAM ----- */
    try {
        createProgram();
    } catch(exception& e) {
        cout << e.what() << '\n';
    }
}

ShaderProgram::~ShaderProgram()
{
    try {
        deleteProgram();
    } catch(exception& e) {
        cout << e.what() << '\n';
    }
}

/**
 * Attaches provided shaders to the program and links it.
 */
void ShaderProgram::attachShaders(GLuint vertexShader, GLuint fragmentShader)
{
    /* ----- ATTACH SHADERS ----- */
    try{
        attachShader(vertexShader);
        attachShader(fragmentShader);
    } catch(exception& e) {
        cout << e.what() << '\n';
    }

    /* ----- LINK PROGRAM ----- */
    try {
        linkProgram();
    } catch(exception& e) {
        cout << e.what() << '\n';
;    }

}

/**
 * Method calls glCreateProgram() and throws appropriate exception when needed.
 */
void ShaderProgram::createProgram()
{
    programID = glCreateProgram();
    if(GL_INVALID_OPERATION == glGetError())
    {
        printf("[Error] glCreateProgram is executed between the execution of glBegin "
                       "and the corresponding execution of glEnd.");
        throw createProgEx;
    }
}

/**
 * Calls glDeleteProgram and check for errors.
 */
void ShaderProgram::deleteProgram()
{
    glDeleteProgram(programID);

    if(GL_INVALID_VALUE == glGetError())
    {
        printf("[Error] Program's id is not a value generated by OpenGL\n");
        throw deleteProgEx;
    }
}

/**
 * Calls glAttachShader and checks for every possible error.
 */
void ShaderProgram::attachShader(GLuint shaderID)
{
    glAttachShader(programID,shaderID);

    switch(glGetError())
    {
        case GL_INVALID_VALUE:
            printf("[Error] program: %d shader %d\n", (int)programID,(int)shaderID);
            printf("[Error] Either program or shader is not a value generated by OpenGL\n");
            throw attachShdEx;

        case GL_INVALID_OPERATION:
            printf("[Error] programID: %d shaderID %d\n", (int)programID,(int)shaderID);
            printf("[Error] Program's id does not represent a program "
                            "or shader's id does not represent shader or "
                           "shader is attached to another program\n");
            throw attachShdEx;
    }
}

/**
 * Method calls glLinkProgram() and checks for errors.
 * If everything is correct, log of the linking process is displayd,
 * if not - appropriate LinkProgrEx is thrown.
 */
void ShaderProgram::linkProgram()
{
    glLinkProgram(programID);

    /* ----- ERRORS FROM CALLING glLinkProgram() */
    switch(glGetError())
    {
        case GL_INVALID_VALUE:
            printf("[Error] programID: %d", (int) programID);
            printf("[Error] Program's id is not a value generated by OpenGL\n");
            throw linkShdEx;
        case GL_INVALID_OPERATION:
            printf("[Error] programID: %d", (int) programID);
            printf("[Error] Program's id does not represent program\n");
            throw linkShdEx;
    }

    /* ----- LOG FROM LINKING PROCESS ----- */
    GLint programSuccess = GL_TRUE;
    glGetProgramiv(programID, GL_LINK_STATUS, &programSuccess);

    if( programSuccess != GL_TRUE )
    {
        printf( "[Error] Linking program %d!\n", programID );
        printProgramLog( programID );
        throw linkShdEx;
    }

    /* ----- VALIDATE ----- */
    glValidateProgram(programID);
    if(GL_INVALID_VALUE == glGetError()) printf("macki Boga\n");
}

/**
 * Prints on stdout log of provided program. ALl possible errors are handled
 * and if any occurred, appropriate exception is thrown.
 */
void ShaderProgram::printProgramLog(GLuint programID)
{
    if(glIsProgram(programID))
    {
        int infoLogLength = 0;
        int maxLength = infoLogLength;

        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);

        char* infoLog = new char[maxLength];

        getInfoLog(programID, maxLength, &infoLogLength, infoLog);
        if( infoLogLength > 0 )
        {
            printf("[Error] Log: \n");
            printf( "%s\n",infoLog);
        }
        //Deallocate string
        delete[] infoLog;
    }
    else
    {
        printf( "[Error] programID %d is not representing a program\n", programID);
        throw logProgEx;
    }
}
//TODO error check
/**
 * Sets the program as a currently used.
 */
void ShaderProgram::useProgram()
{
    glUseProgram(programID);
    /* ----- VALIDATE ----- */
    glValidateProgram(programID);
    if(GL_INVALID_VALUE == glGetError()) printf("macki Boga\n");
}
//TODO error check
/**
 * Prevents OpenGL from using this program.
 */
void ShaderProgram::stopProgram()
{
    glUseProgram(0);
}

/**
 * Sets up approriate variable in the shader. All errors are handled.
 */
void ShaderProgram::setModelMatrix(glm::mat4 modelMatrix)
{
    GLint _id = -1;
    try {
        _id = getUniform(UNIFORM_MODEL_MATRIX);
    }catch(exception& e) {
        printf("[Error] setModelMatrix() call\n");
        return;
    }
    try {
        setUniformMatrix(_id, 1, GL_FALSE, &modelMatrix[0][0]);
    } catch (exception& e) {
        printf("[Error] setModelMatrix() call\n");
        return;
    }
}

/**
 * Sets up approriate variable in the shader. All errors are handled.
 */
void ShaderProgram::setViewMatrix(glm::mat4 viewMatrix)
{
    GLint _id = -1;
    try {
        _id = getUniform(UNIFORM_VIEW_MATRIX);
    }catch(exception& e) {
        printf("[Error] setViewMatrix() call\n");
        return;
    }
    try {
        setUniformMatrix(_id, 1, GL_FALSE, &viewMatrix[0][0]);
    } catch (exception& e) {
        printf("[Error] setViewMatrix() call\n");
        return;
    }
}

/**
 * Sets up approriate variable in the shader. All errors are handled.
 */
void ShaderProgram::setProjectionMatrix(glm::mat4 projectionMatrix)
{
    GLint _id = -1;
    try {
        _id = getUniform(UNIFORM_PROJECTION_MATRIX);
    }catch(exception& e) {
        printf("[Error] setProjectionMatrix() call\n");
        return;
    }
    try {
        setUniformMatrix(_id, 1, GL_FALSE, &projectionMatrix[0][0]);
    } catch (exception& e) {
        printf("[Error] setProjectionMatrix() call\n");
        return;
    }
}
//TODO comment
//TODO error handling
//TODO if aPosition not found - print "no aPosition pointer - is it correct shader source" or whatever

void ShaderProgram::setVertices(GLuint bufferID)
{
    GLuint aPosition = glGetAttribLocation(programID, ATTRIBUTE_POSITION);

    glBindBuffer(GL_ARRAY_BUFFER, bufferID);
    glVertexAttribPointer(
            aPosition,  // The attribute we want to configure
            3,                            // size
            GL_FLOAT,                     // type
            GL_FALSE,                     // normalized?
            0,                            // stride
            (void*)0                      // array buffer offset
    );
    glEnableVertexAttribArray(aPosition);
}

/**
 * Handles errors for glGetUniformLocation call.
 */
GLuint ShaderProgram::getUniform(const GLchar* name)
{
    GLuint _id = glGetUniformLocation(programID, name);

    switch(glGetError()) {

        case GL_INVALID_VALUE:
            printf("[Error] Program's id is not a value generated by OpenGL\n");
            throw uniformLocationEx;

        case GL_INVALID_OPERATION:
            printf("[Error] Program's id does not represents program object "
                           "or program has not been successfully linked\n");
            throw uniformLocationEx;

    }
    return _id;
}

/**
 * Handles errors for glUniformMatrix4fv() call.
 */
void ShaderProgram::setUniformMatrix(GLint location, GLsizei count, GLboolean transpose, const GLfloat *value)
{
    glUniformMatrix4fv(location, count, transpose, value);

    switch(glGetError())
    {
        case GL_INVALID_OPERATION:
            printf("[Error] Possibilities\n"
                   "[Error] [*] There is no current program object\n"
                   "[Error] [*] size of the uniform variable declared in the shader does not "
                               "match the size indicated by the glUniform command\n"
                   "[Error] [*]  one of the integer variants of this function is used to load "
                           "a uniform variable of type float, vec2, vec3, vec4, or an array of these, "
                                 "or if one of the floating-point variants of this function is used to load "
                                 "a uniform variable of type int, ivec2, ivec3, or ivec4, or an array of these\n"
                   "[Error] [*] location is an invalid uniform location for the current program object and location "
                               "is not equal to -1\n"
                   "[Error] [*] count is greater than 1 and the indicated uniform variable is not an array variable\n"
                   "[Error] [*] a sampler is loaded using a command other than glUniform1i and glUniform1iv\n");
            throw setUniformMatEx;

        case GL_INVALID_VALUE:
            printf("[Error] count < 0 or transpose != GL_FALSE\n");
            throw setUniformMatEx;
    }
}
