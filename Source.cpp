#include "imgui.h"
#include "imgui-SFML.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include "shapes.hpp"
#include <Windows.h>


int main(int argc, char*[]) {
	
	Circle* currentC = nullptr;
	myRectangle* currentR = nullptr;
	
	InitializeShapes(windowWidth, windowHeight);
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Bouncing shapes!");
	window.setFramerateLimit(60);
	
    ImGui::SFML::Init(window);

    sf::Clock deltaClock;
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			ImGui::SFML::ProcessEvent(event);
			if (event.type == sf::Event::Closed)
				window.close();
		}
		ImGui::SFML::Update(window, deltaClock.restart());

		window.clear(sf::Color(windowColors[0], windowColors[1], windowColors[2]));
		

		for (auto& currentShape : shapesR) {
			if (!currentShape.hidden) {
				window.draw(currentShape.dRectangle);
				window.draw(currentShape.dName);
			}
		}
		for (auto& currentShape : shapesC) {
			if (!currentShape.hidden) {
				window.draw(currentShape.dCircle);
				window.draw(currentShape.dName);
			}
		}

		ImGui::Begin("Shapes!");
		ImGui::Text(shapeInUse.c_str());
		

		if (currentC) {
			
			if (currentC->radius != currentC->firstRadius * tempScale) {
				currentC->radius = currentC->firstRadius * tempScale;
				currentC->dCircle.setRadius(currentC->radius);
			}
			if (currentC->speX != currentC->firstSpeX * speedScaleX) {
				currentC->speX = currentC->firstSpeX * speedScaleX;
			}
			if (currentC->speY != currentC->firstSpeY * speedScaleY) {
				currentC->speY = currentC->firstSpeY * speedScaleY;
			}
			
		}
		else if (currentR) {
			if (currentR->width != currentR->firstWidth * tempScale) {
				currentR->width = currentR->firstWidth * tempScale;
				currentR->height = currentR->firstHeight * tempScale;
				currentR->dRectangle.setScale(tempScale, tempScale);
			}
			if (currentR->speX != currentR->firstSpeX * speedScaleX) {
				currentR->speX = currentR->firstSpeX * speedScaleX;
			}
			if (currentR->speY != currentR->firstSpeY * speedScaleY) {
				currentR->speY = currentR->firstSpeY * speedScaleY;
			}
		}
		for (auto& currentShape : shapesR) {
			currentShape.posX += currentShape.speX;
			currentShape.posY += currentShape.speY;
			if (currentShape.posX + currentShape.width > windowWidth || currentShape.posX < 0) {
				currentShape.speX *= -1;
				currentShape.firstSpeX *= -1;
			}
			if (currentShape.posY < 0 || currentShape.posY + currentShape.height > windowHeight) {
				currentShape.speY *= -1;
				currentShape.firstSpeY *= -1;
			}

			currentShape.dRectangle.setPosition(currentShape.posX, currentShape.posY);
		}
		for (auto& currentShape : shapesC) {
			currentShape.posX += currentShape.speX;
			currentShape.posY += currentShape.speY;
			if (currentShape.posX + currentShape.radius * 2 > windowWidth || currentShape.posX < 0) {
				currentShape.speX *= -1;
				currentShape.firstSpeX *= -1;
			}
			if (currentShape.posY < 0 || currentShape.posY + currentShape.radius * 2 > windowHeight) {
				currentShape.speY *= -1;
				currentShape.firstSpeY *= -1;
			}

			currentShape.dCircle.setPosition(currentShape.posX, currentShape.posY);
		}
			if (ImGui::CollapsingHeader("Shapes!")){
				if (ImGui::BeginTable("split", 3, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings)) {
	
					
					for (auto& rect : shapesR) {
						ImGui::TableNextColumn();
						if (ImGui::Button(rect.name.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
							for (auto& shape : shapesR) {
								shape.current = false;
							}
							for (auto& shape : shapesC) {
								shape.current = false;
							}
							rect.setShape();
							rect.setCurrent();
							currentR = &rect;
							currentC = nullptr;
							tempScale = 1.0f;
							
						}
					}
					for (auto& circle : shapesC) {
						ImGui::TableNextColumn();
						if (ImGui::Button(circle.name.c_str(), ImVec2(-FLT_MIN, 0.0f))) {
							for (auto& shape : shapesR) {
								shape.current = false;
							}
							for (auto& shape : shapesC) {
								shape.current = false;
							}
							currentR = nullptr;
							currentC = &circle;
							circle.setShape();
							circle.setCurrent();
							tempScale = 1.0f;
							
						}

					}
					ImGui::EndTable();
				}
			}

			ImGui::SliderFloat("Scale", &tempScale, 0.5f, 2.0f);
			ImGui::SliderFloat("Speed X", &speedScaleX, -2.0f, 2.0f);
			ImGui::SliderFloat("Speed Y", &speedScaleY, -2.0f, 2.0f);
			if (currentC) {
				
				if (ImGui::InputText("##StringInput", display, sizeof(display))) {
					std::string inputString = display;
					currentC->name = inputString;
					currentC->dName.setString(inputString);
				}
				if (ImGui::Checkbox("Hide", &currentC->hidden));
				ImGui::SameLine();
				ImGui::ColorEdit3("Color", rgb);
				currentC->red = round(rgb[0] * 255);
				currentC->green = round(rgb[1] * 255);
				currentC->blue = round(rgb[2] * 255);
				if (!currentC->hidden) {
					currentC->dCircle.setFillColor(sf::Color(
						(int)(currentC->red),
						(int)(currentC->green),
						(int)(currentC->blue)));
				}
			}
			else if (currentR) {
				if (ImGui::InputText("##StringInput", display, sizeof(display))) {
					std::string inputString = display;
					currentR->name = inputString;
					currentR->dName.setString(inputString);
				}
				if (ImGui::Checkbox("Hide", &currentR->hidden));
			
				ImGui::SameLine();
				ImGui::ColorEdit3("Color", rgb);
				currentR->red = round(rgb[0] * 255);
				currentR->green = round(rgb[1] * 255);
				currentR->blue = round(rgb[2] * 255);
				if (!currentR->hidden) {
				currentR->dRectangle.setFillColor(sf::Color(
					(int)(currentR->red),
					(int)(currentR->green),
						(int)(currentR->blue)));
				}
			}
			
					
		ImGui::End();

		
		ImGui::SFML::Render(window);
        window.display();
		Sleep(10);
		for (auto& currentShape : shapesR) {
			currentShape.posX += currentShape.speX;
			currentShape.posY += currentShape.speY;
			if (currentShape.posX + currentShape.width > windowWidth || currentShape.posX < 0) {
				currentShape.speX *= -1;
			}
			if (currentShape.posY < 0 || currentShape.posY + currentShape.height > windowHeight) {
				currentShape.speY *= -1;
			}
			
			currentShape.dRectangle.setPosition(currentShape.posX, currentShape.posY);
			currentShape.dName.setPosition(currentShape.posX + currentShape.width/4, currentShape.posY + currentShape.height/3);
			
		}
		for (auto& currentShape : shapesC) {
			currentShape.posX += currentShape.speX;
			currentShape.posY += currentShape.speY;
			if (currentShape.posX + currentShape.radius*2 > windowWidth || currentShape.posX < 0) {
				currentShape.speX *= -1;
			}
			if (currentShape.posY < 0 || currentShape.posY + currentShape.radius * 2 > windowHeight) {
				currentShape.speY *= -1;
			}
			
			currentShape.dCircle.setPosition(currentShape.posX, currentShape.posY);
			currentShape.dName.setPosition(currentShape.posX + currentShape.radius*0.8, currentShape.posY + currentShape.radius*0.9);

		}
    }

    ImGui::SFML::Shutdown();
    return 0;
}