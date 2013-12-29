#include "Layer.h"
#include "Nucleus.h"

class Atom
{
private:
	Layer layerK;
	Layer layerL;
	Layer layerM;

	Nucleus nucleus;

public:
	Atom(int protons, int neutrons, int electrons);

	void draw();
	void animate();
};