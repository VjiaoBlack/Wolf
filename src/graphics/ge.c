/*
 * ge.c
 * The graphics engine used by Wolf.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/GLU.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "ge.h"

// The window that we'll draw on.
SDL_Window *gWindow = NULL;

// OpenGL context
SDL_GLContext gContext;

bool initGL();

bool init() {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return false;
    }
    
    // Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );

    // Create a window
    gWindow = SDL_CreateWindow( "Project Wolf", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
    if ( gWindow == NULL ) {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    // Create a context
    gContext = SDL_GL_CreateContext( gWindow );
    if ( gContext == NULL ) {
        printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
        return false;
    }

    // Use VSync
    if ( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        printf( "Warning: Unable to set VSync!: SDL Error: %s\n", SDL_GetError() );
    }
    
    // Initialize OpenGL
    if ( !initGL() ) {
        printf("Unable to initialize OpenGL!\n");
        return false;
    }

    return true;
}

bool initGL() {
    GLenum error = GL_NO_ERROR;

    // Initialize a Project Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    // Check for an error.
    error = glGetError();
    if (error != GL_NO_ERROR) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    // Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    // Check for an error
    error = glGetError();
    if ( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    // Initialize clear Color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    // Check for an error
    error = glGetError();
    if ( error != GL_NO_ERROR ) {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        return false;
    }

    return true;
}

void close() {
    // Destroy window
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    // Quit SDL subsystems
    SDL_Quit();
};

void drawTriangle(float *arr) {
    glBegin( GL_TRIANGLES );
        glVertex3f(arr[0], arr[1], arr[2]);
        glVertex3f(arr[3], arr[4], arr[5]);
        glVertex3f(arr[6], arr[7], arr[8]);
    glEnd();
}
int main( int argc, char **argv) {
    init();

    bool quit = false;
    SDL_Event e;
    SDL_StartTextInput();

    while (!quit) {
        while (SDL_PollEvent( &e ) != 0 ) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
        float arr[] = { -0.5f, -0.5f, 1.f, 0.5f, -0.5f, 1.f, 0.5f, 0.5f, 1.f };
        drawTriangle(arr); //-0.25f, -0.25f, 1.f, 0.25f, 0.25f, 1.f, 1.f, 1.f, 1.f);

        SDL_GL_SwapWindow( gWindow );
        glClear( GL_COLOR_BUFFER_BIT );
    }

    SDL_StopTextInput();

    close();

    return 0;
}       
