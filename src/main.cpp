#include <GML/gml.h>
#include <stdio.h>
#include <chrono>
#include <iostream>

using namespace gml;

int main(int argc, char** argv) {

	vec4 v = gml::Translate(vec3(-1, 1, 10)) * vec4(1, 0, 0, 1);

	printf("%f %f %f %f\n", v.x, v.y, v.z, v.w);

}
