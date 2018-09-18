#version 450 core

layout(binding = 0, r32ui) uniform readonly uimage2D head_pointer_image;

layout(location = 0) out vec4 output_color;

void main(void){
	uint value = imageLoad(head_pointer_image, ivec2(gl_FragCoord.xy)).r;
	if (value == 0) {
		output_color = vec4(0,0,1,1);
		return;
	}
	output_color = vec4(1,0,0,1);
}
