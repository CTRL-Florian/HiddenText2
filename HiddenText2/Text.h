#pragma once

#include "Scene.h"
#include "StyleSheet.h"

#include <string>

#include <SDL2/SDL.h>

class Text
{
public:
	Text(Scene& scene, std::string& text, int size);
	Text(Scene& scene, std::string& text, int size, StyleSheet style);

	std::string getText() const { return mText; }
	int getSize() const { return mSize; }

	void setText(std::string text) { mText = text; }
	void setSize(int size) { mSize = size; }

private:
	Scene& mScene;
	std::string& mText;
	int mSize;

	StyleSheet mStyle;
};

