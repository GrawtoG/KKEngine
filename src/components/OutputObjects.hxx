//
// Created by Matieusz on 05.08.2026.
//

#ifndef KKENGINE_OUTPUTOBJECTS_HXX
#define KKENGINE_OUTPUTOBJECTS_HXX
#include "../core/Component.hxx"

namespace kk
{
    class OutputObjects : public kk::Component
    {
    public:
        [[nodiscard]] std::string ToString() const override {return "OutputObjects";};
        OutputObjects() = default;
        void Update(float dt)
        {
            static float elapsedTime = 0.0f;
            elapsedTime += dt;
            if (elapsedTime > 1.0f)
            {
                for (auto& component : owner->scene->GetAllObjects())
                {
                    std::cout<<component->ToString()<<std::endl;
                }
                elapsedTime = 0.0f;
            }
        };



    };
}
#endif //KKENGINE_OUTPUTOBJECTS_HXX
