#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

sf::View view;

View setPlayerCoordinateForView(float x, float y) {
	float TempX = x, TempY = y;
	if (x < 320) TempX = 320;
	if (y < 240) TempY = 240;
	if (y > 554) TempY = 554;

	view.setCenter(TempX, TempY);
	return view;
}