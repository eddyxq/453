#version 410

layout(isolines) in;

in vec3 teColour[];

out vec3 color;

uniform int degree;

void main()
{
	float u = gl_TessCoord.x;
	
	//degree 2 - quadratic
	if (degree == 2) {
		vec3 color0 = teColour[0];
		vec3 color1 = teColour[1];
		vec3 color2 = teColour[2];

		vec2 p0 = gl_in[0].gl_Position.xy;
		vec2 p1 = gl_in[1].gl_Position.xy;
		vec2 p2 = gl_in[2].gl_Position.xy;
		
		vec2 position = ((1-u)*(1-u) * p0) + (2*u*(1-u) * p1) + ((u*u) * p2);
		gl_Position = vec4(position, 0, 1);
		color = (1-u)*color0 + (u)*color2;
	}
	//degree 3 - cubic
	else if (degree == 3) {
		vec3 color0 = teColour[0];
		vec3 color1 = teColour[1];
		vec3 color2 = teColour[2];
		vec3 color3 = teColour[3];

		vec2 p0 = gl_in[0].gl_Position.xy;
		vec2 p1 = gl_in[1].gl_Position.xy;
		vec2 p2 = gl_in[2].gl_Position.xy;
		vec2 p3 = gl_in[3].gl_Position.xy;
		
		vec2 position = ((1-u)*(1-u)*(1-u) * p0) + (3*u*(1-u)*(1-u) * p1) + ((3*(1-u)*u*u) * p2) + ((u*u*u) * p3);
		gl_Position = vec4(position, 0, 1);
		color = (1-u)*color0 + (u)*color2;
	}
}
