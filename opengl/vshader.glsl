#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 mvp_matrix;

in vec4 position;
in vec4 color;

//smooth out vec4 theColor;
//varying vec2 v_texcoord;
//varying vec4 v_fragment_color;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = mvp_matrix * position;

    // Pass texture coordinate to fragment shader
    // Value will be automatically interpolated to fragments inside polygon faces
//    v_texcoord = a_texcoord;
//    v_fragment_color = a_color;
}
//! [0]
