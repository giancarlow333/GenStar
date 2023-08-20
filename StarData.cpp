#include <utility>  // for overloading remaining comparison operators
#include <string>
#include <iostream>
#include "StarData.h"
using namespace std;

StarData::StarData()
{
    //ctor
}

StarData::StarData(const StarData& other)
{
    spectral = other.spectral;
    sub = other.sub;
    luminos = other.luminos;
}

//alternate constructor
StarData::StarData(int sp, int sb, int l)
{
    spectral = sp;
    sub = sb;
    luminos = l;
}

///////////////////////////////////////
// ACCESSORS
///////////////////////////////////////

int StarData::GetSpectralInt ()
{
    return spectral;
}

int StarData::GetLuminosityInt ()
{
    return luminos;
}

char StarData::GetSpectralClass () const
{   // BAFGKMLTDX
    switch (spectral) {
        case 0 : return 'B';
        case 1 : return 'A';
        case 2 : return 'F';
        case 3 : return 'G';
        case 4 : return 'K';
        case 5 : return 'M';
        case 6 : return 'L';
        case 7 : return 'T';
        case 8 : return 'D';
        case 9 : return 'X';
    }
}

int StarData::GetSubClass () const
{
    return sub;
}

string StarData::GetLuminosityClass () const
{   // III, IV, V
    switch (luminos) {
        case 0 : return "III";
        case 1 : return "IV";
        case 2 : return "V";
        case -1 : return "";
    }
}

/*string GetStarData ()
{
    string sp, sb, l;
    sp = GetSpectralClass();
    sb = GetSubClass();
    l = GetLuminosityClass();

}*/

///////////////////////////////////////
// MUTATORS
///////////////////////////////////////

void StarData::SetSpectralInt (int n)
{
    spectral = n;
}

void StarData::SetSubClass (int n)
{
    sub = n;
}

void StarData::SetLuminosityInt (int n)
{
    luminos = n;
}

///////////////////////////////////////
// OPERATORS
///////////////////////////////////////

StarData& StarData::operator=(const StarData& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}

bool operator==(StarData a, StarData b)
{
    return (a.luminos == b.luminos) && (a.spectral == b.spectral) && (a.sub == b.sub);
}

bool operator<(StarData a, StarData b)
{
    /*int a_block = a.spectral*100 + a.sub*10 + a.luminos;
    int b_block = b.spectral*100 + b.sub*10 + b.luminos;
    return a_block < b_block;*/

    if (a.luminos < b.luminos)
        return true;
    else {
        if (a.spectral < b.spectral)
            return true;
        else {
            if (a.sub < b.sub)
                return true;
        }
        return false;
    }
}

ostream& operator<<(ostream & outs, const StarData & star)
{
    //string L =
    outs << star.GetSpectralClass();
    outs << star.GetSubClass();
    outs << star.GetLuminosityClass();
}
