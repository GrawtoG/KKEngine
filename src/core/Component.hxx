//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_COMPONENT_HXX
#define KKENGINE_COMPONENT_HXX


#include <raylib.h>
#include <vector>
#include <memory>
#include <iostream>
#include "GameObject.hxx"

namespace kk
{
    class Component {
    public:
        GameObject* gameObject = nullptr;
        virtual ~Component() = default;

        void Start() {} //hapens once at the start
        void Update(float dt) {} //happens everyframe
        void Awake() {} //happens everytime component is activated

    };
}


#endif //KKENGINE_COMPONENT_HXX
