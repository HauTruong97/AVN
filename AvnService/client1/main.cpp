#include <stdio.h>
#include "AVNViewer.h"

int main(int argc, char *argv[])
{

	AVNViewer client1;
	client1.start(true);
	usleep(5000000);
	client1.viewerRequest();
	return EXIT_SUCCESS;
}