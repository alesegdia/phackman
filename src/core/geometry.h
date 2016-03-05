
#pragma once

struct vec2 {
	float x, y;
	vec2() : x(0), y(0) {}
	vec2(float _x, float _y) : x(_x), y(_y) {}
};

struct rect {
	vec2 min, max;
};
