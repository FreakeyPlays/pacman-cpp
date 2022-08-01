#pragma once
#include "MyString.hpp"
#include "Position.hpp"

class Spieler
{
    MyString name;
    Position pos;
    unsigned int muenzen;

public:
    Spieler()
    {
        muenzen = 0;
    }

    Spieler(const char *neuerName)
    {
        name.assign(MyString(neuerName));
        muenzen = 0;
    }
    Spieler(MyString neuerName)
    {
        name.assign(neuerName);
        muenzen = 0;
    }
    Position &getPos();
    void setPos(Position &neuePos);
    void setRichtung(Richtung neueRichtung);
    int getMuenzen();
    void plusMuenze();
    Spieler &schritt(Labyrinth &lab);
    void orientieren(Labyrinth &lab);
};