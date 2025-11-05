#include "Rect.h"

Rect::Rect(int x, int y, int w, int h) :
	Rect(x, y, w, h, Color{255, 255, 255, 255})
{
	
}

Rect::Rect(int x, int y, int w, int h, Color c) :
	mX{ x }, mY{ y },
	mW{ w }, mH{ h },
	mColor{c}
{
	mFilled = false;
	mRect = { mX, mY, mW, mH };
}

void Rect::draw(SDL_Renderer* r) const
{
	SDL_SetRenderDrawColor(r, mColor.mR, mColor.mG, mColor.mB, mColor.mA);
	if (mFilled) {
		SDL_RenderFillRect(r, &mRect);
	}
	else {
		SDL_RenderDrawRect(r, &mRect);
	}
}

