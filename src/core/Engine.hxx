//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_ENGINE_HXX
#define KKENGINE_ENGINE_HXX


#include <raylib.h>
#include <vector>
#include <memory>
#include <iostream>

class Engine {
public:
    void Run() {
        InitWindow(800, 600, "Mój Silnik");
        SetTargetFPS(60);

        while (!WindowShouldClose()) {
            float deltaTime = GetFrameTime(); // czas między klatkami
            Update(deltaTime);
            Render();
        }
        CloseWindow();
    }
private:
    void Update(float dt) { /* aktualizacja logiki */ }
    void Render() {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        // rysowanie
        EndDrawing();
    }
};


#endif //KKENGINE_ENGINE_HXX
