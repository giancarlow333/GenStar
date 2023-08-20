#ifndef STARDATA_H
#define STARDATA_H

#include <string>
#include <iostream>
using namespace std;

class StarData
{
    public:
        // Constructors
        StarData();
        StarData(int sp, int sb, int l);
        StarData(const StarData& other);
        // Accessors
        int GetSpectralInt ();
        int GetLuminosityInt ();
        char GetSpectralClass () const;
        int GetSubClass () const;
        string GetLuminosityClass () const;
        //string GetStarData ();
        // Mutators
        void SetSpectralInt (int n);
        void SetSubClass (int n);
        void SetLuminosityInt (int n);
        //void ;
        // Operators
        StarData& operator=(const StarData& other);
        friend bool operator==(StarData a, StarData b);
        friend bool operator<(StarData a, StarData b);
        friend ostream& operator<<(ostream & outs, const StarData & star);
    protected:
    private:
        int spectral;
        int sub;
        int luminos;
};

#endif // STARDATA_H
