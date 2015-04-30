## vertex
attribute vec2 a_pos;
void main() {
    gl_Position = vec4(a_pos.x, a_pos.y, 0, 1);
}

## fragment
void main() {
    gl_FragColor = vec4(0.7, 0.7, 0.7, 1.0);
}

