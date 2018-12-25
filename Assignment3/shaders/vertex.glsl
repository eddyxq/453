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
layout(location = 1) in vec3 VertexColor;

uniform float dx;

// output to be interpolated between vertices and passed to the fragment stage
out vec3 color;

void main()
{

    // assign vertex position without modification
	vec3 transformedPosition = VertexPosition;
	transformedPosition.x += dx;
	
    gl_Position = vec4(transformedPosition.xy, 0.0, 1.0);

    // assign output colour to be interpolated
    color = VertexColor;
}
