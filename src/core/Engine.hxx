//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_ENGINE_HXX
#define KKENGINE_ENGINE_HXX


#include <raylib.h>
#include <vector>
#include <memory>
#include <iostream>
#include "Scene.hxx"
#include "GameObject.hxx"
namespace kk
{
    class Engine {
    private:
        Scene* currentScene;
        float deltaTime = 0.0f;

    public:

        void SetFPS(const int fps) {SetTargetFPS(fps);}

        void changeScene(Scene*  scene)
        {
            currentScene = scene;
            //hm jedyne co moge teraz wymyslec to goto na poczatek glownej petli xddd
            // TODO jak zmienic ladnie scene
        };

        GameObject* createGameObject(std::string name)
        {
            GameObject* obj = new GameObject(std::move(name));
            return obj;
        }

        Scene* createScene()
        {
            Scene* scene = new Scene();
            return scene;
        }
        void Run(int screenWidth, int screenHeight, std::string Title) {

            InitWindow(screenWidth, screenHeight, Title.c_str());
            SetTargetFPS(999999999);

            // --- Główna pętla ---
            while (!WindowShouldClose()) {
                deltaTime = GetFrameTime();

                currentScene->Update(deltaTime);
                currentScene->Render();

                BeginDrawing();
                ClearBackground(RAYWHITE);

                currentScene->Render();
                // for (auto& obj : currentScene->GetAllObjects())
                // {
                //     std::cout << *obj << std::endl;
                // }
                DrawText(TextFormat("FPS: %d", GetFPS()), 10, 10, 20, DARKGRAY);
                DrawText("Steruj strzalkami", 10, 40, 20, DARKGRAY);

                EndDrawing();
            }

            CloseWindow();
        }
    };
}
#endif //KKENGINE_ENGINE_HXX
