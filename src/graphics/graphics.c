#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <GL/glew.h>
#include <SDL2/SDL_opengl.h>

#include <stdio.h>

#include "graphics.h"

void initialize() {
    puts("Initializing graphics.");
}

void destroy()  {
    puts("Destroying graphics.");
}

bool init() {
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    } else {
        //Use OpenGL 2.1
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2);
        SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1);

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        if (gWindow == NULL) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        } else {
            //Create context
            gContext = SDL_GL_CreateContext( gWindow );
            if (gContext == NULL) {
                printf("OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Use Vsync
                if (SDL_GL_SetSwapInterval (1) < 0) {
                    printf("Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
                }

                //Initialize OpenGL
                if (!initGL()) {
                    printf("Unable to initialize OpenGL!\n");
                    success = false;
                }
            }
        }
    }
    return success;
}

bool initGL() {
    bool success = true;
    GLenum error = GL_NO_ERROR;

    //Initialize Project Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if ( error != GL_NO_ERROR ) {
        printf("Error initializing OpenGL! %s\n", gluErrorString( error ));
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL %s \n", gluErrorString( error) );
        success = false;
    }

    //Initialize clear color
    glClearColor(0.f, 0.f, 0.f, 1.f);

    //Check for error
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf("Error initializing OpenGL! %s\n", gluErrorString( error ));
        success = false;
    }

    return success;
}

void handleKeys(unisgned char key, int x, int y) {
    //Toggle quad
    if (key == 'q') {
        gRenderQuad = !gRenderQuad;
    }
}

void update() {
    //No per frame update needed
}

void render() {
    //Clear color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    //Render quad
    if (gRenderQuad) {
        glBegin( GL_QUADS );
            glVertex2f( -0.5f, -0.5f);
            glVertex2f( 0.5f, -0.5f);
            glVertex2f( 0.5f, 0.5f);
            glVertex2f( -0.5f, 0.5f);
        glEnd();
    }
}

int main(int argc, char **argv) {
    initialize();
    puts("Hello world");
    destroy();
    exit(0);
}
