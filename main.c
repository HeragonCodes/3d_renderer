#include <SDL3/SDL.h>
#include <stdio.h>
#include <math.h>

#define n 8
#define conns 12

typedef struct {float x, y, z;} vector3;


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    int Win_Width = 640;
    int Win_Height = 480;

    SDL_Window* window = SDL_CreateWindow("3D Renderer", Win_Width, Win_Height, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    vector3 points[n] = {
        {-1.0f, 1.0f, 1.0f},
        {1.0f, 1.0f, 1.0f},
        {1.0f, -1.0f, 1.0f},
        {-1.0f, -1.0f, 1.0f},
        {-1.0f, 1.0f, -1.0f},
        {1.0f, 1.0f, -1.0f},
        {1.0f, -1.0f, -1.0f},
        {-1.0f, -1.0f, -1.0f},
    };

    int connections[conns][2] = {
        {0, 1}, {1, 2}, {2, 3}, {3, 0}, {0, 4}, {1, 5}, {2, 6}, {3, 7}, {4, 5}, {5, 6}, {6, 7}, {7, 4}
    };

    float FOV = 200.0f;
    vector3 camera = {0, 0, -5};


    int running = 1;
    SDL_Event event;


    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = 0;
            else if (event.type == SDL_EVENT_KEY_DOWN) {
                switch (event.key.key) {
                    case SDLK_ESCAPE: running = 0; break;
                    case SDLK_W: camera.z += 0.2f; break; 
                    case SDLK_S: camera.z -= 0.2f; break;
                    case SDLK_A: camera.x -= 0.2f; break; 
                    case SDLK_D: camera.x += 0.2f; break;
                    case SDLK_UP: camera.y -= 0.2f; break;
                    case SDLK_DOWN: camera.y += 0.2f; break;
                }
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_FPoint screen_points[n];

        for (int i = 0; i < n; i++)
        {
            float final_x = points[i].x - camera.x;
            float final_y = points[i].y - camera.y;
            float final_z = points[i].z - camera.z;

            if (final_z <= 0.1f) final_z = 0.1f;

            float screenx = final_x*FOV/final_z - 2 + (Win_Width/2);
            float screeny = final_y*FOV/final_z - 2 + (Win_Height/2);

            screen_points[i].x = screenx;
            screen_points[i].y = screeny;

            SDL_FRect rect = {screenx- 2, screeny - 2, 5, 5};
            SDL_RenderFillRect(renderer, &rect);
        }

        for (int i = 0; i < conns; i++)
        {
            SDL_RenderLine(renderer, screen_points[connections[i][0]].x, screen_points[connections[i][0]].y, screen_points[connections[i][1]].x, screen_points[connections[i][1]].y);
        }
        

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}