#include "Labyrinth.hpp"
#include <conio.h>
#include <iostream>
#include <fstream>
using namespace std;

int Labyrinth::getZeilen()
{
	return labZeilen;
}

int Labyrinth::getSpalten()
{
	return labSpalten;
}

int Labyrinth::getAnzGeister()
{
	return labAnzGeister;
}

int Labyrinth::getMuenzen()
{
	return muenzen;
}

void Labyrinth::zeichneChar(char c, Position pos)
{
	lab[pos.posy][pos.posx] = c;
}

void Labyrinth::zeichneChar(char c, Position posalt, Position posneu)
{
	zeichneChar(WEG, posalt);
	zeichneChar(ICH, posneu);
}

char Labyrinth::getZeichenAnPos(Position pos)
{
	return lab[pos.posy][pos.posx];
}

bool Labyrinth::istMuenzeAnPos(Position pos)
{
	return lab[pos.posy][pos.posx] == MUENZE;
}

void Labyrinth::exportDatei(const char *dateiname)
{
	ofstream datei(dateiname);
	if (!datei)
	{
		cerr << "Kann Datei nicht oeffnen" << endl;
	}
	for (int i = 0; i < kZeilen; i++)
	{
		datei << lab[i];
	}
	datei.close();
}

void Labyrinth::importDatei(const char *dateiname)
{
	ifstream datei(dateiname);
	if (!datei)
	{
		cerr << "Kann Datei nicht oeffnen" << endl;
	}
	for (int i = 0; i < kZeilen; i++)
	{
		datei.getline(lab[i], kSpalten + 2);
		lab[i][kSpalten] = NL;
		lab[i][kSpalten + 1] = EOS;
	}
	datei.close();
}

void Labyrinth::legeMuenzen()
{
	for (auto &i : lab)
	{
		for (auto &j : i)
		{
			if (j == WEG)
			{
				j = MUENZE;
				muenzen++;
			}
		}
	}
	muenzen -= 1;
}

void Labyrinth::initialisieren()
{
	for (auto &i : lab)
	{
		int c = 0;
		for (auto &j : i)
		{
			if (c == 11)
			{
				j = NL;
			}
			else if (c == 12)
			{
				j = EOS;
			}
			else
				j = MAUER;
			c++;
		}
	}
}

void Labyrinth::drucken()
{
	// Console frei machen
	system("cls");
	// Labyrinth ausgeben
	for (auto &i : lab)
	{
		for (auto j : i)
		{
			cout << j;
		}
	}
}
// Durch Herumlaufen werden Wege im Labyrinth erzeugt
// ASCII-Wert der Tasten: oben 72, links 75, rechts 77, unten 80

void Labyrinth::erzeugen()
{
	char c = 'x';
	int posx = kSpalten / 2;
	int posy = kZeilen / 2;
	lab[posy][posx] = ICH;
	drucken();
	while (c != 'q')
	{
		drucken();
		cout << "Laufen mit Pfeiltasten. Beenden mit q." << endl;
		lab[posy][posx] = WEG;
		c = _getch();
		switch (int(c))
		{
			// oben
		case 72:
			posy = max(1, posy - 1);
			break;
			// links
		case 75:
			posx = max(1, posx - 1);
			break;
			// rechts
		case 77:
			posx = min(kSpalten - 2, posx + 1);
			break;
			// unten
		case 80:
			posy = min(kZeilen - 2, posy + 1);
			break;
			// q = quit
		case 113:
			return;
		}
		lab[posy][posx] = ICH;
	}
}