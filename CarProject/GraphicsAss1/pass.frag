#version 330

in vec4 colorV;

out vec4 flatColor;

void main()
{
    //flatColor = vec4(1.0,1.0,1.0,1.0); //white
    flatColor = colorV;
}