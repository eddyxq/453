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

	const int QUADRATIC_BEZIER_CURVE_COUNT = 4;
	const int QUADRATIC_CONTROL_POINT_COUNT = 3;
	const float QUADRATIC_NORMALIZATION_FACTOR = 4.0f;

	const int CUBIC_BEZIER_CURVE_COUNT = 5;
	const int CUBIC_CONTROL_POINT_COUNT = 4;
	const float CUBIC_NORMALIZATION_FACTOR = 6.0f;
	// Part II
	static const int LORA = 2;
	static const int SOURCE_SANS_PRO = 3;
	static const int COMIC_SANS = 4;
	// Part III
	static const int SCROLLING_ALEX_BRUSH = 5;
	static const int SCROLLING_INCONSOLATA = 6;
	static const int SCROLLING_ZAPFINO = 7;
	const float SCROLL_AMOUNT = 0.001f;
	const float SCROLL_MAX = 0.025f;
	const float SCROLL_START = -3*SCROLL_AMOUNT;

	const float LORA_NORMALIZATION_FACTOR = 2.6f;
	const float SOURCE_SANS_PRO_NORMALIZATION_FACTOR = 2.5f;
	const float COMIC_SANS_NORMALIZATION_FACTOR = 3.5f;
	const float ALEX_BRUSH_NORMALIZATION_FACTOR = 2.0f;
	const float INCONSOLATA_NORMALIZATION_FACTOR = 3.0f;
	const float ZAPFINO_NORMALIZATION_FACTOR = 3.0f;
	//BONUS
	static const int BONUS = 8;

	//Send geometry to the renderer
	void displayScene();
	void setScene(int sceneType);
	void speedUp();
	void speedDown();

	float xOffsetStart;
	float yOffsetStart;
	float xOffsetStartScrolling;

private:
	RenderingEngine* renderer;

	GlyphExtractor glyphExtractor;
	MyGlyph glyph;

	Geometry degreeOne;
	Geometry degreeTwo;
	Geometry degreeThree;
	Geometry controlPolygon;
	Geometry controlPoints;

	std::vector<Geometry> degreeOneObjects;
	std::vector<Geometry> degreeTwoObjects;
	std::vector<Geometry> degreeThreeObjects;
	std::vector<Geometry> polygonObjects;
	std::vector<Geometry> pointObjects;

	float scrollSpeed;

	void clearWindow();
	void pushObjects();
	void drawGlyph(MyGlyph glyph, float xOffset, float yOffset, float normalizationFactor);
	void drawString(std::string str, std::string fontPath, float xStart, float yStart, float normalizationFactor);
	void drawQuadratic();
	void drawCubic();
	void drawLora();
	void drawSourceSansPro();
	void drawComicSans();
	void drawScrollingAlexBrush();
	void drawScrollingInconsolata();
	void drawScrollingZapfino();
	void drawBonus();
};

#endif /* SCENE_H_ */
