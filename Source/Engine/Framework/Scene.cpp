#include "Scene.h"
#include "Actor.h"
#include "Framework/Components/CollisionComponent.h"

namespace ringo {
	void Scene::Update(float dt)
	{
		//remove destroyed actors
		auto iter = m_actors.begin();
		while (iter != m_actors.end()) {
			(*iter)->Update(dt);
			/*if ((*iter)->m_destroyed) {
				m_actors.erase(iter);
			}
			iter++;*/
			((*iter)->m_destroyed) ? iter = m_actors.erase(iter) : iter++;
			//if ((*iter)->m_destroyed) {
			//	iter = m_actors.erase(iter); // Erase the element and update the iterator
			//}
			//else {
			//	iter++; // Move the iterator forward if the element was not erased
			//}
		}
		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {
				CollisionComponent* collision1 = (*iter1)->GetComponent<CollisionComponent>();
				CollisionComponent* collision2 = (*iter2)->GetComponent<CollisionComponent>();

				if (!collision1 || !collision2) continue;

				if (collision1->CheckCollision(collision2)) {
					(*iter1)->OnCollision(iter2->get());
					(*iter2)->OnCollision(iter1->get());
				}

			}
		}
	}
	//iter = ((*iter)->m_destroyed) ? m_actors.erase(iter) : iter++;
	void Scene::Draw(Renderer& renderer)
	{
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}
	void Scene::Add(std::unique_ptr<Actor> actor)
	{
		actor->m_scene = this;
		m_actors.push_back(std::move(actor));
	}
	void Scene::RemoveAll()
	{
		m_actors.clear();
	}
}