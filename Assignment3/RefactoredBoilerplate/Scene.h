#ifndef SCENE_H_
#define SCENE_H_
#include <vector>
#include "Geometry.h"
#include "GlyphExtractor.h"
#include <string>

class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	int currentScene;

	// Part I
	static const int CUBIC = 0;
	static const int QUADRATIC = 1;
	// Part II
	static const int LORA = 2;
	static const int SOURCE_SANS_PRO = 3;
	static const int COMIC_SANS = 4;
	// Part III
	static const int SCROLLING_ALEX_BRUSH = 5;
	static const int SCROLLING_INCONSOLATA = 6;

	//Send geometry to the renderer
	void displayScene();
	void setScene(int sceneType);
	void speedUp();
	void speedDown();

	float xOffset;
	float yOffset;

	float xOffsetScrolling;
	float yOffsetScrolling;

private:
	RenderingEngine* renderer;

	GlyphExtractor glyphExtractor;
	MyGlyph glyph;

	Geometry degreeOne;
	Geometry degreeTwo;
	Geometry degreeThree;

	std::vector<Geometry> degreeOneObjects;
	std::vector<Geometry> degreeTwoObjects;
	std::vector<Geometry> degreeThreeObjects;

	// Resizes the font size and advance
	const float FONT_NORMALIZATION_FACTOR = 7.0f;

	float scrollSpeed;
	
	void clearWindow();
	void pushObjects();

	void drawGlyph(MyGlyph glyph, float xOffset, float yOffset);
	void drawString(std::string str, std::string font, std::string fontPath, float xStart, float yStart);

	void drawQuadratic();
	void drawCubic();
	void drawLora();
	void drawSourceSansPro();
	void drawComicSans();
	void drawScrollingAlexBrush();
	void drawScrollingInconsolata();
};

#endif /* SCENE_H_ */
