
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <iostream>
#include "globaldef.h"
#include "hull.h"
#include "vector2.h"
#include "Timer.h"
#include "InputParser.h"

std::vector<Vector2> GenerateRandomPoints(int amount)
{
	std::vector<Vector2> temp;
	float randX = 0;
	float randY = 0;
	for (int i = 0; i < amount; i++)
	{
		randX = std::rand() % (WIDTH-100) + 50;
		randY = std::rand() % (HEIGHT-100) +50;

		Vector2 rand(randX, randY);
		temp.push_back(rand);
	}
	return temp;
}
std::vector<Vector2> GenerateRandomPointsY(int amount)
{
	std::vector<Vector2> temp;
	float randX = WIDTH / 2;
	float randY = 0;
	for (int i = 0; i < amount; i++)
	{
		randY = std::rand() % (HEIGHT - 100) + 50;
		Vector2 rand(randX, randY);
		temp.push_back(rand);
	}
	return temp;
}
std::vector<Vector2> GenerateRandomPointsX(int amount)
{
	std::vector<Vector2> temp;
	float randX = 0;
	float randY = HEIGHT / 2;;
	for (int i = 0; i < amount; i++)
	{
		randX = std::rand() % (WIDTH - 100) + 50;

		Vector2 rand(randX, randY);
		temp.push_back(rand);
	}
	return temp;
}

int main(int argc, char *argv[])
{
	//Pause
	bool pause = true;

	// check Inputs -> if there are no -> take standard values
	// StepbyStep Mode is on and 40 Points
	int check = checkInputs(argc, argv);
	if (check == 0) { return 0; }
	
	// Step by Step -> in Input Parser
	//bool StepbyStep = true;

	//Timer
	Timer timer;

	//Points Data representation
	std::vector<Vector2> points;
	std::vector<Vector2> pointsLineX;
	std::vector<Vector2> pointsLineY;
	//Setup for Points
	points = GenerateRandomPoints(NUMBEROFPOINTS);
	pointsLineX = GenerateRandomPointsX(NUMBEROFPOINTS);
	pointsLineY = GenerateRandomPointsY(NUMBEROFPOINTS);
	//Convex Hull
	Hull ConvexHull;
	ConvexHull.SetPointcloud(points);
	Hull ConvexHullX;
	ConvexHullX.SetPointcloud(pointsLineX);
	Hull ConvexHullY;
	ConvexHullY.SetPointcloud(pointsLineY);

	// create the window
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Convex Hull");
	sf::Clock deltaClock;
	sf::Time deltaTime;

	window.setFramerateLimit(120);

	if (!StepbyStep)
	{
		timer.startTimer();
		ConvexHull.CalculateConvexHull(WIDTH);
		timer.stopTimer(' ');

		timer.startTimer();
		ConvexHullX.CalculateConvexHull(WIDTH);
		timer.stopTimer('X');

		timer.startTimer();
		ConvexHullY.CalculateConvexHull(WIDTH);
		timer.stopTimer('Y');
		timer.saveTimes("results.txt");
	}

	sf::Font font;
	if (!font.loadFromFile("font.ttf"))
	{
		std::cout << "Cannot load font \n";
	}

	sf::Text text;

	// select the font
	text.setFont(font); // font is a sf::Font
	
	if (StepbyStep == true) {
		// set the string to display
		text.setString("Step Mode  Space to continue");
	}
	else {
		text.setString("Test Mode");
	}

	// set the character size
	text.setCharacterSize(24); // in pixels, not points!

	//Drawable Points
	std::vector<sf::CircleShape> drawablePoints;
	for each (Vector2 point in points)
	{
		sf::CircleShape drawablepoint;
		sf::Vector2f position(point.x,point.y);
		drawablepoint.setPosition(position);
		drawablepoint.setRadius(POINTRADIUS);
		drawablepoint.setFillColor(sf::Color::Red);
		drawablepoint.setOrigin(POINTRADIUS, POINTRADIUS);
		drawablePoints.push_back(drawablepoint);
	}

	//Drawable lines 
	sf::VertexArray lines(sf::LinesStrip, ConvexHull.GetPointsHull().size());
	int i=0;
	for each (int index in ConvexHull.GetPointsHull())
	{
		lines[i].position = sf::Vector2f(ConvexHull.GetPointcloud()[index].x, ConvexHull.GetPointcloud()[index].y);
		lines[i].color = sf::Color(0, 153, 204);
		i++;
	}

	std::vector<sf::Vertex> sbsLines;
	sf::Vertex sbsPointToPointline[] =
	{
		sf::Vertex(sf::Vector2f(0, 0)),
		sf::Vertex(sf::Vector2f(0, 0))
	};
	// run the program as long as the window is open
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					if (!pause) pause = true;
					else pause = false;
				}
			}
		}
		// clear the window with black color
		window.clear(sf::Color::Black);
		if (StepbyStep && !ConvexHull.GetFinished())
		{
			if (!pause)
			{
				ConvexHull.CalculateConvexHullStepByStep(WIDTH);
				float x = ConvexHull.GetPointcloud()[ConvexHull.GetPointsHull()[ConvexHull.GetPointsHull().size() - 1]].x;
				float y = ConvexHull.GetPointcloud()[ConvexHull.GetPointsHull()[ConvexHull.GetPointsHull().size() - 1]].y;
				sf::Vertex vert(sf::Vector2f(x, y),sf::Color(0,153,204));
				sbsLines.push_back(vert);

				//Add line from current point to examined point
				sf::Vertex vert1(sf::Vector2f(ConvexHull.GetPointcloud()[ConvexHull.drawP].x, ConvexHull.GetPointcloud()[ConvexHull.drawP].y),sf::Color::Yellow);
				sf::Vertex vert2(sf::Vector2f(ConvexHull.GetPointcloud()[ConvexHull.drawR].x, ConvexHull.GetPointcloud()[ConvexHull.drawR].y), sf::Color::Yellow);
				sbsPointToPointline[0] = vert1;
				sbsPointToPointline[1] = vert2;
				pause = true;
			}
		}
		int i = 0;
		for each (sf::CircleShape point in drawablePoints)
		{
			for each (int index in ConvexHull.GetPointsHull())
			{
				if (i == index)
				{
					point.setFillColor(sf::Color::Red);
					sf::CircleShape Circle;
					Circle.setFillColor(sf::Color::Transparent);
					Circle.setOutlineColor(sf::Color::Blue);
					Circle.setRadius(POINTHULLRADIUS);
					Circle.setOrigin(POINTHULLRADIUS, POINTHULLRADIUS);
					Circle.setOutlineThickness(1);
					Circle.setPosition(point.getPosition());
					window.draw(Circle);
				}
			}
			window.draw(point);
			i++;
		}
		window.draw(lines);
		int j = 0;
		for each (sf::Vertex vert in sbsLines)
		{
			if (sbsLines.size()>1&&j>0)
			{
				sf::Vertex line[] =
				{
					sbsLines[j - 1],
					vert	
				};
				window.draw(line, 2, sf::Lines);
			}
			j++;
		}
		window.draw(sbsPointToPointline, 2, sf::Lines);

		// draw Text for Mode
		window.draw(text);

		// end the current frame
		window.display();
	
		deltaTime = deltaClock.restart();
	}

	return 0;
}