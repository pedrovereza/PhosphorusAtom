#include <math.h>
#include "Nucleus.h"
#include "Transformer.h"

void Nucleus::addHadron(Hadron hadron)
{
	hadrons.push_back(hadron);
}

void Nucleus::draw()
{
	for(auto it = hadrons.begin(); it != hadrons.end(); it++)
		(*it).draw();
}

Point4D randomPositionForHadron(){
    double x, y,z;
    
    x = (rand() % 4) - 2;
    y = (rand() % 4) - 2;
    z = (rand() % 4) - 2;
    
    return Point4D(x, y, z);
}

Nucleus::Nucleus(int protons, int neutrons)
{
	Transformer transformer;

	for(int i = 0; i < protons; i++)
	{
		Hadron proton = Hadron::createProton();

		proton.setMatrix(transformer.makeTranslation(proton.getMatrix(), randomPositionForHadron()));

		addHadron(proton);
	}

	for(int i = 0; i < neutrons; i++)
	{
		Hadron neutron = Hadron::createNeutron();

		neutron.setMatrix(transformer.makeTranslation(neutron.getMatrix(), randomPositionForHadron()));

		addHadron(neutron);
	}

}

Nucleus::Nucleus()
{
}