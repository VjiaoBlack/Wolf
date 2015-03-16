#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <OpenGL/GLU.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "kiwi.h"

/*
 * KIWI: KIWI Is What I want
 * KIWI is a simple 3d engine.
 */
struct kiwi {
    SDL_Window *gWindow;                              // The window that we'll draw on
    SDL_GLContext gContext;                           // The OpenGL Context
    double screen_width_meters, screen_height_meters; // The normalizing dimensions of the screen.
    int screen_width_pix, screen_height_pix;          // The physical dimensions of the screen
};

/*
 * Creates a new Kiwi with the given screen width and height (in pixels) and sets two normalizing width and heights.
 * Returns NULL on an error.
 * example:
 *     kiwi *screen = new_wiki(640, 480, 1., 1.);
 */
kiwi *new_kiwi(int screen_width_pix, int screen_height_pix, double screen_width_meters, double screen_height_meters) {
    kiwi *result = (kiwi*)malloc(sizeof(kiwi));

    result->screen_width_meters  = screen_width_meters;
    result->screen_height_meters = screen_height_meters;
    result->screen_width_pix     = screen_width_pix;
    result->screen_height_pix    = screen_height_pix;

    // Create the window.
    result->gWindow = SDL_CreateWindow("Kiwi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, result->screen_width_pix,
                                       result->screen_height_pix, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if ( result->gWindow == NULL ) {
        fprintf(stderr, "Window could not be created! SDL Error: %s\n", SDL_GetError());
        goto error;
    }

    // Create the context.
    result->gContext = SDL_GL_CreateContext( result->gWindow );
    if ( result->gContext == NULL ) {
        fprintf(stderr, "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError());
        goto error;
    }

    // Use VSync
    if ( SDL_GL_SetSwapInterval( 1 ) < 0 ) {
        fprintf(stderr, "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError());
    }

    // Initialize OpenGL
    {
        GLenum error = GL_NO_ERROR;
        
        // Initialize a Projection matrix.
        glMatrixMode( GL_PROJECTION );
        glLoadIdentity();
        
        // Check for any errors.
        error = glGetError();
        if (error != GL_NO_ERROR) {
            fprintf(stderr, "Error initializing OpenGL! %s\n", gluErrorString( error ) );      
            goto error;
        }

        // Initialize Modelview Matrix
        glMatrixMode( GL_MODELVIEW );
        glLoadIdentity();

        // Check for any errors.
        error = glGetError();
        if (error != GL_NO_ERROR) {
            fprintf(stderr, "Error Initializing OpenGL! %s\n", gluErrorString( error ) );
            goto error;
        }

        // Initiailize clear color
        glClearColor( 0.f, 0.f, 0.f, 1.f );
        
        // Check for any errors.
        error = glGetError();
        if (error != GL_NO_ERROR) {
            fprintf(stderr, "Error initializing OpenGL! %s\n", gluErrorString( error ) );
            goto error;
        }
    }

    return result;

    error:
    free((void*)result);
    return NULL;
}


/*
 * Destroys the given kiwi.
 */
void free_kiwi(kiwi* screen) {
    // Destroy window.
    SDL_DestroyWindow( screen->gWindow );
    screen->gWindow = NULL;
}

/*
 * Run ONLY once before creating any kiwis. Sets up the environment.
 */
void pre_workout() {
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
        fprintf("SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        return;
    }

    // Use OpenGL 2.1
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
    SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 1 );
}

/*
 * Run ONLY once after destroying all kiwis. Destroys the environment.
 */
void post_workout() {
    SDL_Quit();
}
