#version 450

layout(location = 0) in vec2 in_position;

layout(location = 0) out vec2 out_map_position;
layout(location = 1) out vec2 out_screen_size;

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
    out_map_position = universal_data.map_position;
    out_screen_size = universal_data.screen_size;
}