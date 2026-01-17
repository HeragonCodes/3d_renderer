#include <SDL3/SDL.h>
#include <stdio.h>
#include <math.h>
#include "vector.h"
#include "empty.h"
#include "mesh.h"

int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_DisplayID primary = SDL_GetPrimaryDisplay();
    const SDL_DisplayMode *mode = SDL_GetDesktopDisplayMode(primary);
    int W = mode->w;
    float w = W / 2.0f;
    int H = mode->h;
    float h = H / 2.0f;

    Uint64 LAST = 0;
    Uint64 NOW = SDL_GetPerformanceCounter(); 
    double deltaTime = 0;

    SDL_Window* window = SDL_CreateWindow("3D Renderer", W, H, SDL_WINDOW_FULLSCREEN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, NULL);

    mesh model = load_model(".\\assets\\sphere.obj");
    vector2 screen_points[model.v_count];
    float depths[model.v_count];

    float FOV = 300.0f;
    empty camera = empty_init();
    camera.pos = (vector3){0, 0, -5};
    float camera_speed = 0.0015f;
    float camera_rotation_speed = 0.001f;

    int running = 1;
    SDL_Event event;
    const bool* keys = SDL_GetKeyboardState(NULL);

    while (running) {

        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();

        deltaTime = (double)((NOW - LAST)*1000 / (double)SDL_GetPerformanceFrequency());


        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EVENT_QUIT) running = 0;
            if (event.type == SDL_EVENT_KEY_DOWN && event.key.key == SDLK_ESCAPE) running = 0;
        }

        if (keys[SDL_SCANCODE_W]) camera.pos.z += camera_speed*deltaTime;
        if (keys[SDL_SCANCODE_S]) camera.pos.z -= camera_speed*deltaTime;
        
        if (keys[SDL_SCANCODE_A]) camera.pos.x -= camera_speed*deltaTime;
        if (keys[SDL_SCANCODE_D]) camera.pos.x += camera_speed*deltaTime;
        
        if (keys[SDL_SCANCODE_SPACE]) camera.pos.y -= camera_speed*deltaTime;
        if (keys[SDL_SCANCODE_LSHIFT]) camera.pos.y += camera_speed*deltaTime;

        if (keys[SDL_SCANCODE_UP]) camera.rot.x -= camera_rotation_speed*deltaTime;
        if (keys[SDL_SCANCODE_DOWN]) camera.rot.x += camera_rotation_speed*deltaTime;

        if (keys[SDL_SCANCODE_LEFT]) camera.rot.y -= camera_rotation_speed*deltaTime;
        if (keys[SDL_SCANCODE_RIGHT]) camera.rot.y += camera_rotation_speed*deltaTime;


        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

        float cosA = cos(camera.rot.x);
        float cosT = cos(camera.rot.y);
        float sinA = sin(camera.rot.x);
        float sinT = sin(camera.rot.y);

        float rotation_matrix[] = {
            cosT, 0, -sinT, 
            -sinT*sinA, cosA, -sinA*cosT, 
            cosA*sinT, sinA, cosA*cosT
        };
        matrix H = matrix_init(3, 3, rotation_matrix);

        for (int i = 0; i < model.v_count; i++)
        {
            vector3 point = {model.vertices[i].x - camera.pos.x, model.vertices[i].y - camera.pos.y, model.vertices[i].z - camera.pos.z};

            vec3_matrixmul(&point, H);

            float flat_x = FOV*point.x/point.z;
            float flat_y = FOV*point.y/point.z;

            flat_x += w-2;
            flat_y += h-2;

            screen_points[i] = (vector2){flat_x, flat_y};
            depths[i] = point.z;

            if (point.z > 0.1f)
            {SDL_FRect rect = {flat_x - 2, flat_y - 2, 5, 5};
            SDL_RenderFillRect(renderer, &rect);}
        }

        for (int i = 0; i < model.f_count; i++)
        {
            float x1 = screen_points[model.faces[i].a].x;
            float y1 = screen_points[model.faces[i].a].y;

            float x2 = screen_points[model.faces[i].b].x;
            float y2 = screen_points[model.faces[i].b].y; 

            float x3 = screen_points[model.faces[i].c].x;
            float y3 = screen_points[model.faces[i].c].y; 
            
            if (depths[model.faces[i].a] > 0 && depths[model.faces[i].b] > 0) SDL_RenderLine(renderer, x1, y1, x2, y2);
            if (depths[model.faces[i].b] > 0 && depths[model.faces[i].c] > 0) SDL_RenderLine(renderer, x2, y2, x3, y3);
            if (depths[model.faces[i].c] > 0 && depths[model.faces[i].a] > 0) SDL_RenderLine(renderer, x3, y3, x1, y1);
        }

        free_matrix(H);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}