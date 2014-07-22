#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D textureSample;
uniform bool hasTexture;

varying vec2 v_texcoord;
varying vec4 fragment_color;

void main()
{
    vec4 color = fragment_color;
    if (hasTexture)
        color *= texture2D(textureSample, v_texcoord);
    gl_FragColor = color;
}
