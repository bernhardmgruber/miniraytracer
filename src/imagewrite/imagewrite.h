#pragma once

// this is a great image writing library that can be called from C and C++ client code, independently of their compiler

#ifdef __cplusplus
extern "C" {
#endif

	// returns zero on failure, non-zero on success
	int writeImage(const char* filename, unsigned int width, unsigned int height, const unsigned char* pixels);

#ifdef __cplusplus
}
#endif
