#type vertex

#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProj;

out vec2 o_TexCoord;

void main()
{
    gl_Position = u_ViewProj * vec4(a_Position, 1.0);
    o_TexCoord = a_TexCoord;
}

#type fragment

#version 460

layout(location = 0) out vec4 color;

in vec2 o_TexCoord;

uniform sampler2D u_Texture;

void main()
{
    vec2 uv = vec2(gl_FragCoord.x, gl_FragCoord.y) / 1000;

    float size = 1.0 / 7.0;   // size of the tile
    float edge = size / 32.0; // size of the edge

    uv = (mod(uv, size) - mod(uv - edge, size) - edge) * 1.0 / size;

    color = vec4(0.9 - length(uv) * 0.5); // 0.9 for the face of the tile, 0.5 for the edge
}
