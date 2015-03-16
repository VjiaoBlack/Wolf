#include <unistd.h>
#include "kiwi.h"

int main(int argc, char **argv) {
    // create a window
    pre_workout();
    kiwi *kamehameha = new_kiwi(512, 512, 1., 1.);

    // draw the polygon
    kiwi_polygon p = { -0.5f, -0.5f, 1.f, 0.5f, -0.5f, 1.f, 0.5f, 0.5f, 1.f };
    kiwi_draw_polygon(kamehameha, &p);
    
    // show the polygon
    kiwi_show(kamehameha);

    // wait for 5 seconds
    sleep(5);

    // destroy all humans!!!
    free_kiwi(kamehameha);
    post_workout();
}
