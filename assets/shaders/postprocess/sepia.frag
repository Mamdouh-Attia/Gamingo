#version 330

// this applies sepia tone to the image

uniform sampler2D tex;

in vec2 tex_coord;
out vec4 frag_color;

void main() {
    vec4 color = texture(tex, tex_coord);

    // Convert the color to sepia tone
    color.rgb = vec3(dot(color.rgb, vec3(0.393, 0.769, 0.189)),
                     dot(color.rgb, vec3(0.349, 0.686, 0.168)),
                     dot(color.rgb, vec3(0.272, 0.534, 0.131)));

    frag_color = color;
}