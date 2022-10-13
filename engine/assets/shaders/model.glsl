#type vertex

#version 460

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;
layout(location = 2) in vec2 a_TexCoord;

uniform mat4 u_ViewProj;

out vec3 o_Position;
out vec3 o_Normal;
out vec2 o_TexCoord;

void main()
{
    gl_Position = u_ViewProj * vec4(a_Position, 1.0f);

    o_Position = a_Position;
    o_Normal = a_Normal;
    o_TexCoord = a_TexCoord;
}

#type fragment

#version 460

layout(location = 0) out vec4 color;

in vec3 o_Position;
in vec3 o_Normal;
in vec2 o_TexCoord;

struct DirectionalLight {
    vec3 Color;
    
    float Intensity;

    vec3 Direction;
};

uniform DirectionalLight light;

uniform sampler2D s_Texture;

void main() {
    float factor = dot(normalize(o_Normal), -light.Direction);

    vec4 result = vec4(0.0f, 0.0f, 0.0f, 0.0f);

    if (factor > 0) {
        result = vec4(light.Color, 1.0f) *
                       light.Intensity *
                       factor;
    }
    
    color = texture(s_Texture, o_TexCoord) + result;
}
