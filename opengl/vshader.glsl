#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

attribute vec4 position;
attribute vec4 color;

varying vec4 fragment_color;

attribute vec2 texcoord;
varying vec2 v_texcoord;

void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * position;

    // Pass color and texture coordinates to fragment shader
    fragment_color = color;
    v_texcoord = texcoord;
}
