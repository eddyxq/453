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

	void switchScene(int idx);

	void updateBackground(int idx);

private:
	RenderingEngine* renderer;

	Geometry rectangle;

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

	const char* const FG_IMG1 = "image1-mandrill.png";
	const char* const FG_IMG2 = "image2-uclogo.png";
	const char* const FG_IMG3 = "image3-aerial.png";
	const char* const FG_IMG4 = "image4-thirsk.png";
	const char* const FG_IMG5 = "image5-pattern.png";
	const char* const FG_IMG6 = "image6-bubble.png";
	const char* const BG_IMG1 = "background1-asphalt.jpg";
	const char* const BG_IMG2 = "background2-marble.jpg";
	const char* const BG_IMG3 = "background3-wood.jpg";

	std::vector<GLfloat> gaussian1D(int n);

	MyTexture fgTexture;
	MyTexture bgTexture;
};

#endif /* SCENE_H_ */
