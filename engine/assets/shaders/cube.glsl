#type vertex

#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform vec3 u_Color;
uniform mat4 u_Transform;

uniform mat4 u_ViewProj;

out vec3 o_Color;
out vec2 o_TexCoord;

void main()
{
    gl_Position = u_ViewProj * vec4(a_Position, 1.0f);
    o_Color = a_Color;
    o_TexCoord = a_TexCoord;
}

#type fragment

#version 460

layout(location = 0) out vec4 color;

in vec3 o_Color;
in vec2 o_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    color = vec4(o_Color, 1.0f);
}
