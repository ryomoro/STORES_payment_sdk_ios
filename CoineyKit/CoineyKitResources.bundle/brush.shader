## vertex
uniform mat4 u_mvp;
attribute vec2 a_pos;
attribute float a_thickness, a_alpha;
varying mediump float v_alpha;
void main() {
    gl_Position  = u_mvp * vec4(a_pos.x, a_pos.y, 0, 1);
    gl_PointSize = a_thickness*12.0;
    v_alpha      = a_alpha;
}

## fragment
uniform sampler2D u_tex;
varying mediump float v_alpha;
void main() {
    gl_FragColor = texture2D(u_tex, gl_PointCoord);
    gl_FragColor.a *= v_alpha;
}
