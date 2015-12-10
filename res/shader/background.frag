uniform vec2 offset;

float x;
float y;

float rand(vec2 seed);

float hasStar() {
	float d = 10.0;
	float rx = round(x / d);
	float ry = round(y / d);

	if (rand(vec2(rx, ry)) > 0.9) {
		float cx = rx * d;
		float cy = ry * d;

		float r = sqrt(pow(x - cx, 2) + pow(y - cy, 2));
		return 1.0 - ((r * 2) / d);
	}
	return 0.0;
}

vec4 starColor() {
	return vec4(
		abs(mod(y - x, 255.0)) / 255.0,
		abs(mod(x + y, 255.0)) / 255.0,
		abs(mod(x - y, 255.0)) / 255.0,
		1.0
	);
}

void main() {
	x = round(offset.x + gl_FragCoord.x);
	y = round(offset.y + gl_FragCoord.y);
	vec4 result = starColor() * hasStar();
	gl_FragColor = result;
}

float rand(vec2 seed) {
	return fract(sin(dot(seed.xy, vec2(12.9898, 78.233))) * 43758.5453);
}