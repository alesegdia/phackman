#include "game/phackmangame.h"
#include "constants.h"

int main(int argc, char** argv) {
    PhackmanGame tsr(Constants::WindowWidth, Constants::WindowHeight);
	tsr.exec(argc, argv);
	return 0;
}
