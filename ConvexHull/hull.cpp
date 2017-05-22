#include "hull.h"
#include <iostream>


Hull::Hull()
{
}


Hull::~Hull()
{
}

void Hull::CalculateConvexHull(int width)
{
	int p = StartingPoint(width);
	int l = 0;

	// start point = left most point
	l = p;
	// calculate next point
	int  q = (p + 1) % m_pointsCloud.size();
	// if less than 3 elements -> nothing to compute
	if (m_pointsCloud.size()<3)
	{
		for (int i = 0; i<m_pointsCloud.size() - 1; i++)
		{
			m_pointsHull.push_back(i);
		}
	}
	else
	{
		do  // as long as point on hull is not the left most point
		{
			// add left most point and the points to follow
			m_pointsHull.push_back(p);
			for (int r = 0; r<m_pointsCloud.size(); r++)
			{
				int ccw = Rightturn(m_pointsCloud[p], m_pointsCloud[q], m_pointsCloud[r]);
				// Counter-clockwise (start point left most lowest value) -> if turn right -> set new point
				if (ccw == 1 || ccw == 0 && m_pointsCloud[p].GetAbsDistance(m_pointsCloud[r]) > m_pointsCloud[p].GetAbsDistance(m_pointsCloud[q]))
				{
					// if turn right then set current point as next point on the hull -> rightturn is called with updated value
					q = r;
				}
			}
			// set final q to next point on hull
			p = q;
			// go to next point in array after hullpoint
			q = (p + 1) % m_pointsCloud.size();
		} while (p != l);
		// add left most point twice for drawing
		m_pointsHull.push_back(p);
	}

	//

}
void Hull::CalculateConvexHullStepByStep(int width)
{
	int p = 0;
	if (m_pointsHull.size() == 0)
	{
		int p = StartingPoint(width);
		m_pointsHull.push_back(p);
		return;
	}
	if (m_pointsHull.size() > 0)
	{
		if(m_pointsHull.size() == 1)	p = m_pointsHull[0];
		else p = m_pointsHull[m_pointsHull.size()-1];
		int l = 0;
		// start point = left most point
		l = m_pointsHull[0];
		// calculate next point
		int  q = (p + 1) % m_pointsCloud.size();
	
		if (m_pointsCloud.size() < 3)
		{
			for (int i = 0; i < m_pointsCloud.size() - 1; i++)
			{
				m_pointsHull.push_back(i);
			}
		}
		else
		{

			do  // as long as point on hull is not the left most point
			{
				for (int r = 0; r<m_pointsCloud.size(); r++)
				{
					int ccw = Rightturn(m_pointsCloud[p], m_pointsCloud[q], m_pointsCloud[r]);
					// Counter-clockwise (start point left most lowest value) -> if turn right -> set new point
					if (ccw == 1 || ccw == 0 && m_pointsCloud[p].GetAbsDistance(m_pointsCloud[r]) > m_pointsCloud[p].GetAbsDistance(m_pointsCloud[q]))
					{
						// if turn right then set current point as next point on the hull -> rightturn is called with updated value
						q = r;
						
					}
					if (r == limit)
					{
						limit = r + 1;
						drawP = p;
						drawR = r;
						return;
					}
				}
				// set final q to next point on hull
				p = q;
				// go to next point in array after hullpoint
				q = (p + 1) % m_pointsCloud.size();
				// add left most point and the points to follow
				m_pointsHull.push_back(p);
				limit = 0; 
			} while (p != l);
			// add left most point twice for drawing
 			m_pointsHull.push_back(p);
			drawP = 0;
			drawR = 0;
			m_finished = true;
			return;
		}
	}
}


double Hull::Rightturn(Vector2 p, Vector2 q, Vector2 r)
{
	// cross product to determine polygon orientation
	double x1 = (q.x - p.x) * (r.y - p.y);
	double x2 = (r.x - p.x) * (q.y - p.y);
	double val = x1 - x2;

	if (val == 0)
		return 0;
	if (val>0)   // CW orientation
		return 1;
	else
		return -1;
}

int Hull::StartingPoint(int width)
{
	Vector2 temp(width,0);
	int p = 0;
	int i=0;
	for each (Vector2 point in m_pointsCloud)
	{
		if (point.x < temp.x)
		{
			temp = point;
			p = i;
		}
		else if (point.x == temp.x && point.y < temp.y)
		{
			temp = point;
			p = i;
		}
		i++;
	}
	return p;
}
