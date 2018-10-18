#version 410

layout(isolines) in;

in vec3 teColour[];

out vec3 color;

#define PI 3.14159265359

void main()
{
	float u = gl_TessCoord.x; //gets the u value

	vec3 startColour = teColour[0];
	vec3 endColour = teColour[1];
	vec3 endColour2 = teColour[2];
	//and more colors as well

	vec2 p0 = gl_in[0].gl_Position.xy;
	vec2 p1 = gl_in[1].gl_Position.xy;
	vec2 p2 = gl_in[2].gl_Position.xy;
	//more vecs for each extra point

	//vec2 bx = p1-p0;

	//vec2 by = vec2(bx.y, bx.x);

	//float cycles = 3.0;
	
	//quadratic bezier curve formula
	vec2 position = ((1-u)*(1-u) * p0) + (2*u * (1-u) * p1) + (u*u * p2);
	
	//vec2 position = u*cos(u*cycles*2.0*PI)*bx + u*sin(u*cycles*2.0*PI)*by + p0; //formula for curve

	gl_Position = vec4(position, 0, 1);

	color = (1-u)*startColour + u*endColour; //interpolates colors

}
