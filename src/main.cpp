#include "Engine.h"
#include <time.h>


int main()
{
	srand(static_cast<unsigned>(time(0)));

	Engine Engine;

	Engine.run();

	return 0;
}