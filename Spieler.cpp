#include <cmath>
#include "Spieler.hpp"
#include "Labyrinth.hpp"

Position &Spieler::getPos()
{
	return pos;
}

void Spieler::setPos(Position &neuePos)
{
	pos = neuePos;
}

void Spieler::setRichtung(Richtung neueRichtung)
{
	pos.r = neueRichtung;
}

int Spieler::getMuenzen()
{
	return muenzen;
}

void Spieler::plusMuenze()
{
	muenzen++;
}

Spieler &Spieler::schritt(Labyrinth &lab)
{
	pos.schritt(lab, 0);
	return *this;
}

void Spieler::orientieren(Labyrinth &lab)
{
	Position postmp = pos;
	// Eine von 4 Richtungen ausw�hlen
	int rint = rand() % 4;
	postmp.r = Richtung(rint);
	while ((lab.getZeichenAnPos(postmp)) == MAUER)
	{
		rint = rand() % 4;
		postmp.r = Richtung(rint);
	}
	pos.r = Richtung(rint);
}