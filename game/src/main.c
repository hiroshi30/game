#include "engine.h"

#define window_width 16 * 70
#define window_height 9 * 70


int main(int argv, char **args) {

    int count = 1;

    Vector3f triangles[] = {
        (Vector3f){100, 250, 0},
        (Vector3f){200, 250, 0},
        (Vector3f){300, 250, 100}
    };

    // Vector3f triangles[] = {
    //     (Vector3f){0.0f, 0.0f, 1.0f},
    //     (Vector3f){0.5f, 1.0f, 1.0f},
    //     (Vector3f){1.0f, 0.0f, 1.0f},
    // };

    Vector3f *ptr_triangles = triangles;

    Engine_init(window_width, window_height);

    Camera *camera = Camera_create(0, 0, 0, 30, 10, 100, 0.1, 1000, 650);

    bool go = true;
    bool update = true;

    while(go) {
        if (update) {
            Camera_perspective_projection(camera, count, ptr_triangles);

            Engine_update();

            update = false;
        }

        while (Engine_event_status()) {
            go = Engine_event_exit();
            update = Camera_controls(camera);
        }
    }

    Camera_exit(camera);
    Engine_exit();

    return 0;
}
