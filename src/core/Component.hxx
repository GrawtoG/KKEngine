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

        virtual void Awake(){}
        virtual void OnEnable(){}
        virtual void Start() {}
        virtual void FixedUpdate(float dt){}
        virtual void Update(float dt){}
        virtual void LateUpdate(float dt){}
        virtual void OnDisable(){};
        virtual void OnDestroy(){};

        virtual void OnCollisionEnter(){};
        virtual void OnCollisionExit(){};
        virtual void OnCollisionStay(){};



        [[nodiscard]] virtual std::string ToString() const = 0;

    };

    inline std::ostream& operator<<(std::ostream& os, const Component& c)
    {
        return os << c.ToString();
    }
}


#endif //KKENGINE_COMPONENT_HXX
