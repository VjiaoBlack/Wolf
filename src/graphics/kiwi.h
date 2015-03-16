#ifndef KIWI_H
#define KIWI_H
/*
 * KIWI: KIWI Is What I want
 * KIWI is a simple 3d engine.
 */
typedef struct kiwi kiwi;

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
#endif
