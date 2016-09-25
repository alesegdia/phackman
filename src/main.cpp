#include "game/phackmangame.h"

int main(int argc, char** argv) {
	PhackmanGame tsr(640, 480);
	tsr.exec(argc, argv);
	return 0;
}
