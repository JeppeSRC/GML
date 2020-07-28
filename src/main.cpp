#include <gml.h>
#include <stdio.h>

int main(int argc, char** argv) {
	
	vec4 a(10), b((float)argc * 10, (float)argc * 13, (float)argc * 12, (float)argc * 11);



	vec4 res = b.Normalize();

	printf("%f %f %f %f\n", res.x, res.y, res.z, res.w);

	printf("%f\n", res.Dot(res));
}
