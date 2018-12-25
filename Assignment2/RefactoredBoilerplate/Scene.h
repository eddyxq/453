/*
 * Scene.h
 *	Class for storing objects in a scene
 *  Created on: Sep 10, 2018
 *      Author: cb-ha
 */

#ifndef SCENE_H_
#define SCENE_H_

#include <vector>

#include "Geometry.h"

#include "texture.h"

//Forward declaration of classes
//(note this is necessary because these are pointers and it allows the #include to appear in the .cpp file)
class RenderingEngine;

class Scene {
public:
	Scene(RenderingEngine* renderer);
	virtual ~Scene();

	//Send geometry to the renderer
	void displayScene();

	void selectFilter(int idx);
	void selectForeground(int idx);
	void selectBackground(int idx);

	void updateVertices(float dx, float dy);
	void rotateForeground(float degree);
	void stopVerticesUpdate();
	void updateZoom(float zoom);

private:
	RenderingEngine* renderer;

	Geometry fgRectangle, bgRectangle;

	//list of objects in the scene
	std::vector<Geometry> objects;

	const GLfloat identity[1] = { 1.0f };

	const GLfloat vertical_sobel[9] = {
		-1.0f, 0.0f, 1.0f,
		-2.0f, 0.0f, 2.0f,
		-1.0f, 0.0f, 1.0f,
	};

	const GLfloat horizontal_sobel[9] = {
		-1.0f, -2.0f, -1.0f,
		0.0f, 0.0f, 0.0f,
		1.0f, 2.0f, 1.0f,
	};

	const GLfloat unsharpen_mask[9] = {
		0.0f, -1.0f, 0.0f,
		-1.0f, 5.0f, -1.0f,
		0.0f, -1.0f, 0.0f,
	};

	std::string FG_IMG1 = "image1-mandrill.png";
	std::string FG_IMG2 = "image2-uclogo.png";
	std::string FG_IMG3 = "image3-aerial.jpg";
	std::string FG_IMG4 = "image4-thirsk.jpg";
	std::string FG_IMG5 = "image5-pattern.png";
	std::string FG_IMG6 = "image6-bubble.png";
	std::string FG_IMG7 = "image7-hourglass.png";
	std::string BG_IMG1 = "background1-asphalt.jpg";
	std::string BG_IMG2 = "background2-marble.jpg";
	std::string BG_IMG3 = "background3-wood.jpg";

	std::vector<GLfloat> gaussian1D(int n);

	MyTexture fgTexture;
	MyTexture bgTexture;

	int sceneIdx;

	const std::vector<std::string> fgImages = { FG_IMG1, FG_IMG2, FG_IMG3, FG_IMG4, FG_IMG5, FG_IMG6, FG_IMG7 };
	const std::vector<std::string> bgImages = { BG_IMG1, BG_IMG2, BG_IMG3 };
	std::vector<MyTexture> foregrounds;
	std::vector<MyTexture> backgrounds;

	void selectFilter();

	std::vector<glm::vec3> fgVertices;
	std::vector<glm::vec3> bgVertices;

	float prevX, prevY, prevZoom = 1.0f;
};

#endif /* SCENE_H_ */
