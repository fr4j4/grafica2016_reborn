#version 130
//layout(location = 0) in vec3 vertex_position;
//layout(location = 1) in vec3 vertex_normal;
//layout(location = 2) in vec2 texture_coord;
in vec3 vertex_position;
in vec3 vertex_normal;
in vec2 texture_coord;
uniform mat4 view, proj, model;
out vec3 normal;
out vec3 light;
out vec2 st;

void main() {

	light = (view * vec4(1.0f, 0.0f, 1.0f, 0.0f)).xyz;
	st = texture_coord;
	normal = (view * vec4(vertex_normal, 0.0)).xyz;
	gl_Position = proj * view * model * vec4(vertex_position, 1.0);
	//gl_Position =vec4 (vertex_position, 1.0);
}
