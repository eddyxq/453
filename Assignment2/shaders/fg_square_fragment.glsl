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

uniform sampler2DRect fgTexture;
uniform float l;

// only square kernels with odd side length are supported
uniform int kSize;
uniform float filterKernel[50];

vec4 computeFilterColor(vec2 uv) {
	vec4 filterColor;
	vec4 original = texture(fgTexture, uv);
	if (l == 0)
	{
		filterColor = original;
	}
	else if (l == 1)
	{
		filterColor = vec4((original.r*0.333) + (original.g*0.333) + (original.b*0.333),
						   (original.r*0.333) + (original.g*0.333) + (original.b*0.333),
						   (original.r*0.333) + (original.g*0.333) + (original.b*0.333),
						   original.a);
	}
	else if (l == 2)
	{
		filterColor = vec4((original.r*0.299) + (original.g*0.587) + (original.b*0.114),
						   (original.r*0.299) + (original.g*0.587) + (original.b*0.114),
						   (original.r*0.299) + (original.g*0.587) + (original.b*0.114),
						   original.a);
	}
	else if (l == 3)
	{
		filterColor = vec4((original.r*0.213) + (original.g*0.715) + (original.b*0.072),
						   (original.r*0.213) + (original.g*0.715) + (original.b*0.072),
						   (original.r*0.213) + (original.g*0.715) + (original.b*0.072),
						   original.a);
	}
	else if (l == 4)
	{
		filterColor = vec4((original.r * .393) + (original.g *.769) + (original.b * .189), 
		                   (original.r * .349) + (original.g *.686) + (original.b * .168), 
						   (original.r * .272) + (original.g *.534) + (original.b * .131), 
						    original.a);
	}
	return filterColor;
}

void main(void)
{
	vec4 p = texture(fgTexture, uv);
	for (int k = 0; k < 3; k++) {
		float ans = 0.0f;
		for (int i = 0; i < kSize; i++) {
			for (int j = 0; j < kSize; j++) {
				vec2 pos = {uv.x+j-kSize/2, uv.y+i-kSize/2};
				vec4 pixel = computeFilterColor(pos);
				ans += filterKernel[kSize*kSize-1 - (3*i+j)] * pixel[k];
			}
		}
		if (ans < 0) ans *= -1;
		FragmentColour[k] = ans;
	}
	FragmentColour[3] = p[3];
}