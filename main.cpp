#include <iostream>



#include "include/Components.hxx"
#include "src/core/Engine.hxx"
int main() {

      std::cout << "Hello World!" << std::endl;
      kk::Engine engine;

      kk::GameObject *TM = engine.createGameObject("TimeManager");
      TM->AddComponent<kk::OutputObjects>();
      kk::Scene* scene = engine.createScene();
      engine.changeScene(scene);
      scene->AddObject(TM);

      engine.Run(800,800,"Agrest");
      return 0;
}