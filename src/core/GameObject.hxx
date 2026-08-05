//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_GAMEOBJECT_HXX
#define KKENGINE_GAMEOBJECT_HXX

#include <algorithm>
#include <raylib.h>
#include <utility>
#include <vector>
#include <memory>
#include <iostream>
#include "Component.hxx"
#include "..//components//Renderer.hxx"
#include "Scene.hxx"


namespace kk
{
    class Scene;
    class GameObject {
    public:

        Scene* scene = nullptr;

        GameObject(std::string name_, Scene* scene_)
        {
            name = std::move(name_);
            scene = scene_;
        };
        GameObject(std::string name_)
        {
            name = std::move(name_);
        };
        std::vector<std::string> tags;

        [[nodiscard]]  std::string ToString() const
        {
            std::string str = name + " {";
            for (auto& comp : components)
            {
                str += "'";
                str += comp->ToString();
                str += "', ";
            }
            str+="}";
            return str;
        }



        std::string GetName() {return name;}


        bool isActive() const { return active; }
        void setActive(const bool _active)
        {
            if (active == false && _active == true)
            {
                for (auto& comp : components) {
                    comp->Awake();
                }
            }
            this->active = _active;


        }


        std::vector<std::unique_ptr<Component>> components;
        std::vector<Renderer*> renderers;

        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            auto comp = std::make_unique<T>(std::forward<Args>(args)...);
            T* raw = comp.get();

            if (auto* base = dynamic_cast<Component*>(raw)) {
                base->owner = this;
            }

            if (auto* rend = dynamic_cast<Renderer*>(raw)) {
                renderers.push_back(rend);
            }

            components.push_back(std::move(comp));

            raw->Awake();

            return raw;
        }

        template<typename T>
        T* GetComponent() {
            for (auto& comp : components) {
                if (T* result = dynamic_cast<T*>(comp.get())) {
                    return result;
                }
            }
            return nullptr;
        }

        void Update(float dt) {
            if (!active) return;
            for (auto& comp : components) {
                comp->Update(dt);

            }
        }
        void Start()
        {
            for (auto& comp : components) {
                comp->Start();
            }
        }
        void LateUpdate(float dt)
        {
            for (auto& comp : components)
            {
                comp->LateUpdate(dt);
            }
        }

        void Render() {
            if (!active) return;
            for (Renderer* rend : renderers) {
                rend->Render();
            }
        }


        // std::string setName(std::string name)
        // {
        //     std::vector<std::string> takenNames = scene->GetAllNames();
        //     if (std::find(takenNames.begin(), takenNames.end(), name) != takenNames.end()) {
        //         _setName(name+"(1)",takenNames);
        //     } else {
        //
        //     }
        // };

    private:

        // std::string _setName(std::string name, const std::vector<std::string>& names)
        // {
        //     if (std::find(names.begin(), names.end(), name) != names.end()) {
        //         _setName(name+"(1)",names);
        //     } else {
        //         // nie istnieje
        //     }
        // };

        bool active = true;

        std::vector<GameObject*> m_children;
        GameObject* m_parent = nullptr;

        std::string name;

    };

    inline std::ostream& operator<<(std::ostream& os, const GameObject& c)
    {
        return os << c.ToString();
    }

}

#endif //KKENGINE_GAMEOBJECT_HXX
