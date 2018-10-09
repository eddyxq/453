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

// only square kernels with odd side length are supported
uniform int kSize;
uniform float filterKernel[50];

void main(void)
{
	vec4 p = texture(imageTexture, uv);
	for (int k = 0; k < 3; k++) {
		float ans = 0.0f;
		for (int i = 0; i < kSize; i++) {
			for (int j = 0; j < kSize; j++) {
				ivec2 pos = {int(uv.x)+j-kSize/2, int(uv.y)+i-kSize/2};
				vec4 pixel = texelFetch(imageTexture, pos);
				ans += filterKernel[kSize*kSize-1 - (3*i+j)] * pixel[k];
			}
		}
		if (ans < 0) ans *= -1;
		FragmentColour[k] = ans;
	}
	FragmentColour[3] = 0.5;
	// FragmentColour = texture(imageTexture, uv + offset);
}
