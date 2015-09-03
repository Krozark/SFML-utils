#include "App.h"

int main(int argc, char *argv[])
{
	App theApp;

	if (!theApp.Initialize())
	{
		printf("Failed to initialize the app!");
		return 0;
	}
	theApp.Run();
}
