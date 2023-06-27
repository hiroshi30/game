#include "math_a.h"
#include "engine2d.h"
#include "camera.h"
#include "globals.h"


#define window_width 16 * 70
#define window_height 9 * 70


int main(int argv, char **args) {

    Triangle triangles[] = {
        {
            (Vector3f){100, 250, 0},
            (Vector3f){200, 250, 0},
            (Vector3f){300, 250, 100}
        }
    };
    Triangle *ptr_triangles = triangles;

    Mesh *mesh = malloc(sizeof(Mesh));
    mesh->count = 1;
    mesh->triangles = ptr_triangles;
    
    Engine_init(window_width, window_height);
    Engine_keyboard_init();
    Engine_mouse_init();

    Camera *camera = Camera_create(120, 10, 0, 30, 10, 100, 1, 200, 650);

    bool go = true;
    bool update = true;

    while(go) {
        if (update) {
            Camera_perspective_projection(camera, mesh);

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
    free(mesh);

    return 0;
}
