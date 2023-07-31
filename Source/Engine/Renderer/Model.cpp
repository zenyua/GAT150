#include "Model.h"
#include <sstream>
#include <iostream>
#include <fstream>

namespace ringo {
	bool Model::Load(const std::string& filename) {
		std::string buffer;
		ringo::readFile(filename, buffer);

		std::istringstream stream(buffer);

		//read color, not yet
		//stream >> m_color;

		//read number of points
		std::string line = "";
		std::getline(stream, line);
		int numPoints = std::stoi(line);
		//int numPoints = 11;

		//read vector2 points
		for (int i = 0; i < numPoints; i++)
		{
			vec2 point;
			stream >> point;

			m_points.push_back(point);
		}

		return true;
	}

	void Model::Draw(Renderer& renderer, const vec2& position, float rotation, float scale)
	{
		if (m_points.empty()) return;
		for (int i = 0; i < m_points.size()-1; i++)
		{
			vec2 p1 = (m_points[i]*scale).Rotate(rotation) + position;
			vec2 p2 = (m_points[i + 1]*scale).Rotate(rotation) + position;
			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Model::Draw(Renderer& renderer, const Transform& transform)
	{
		Draw(renderer, transform.position, transform.rotation, transform.scale);
	}
	float Model::GetRadius() {
		if (m_radius) return m_radius;

		for (auto& point : m_points) {
			float length = point.Length();
			if (length > m_radius) m_radius = length;
		}

		return m_radius;
	}
}