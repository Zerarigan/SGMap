#include "common.h"
#include <string.h>

int main(int argc, char **argv) {
	local_error = 0;
#if DEBUG_H
	uint8_t imagePath[DEBUG_PATH_LIMIT];
	memset(imagePath, 0, DEBUG_PATH_LIMIT);
	strcpy_s(imagePath, DEBUG_PATH_LIMIT, DEBUG_PATH);
#else 
	if (argc < 2) {
		// help
		return -1;
	}
	uint8_t * imagePath;
	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'p':
				imagePath = argv[i];
			default:
			}
		}
	}
#endif
	FILE * descriptor;
	errno_t error_code = fopen_s(&descriptor, imagePath, "r");
	if (!error_code) {
		// Error
		return -1;
	}
	fseek(descriptor, 0, SEEK_END);
	uint64_t size = ftell(descriptor);
	rewind(descriptor);
	IMAGE  * file_image = (IMAGE *)malloc(sizeof(IMAGE) * size);
	uint64_t result = fread(file_image, sizeof(IMAGE), size, descriptor);
	if (result != size) {
		// Error
		return -1;
	}
	if (ValidImage(file_image, size)) {
		result = Decopmresion(&file_image, size);							// Factual Address 
	}
	
}