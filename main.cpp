//__ VBound Main CPP File

#include <glad/glad.h>
#include <SDL3/SDL.h>
#include <iostream>
#include <cmath>

// Vertex Shader source
const char* vertexShaderSrc = R"(
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 vColor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    vColor = aColor;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

// Fragment Shader source
const char* fragmentShaderSrc = R"(
#version 330 core
in vec3 vColor;
out vec4 FragColor;

void main() {
    FragColor = vec4(vColor, 1.0);
}
)";

// Cube vertices (positions + colors)
float vertices[] = {
    // positions        // colors
    -0.5f,-0.5f,-0.5f,  1.0f,0.0f,0.0f,
     0.5f,-0.5f,-0.5f,  0.0f,1.0f,0.0f,
     0.5f, 0.5f,-0.5f,  0.0f,0.0f,1.0f,
     0.5f, 0.5f,-0.5f,  0.0f,0.0f,1.0f,
    -0.5f, 0.5f,-0.5f,  1.0f,1.0f,0.0f,
    -0.5f,-0.5f,-0.5f,  1.0f,0.0f,0.0f,

    -0.5f,-0.5f, 0.5f,  1.0f,0.0f,1.0f,
     0.5f,-0.5f, 0.5f,  0.0f,1.0f,1.0f,
     0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,
     0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,
    -0.5f, 0.5f, 0.5f,  0.5f,0.5f,0.5f,
    -0.5f,-0.5f, 0.5f,  1.0f,0.0f,1.0f,

    -0.5f, 0.5f, 0.5f,  1.0f,0.0f,0.0f,
    -0.5f, 0.5f,-0.5f,  0.0f,1.0f,0.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,0.0f,1.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,0.0f,1.0f,
    -0.5f,-0.5f, 0.5f,  1.0f,1.0f,0.0f,
    -0.5f, 0.5f, 0.5f,  1.0f,0.0f,0.0f,

     0.5f, 0.5f, 0.5f,  1.0f,0.0f,1.0f,
     0.5f, 0.5f,-0.5f,  0.0f,1.0f,1.0f,
     0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,
     0.5f,-0.5f,-0.5f,  1.0f,1.0f,1.0f,
     0.5f,-0.5f, 0.5f,  0.5f,0.5f,0.5f,
     0.5f, 0.5f, 0.5f,  1.0f,0.0f,1.0f,

    -0.5f,-0.5f,-0.5f,  0.0f,1.0f,0.0f,
     0.5f,-0.5f,-0.5f,  1.0f,0.0f,0.0f,
     0.5f,-0.5f, 0.5f,  0.0f,0.0f,1.0f,
     0.5f,-0.5f, 0.5f,  0.0f,0.0f,1.0f,
    -0.5f,-0.5f, 0.5f,  1.0f,1.0f,0.0f,
    -0.5f,-0.5f,-0.5f,  0.0f,1.0f,0.0f,

    -0.5f, 0.5f,-0.5f,  1.0f,0.0f,1.0f,
     0.5f, 0.5f,-0.5f,  0.0f,1.0f,1.0f,
     0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,
     0.5f, 0.5f, 0.5f,  1.0f,1.0f,1.0f,
    -0.5f, 0.5f, 0.5f,  0.5f,0.5f,0.5f,
    -0.5f, 0.5f,-0.5f,  1.0f,0.0f,1.0f
};

// Simple 4x4 matrix multiplication helpers
void multiplyMatrix(const float* a, const float* b, float* out) {
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            out[i*4+j]=0;
            for(int k=0;k<4;k++) out[i*4+j] += a[i*4+k]*b[k*4+j];
        }
    }
}

// Simple perspective matrix
void perspective(float fov, float aspect, float near, float far, float* out){
    float f = 1.0f / tanf(fov/2);
    out[0]=f/aspect; out[1]=0; out[2]=0; out[3]=0;
    out[4]=0; out[5]=f; out[6]=0; out[7]=0;
    out[8]=0; out[9]=0; out[10]=(far+near)/(near-far); out[11]=-1;
    out[12]=0; out[13]=0; out[14]=(2*far*near)/(near-far); out[15]=0;
}

// Identity matrix
void identity(float* out){
    for(int i=0;i<16;i++) out[i]=0;
    out[0]=out[5]=out[10]=out[15]=1;
}

// Rotation around Y
void rotateY(float angle, float* out){
    identity(out);
    out[0]=cosf(angle);
    out[2]=sinf(angle);
    out[8]=-sinf(angle);
    out[10]=cosf(angle);
}

int main(int argc, char** argv) {
    if(!SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "SDL_Init Error: " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL3 X OpenGL  -  Rotating Cube", 800, 600, SDL_WINDOW_OPENGL |SDL_WINDOW_RESIZABLE |SDL_WINDOW_TRANSPARENT);

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if(!gladLoadGL()){
        std::cerr << "Failed to initialize GLAD\n";
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    // Compile shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Cube VAO & VBO
    GLuint VAO, VBO;
    glGenVertexArrays(1,&VAO);
    glGenBuffers(1,&VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)(3*sizeof(float)));
    glEnableVertexAttribArray(1);

    float angle = 0.0f;
    bool running = true;
    SDL_Event event;

    while(running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_EVENT_QUIT) running=false;
        }

        angle += 0.01f;

        glClearColor(0.1f,0.2f,0.3f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shaderProgram);

        // Model, view, projection
        float model[16]; rotateY(angle, model);
        float view[16]; identity(view); view[14]=-3.0f; // simple translate back
        float projection[16]; perspective(3.14159f/4.0f, 800.0f/600.0f, 0.1f, 100.0f, projection);

        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"model"),1,GL_FALSE,model);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"view"),1,GL_FALSE,view);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"projection"),1,GL_FALSE,projection);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES,0,36);

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1,&VAO);
    glDeleteBuffers(1,&VBO);
    glDeleteProgram(shaderProgram);
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
