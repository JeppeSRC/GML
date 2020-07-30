#include <gml.h>
#include <stdio.h>
#include <chrono>
#include <iostream>

typedef vec4d vec;

int main(int argc, char** argv) {

	std::cout << alignof(vec3) << std::endl;
	std::cout << alignof(vec3d) << std::endl;
	std::cout << alignof(vec3i) << std::endl << std::endl;

	std::cout << alignof(vec4) << std::endl;
	std::cout << alignof(vec4d) << std::endl;
	std::cout << alignof(vec4i) << std::endl << std::endl;

	constexpr long long iterations = 1000000;

	vec* arr = new vec[iterations];

	for (long long i = 0; i < iterations; i++) {
		arr[i] = vec(i + 1, i * 2 + 1, i * -100 + 20, 1);
	}

	auto start = std::chrono::high_resolution_clock::now();

	for (long long i = 0; i < iterations; i++) {
		arr[i] *= vec(1.0f, 2.0f, 4.0f, 1);
	}

	auto end = std::chrono::high_resolution_clock::now();

	printf("Time: %fns\n", (double)std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / iterations * 1000);

	for (int i = 0; i < 10; i++) {
		auto& v = arr[i];
		printf("%llu %llu %llu\n", v.x, v.y, v.z);
	}

}
