#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NUM_PAGES	1024

static void wait_for_input(const char *msg)
{
	char buf[32];

	printf(" * %s\n", msg);
	printf(" -- Press ENTER to continue ..."); fflush(stdout);
	fgets(buf, 32, stdin);
}

int main(void)
{
	char *p;
	int status;
	size_t i;
	int page_size = getpagesize();
	char value;

	wait_for_input("beginning");

	p = mmap(NULL, NUM_PAGES * page_size, PROT_READ | PROT_WRITE,
			MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
	if (p == MAP_FAILED) {
		perror("mmap");
		exit(EXIT_FAILURE);
	}

	for (i = 0; i < NUM_PAGES; i++)
		p[i*page_size] = i;

	wait_for_input("init p before fork");

	switch (fork()) {
		case -1:    /* handle error */
			perror("fork");
			exit(EXIT_FAILURE);

		case 0:     /* child process */
			wait_for_input("child begin");

			for (i = 0; i < NUM_PAGES / 2; i++)
				value = p[i*page_size];
			wait_for_input("child after read");

			for (i = NUM_PAGES / 2; i < NUM_PAGES; i++)
				p[i*page_size] = page_size-i;
			wait_for_input("child after write");

			exit(EXIT_SUCCESS);
			break;

		default:
			break;
	}

	wait(&status);
	wait_for_input("parent after wait");

	for (i = 0; i < NUM_PAGES; i++)
		p[i*page_size] = i;

	wait_for_input("end");
	return 0;
}
