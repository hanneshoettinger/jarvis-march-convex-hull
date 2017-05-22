#pragma once
#include "vector2.h"
#include <vector>

class Hull
{
	public:
		Hull();
		~Hull();
		
		void CalculateConvexHull(int width);

		void CalculateConvexHullStepByStep(int width);

		double Rightturn(Vector2 p, Vector2 q, Vector2 r);

		inline void SetPointcloud(std::vector<Vector2> points) { m_pointsCloud = points; };
		inline std::vector<Vector2> GetPointcloud() { return m_pointsCloud; };

		inline std::vector<int> GetPointsHull() { return m_pointsHull; };

		inline bool GetFinished() { return m_finished; };

		int limit = 0;
		int drawP = 0;
		int drawR = 0;

	private:
		std::vector<Vector2> m_pointsCloud;
		std::vector<int> m_pointsHull;
		bool m_finished = false;

		int StartingPoint(int width);
		

		
};

