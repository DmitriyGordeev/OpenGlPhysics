#ifdef GL_ES
precision mediump float;
#endif

uniform vec2 u_resolution;
uniform float u_time;


void main() {

    vec2 position = (gl_FragCoord.xy) / u_resolution;

    float redColor = 0.9 * sin(u_time * gl_FragCoord.x);
    float greenColor = 0.1 * cos(u_time * gl_FragCoord.y);
    float blueColor = 0.9 * cos(u_time * gl_FragCoord.x);

    vec3 color = vec3(redColor, greenColor, blueColor);

    gl_FragColor = vec4(color, 1.0);
}