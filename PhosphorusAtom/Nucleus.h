#include <vector>
#include "Hadron.h"

using namespace std;

class Nucleus
{
private:
	vector<Hadron> hadrons;

public:
	void draw();
	void addHadron(Hadron hadron);

	Nucleus();
	Nucleus(int protons, int neutrons);
};