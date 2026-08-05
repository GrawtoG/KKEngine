//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_COMPONENT_HXX
#define KKENGINE_COMPONENT_HXX


#include <raylib.h>
#include <vector>
#include <memory>
#include <iostream>


namespace kk
{
    class GameObject;

    class Component {
    public:
        GameObject* owner = nullptr;
        virtual ~Component() = default;

        virtual void Start() {} //hapens once at the start
        virtual void Update(float dt){} //happens everyframe
        virtual void Awake(){} //happens everytime component is activated

        [[nodiscard]] virtual std::string ToString() const = 0;

    };

    inline std::ostream& operator<<(std::ostream& os, const Component& c)
    {
        return os << c.ToString();
    }
}


#endif //KKENGINE_COMPONENT_HXX
