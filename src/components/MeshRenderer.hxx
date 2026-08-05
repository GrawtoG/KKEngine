//
// Created by Matieusz on 05.08.2026.
//

#ifndef KKENGINE_MESHRENDERER_HXX
#define KKENGINE_MESHRENDERER_HXX


#include <raylib.h>

#include "Renderer.hxx"
#include "Transform.hxx"
#include "../core/GameObject.hxx"

namespace kk
{

    class MeshRenderer : public Renderer {

    public:

        [[nodiscard]] std::string ToString() const override {return "MeshRenderer";};
        // Konstruktor przyjmuje siatkę i materiał (możesz dodać domyślne)
        MeshRenderer(const Mesh& meshData, const Material& mat)
            : mesh(meshData), material(mat) {
            // Kopiujemy mesh i material (Raylib ma wewnętrzne bufory, ale dla prostoty tak)
        }

        MeshRenderer() = default;

        void SetMesh(const Mesh& newMesh) { mesh = newMesh; }
        void SetMaterial(const Material& newMat) { material = newMat; }

        void Start() {
            if (owner) {
                transform = owner->GetComponent<Transform>();
            }
        }

        void Render() override
        {
            //if (!transform) return;
            const Matrix transformMatrix = transform->GetMatrix();
            DrawMesh(mesh, material, transformMatrix);
        }

    private:
        Mesh mesh;
        Material material;
        kk::Transform* transform = nullptr;

    };


}
#endif //KKENGINE_MESHRENDERER_HXX
