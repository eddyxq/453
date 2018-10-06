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

	std::vector<GLfloat> gaussian1D(int n);
};

#endif /* SCENE_H_ */
