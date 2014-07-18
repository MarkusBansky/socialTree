#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

in vec4 position;
in vec4 color;

varying vec4 fragment_color;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * position;

    // Pass color to to fragment shader
    fragment_color = color;
}
