//
// Created by Matieusz on 05.08.2026.
//

#ifndef KKENGINE_RIGIDBODY_HXX
#define KKENGINE_RIGIDBODY_HXX
#include "raylib.h"
#include "Transform.hxx"
#include "../core/helpers.hxx"
namespace kk
{
    class Rigidbody : public Component
    {
    public:

        Rigidbody(float mass_, const Vector3& centerOfMass_): mass(mass_), centerOfMass(centerOfMass_) {
            angularVelocity = {0,0,0};
            forceAccum = {0,0,0};
            torqueAccum = {0,0,0};
        }

        float mass=1;
        Vector3 centerOfMass = Vector3{.0f,.0f,.0f}; //relative to transform position


        Matrix inertiaTensor = MatrixIdentity();
        Matrix invInertiaTensor = MatrixIdentity();

        bool autoCalculateInertiaTensor = true;
        bool autoCenterOfMass = true;

        Vector3 forceAccum = Vector3{0,0,0};
        Vector3 torqueAccum = Vector3{0,0,0};

        float angularDamping = .0f;
        float linearDamping = .0f;

        float gravityAcceleration = -9.81f;

        Vector3 linearVelocity = Vector3{0,0,0};
        Vector3 linearAcceleration = Vector3{0,0,0};

        Vector3 angularVelocity = Vector3{0,0,0};
        Vector3 angularAcceleration = Vector3{0,0,0};


        float maxAngularVelocity;
        float maxLinearVelocity;


        void SetCenterOfMass(const Vector3& centerOfMass_)
        {
            autoCenterOfMass=false;
            centerOfMass = centerOfMass_;
        }

        void SetInertiaTensor(const Matrix& inertia) {
            inertiaTensor = inertia;
            invInertiaTensor = MatrixInvert(inertia);
            autoCalculateInertiaTensor = false;
        }

        void AutoCenterOfMassOn()
        {
            autoCenterOfMass = true;
        }

        void AddForce(const Vector3& force, const Vector3& worldPoint) {
            forceAccum = forceAccum + force;
            Vector3 r = worldPoint - thisTransform->getPosition();
            torqueAccum = torqueAccum + Vector3CrossProduct(r, force);

        }
        void AddForceAtCenter(const Vector3& force) {
            AddForce(force, thisTransform->getPosition());
        }

        void ClearForces() {
            forceAccum = {0,0,0};
            torqueAccum = {0,0,0};
        }

        void UpdateInertiaTensor()
        {

        }

        void ApplyDamping(float dt)
        {
            linearVelocity -= linearVelocity * (linearDamping * dt);
            angularVelocity -= angularVelocity * (angularDamping * dt);
        }

        void Integrate(float dt) {
            if (mass < 1e-10f) return; // unikaj dzielenia przez zero

            // ---- Część liniowa ----
            Vector3 acceleration = forceAccum * (1.0f / mass);
            linearVelocity += acceleration * dt;
            thisTransform->setPosition(thisTransform->getPosition() + linearVelocity * dt);

            // ---- Część kątowa ----
            // 1. Pobierz macierz rotacji z kwaternionu (Raylib)
            Quaternion q = thisTransform->getRotation();
            Matrix rotMat = QuaternionToMatrix(q);

            // 2. Oblicz odwrotny tensor bezwładności w świecie: I_world_inv = R * I_local_inv * R^T
            Matrix rotMatT = MatrixTranspose(rotMat);
            Matrix I_world_inv = MatrixMultiply(MatrixMultiply(rotMat, invInertiaTensor), rotMatT);

            // 3. Oblicz I * omega (używamy lokalnego tensora, ale możemy obrócić do świata)
            //    Możemy policzyć I_world = R * I_local * R^T, ale potrzebujemy tylko I_world * omega
            //    Alternatywnie: Iomega = R * I_local * R^T * omega
            //    Używamy Vector3Transform z macierzą 4x4 (Raylib)
            Vector3 Iomega = Vector3Transform(angularVelocity, I_world_inv); // UWAGA: to byłoby I^(-1)*omega, a my chcemy I*omega! Musimy użyć odwrotności.

            // Żeby dostać I*omega, lepiej użyć pełnego tensora w świecie:
            Matrix I_world = MatrixMultiply(MatrixMultiply(rotMat, inertiaTensor), rotMatT);
            Vector3 Iomega_full = Vector3Transform(angularVelocity, I_world); // mnoży macierz 4x4 przez wektor

            // 4. Oblicz przyspieszenie kątowe: alpha = I_world_inv * (torque - omega x Iomega_full)
            Vector3 torque = torqueAccum;
            Vector3 cross = Vector3CrossProduct(angularVelocity, Iomega_full);
            Vector3 alpha = Vector3Transform(torque - cross, I_world_inv); // mnożenie przez odwróconą macierz

            // 5. Aktualizuj prędkość kątową
            angularVelocity += alpha * dt;

            // 6. Damping
            ApplyDamping(dt);

            // 7. Aktualizacja kwaternionu (metoda eksponencjalna)
            float angle = Vector3Length(angularVelocity) * dt;
            if (angle > 1e-10f) {
                Vector3 axis = Vector3Normalize(angularVelocity);
                Quaternion deltaQ = QuaternionFromAxisAngle(axis, angle);
                q = QuaternionMultiply(q, deltaQ); // kolejność zależy od konwencji
                q = QuaternionNormalize(q);
                thisTransform->setRotation(q);
            }

            // 8. Wyczyść siły na koniec (opcjonalnie, zależnie od architektury)
            // ClearForces();
        }

    private:
        Transform *thisTransform;
    };
}
#endif //KKENGINE_RIGIDBODY_HXX
