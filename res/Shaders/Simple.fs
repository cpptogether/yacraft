#version 330 core

uniform sampler2D blockAtlas;

in vec2 fragTexCoords;

out vec4 outColor;

void main(){
    outColor = texture(blockAtlas, fragTexCoords);
}