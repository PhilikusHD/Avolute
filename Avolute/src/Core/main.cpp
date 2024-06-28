#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image/SDL_image.h>
#include <memory>
#include <vector>


#include "Avolute.h"
#include "Entity.h"
#include "RenderWindow.h"
#include "Utils.h"

#include <backends/imgui_impl_sdl2.h>
#include <backends/imgui_impl_sdlrenderer2.h>
#include <imgui.h>


// https://lazyfoo.net/tutorials/SDL/index.php#Optimized%20Surface%20Loading%20and%20Soft%20Stretching

enum KeyPressSurfaces
{
    KEY_PRESS_DEFAULT,
    KEY_PRESS_UP,
    KEY_PRESS_DOWN,
    KEY_PRESS_LEFT,
    KEY_PRESS_RIGHT,
    KEY_PRESS_TOTAL
};

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) > 0)
    {
        Log("Failed to initialize SDL2. SDL_ERROR: %s", SDL_GetError());
    }
    if (!(IMG_Init(IMG_INIT_PNG)))
    {
        Log("Failed to initialize SDL_image. ERROR: %s", SDL_GetError());
    }

    RenderWindow window("Avolute", 1280, 720);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    ImGui::StyleColorsDark();
    ImGui_ImplSDL2_InitForSDLRenderer(window.GetWindow(), window.GetRenderer());
    ImGui_ImplSDLRenderer2_Init(window.GetRenderer());


    SDL_Texture *grassTexture = window.loadTexture("../assets/textures/ground_grass_1.png");
    SDL_Texture *bob = window.loadTexture("../assets/textures/ground_grass_1.png");

    Entity test;

    std::vector<Entity> entities = {Entity(Vector2f(0, 0), grassTexture, 1.0f, 1.0f),
                                    Entity(Vector2f(30, 0), grassTexture, 1.0f, 1.0f),
                                    Entity(Vector2f(30, 30), grassTexture, 1.0f, 1.0f),
                                    Entity(Vector2f(30, 60), grassTexture, 1.0f, 1.0f),
                                    Entity(Vector2f(30, 90), grassTexture, 1.0f, 1.0f)};


    Entity Bob(Vector2f(30, 100), bob, 1.0f, 1.0f);

    bool running = true;
    SDL_Event event;

    const float deltaTime = 1.0f / 60.0f;
    const int tileSize = 32;
    float velocity = 1.0f;
    float accumulator = 0.0f;
    float currentTime = Utils::hireTimeInSeconds();

    while (running)
    {
        float newTime = Utils::hireTimeInSeconds();
        float frameTime = newTime - currentTime;
        currentTime = newTime;
        accumulator += frameTime;

        while (accumulator >= deltaTime)
        {
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT)
                {
                    running = false;
                }
                else if (event.type == SDL_KEYDOWN)
                {
                    switch (event.key.keysym.sym)
                    {
                    case SDLK_d:
                        Bob.getPos().m_x += tileSize * accumulator * velocity;
                        break;
                    case SDLK_a:
                        Bob.getPos().m_x -= tileSize * accumulator * velocity;
                        break;
                    case SDLK_w:
                        Bob.getPos().m_y -= tileSize * accumulator * velocity;
                        break;
                    case SDLK_s:
                        Bob.getPos().m_y += tileSize * accumulator * velocity;
                        break;
                    default:
                        Bob.getPos().print();
                        break;
                    }
                }
            }

            accumulator -= deltaTime;
        }

        const float alpha = accumulator / deltaTime;

        window.clear();

        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();


        ImGui::ShowDemoWindow();

        {
            static float f = 0.0f;
            static int counter = 0;

            ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.

            ImGui::Text("This is some useful text."); // Display some text (you can use a format strings too)


            ImGui::SliderFloat("float", &f, 0.0f, 1.0f); // Edit 1 float using a slider from 0.0f to 1.0f

            if (ImGui::Button(
                    "Button")) // Buttons return true when clicked (most widgets return true when edited/activated)
                counter++;
            ImGui::SameLine();
            ImGui::Text("counter = %d", counter);

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
            ImGui::End();
        }
        for (Entity &ent : entities)
        {
            window.render(ent);
            window.render(Bob);
        }


        ImGui::Render();
        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        window.display();
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    window.cleanup();
    SDL_Quit();
    return 0;
}
