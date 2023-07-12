#version 450

layout(location = 0) in vec2 in_position;
layout(location = 1) in vec2 in_texture;
layout(location = 2) in vec4 in_color;

layout(location = 0) out vec4 out_color;
layout(location = 1) out vec2 out_texture;

layout(binding = 0) uniform UniversalData {
    mat4 model;
    mat4 view;
    mat4 projection;
    vec2 map_position;
    vec2 screen_size;
} universal_data;

void main()
{
    gl_Position = universal_data.model * universal_data.view * universal_data.projection * vec4(in_position, 0.0, 1.0);
    out_color = in_color;
    out_texture = in_texture;
}