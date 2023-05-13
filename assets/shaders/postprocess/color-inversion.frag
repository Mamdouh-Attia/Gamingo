#version 330

// this applies a color inversion to the image
uniform sampler2D tex;

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    vec4 color = texture(tex, tex_coord);

    // Invert the color
    color.rgb = vec3(1.0) - color.rgb;

    frag_color = color;
}
