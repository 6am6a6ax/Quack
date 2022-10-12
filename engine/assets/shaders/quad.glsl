#type vertex

#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProj;
uniform vec4 u_Color;
uniform mat4 u_Transform;
uniform vec4 u_Test;

out vec4 o_Color;
out vec2 o_TexCoord;

void main()
{
    gl_Position = vec4(a_Position, 1.0);
    o_Color = u_Color;
    o_TexCoord = a_TexCoord;
}

#type fragment

#version 460

layout(location = 0) out vec4 color;

in vec4 o_Color;
in vec2 o_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    color = texture(u_Texture, o_TexCoord);
}
