#include <SDL3/SDL.h>
#include <stdio.h>
#include "vector.h"
#include "empty.h"
#include "mesh.h"

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    int Win_Width = 1920;
    int Win_Height = 1080;

    SDL_Window* window = SDL_CreateWindow("3D Renderer", Win_Width, Win_Height, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    mesh cube = load_model(".\\assets\\weirdmesh.obj");

    float FOV = 300.0f;
    vector3 camera = {0, 0, -5};
    float speed = 0.0015f;

    int running = 1;
    SDL_Event event;
    const bool* keys = SDL_GetKeyboardState(NULL);

    while (running) {

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = 0;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = 0;
        }

        if (keys[SDL_SCANCODE_W]) camera.z += speed;
        if (keys[SDL_SCANCODE_S]) camera.z -= speed;
        
        if (keys[SDL_SCANCODE_A]) camera.x -= speed;
        if (keys[SDL_SCANCODE_D]) camera.x += speed;
        
        if (keys[SDL_SCANCODE_SPACE])   camera.y -= speed;
        if (keys[SDL_SCANCODE_LSHIFT]) camera.y += speed;

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        SDL_FPoint screen_points[cube.v_count];
        float depths[cube.v_count];

        for (int i = 0; i < cube.v_count; i++)
        {
            float final_x = cube.vertices[i].x - camera.x;
            float final_y = cube.vertices[i].y - camera.y;
            float final_z = cube.vertices[i].z - camera.z;

            if (final_z <= 0.1f) final_z = 0.1f;

            float screenx = final_x*FOV/final_z - 2 + (Win_Width/2);
            float screeny = final_y*FOV/final_z - 2 + (Win_Height/2);

            screen_points[i].x = screenx;
            screen_points[i].y = screeny;
            depths[i] = final_z;

            if (cube.vertices[i].z > camera.z)
            {SDL_FRect rect = {screenx- 2, screeny - 2, 5, 5};
            SDL_RenderFillRect(renderer, &rect);}
        }

        for (int i = 0; i < cube.f_count; i++)
        {
            float x1 = screen_points[cube.faces[i].a].x;
            float y1 = screen_points[cube.faces[i].a].y;

            float x2 = screen_points[cube.faces[i].b].x;
            float y2 = screen_points[cube.faces[i].b].y; 

            float x3 = screen_points[cube.faces[i].c].x;
            float y3 = screen_points[cube.faces[i].c].y; 
            
            SDL_RenderLine(renderer, x1, y1, x2, y2);
            SDL_RenderLine(renderer, x2, y2, x3, y3);
            SDL_RenderLine(renderer, x3, y3, x1, y1);
        }
        

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}