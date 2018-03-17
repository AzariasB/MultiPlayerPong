
#version 300 es

varying vec2 position;

void main()
{
    gl_FragColor.r = position.x;
    gl_FragColor.g = 0.0;
    gl_FragColor.b = position.y;
    gl_FragColor.a = 1.0;
}
