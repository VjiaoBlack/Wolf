#ifndef KIWI_H
#define KIWI_H
/*
 * KIWI: KIWI Is What I want
 * KIWI is a simple 3d engine.
 */
typedef struct kiwi kiwi;

/*
 * POLYGON: POLYGON Or Love, You Give Our Name
 * POLYGON holds a triangle.
 */
typedef struct kiwi_polygon {
    float x1, x2, x3, y1, y2, y3, z1, z2, z3;
} kiwi_polygon;

/*
 * Creates a new Kiwi with the given screen width and height (in pixels) and sets two normalizing width and heights.
 * Returns NULL on an error.
 * example:
 *     kiwi *screen = new_wiki(640, 480, 1., 1.);
 */
kiwi *new_kiwi(int screen_width_pix, int screen_height_pix, double screen_width_meters, double screen_height_meters);

/*
 * Destroys the given kiwi.
 */
void free_kiwi(kiwi* screen);

/*
 * Run ONLY once before creating any kiwis. Sets up the environment.
 */
void pre_workout();

/*
 * Run ONLY once after destroying all kiwis. Destroys the environment.
 */
void post_workout();

/*
 * Draws a polygon in the kiwi.
 */
void kiwi_draw_polygon(kiwi *screen, kiwi_polygon *poly);
    
/*
 * Displays the current kiwi screen.
 */
void kiwi_show(kiwi *screen);
#endif
