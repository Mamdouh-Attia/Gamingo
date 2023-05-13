#version 330
uniform sampler2D tex;

in vec2 tex_coord;
out vec4 frag_color;

const vec2 screen_resolution = vec2(640.0, 480.0); // The resolution of the CRT screen
const float screen_curve = 0.5; // The curvature of the screen
const float screen_scale = 1.0; // The scaling of the screen
const float screen_bloom = 0.1; // The amount of bloom effect
const vec3 screen_scanlines_color = vec3(0.0, 0.0, 0.0); // The color of the scanlines

void main() {
    // Sample the color of the current pixel from the input texture
    vec4 color = texture(tex, tex_coord);

    // Calculate the distance from the current pixel to the center of the screen
    vec2 center = vec2(0.5, 0.5) * screen_resolution;
    vec2 distance = tex_coord * screen_resolution - center;
    distance *= vec2(1.0, screen_curve);

    // Calculate the scaling of the screen
    float scaling = 1.0 / screen_scale;

    // Apply the CRT screen distortion
    vec2 distorted_coords = (distance * scaling + center) / screen_resolution;
    color = texture(tex, distorted_coords);

    // Add scanlines effect
    float scanline = mod(tex_coord.y * screen_resolution.y, 2.0);
    color.rgb = mix(color.rgb, screen_scanlines_color, scanline);

    // Add bloom effect
    vec4 bloom = vec4(0.0, 0.0, 0.0, 0.0);
    vec4 bloom_contrib = color * screen_bloom;
    for (int i = -4; i <= 4; i++) {
        bloom += texture(tex, distorted_coords + vec2(float(i), 0.0) / screen_resolution) * screen_bloom;
    }
    color += bloom;

    frag_color = color;
}








