#version 330 core

uniform mat4 projection;
uniform mat4 view;

layout(location = 0) in vec3 inVertexPosition;
layout(location = 2) in vec2 inTexCoords;

out vec2 fragTexCoords;

void main(){
	gl_Position = projection * view * vec4(inVertexPosition, 1.0);
	fragTexCoords = inTexCoords;
}