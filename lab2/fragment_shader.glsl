#version 460 core
out vec4 color; 
uniform float timeValue; 
void main() {
    color = vec4(sin(timeValue), 1.0, cos(timeValue), 1.0);
}
