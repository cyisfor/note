#include "note.h"

int main(int argc, char *argv[])
{
    INFO("info level %d %s", argc, argv[0]);
	INFO("this file is " __FILE__);
	WARN("warning level");
	ERROR("the program dies here");
	ERROR("never get here");
    return 0;
}
