## vertex
attribute vec2 a_pos, a_texCoord;
varying vec2 v_texCoord;
void main() {
    gl_Position = vec4(a_pos.x, a_pos.y, 0, 1);
    v_texCoord = a_texCoord;
}

## fragment
uniform sampler2D u_tex;
varying highp vec2 v_texCoord;
void main() {
    gl_FragColor = texture2D(u_tex, v_texCoord);
}