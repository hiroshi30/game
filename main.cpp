#include <SDL2/SDL.h>
#include <cstdlib>
#include <cstdio>

// #include "block.hpp"
// #include "camera.hpp"

const int window_width = 500;
const int window_height = 500

int** create_map(int width, int height) {
    float rnd;

    int** arr;

    arr = new int*[height];
    for (int h = 0; h < height; ++h) {
        arr[h] = new int[width];
        for (int w = 0; w < width; ++w) {
            rnd = std::rand() % 100;
            rnd = rnd / 100;
            if (rnd > 0.75)
                arr[h][w] = 1;
            else
                arr[h][w] = 0;
        }
    }

    return arr;
}



int main() {

    int** map = create_map(window_width / block_width, window_height / block_height);

    Camera camera = Camera(window_width / 2, window_height / 2);

    printf("{\n");
    for (int h = 0; h < window_height / block_height; ++h) {
        printf("    {");
        for (int w = 0; w < window_width / block_width; ++w) {
            printf("%i, ", map[h][w]);
        }
        printf("},\n");
    }
    printf("}\n");

    sf::RenderWindow window(sf::VideoMode(window_width, window_height), "SFML works!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                if (event.key.code == sf::Keyboard::W) {
                    camera.move_forward();
                }
                if (event.key.code == sf::Keyboard::S) {
                    camera.move_backward();
                }
                if (event.key.code == sf::Keyboard::D) {
                    camera.move_right();
                }
                if (event.key.code == sf::Keyboard::A) {
                    camera.move_left();
                }
            }
        }

        window.clear();

        for (int h = 0; h < window_height / block_height; ++h) {
            for (int w = 0; w < window_width / block_width; ++w) {
                if (map[h][w] == 1) {
                    Block block = Block(w * block_width, h * block_height);
                    window.draw(block.rect);
                }
            }
        }

        camera.update();
        window.draw(camera.circle);

        window.display();
    }

    for (int h = 0; h < window_height / block_height; ++h) {
        delete [] map[h];
    }
    delete [] map;
    map = 0;

    return 0;
}
