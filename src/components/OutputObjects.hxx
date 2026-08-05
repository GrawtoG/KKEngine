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
            std::cout<<"OutputObjectasds";
            static float elapsedTime = 0.0f;
            elapsedTime += dt;
            if (elapsedTime > 1.0f)
            {
                elapsedTime = 0.0f;
                std::cout<<elapsedTime<<std::endl;
            }
        };



    };
}
#endif //KKENGINE_OUTPUTOBJECTS_HXX
