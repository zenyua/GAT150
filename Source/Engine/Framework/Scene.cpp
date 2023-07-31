#include "Scene.h"
#include "Actor.h"

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
			if ((*iter)->m_destroyed) {
				iter = m_actors.erase(iter); // Erase the element and update the iterator
			}
			else {
				iter++; // Move the iterator forward if the element was not erased
			}
		}
		//check collisions
		for (auto iter1 = m_actors.begin(); iter1 != m_actors.end(); iter1++) {
			for (auto iter2 = std::next(iter1, 1); iter2 != m_actors.end(); iter2++) {
				float distance = (*iter1)->m_transform.position.Distance((*iter2)->m_transform.position);
				float radius = (*iter1)->GetRadius() + (*iter2)->GetRadius();
				if (distance <= radius) {
					//boom
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