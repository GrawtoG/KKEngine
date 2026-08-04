//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_TRANSFORM_HXX
#define KKENGINE_TRANSFORM_HXX

#include <raylib.h>
#include "../core/Component.hxx"
#include "../core/GameObject.hxx"
namespace kk
{
    class Transform : public Component {
    public:
        void setPosition(const Vector3& pos);
        void setRotation(const Vector3& rot);
        void setRotation(const Vector3& rot, Vector3 origin);
        void setScale(const Vector3& scale);

        [[nodiscard]] Vector3 getPosition() const {return position;};
        [[nodiscard]] Vector3 getRotation() const {return rotation;};
        [[nodiscard]] Vector3 getScale() const {return scale;};
    private:
        Vector3 position{0.0f, 0.0f, 0.0f};
        Vector3 rotation{0.0f, 0.0f, 0.0f};
        Vector3 scale{1.0f, 1.0f, 1.0f};


    };
}

#endif //KKENGINE_TRANSFORM_HXX
