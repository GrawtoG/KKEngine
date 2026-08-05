//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_RENDERER_HXX
#define KKENGINE_RENDERER_HXX

//ogolna klasa dla wszelkiej masci rendererow typu sprite renderer czy mesh renderer

#include "../core/Component.hxx"
namespace kk
{
    class Renderer:public Component {
    public:
        [[nodiscard]] std::string ToString() const override {return "Renderer";};
        virtual void Render();
    };

}

#endif //KKENGINE_RENDERER_HXX
