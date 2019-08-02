// path multi-param to func
#include <stdio.h>
#include <stdlib.h>

void sma_printf(const char * s, ...) {
	va_list args;
	// va_start(args, s);
	// vprintf(stderr, s, args);
	// fprintf(stderr, "\n");
	// va_end(args);
	// abort();
}

int main(int argc, char const *argv[])
{
	sma_printf("%s\n", "Sohaib Mohammed");
	return 0;
}