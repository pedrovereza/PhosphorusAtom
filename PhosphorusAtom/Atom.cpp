#include "Atom.h";

Atom::Atom(int protons, int neutrons, int electrons)
{
	layerK = Layer(electrons, 2, 10);
	layerL = Layer(electrons, 8, 20);
	layerM = Layer(electrons, 5, 40);

	nucleus = Nucleus(protons, neutrons);
}

void Atom::animate()
{
	layerK.moveElectrons();
	layerL.moveElectrons();
	layerM.moveElectrons();
}

void Atom::draw()
{
	layerK.draw();
	layerL.draw();
	layerM.draw();

	nucleus.draw();
}