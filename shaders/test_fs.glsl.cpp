#version 130

in vec3 normal;
in vec2 st;
out vec4 frag_colour;
in vec3 light;

void main() {
	//frag_colour=vec4(0.0,0.0,0.0,1.0);
	//vec4 texel = texture (basic_texture, st);
	//float l = clamp( dot(normalize(normal), normalize(light)), 0, 1 );
	//frag_colour = texel*l;
	frag_colour = vec4 (normal, 1.0);

}
