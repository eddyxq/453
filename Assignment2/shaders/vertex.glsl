// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// location indices for these attributes correspond to those specified in the
// InitializeGeometry() function of the main program
layout(location = 0) in vec3 VertexPosition;
layout(location = 1) in vec2 VertexUV;

// output to be interpolated between vertices and passed to the fragment stage
out vec2 uv;
out vec2 vertPos;

uniform float zoom;
uniform float cursor_x;
uniform float cursor_y;
uniform float degree;

float x;
float y;

void main()
{
	vertPos.x = (VertexPosition.x * zoom) + cursor_x;
	vertPos.y = (VertexPosition.y * zoom) + cursor_y;
	x = vertPos.x;
	y = vertPos.y;
	vertPos.y = sin(degree)*x + cos(degree)*y;
	vertPos.x = cos(degree)*x - sin(degree)*y;

	gl_Position = vec4(vertPos.xy, 0.0, 1.0);

    // assign output colour to be interpolated
    uv = VertexUV;
}
