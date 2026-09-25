#pragma once
#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>
#include <iostream>

class P0S_Scene : public Scene {
public:
    explicit P0S_Scene(std::string name) : Scene(std::move(name)) {}

    void init() override {

        Vector3D u(3.0f, 1.0f, 0.0f); // x (rojo)
        Vector3D v(0.0, 4.0, 0.0); //  y verde

        Vector3D w = u.cross(v); // z azul


        //Crear una esfera de radio 1.0f
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));
        physx::PxShape* dot = CreateShape(physx::PxSphereGeometry(0.25f)); // uso una esfera mas pequeña a modo de un punto para comprobar 

        Vector3D rojo = u.normalize() * 5; 
		Vector3D verde = v.normalize() * 5;
		Vector3D azul = w.normalize() * 5;

        Vector3D black(0.0f, 0.0f, 0.0f);

        m_transformBlue = physx::PxTransform(azul);
        m_originalPos.push_back(azul);

        m_transformRed = physx::PxTransform(rojo);
        m_originalPos.push_back(rojo);

        m_transformGreen = physx::PxTransform(verde);
        m_originalPos.push_back(verde);

        m_transformDot = physx::PxTransform(black);
        m_originalPos.push_back(black);
        
        m_renderItemBlue = new RenderItem(shape, &m_transformBlue, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
        m_renderItemRed = new RenderItem(shape, &m_transformRed, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
        m_renderItemGreen = new RenderItem(shape, &m_transformGreen, Vector4(0.0f, 1.0f, 0.0f, 1.0f));
		m_renderItemDot = new RenderItem(dot, &m_transformDot, Vector4(0.0f, 0.0f, 0.0f, 1.0f));


        m_renderItems.push_back(std::make_pair(m_renderItemBlue, m_transformBlue));
        m_renderItems.push_back(std::make_pair(m_renderItemRed, m_transformRed));
        m_renderItems.push_back(std::make_pair(m_renderItemGreen, m_transformGreen));
		m_renderItems.push_back(std::make_pair(m_renderItemDot, m_transformDot));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {

		std::cout << "Keypressed: " << key << std::endl;
        if (key == 'r' || key == 'R') {
            for (int i = 0; i < m_originalPos.size(); ++i) {
               // m_renderItems.at(i).first->transform = &physx::PxTransform(m_originalPos.at(i)); // Reset
            }
        }
    }

    void cleanup() override {

        for (int i = 0; i < m_renderItems.size(); ++i) {
            if (m_renderItems[i].first) {
                m_renderItems[i].first->release(); // Deregistra y destruye el item
                m_renderItems[i].first = nullptr;
            }
        }

    }

private:
    physx::PxTransform m_transformBlue;
    physx::PxTransform m_transformRed;
    physx::PxTransform m_transformGreen;

    RenderItem* m_renderItemBlue{ nullptr };
    RenderItem* m_renderItemRed{ nullptr };
    RenderItem* m_renderItemGreen{ nullptr };

    physx::PxTransform m_transformDot;
    RenderItem* m_renderItemDot{ nullptr };

    std::vector <std::pair<RenderItem*, physx::PxTransform>> m_renderItems;
    std::vector <Vector3D> m_originalPos;

};
