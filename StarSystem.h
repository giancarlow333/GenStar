#ifndef STARSYSTEM_H
#define STARSYSTEM_H

#include <vector>
#include "StarData.h"
using namespace std;

class StarSystem
{
    public:
        StarSystem();
        //virtual ~StarSystem();
        //StarSystem(const StarSystem& other);
        //StarSystem& operator=(const StarSystem& other);
        // Mutators
        void SetNumber (int n);
        void SetX (float n);
        void SetY (float n);
        void SetZ (float n);
        void AddStar (StarData s);
        // Useful function
        void PrintSystemCout(int arity);
        void SortStars();
        // Operators
        friend ostream& operator<<(ostream & outs, const StarSystem & sys);
    protected:
    private:
        int number;
        vector<StarData> stars;
        float x;
        float y;
        float z;
};

#endif // STARSYSTEM_H
