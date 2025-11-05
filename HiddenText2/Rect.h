#pragma once

#include "Color.h"

#include <SDL2/SDL.h>

class Rect
{
public:
	Rect(int x, int y, int w, int h);
	Rect(int x, int y, int w, int h, Color c);

	int getX() const { return mX; }
	int getY() const { return mY; }

	void draw(SDL_Renderer* r) const;

	void position(int x, int y) { mX = x; mY = y; mRect.x = x; mRect.y = y; }
	void move(int x, int y) { mX += x; mY += y; mRect.x += x; mRect.y += y; }

	void fill() { mFilled = true; }
	void empty() { mFilled = false; }
	bool isFilled() const { return mFilled; }

	void resize(int width, int height) { mW = height; mH = height; }

private:
	int mX;
	int mY;
	int mW;
	int mH;

	bool mFilled;

	SDL_Rect mRect;

	Color mColor;

};