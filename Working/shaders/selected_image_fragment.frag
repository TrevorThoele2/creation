#version 450

layout(location = 0) in vec4 in_color;
layout(location = 1) in vec2 in_texture_coordinate;
layout(binding = 1) uniform sampler2D textureSampler;

layout(location = 0) out vec4 out_color;

void main()
{
    const vec4 textureColor = texture(textureSampler, in_texture_coordinate);
    const vec4 overlayColor = vec4(0.0f, 0.0f, 1.0f, 0.5f);
    
    // outRGB = (srcRGB * srcA + dstRGB * dstA(1 - srcA)) / (srcA + dstA(1 - srcA))
    vec3 outputColor = vec3((overlayColor.rgb * overlayColor.a + textureColor.rgb * textureColor.a * (1.0f - overlayColor.a)) / (overlayColor.a + textureColor.a * (1.0f - overlayColor.a)));
    out_color = vec4(outputColor, textureColor.a);
}