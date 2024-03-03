#version 450

layout(location = 0) in vec2 in_map_position;
layout(location = 1) in vec2 in_screen_size;

layout(origin_upper_left) in vec4 gl_FragCoord;

layout(location = 0) out vec4 out_color;

const float line_separation = 16.0;
const float peak_distance = line_separation / 2.0;

void main()
{
    vec2 map_top_left = in_map_position - (in_screen_size / 2);
    vec2 adjusted_coordinate = floor(map_top_left + gl_FragCoord.xy);
    
    float distance = mod(adjusted_coordinate.x - adjusted_coordinate.y, line_separation);
    float check = -1.0 * abs(distance - peak_distance) + peak_distance;
   
    float component = step(check, 1.0);
    out_color = vec4(component * 0.2, component * 0.2, component, component * 0.75);
}