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
	scrollSpeed = SCROLL_START;
	xOffsetStart = -0.5f;
	xOffsetStartScrolling = 0.0f;
	yOffsetStart = 0.0f;
	setScene(QUADRATIC);
}

Scene::~Scene() {

}

void Scene::displayScene() {
	switch (currentScene) {
	case SCROLLING_ALEX_BRUSH:
		renderer->dx += scrollSpeed;
		if (renderer->dx > 2.0f) {
			renderer->dx = -7.125f + xOffsetStart;
		}
		else if (renderer->dx < -7.125f + xOffsetStart) {
			renderer->dx = 2.0f;
		}
		break;
	case SCROLLING_INCONSOLATA:
		renderer->dx += scrollSpeed;
		if (renderer->dx > 2.0f) {
			renderer->dx = -7.287f + xOffsetStart;
		}
		else if (renderer->dx < -7.287f + xOffsetStart) {
			renderer->dx = 2.0f;
		}
		break;
	case SCROLLING_ZAPFINO:
		renderer->dx += scrollSpeed;
		if (renderer->dx > 2.0f) {
			renderer->dx = -8.641f + xOffsetStart;
		}
		else if (renderer->dx < -8.641f + xOffsetStart) {
			renderer->dx = 2.0f;
		}
		break;
	default:
		renderer->dx = 0;
		xOffsetStart = -1.0f;
	}
	renderer->RenderControlLines(polygonObjects);
	renderer->RenderDegreeOneCurves(degreeOneObjects);
	renderer->RenderDegreeTwoCurves(degreeTwoObjects);
	renderer->RenderDegreeThreeCurves(degreeThreeObjects);
	renderer->RenderControlPoints(pointObjects);
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
	case SCROLLING_ZAPFINO:
		drawScrollingZapfino();
		break;
	case BONUS:
		drawBonus();
		break;

	default:
		std::cerr << "Scene.setScene(): Invalid sceneType." << std::endl;
	}
	currentScene = sceneType;
	pushObjects();
}
void Scene::speedUp() {
	if (scrollSpeed < SCROLL_MAX) {
		scrollSpeed += SCROLL_AMOUNT;
	}
}

void Scene::speedDown() {
	if (scrollSpeed > -SCROLL_MAX) {
		scrollSpeed -= SCROLL_AMOUNT;
	}
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

	polygonObjects.clear();
	controlPolygon.verts.clear();
	controlPolygon.colors.clear();
	controlPolygon.controlPointsPerCurve = 0;

	pointObjects.clear();
	controlPoints.verts.clear();
	controlPoints.colors.clear();
	controlPoints.controlPointsPerCurve = 0;
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

	controlPolygon.drawMode = GL_LINE_STRIP;
	RenderingEngine::assignBuffers(controlPolygon);
	RenderingEngine::setBufferData(controlPolygon);
	polygonObjects.push_back(controlPolygon);

	controlPoints.drawMode = GL_POINTS;
	RenderingEngine::assignBuffers(controlPoints);
	RenderingEngine::setBufferData(controlPoints);
	pointObjects.push_back(controlPoints);
}

void Scene::drawGlyph(MyGlyph glyph, float xOffset, float yOffset, float normalizationFactor) {
	for (unsigned int i = 0; i < glyph.contours.size(); i++) {
		for (unsigned int j = 0; j < glyph.contours[i].size(); j++) {
			for (unsigned int k = 0; k <= glyph.contours[i][j].degree; k++) {
				float x = glyph.contours[i][j].x[k] * (1.0f / normalizationFactor);
				float y = glyph.contours[i][j].y[k] * (1.0f / normalizationFactor);
				float z = 1.0f * (1.0f / normalizationFactor);

				switch (glyph.contours[i][j].degree) {
				case 1:
					degreeOne.verts.push_back(glm::vec3(x + xOffset, y + yOffset, z));
					degreeOne.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
					break;
				case 2:
					degreeTwo.verts.push_back(glm::vec3(x + xOffset, y + yOffset, z));
					degreeTwo.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
					break;
				case 3:
					degreeThree.verts.push_back(glm::vec3(x + xOffset, y + yOffset, z));
					degreeThree.colors.push_back(glm::vec3(1.0f, 0.0f, 0.0f));
					break;
				}
			}
		}
	}
}

void Scene::drawString(std::string str, std::string fontPath, float xStart, float yStart, float normalizationFactor) {
	glyphExtractor.LoadFontFile(fontPath);
	for (char& c : str) {
		glyph = glyphExtractor.ExtractGlyph(c);
		drawGlyph(glyph, xStart, yStart, normalizationFactor);
		xStart += glyph.advance / normalizationFactor;
	}
}

void Scene::drawQuadratic() {
	controlPolygon.controlPointsPerCurve = QUADRATIC_CONTROL_POINT_COUNT;

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
	for (int curve = 0; curve < QUADRATIC_BEZIER_CURVE_COUNT; curve++) {
		for (int point = 0; point < QUADRATIC_CONTROL_POINT_COUNT; point++) {
			// Control points
			degreeTwo.verts.push_back(scene1[curve][point] * (1.0f/QUADRATIC_NORMALIZATION_FACTOR));
			controlPolygon.verts.push_back(scene1[curve][point] * (1.0f/QUADRATIC_NORMALIZATION_FACTOR));
			controlPoints.verts.push_back(scene1[curve][point] * (1.0f/QUADRATIC_NORMALIZATION_FACTOR));
			// Color
			// Green curves
			degreeTwo.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			// Blue polygon curves
			controlPolygon.colors.push_back(glm::vec3(0.0f, 0.0f, 0.5f));
			if (point == 0 || point == 2) {
				// Cyan on curve control points
				controlPoints.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
			}
			else {
				// Magenta off curve control points
				controlPoints.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
			}
		}
	}
}

void Scene::drawCubic() {
	controlPolygon.controlPointsPerCurve = CUBIC_CONTROL_POINT_COUNT;

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
	for (int curve = 0; curve < CUBIC_BEZIER_CURVE_COUNT; curve++) {
		for (int point = 0; point < CUBIC_CONTROL_POINT_COUNT; point++) {
			// Control points
			glm::vec3 p = scene2[curve][point] * (1.0f / CUBIC_NORMALIZATION_FACTOR);
			p.x -= 1.0f;
			p.y -= 0.5f;
			degreeThree.verts.push_back(p);
			controlPolygon.verts.push_back(p);
			controlPoints.verts.push_back(p);
			// Color
			// Green curves
			degreeThree.colors.push_back(glm::vec3(0.0f, 1.0f, 0.0f));
			// Blue polygon curves
			controlPolygon.colors.push_back(glm::vec3(0.0f, 0.0f, 0.5f));
			if (point == 0 || point == 3) {
				// Cyan on curve control points
				controlPoints.colors.push_back(glm::vec3(0.0f, 1.0f, 1.0f));
			}
			else {
				// Magenta off curve control points
				controlPoints.colors.push_back(glm::vec3(1.0f, 0.0f, 1.0f));
			}
		}
	}
}

void Scene::drawLora()
{
	drawString("Evan Quan", "fonts/lora/Lora-Regular.ttf", xOffsetStart, yOffsetStart, LORA_NORMALIZATION_FACTOR);
}

void Scene::drawSourceSansPro()
{
	drawString("Eddy Qiang", "fonts/source-sans-pro/SourceSansPro-Regular.otf", xOffsetStart, yOffsetStart, SOURCE_SANS_PRO_NORMALIZATION_FACTOR);
}

void Scene::drawComicSans()
{
	drawString("Evan and Eddy", "fonts/comic-sans/ComicSans.ttf", xOffsetStart, yOffsetStart, COMIC_SANS_NORMALIZATION_FACTOR);
}

void Scene::drawScrollingAlexBrush()
{
	drawString("The quick brown fox jumps over the lazy dog.", "fonts/alex-brush/AlexBrush-Regular.ttf", xOffsetStartScrolling, yOffsetStart, ALEX_BRUSH_NORMALIZATION_FACTOR);
}

void Scene::drawScrollingInconsolata()
{

	drawString("The quick brown fox jumps over the lazy dog.", "fonts/inconsolata/Inconsolata.otf", xOffsetStartScrolling, yOffsetStart, INCONSOLATA_NORMALIZATION_FACTOR);
}
void Scene::drawScrollingZapfino()
{
	drawString("The quick brown fox jumps over the lazy dog.", "fonts/zapfino/Zapfino.ttf", xOffsetStartScrolling, yOffsetStart, ZAPFINO_NORMALIZATION_FACTOR);
}

void Scene::drawBonus()
{
	drawString("A", "fonts/zapfino/Zapfino.ttf", -0.1f, yOffsetStart, ZAPFINO_NORMALIZATION_FACTOR);
}
