#pragma once

// this is a great image writing library that can be called from C and C++ client code, independently of their compiler

#ifdef _WIN32
#  ifdef BUILD_SHARED_LIBRARY
#    define IMAGEWRITE_API __declspec(dllexport)
#  else
#    define IMAGEWRITE_API __declspec(dllimport)
#  endif
#else
#  define IMAGEWRITE_API
#endif


#ifdef __cplusplus
extern "C" {
#endif

	// returns zero on failure, non-zero on success
	IMAGEWRITE_API int writeImage(const char* filename, unsigned int width, unsigned int height, const unsigned char* pixels);

#ifdef __cplusplus
}
#endif
