// ==========================================================================
// Vertex program for barebones GLFW boilerplate
//
// Author:  Sonny Chan, University of Calgary
// Date:    December 2015
// ==========================================================================
#version 410

// interpolated colour received from vertex stage
in vec2 uv;

// first output is mapped to the framebuffer's colour index by default
out vec4 FragmentColour;

// uniform sampler2DRect bgTexture;
uniform int time;

void main(void)
{
	FragmentColour = vec4(0.2, 0.8, 0.1, 1.0);
	// FragmentColour = texture(bgTexture, uv);
	// FragmentColour[3] = 1.0;
}
