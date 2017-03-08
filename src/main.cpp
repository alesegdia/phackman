#include "game/phackmangame.h"

int main(int argc, char** argv) {
    PhackmanGame tsr(800, 600);
	tsr.exec(argc, argv);
	return 0;
}
