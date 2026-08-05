//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_SCENE_HXX
#define KKENGINE_SCENE_HXX

#include <memory>
#include <unordered_map>
#include <vector>
#include "GameObject.hxx"

namespace kk
{
    class Scene {
    public:

        Scene()= default;
        const std::vector<GameObject*>& GetAllObjects(){return objects;}
        void AddObject(GameObject* tm);

        std::vector<std::string> GetAllNames()
        {
            std::vector<std::string> names;
            for (auto it = nameRegistry.begin(); it != nameRegistry.end(); ++it)
            {
                names.push_back(it->first);
            }
            return names;
        }


        void Update(float dt);
        void Start();
        void Render();

        GameObject* createGameObject(std::string name);

        bool RemoveObject(GameObject* obj);


        // Znajdź obiekt o nazwie
        GameObject* FindObjectByName(const std::string& name);

        // Znajdź wszystie obiekty danym tagiem
        std::vector<GameObject*> GetObjectsWithTag(const std::string& tag);

        // Znajdź obiekty, które mają WSZYSTKIE podane tagi (AND)
        std::vector<GameObject*> GetObjectsWithAllTags(const std::vector<std::string>& requiredTags);

        // Znajdź obiekty, które mają CO NAJMNIEJ JEDEN z podanych tagów (OR)
        std::vector<GameObject*> GetObjectsWithAnyTag(const std::vector<std::string>& anyTags);

        // Wyszukiwanie GameObjects z komponentem
        template<typename T>
        std::vector<GameObject*> FindObjectsWithComponent() const;

    private:
        std::vector<GameObject*> objects = std::vector<GameObject*>();
        std::unordered_map<std::string, GameObject*> nameRegistry = std::unordered_map<std::string, GameObject*>();
        std::unordered_map<std::string, std::vector<GameObject*>> tagRegistry = std::unordered_map<std::string, std::vector<GameObject*>>();

    };
}
#endif //KKENGINE_SCENE_HXX
