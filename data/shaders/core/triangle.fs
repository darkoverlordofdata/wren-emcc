#version 330
in vec3 color;
out vec4 fragment;
void main()
{
    gl_FragColor = vec4(color, 1.0);
};