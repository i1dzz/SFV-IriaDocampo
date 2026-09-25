#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include <vector>

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        
		//Crear una esfera de radio 1.0f
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(1.0f));

		Vector3D pos1(0.0f, 20.0f, 0.0f);
        m_transform = physx::PxTransform(pos1);
		m_originalPos.push_back(pos1);

        m_transformBlue = physx::PxTransform(Vector3(-10.0f, 10.0f, 0.0f));
        m_originalPos.push_back(Vector3(-10.0f, 10.0f, 0.0f));

        m_transformRed = physx::PxTransform(Vector3(10.0f, 10.0f, 0.0f));
        m_originalPos.push_back(Vector3(10.0f, 10.0f, 0.0f));

        m_transformGreen = physx::PxTransform(Vector3(0.0f, 30.0f, 0.0f));
        m_originalPos.push_back(Vector3(0.0f, 30.0f, 0.0f));
       
    
        m_renderItem = new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f));
        m_renderItemBlue = new RenderItem(shape, &m_transformBlue, Vector4(0.0f, 0.0f, 1.0f, 1.0f));
        m_renderItemRed = new RenderItem(shape, &m_transformRed, Vector4(1.0f, 0.0f, 0.0f, 1.0f));
		m_renderItemGreen = new RenderItem(shape, &m_transformGreen, Vector4(0.0f, 1.0f, 0.0f, 1.0f));

		m_renderItems.push_back(std::make_pair(m_renderItem, m_transform));
		m_renderItems.push_back(std::make_pair(m_renderItemBlue, m_transformBlue));
		m_renderItems.push_back(std::make_pair(m_renderItemRed, m_transformRed));
		m_renderItems.push_back(std::make_pair(m_renderItemGreen, m_transformGreen));
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            for(int i = 0; i < m_originalPos.size(); ++i) {
                m_renderItems[i].second.p = m_originalPos[i]; // Reset
			}
        }
    }

    void cleanup() override {

        for(int i = 0; i < m_renderItems.size(); ++i) {
            if (m_renderItems[i].first) {
                m_renderItems[i].first->release(); // Deregistra y destruye el item
                m_renderItems[i].first = nullptr;
            }
		}
        
    }

private:
    physx::PxTransform m_transform;
    physx::PxTransform m_transformBlue;
    physx::PxTransform m_transformRed;
    physx::PxTransform m_transformGreen;
    RenderItem* m_renderItem{ nullptr };
    RenderItem* m_renderItemBlue{ nullptr };
    RenderItem* m_renderItemRed{ nullptr };
    RenderItem* m_renderItemGreen{ nullptr };

	std::vector <std::pair<RenderItem*, physx::PxTransform>> m_renderItems;
    std::vector <physx::PxVec3> m_originalPos;

};