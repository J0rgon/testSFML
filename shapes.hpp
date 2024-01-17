#ifndef shapes
#define shapes

#include "imgui.h"
#include "imgui-SFML.h"
#include <fstream>
#include <vector>
#include <iostream>

#include "SFML/Graphics.hpp"

char display[255];
float tempScale = 1.0f;
float speedScaleY = 1.0f;
float speedScaleX = 1.0f;
int windowWidth, windowHeight;
float rgb[] = { 0.0f, 0.0f, 0.0f };


const int circleSegments = 200;

const int windowColors[] = { 20, 30, 40 };
std::string font;
sf::Font myFont;

std::string shapeInUse = "Shape";


class Rectangle;

class Shape {
public:
	std::string name;
	sf::Text dName;
	float posX;
	float posY;
	float speX, firstSpeX;
	float speY, firstSpeY;
	float red;
	float green;
	float blue;
	bool rectangle;
	bool current;
	bool hidden;
	Shape(bool isRectangle, std::string newName, float initPosX, float initPosY, float initSpeX, float initSpeY, int initRed, int initGreen, int initBlue) :
		rectangle(isRectangle),name(newName), posX(initPosX), posY(initPosY), speX(initSpeX), speY(initSpeY), red(initRed), green(initGreen), blue(initBlue), current(false), firstSpeX(initSpeX), firstSpeY(initSpeY), hidden(false) {
		std::cout << "Shape created succesfully" << std::endl;
		dName.setFont(myFont);
		dName.setCharacterSize(15);
		dName.setOutlineColor(sf::Color::Black);
		dName.setOutlineThickness(2);
		dName.setFillColor(sf::Color::White);
		dName.setPosition(initPosX, initPosY);
		dName.setString(newName);
		dName.setStyle(sf::Text::Bold);
	}
	void setShape() {
		shapeInUse = name;
	}
	void setCurrent() {
		current = true;
	}
};

class myRectangle : public Shape {
public:
	float width, firstWidth;
	float height, firstHeight;
	sf::RectangleShape dRectangle;
	myRectangle(std::string newName, float initPosX, float initPosY, float initSpeX, float initSpeY, int initRed, int initGreen, int initBlue, float initWidth, float initHeight) :
		Shape(true, newName, initPosX, initPosY, initSpeX, initSpeY, initRed, initGreen, initBlue), width(initWidth), height(initHeight), firstWidth(initWidth), firstHeight(initHeight) {
		std::cout << "Rectangle created succesfully" << std::endl;
		dRectangle.setSize(sf::Vector2f(width, height));
		dRectangle.setFillColor(sf::Color(
			(int)(red),
			(int)(green),
			(int)(blue)));
		dRectangle.setPosition(posX, posY);
	}

};

class Circle : public Shape {
public:

	float radius, firstRadius;
	sf::CircleShape dCircle;
	Circle(std::string newName, float initPosX, float initPosY, float initSpeX, float initSpeY, int initRed, int initGreen, int initBlue, float initRadius) :
		Shape(false, newName, initPosX, initPosY, initSpeX, initSpeY, initRed, initGreen, initBlue), radius(initRadius), firstRadius(initRadius) {
		dCircle.setRadius(radius);
		dCircle.setPointCount(circleSegments);

		dCircle.setFillColor(sf::Color(
			(int)(red),
			(int)(green),
			(int)(blue)));
		dCircle.setPosition(posX, posY);
	}

	void show() {
		
	}
};

std::vector<myRectangle> shapesR;
std::vector<Circle> shapesC;

void InitializeShapes(int &windowWidth, int &windowHeight) {
	std::ifstream initFile;
	initFile.open("initShapes.txt");
	std::string line;
	initFile >> line;
	if (line != "Window") {
		std::cout << "Window dimensions not found" << std::endl;
		std::cin.ignore();
		return;
	}
	initFile >> windowWidth;
	initFile >> windowHeight;
	initFile >> line;
	if (line != "Font") {
		std::cout << "Font file not found" << std::endl;
		std::cin.ignore();
		return;
	}
	initFile >> font;
	if (!myFont.loadFromFile(font)) {
		std::cout << "Error while loading font" << std::endl;
		return;
	}
	while (initFile >> line) {
		std::string name;
		int red, green, blue;
		float posX, posY, speX, speY, width, height, radius;
		if (line == "Rectangle") {
			initFile >> name;
			
			initFile >> posX;
			initFile >> posY;
			initFile >> speX;
			initFile >> speY;
			initFile >> red;
			initFile >> green;
			initFile >> blue;
			initFile >> width;
			initFile >> height;
			myRectangle newRectangle(name, posX, posY, speX, speY, red, green, blue, width, height);
			shapesR.push_back(newRectangle);
		}
		else if (line == "Circle") {
			initFile >> name;
			initFile >> posX;
			initFile >> posY;
			initFile >> speX;
			initFile >> speY;
			initFile >> red;
			initFile >> green;
			initFile >> blue;
			initFile >> radius;
			Circle newCircle(name, posX, posY, speX, speY, red, green, blue, radius);
			shapesC.push_back(newCircle);
		}
	}
}


#endif
