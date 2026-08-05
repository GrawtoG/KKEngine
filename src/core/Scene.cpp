//
// Created by Matieusz on 04.08.2026.
//

#include "Scene.hxx"
#include "GameObject.hxx"
namespace kk
{

     void Scene::Render(){
        for (auto& obj : objects) obj->Render();
    }

    void Scene::Update(float dt) {
        for (auto& obj : objects) obj->Update(dt);
    }

    void Scene::Start() {
         for (auto& obj : objects) obj->Start();
     }

    void Scene::AddObject(GameObject* obj){

        // Rejestracja nazwy (jeśli istnieje)
        if (!obj->GetName().empty()) {
            nameRegistry[obj->GetName()] = obj; // zakładamy unikalność
            // TODO Jeżeli taka nazwa istnieje to do skutku dodajemy cos do nazwy i dodajemy jako kopie
        }

        // Rejestracja WSZYSTKICH tagów
        for (const std::string& tag : obj->tags) {
            tagRegistry[tag].push_back(obj);
        }

        // Ustawienie ownerów dla komponentów (jeśli potrzeba) – pomijamy
        objects.push_back(obj);

         obj->scene = this;
    }

    bool Scene::RemoveObject(GameObject* obj) {
        if (!obj) return false;

        // Wyrejestruj nazwę
        if (!obj->GetName().empty()) {
            auto it = nameRegistry.find(obj->GetName());
            if (it != nameRegistry.end() && it->second == obj) {
                nameRegistry.erase(it);
            }
        }

        // Wyrejestruj WSZYSTKIE tagi
        for (const std::string& tag : obj->tags) {
            auto it = tagRegistry.find(tag);
            if (it != tagRegistry.end()) {
                auto& vec = it->second;
                vec.erase(std::remove(vec.begin(), vec.end(), obj), vec.end());
                if (vec.empty()) {
                    tagRegistry.erase(it);
                }
            }
        }

        // Usuń z głównego wektora
        auto vecIt = std::find(objects.begin(), objects.end(), obj);
        if (vecIt != objects.end()) {
            objects.erase(vecIt);
            return true;
        }
        return false;
    }

    GameObject* Scene::FindObjectByName(const std::string& name) {
        auto it = nameRegistry.find(name);
        return (it != nameRegistry.end()) ? it->second : nullptr;
    }


    std::vector<GameObject*> Scene::GetObjectsWithTag(const std::string& tag) {
        auto it = tagRegistry.find(tag);
        if (it != tagRegistry.end()) {
            return it->second; // kopia wektora wskaźników
        }
        return {};
    }


    std::vector<GameObject*> Scene::GetObjectsWithAllTags(const std::vector<std::string>& requiredTags) {
        if (requiredTags.empty()) return {};

        // Zacznij od obiektów z pierwszym tagiem
        auto firstIt = tagRegistry.find(requiredTags[0]);
        if (firstIt == tagRegistry.end()) return {};

        std::vector<GameObject*> result = firstIt->second; // kopia

        // Dla każdego kolejnego tagu – odfiltruj
        for (size_t i = 1; i < requiredTags.size(); ++i) {
            const std::string& tag = requiredTags[i];
            auto it = tagRegistry.find(tag);
            if (it == tagRegistry.end()) return {}; // brak takiego tagu – brak wyników

            const auto& candidates = it->second;
            // Usuń z result te obiekty, które nie występują w candidates
            result.erase(std::remove_if(result.begin(), result.end(),
                [&candidates](GameObject* obj) {
                    return std::find(candidates.begin(), candidates.end(), obj) == candidates.end();
                }), result.end());
            if (result.empty()) break;
        }
        return result;
    }

    std::vector<GameObject*> Scene::GetObjectsWithAnyTag(const std::vector<std::string>& anyTags) {
        std::vector<GameObject*> result;
        for (const std::string& tag : anyTags) {
            auto it = tagRegistry.find(tag);
            if (it != tagRegistry.end()) {
                // Dodaj wszystkie obiekty z tego tagu (unikając duplikatów)
                for (GameObject* obj : it->second) {
                    if (std::find(result.begin(), result.end(), obj) == result.end()) {
                        result.push_back(obj);
                    }
                }
            }
        }
        return result;
    }

    template<typename T>
    std::vector<GameObject*> Scene::FindObjectsWithComponent() const
    {
        std::vector<GameObject*> result;
        for (auto& obj : objects) {
            if (obj->GetComponent<T>() != nullptr) {
                result.push_back(obj);
            }
        }
        return result;
    }
}