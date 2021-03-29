#version 450 cpre

in vec3 Normal;
in vec2 TextCoords;
in vec3 Colour;

out vec4 fColour;

void main(){
fColour = vec4(Colour, 1.0);
}