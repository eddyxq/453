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
uniform float r;
uniform float g;
uniform float b;
uniform float l;
vec4 filterColor;
vec4 original;

void main(void)
{
	original = texture(imageTexture, uv);

	if (l == 0)
	{
		filterColor = original;
	}
	else if (l == 1)
	{
		filterColor = vec4(original.r*0.333, original.g*0.333, original.b*0.333, original.a);
	}
	else if (l == 2)
	{
		filterColor = vec4(original.r*0.299, original.g*0.587, original.b*0.114, original.a);
	}
	else if (l == 3)
	{
		filterColor = vec4(original.r*0.213, original.g*0.715, original.b*0.072, original.a);
	}
	else if (l == 4)
	{
		filterColor = vec4((original.r * .393) + (original.g *.769) + (original.b * .189), 
		                   (original.r * .349) + (original.g *.686) + (original.b * .168), 
						   (original.r * .272) + (original.g *.534) + (original.b * .131), 
						    original.a);
	}
	FragmentColour = filterColor;
}
