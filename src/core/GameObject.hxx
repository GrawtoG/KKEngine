//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_GAMEOBJECT_HXX
#define KKENGINE_GAMEOBJECT_HXX

#include <algorithm>
#include <raylib.h>
#include <vector>
#include <memory>
#include <iostream>
#include "Component.hxx"
#include "../components/transform.hxx"
#include "../components/renderer.hxx"

namespace kk
{
    class GameObject {
    public:

        bool isActive() const { return active; }
        void setActive(const bool _active)
        {
            this->active = _active;
            for (auto& comp : components) {
                comp->Awake();
            }
        }


        std::vector<std::unique_ptr<Component>> components;
        std::vector<Renderer*> renderers;

        template<typename T, typename... Args>
        T* AddComponent(Args&&... args) {
            auto comp = std::make_unique<T>(std::forward<Args>(args)...);
            T* raw = comp.get();

            if (auto* base = dynamic_cast<Component*>(raw)) {
                base->gameObject = this;
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

        void Render() {
            if (!active) return;
            for (Renderer* rend : renderers) {
                rend->Render();
            }
        }

    private:

        bool active = true;

        std::vector<GameObject*> m_children;
        GameObject* m_parent = nullptr;
    };


}

#endif //KKENGINE_GAMEOBJECT_HXX
