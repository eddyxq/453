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

uniform sampler2DRect imageTexture;
uniform int time;

void main(void)
{
    // write colour output without modification
    //FragmentColour = vec4(Colour, 0);
	vec2 temp = vec2(10.0 * time, 0.0);
	FragmentColour = texture(imageTexture, uv + temp);
	//FragmentColour = vec4(0.0, time, 0.0, 0.0);
}
