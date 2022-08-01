// Datei PacMan.cpp
#include <windows.h>
#include <conio.h>
// conio.h f�r _getch() und _kbhit()
// Achtung: Nicht Teil des Standards und daher abh�ngig vom Compiler
#include <iostream>
#include "PacMan.hpp"
using namespace std;

// Konstruktor
PacMan::PacMan(Labyrinth &l, Spieler &sp, Spieler gArr[], int anzGeister)
{
	schritte = 0; // Anzahl der Spielschritte
	muenzen = 0;  // Anzahl der M�nzen im Labyrinth
	lab = &l;
	s = &sp;
	for (int i = 0; i < anzGeister; i++)
	{
		g[i] = &gArr[i];
	}
	// Spieler in die Mitte des Labyrinths setzen
	Position zentrum(lab->getSpalten() / 2, lab->getZeilen() / 2);
	s->setPos(zentrum);
	// Anzahl der M�nzen vom Labyrinth �bernehmen
	muenzen = lab->getMuenzen();
}

// Einen Schritt im Spiel ausf�hren
void PacMan::schritt()
{
	// Schritte z�hlen
	schritte++;
	// Aktuelle Position des Spielers merken,
	// so dass sie mit WEG �berschrieben werden kann.
	Position postmp = s->getPos();
	// Den Spieler einen Schritt machen lassen.
	s->schritt(*lab);
	// Wenn beim neuen Schritt eine M�nze gefunden wurde ...
	if (lab->istMuenzeAnPos(s->getPos()))
	{
		// Anzahl der gesammelten M�nzen des Spielers erh�hen
		s->plusMuenze();
		// Anzahl der vorhandenen M�nzen reduzieren
		muenzen--;
	}
	// den getanen Schritt des Spielers einzeichnen
	lab->zeichneChar(WEG, postmp, s->getPos());
	lab->zeichneChar(ICH, s->getPos());
	// Dem Spieler 5 Schritte Vorsprung vor den Geistern lassen
	if (schritte == 10)
	{
		Position zentrum(lab->getSpalten() / 2, lab->getZeilen() / 2);
		for (int i = 0; i < kAnzGeister; i++)
		{
			g[i]->setPos(zentrum);
			lab->zeichneChar(GEIST, g[i]->getPos());
		}
	}
	// Jetzt laufen die Geister
	if (schritte > 10)
	{
		for (int i = 0; i < kAnzGeister; i++)
		{
			// Geist-Zeichen l�schen
			lab->zeichneChar(WEG, g[i]->getPos());
			// Geist w�hlt zuf�llig seine Schrittrichtung
			g[i]->orientieren(*lab);
			// Geist macht seinen Schritt
			g[i]->schritt(*lab);
		}
		// Geister einzeichnen
		for (int i = 0; i < kAnzGeister; i++)
		{
			// Geister sammeln M�nzen
			if (lab->istMuenzeAnPos(g[i]->getPos()))
			{
				// Anzahl der vorhandenen M�nzen reduzieren
				muenzen--;
			}
			// Geist einzeichnen
			lab->zeichneChar(GEIST, g[i]->getPos());
		}
	}
}

// Spiel spielen
void PacMan::spielen()
{
	// Das Spiel l�uft solange noch M�nzen im Labyrinth sind
	// und eine Geist nicht auf der Position des Spielers ist.
	// Tempor�re Variable f�r die Keyboard-Eingabe
	char c = 'x';
	// Tempor�re Variable, um die gew�hlte Richtung zu speichern
	Richtung r = s->getPos().r;
	// Position des Spielers einzeichnen
	lab->zeichneChar(ICH, s->getPos());
	// Tempor�re Variable f�r die Abbruchbedingung der Spielschleife
	bool cond = (muenzen > 0);
	while (cond)
	{
		// Eine Weile warten (Windows)
		Sleep(500);
		// Eine Weile warten (C++11)
		// std::this_thread::sleep_for(std::chrono::milliseconds(700));
		if (_kbhit())
		{ // wenn Taste gedr�ckt wurde ...
			c = _getch();
			switch (int(c))
			{
				// oben
			case 72:
				r = OBEN;
				break;
				// links
			case 75:
				r = LINKS;
				break;
				// rechts
			case 77:
				r = RECHTS;
				break;
				// unten
			case 80:
				r = UNTEN;
				break;
				// q = quit
			case 113:
				muenzen = 0;
				break;
			}
			s->setRichtung(r);
		}
		// Einen Spielschritt ausf�hren
		schritt();
		// Neue Spielsituation anzeigen
		lab->drucken();
		cout << "Gesammelte Muenzen: " << s->getMuenzen() << endl;
		cout << "Verbleibende Muenzen: " << muenzen << endl;
		cout << schritte << ". Schritt" << endl
			 << endl;
		cout << "Zum Abbrechen q druecken" << endl;
		// Pr�fen, ob noch M�nzen da sind
		// und ob der Spieler noch nicht gefangen wurde
		cond = (muenzen > 0);
		for (int i = 0; i < kAnzGeister; i++)
		{
			cond = cond && !(s->getPos().istGleichZu(g[i]->getPos()));
		}
	}
}
