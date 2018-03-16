
#version 150 core

uniform mat4 modelView;
uniform mat4 projection;
uniform float time;

in vec3 pos;
in vec4 clr;

out vec4 v_clr;

void main()
{
        v_clr = clr;
        vec3 new_pos = pos * (1.0 + 0.25*sin(pos.x+pos.y+pos.z+5.0*time));
        gl_Color = vec4(0.5,0.5,0.5,0.5);
}
