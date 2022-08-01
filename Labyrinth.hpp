#pragma once
#include "Position.hpp"

const int kZeilen = 11;
const int kSpalten = 11;
const int kAnzGeister = 3;

enum Symbole
{
	MAUER = '#',
	WEG = ' ',
	MUENZE = '.',
	NL = '\n',
	EOS = '\0',
	ICH = 'C',
	GEIST = 'G'
};

class Labyrinth
{
private:
	int labZeilen;
	int labSpalten;
	int labAnzGeister;
	unsigned int muenzen;
	char lab[kZeilen][kSpalten + 2];

public:
	Labyrinth()
	{
		muenzen = 0;
		labZeilen = kZeilen;
		labSpalten = kSpalten;
		labAnzGeister = kAnzGeister;
		initialisieren();
	}
	void legeMuenzen();
	int getZeilen();
	int getSpalten();
	int getAnzGeister();
	int getMuenzen();
	void initialisieren();
	void drucken();
	void erzeugen();
	void zeichneChar(char c, Position pos);
	void zeichneChar(char c, Position posalt, Position posneu);
	char getZeichenAnPos(Position pos);
	bool istMuenzeAnPos(Position pos);
	void exportDatei(const char *dateiname);
	void importDatei(const char *dateiname);
};
