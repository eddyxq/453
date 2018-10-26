#include "Scene.h"
#include <iostream>
#include <vector>
#include "RenderingEngine.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GlyphExtractor.h"

Scene::Scene(RenderingEngine* renderer) : renderer(renderer) {
	scrollSpeed = 0.01f;
	xOffset = -0.5f;
	yOffset = 0.0f;
	xOffsetScrolling = xOffset;
	yOffsetScrolling = yOffset;
	//setScene(QUADRATIC);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	switch (currentScene) {
	case SCROLLING_ALEX_BRUSH:
		setScene(SCROLLING_ALEX_BRUSH);
		break;
	case SCROLLING_INCONSOLATA:
		setScene(SCROLLING_INCONSOLATA);
		break;
	}
	renderer->RenderDegreeOneCurves(degreeOneObjects);
	renderer->RenderDegreeTwoCurves(degreeTwoObjects);
	renderer->RenderDegreeThreeCurves(degreeThreeObjects);
}

void Scene::setScene(int sceneType) {
	clearWindow();
	switch (sceneType) {
	case QUADRATIC:
		drawQuadratic();
		break;
	case CUBIC:
		drawCubic();
		break;
	case LORA:
		drawLora();
		break;
	case SOURCE_SANS_PRO:
		drawSourceSansPro();
		break;
	case COMIC_SANS:
		drawComicSans();
		break;
	case SCROLLING_ALEX_BRUSH:
		drawScrollingAlexBrush();
		break;
	case SCROLLING_INCONSOLATA:
		drawScrollingInconsolata();
		break;
	default:
		std::cerr << "Scene.setScene(): Invalid sceneType." << std::endl;
	}
	currentScene = sceneType;
	pushObjects();
}

void Scene::speedUp() {
	scrollSpeed += 0.1f;
}

void Scene::speedDown() {
	scrollSpeed -= 0.1f;
}

void Scene::clearWindow() {
	degreeOneObjects.clear();
	degreeOne.verts.clear();
	degreeOne.colors.clear();

	degreeTwoObjects.clear();
	degreeTwo.verts.clear();
	degreeTwo.colors.clear();

	degreeThreeObjects.clear();
	degreeThree.verts.clear();
	degreeThree.colors.clear();
}

void Scene::pushObjects() {
	degreeOne.drawMode = GL_LINES;
	RenderingEngine::assignBuffers(degreeOne);
	RenderingEngine::setBufferData(degreeOne);
	degreeOneObjects.push_back(degreeOne);

	degreeTwo.drawMode = GL_PATCHES;
	RenderingEngine::assignBuffers(degreeTwo);
	RenderingEngine::setBufferData(degreeTwo);
	degreeTwoObjects.push_back(degreeTwo);

	degreeThree.drawMode = GL_PATCHES;
	RenderingEngine::assignBuffers(degreeThree);
	RenderingEngine::setBufferData(degreeThree);
	degreeThreeObjects.push_back(degreeThree);
}

void Scene::drawGlyph(MyGlyph glyph, float xOffset, float yOffset) {
	for (unsigned int i = 0; i < glyph.contours.size(); i++) {
		for (unsigned int j = 0; j < glyph.contours[i].size(); j++) {
			for (unsigned int k = 0; k <= glyph.contours[i][j].degree; k++) {
				float x = glyph.contours[i][j].x[k] * (1.0f / FONT_NORMALIZATION_FACTOR);
				float y = glyph.contours[i][j].y[k] * (1.0f / FONT_NORMALIZATION_FACTOR);
				float z = 1.0f * (1.0f / FONT_NORMALIZATION_FACTOR);

				if (glyph.contours[i][j].degree == 1) {
					degreeOne.verts.push_back(glm::vec3(x + xOffset, y + yOffset, z));
					degreeOne.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				}
				else if (glyph.contours[i][j].degree == 2) {
					degreeTwo.verts.push_back(glm::vec3(x + xOffset, y + yOffset, z));
					degreeTwo.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				}
				else if (glyph.contours[i][j].degree == 3) {
					degreeThree.verts.push_back(glm::vec3(x + xOffset, y + yOffset, z));
					degreeThree.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
				}
			}
		}
	}
}

void Scene::drawString(std::string str, std::string font, std::string fontPath, float xStart, float yStart) {
	glyphExtractor.LoadFontFile(fontPath);
	for (char& c : str) {
		glyph = glyphExtractor.ExtractGlyph(c);
		drawGlyph(glyph, xStart, yStart);
		xStart += glyph.advance / FONT_NORMALIZATION_FACTOR;
	}
}

void Scene::drawQuadratic() {
	const int BEZIER_CURVE_COUNT = 4;
	const int CONTROL_POINT_COUNT = 3;
	const float NORMALIZATION_FACTOR = 4.0f;

	std::vector<glm::vec3> curve1 = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(2.0f, -1.0f, 1.0f),
		glm::vec3(0.0f, -1.0f, 1.0f)
	};
	std::vector<glm::vec3> curve2 = {
		glm::vec3(0.0f, -1.0f, 1.0f),
		glm::vec3(-2.0f, -1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f)
	};
	std::vector<glm::vec3> curve3 = {
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, 1.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f)
	};

	std::vector<glm::vec3> curve4 = {
		glm::vec3(1.2f, 0.5f, 1.0f),
		glm::vec3(2.5f, 1.0f, 1.0f),
		glm::vec3(1.3f, 0.4f, 1.0f)
	};

	std::vector<std::vector<glm::vec3>> scene1 = { curve1, curve2, curve3, curve4 };
	for (int curve = 0; curve < BEZIER_CURVE_COUNT; curve++) {
		for (int point = 0; point < CONTROL_POINT_COUNT; point++) {
			// Control points
			degreeTwo.verts.push_back(scene1[curve][point] * (1.0f/NORMALIZATION_FACTOR));
			// Color
			degreeTwo.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			degreeTwo.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			degreeTwo.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
		}
	}
}

void Scene::drawCubic() {
	const int BEZIER_CURVE_COUNT = 5;
	const int CONTROL_POINT_COUNT = 4;
	const float NORMALIZATION_FACTOR = 5.0f;

	std::vector<glm::vec3> curve1 = {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(4.0f, 0.0f, 1.0f),
		glm::vec3(6.0f, 2.0f, 1.0f),
		glm::vec3(9.0f, 1.0f, 1.0f)
	};
	std::vector<glm::vec3> curve2 = {
		glm::vec3(8.0f, 2.0f, 1.0f),
		glm::vec3(0.0f, 8.0f, 1.0f),
		glm::vec3(0.0f, -2.0f, 1.0f),
		glm::vec3(8.0f, 4.0f, 1.0f)
	};
	std::vector<glm::vec3> curve3 = {
		glm::vec3(5.0f, 3.0f, 1.0f),
		glm::vec3(3.0f, 2.0f, 1.0f),
		glm::vec3(3.0f, 3.0f, 1.0f),
		glm::vec3(5.0f, 2.0f, 1.0f)
	};

	std::vector<glm::vec3> curve4 = {
		glm::vec3(3.0f, 2.2f, 1.0f),
		glm::vec3(3.5f, 2.7f, 1.0f),
		glm::vec3(3.5f, 3.3f, 1.0f),
		glm::vec3(3.0f, 3.8f, 1.0f)
	};

	std::vector<glm::vec3> curve5 = {
		glm::vec3(2.8f, 3.5f, 1.0f),
		glm::vec3(2.4f, 3.8f, 1.0f),
	    glm::vec3(2.4f, 3.2f, 1.0f),
	    glm::vec3(2.8f, 3.5f, 1.0f)
	};

	std::vector<std::vector<glm::vec3>> scene2 = { curve1, curve2, curve3, curve4, curve5 };
	for (int curve = 0; curve < BEZIER_CURVE_COUNT; curve++) {
		for (int point = 0; point < CONTROL_POINT_COUNT; point++) {
			// Control points
			glm::vec3 p = scene2[curve][point] * (1.0f / NORMALIZATION_FACTOR);
			p.x -= 1.0f;
			p.y -= 0.5f;
			degreeThree.verts.push_back(p);
			// Color
			degreeThree.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
			degreeThree.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			degreeThree.colors.push_back(glm::vec3(0.0f, 0.0f, 1.0f));
			degreeThree.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
		}
	}
}

void Scene::drawLora()
{
	drawString("Evan Quan", "lora", "fonts/lora/Lora-Regular.ttf", xOffset, yOffset);
}

void Scene::drawSourceSansPro()
{
	drawString("Eddy Qiang", "sourcesanspro", "fonts/source-sans-pro/SourceSansPro-Regular.otf", xOffset, yOffset);
}

void Scene::drawComicSans()
{
	drawString("Evan and Eddy", "comicsans", "fonts/comic-sans/ComicSans.ttf", xOffset, yOffset);
}

void Scene::drawScrollingAlexBrush()
{
	xOffsetScrolling = (float) fmod(xOffsetScrolling + scrollSpeed, 1);
	drawString("The quick brown fox jumps over the lazy dog.", "alex", "fonts/alex-brush/AlexBrush-Regular.ttf", xOffsetScrolling, yOffsetScrolling);
}

void Scene::drawScrollingInconsolata()
{
	xOffsetScrolling = (float) fmod(xOffsetScrolling + scrollSpeed, 1);
	drawString("abcdefghijklmnopqrstuvwxyz", "inconsolata", "fonts/zapfino/Zapfino.ttf", xOffsetScrolling, yOffsetScrolling);
}
