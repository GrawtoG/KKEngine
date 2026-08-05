//
// Created by Matieusz on 04.08.2026.
//

#ifndef KKENGINE_TRANSFORM_HXX
#define KKENGINE_TRANSFORM_HXX

#include <raylib.h>

#include "raymath.h"
#include "../core/Component.hxx"
#include "../core/GameObject.hxx"
namespace kk
{
    class Transform : public Component {
    public:

        [[nodiscard]] std::string ToString() const override {return "Transform";};
        void setPosition(const Vector3& pos);

        void setRotation(const Vector3& rot);
        void setRotation(const Quaternion& rot);

        void setRotation(const Vector3& rot, Vector3 origin);
        void setScale(const Vector3& scale);

        [[nodiscard]] Vector3 getPosition() const {return position;};
        [[nodiscard]] Vector3 getRotationEuler() const {return QuaternionToEuler(rotation);};
        [[nodiscard]] Quaternion getRotation() const {return rotation;};
        [[nodiscard]] Vector3 getScale() const {return scale;};

        [[nodiscard]] Matrix GetMatrix() const {
            Matrix t = MatrixTranslate(position.x, position.y, position.z);
            Matrix r = QuaternionToMatrix(rotation);
            Matrix s = MatrixScale(scale.x, scale.y, scale.z);

            return MatrixMultiply(MatrixMultiply(t, r), s);
        }
    private:
        Vector3 position{0.0f, 0.0f, 0.0f};
        Quaternion rotation = QuaternionIdentity();
        Vector3 scale{1.0f, 1.0f, 1.0f};
    };
}

#endif //KKENGINE_TRANSFORM_HXX
