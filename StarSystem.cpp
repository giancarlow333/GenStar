#include <iostream>
#include <algorithm>    // for sort
#include "StarSystem.h"
using namespace std;

StarSystem::StarSystem()
{
    number = x = y = z = 0;
}

/*StarSystem::~StarSystem()
{
    //dtor
}

StarSystem::StarSystem(const StarSystem& other)
{
    //copy ctor
}

StarSystem& StarSystem::operator=(const StarSystem& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}
*/

///////////////////////////////////////
// MUTATORS
///////////////////////////////////////

void StarSystem::SetNumber (int n)
{
    number = n;
}

void StarSystem::SetX (float n)
{
    x = n;
}

void StarSystem::SetY (float n)
{
    y = n;
}

void StarSystem::SetZ (float n)
{
    z = n;
}

void StarSystem::AddStar (StarData s)
{
    stars.push_back(s);
}

///////////////////////////////////////
// USEFUL
///////////////////////////////////////
void StarSystem::PrintSystemCout(int arity)
{
    cout << "SYSTEM " << number+1 << endl;
    cout << "Arity: " << arity << endl;
    cout << "Coordinates: (" << x << ", " << y << ", " << z << ")" << endl;

    // print system
    for (int k = 0; k < stars.size(); k++)
    {
        cout << "\t[" << k << "] class: " << stars[k].GetSpectralClass();
        cout << stars[k].GetSubClass();
        cout << stars[k].GetLuminosityClass() << endl;
    //cout << (temp.stars[k]).luminos << endl;
    }

    cout << endl;

}

void StarSystem::SortStars()
{
    sort(stars.begin(), stars.end());
    //cout << "Stars sorted\n";
}


// OUTPUT DATA IN CSV FORM
ostream& operator<<(ostream & outs, const StarSystem & sys)
{
    outs << sys.number << "," << sys.x << "," << sys.y << "," << sys.z;
    for (int i = 0; i < (sys.stars).size(); i++)
    {
        outs << ",";
        outs << sys.stars[i];
        /*outs << (sys.stars[i]).GetSpectralClass();
        outs << (sys.stars[i]).GetSubClass();
        outs << (sys.stars[i]).GetLuminosityClass();*/
    }

    return outs;
}
