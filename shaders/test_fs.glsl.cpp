#version 130

in vec3 normal;

in vec2 st;
in vec3 light;
out vec4 frag_colour;
uniform sampler2D basic_texture;
uniform int istex;

void main() {
	vec4 texel=texture (basic_texture, st);
    float l = clamp( dot(normalize(normal), normalize(light)), 0, 1 );
    
    frag_colour = texel;	
}
