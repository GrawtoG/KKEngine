//
// Created by Matieusz on 05.08.2026.
//

#ifndef KKENGINE_HELPERS_HXX
#define KKENGINE_HELPERS_HXX

#include "raylib.h"
#include "raymath.h"

inline Vector3 RotateVector(const Quaternion& q, const Vector3& v) {
    Quaternion vecQ = { v.x, v.y, v.z, 0 };
    Quaternion inv = QuaternionInvert(q);
    Quaternion result = QuaternionMultiply(QuaternionMultiply(q, vecQ), inv);
    return { result.x, result.y, result.z };
}
inline Vector3 operator/(const Vector3& a, float s) { return {a.x/s, a.y/s, a.z/s}; }
#endif //KKENGINE_HELPERS_HXX
