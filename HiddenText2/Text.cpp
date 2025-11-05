#include "Text.h"

Text::Text(Scene& scene, std::string& text, int size) :
	Text(scene, text, size, Standard())
{

}

Text::Text(Scene& scene, std::string& text, int size, StyleSheet style) :
	mScene{scene},
	mText{text}, mSize{size},
	mStyle{style}
{

}