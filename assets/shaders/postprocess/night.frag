#version 330

uniform sampler2D tex;
in vec2 tex_coord;
out vec4 frag_color;

void main() {
    // Get the color of the current pixel from the texture
    vec4 color = texture(tex, tex_coord);

    // Adjust the color to simulate night mode
    color.r *= 0.4;
    color.g *= 0.4;
    color.b *= 0.8;

    // Output the adjusted color
    frag_color = color;
}