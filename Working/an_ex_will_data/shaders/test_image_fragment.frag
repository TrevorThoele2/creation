#version 450

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_texture_coordinate;
layout(binding = 1) uniform sampler2D textureSampler;

layout(location = 0) out vec4 out_color;

void main()
{
    out_color = texture(textureSampler, in_texture_coordinate) * vec4(0.5f, 0.5f, 0.5f, 0.5f);
}