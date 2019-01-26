#include "game/phackmangame.h"

int main(int argc, char** argv) {
    PhackmanGame tsr(1024, 768);
	tsr.exec(argc, argv);
	return 0;
}
