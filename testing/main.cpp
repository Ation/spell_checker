#include "main.h"

int main(void) {
    StartTesting(__testFunctions, sizeof(__testFunctions)/sizeof(*__testFunctions));
	return 0;
}
