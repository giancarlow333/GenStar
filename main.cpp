#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>          // file output
#include "StarData.h"
#include "StarSystem.h"
using namespace std;

const int SYSTEM_DENSITY = 375;

int main()
{
    cout << "Hello world!" << endl;

    cout << "Please specify the name of a file for the output:\n";
    ofstream outFile;
    string file_out;
    getline(cin, file_out);
    outFile.open(file_out.c_str());

    if (outFile.fail()) {
        cout << "Could not open summary file.\n";
        exit(3);
    }

    cout << "Please specify the seed:\n";
    int seed;
    cin >> seed;
    //construct the random generator
    //int seed = 333;
    cout << "Please specify the width of the cube:\n";
    int width;
    cin>>width;
    default_random_engine engine(seed);

    // array of probabilities
    array<double, 6> arity_weights = { 40, 40, 10, 9, 0.9, 0.1 };
        // [0] = single star, [1] = double, up to sextuple.
        // originally the last three were 5,3,2, too much...
    array<double, 10> sc_weights = { 0.1, 0.9, 2.6, 6, 11.4, 57.8, 8.8, 4.4, 7.9, 0.1 };
        // Classes in order: BAFGKMLTDX
        // O class not presently supported
    array<double, 3> lc_weights = { 0.1, 1.1, 98.8 };
        // Supported classes: III, IV, V
        // Classes I, II not presently supported

    // discrete generators
    discrete_distribution<int> arity_gen (arity_weights.begin(), arity_weights.end());
    discrete_distribution<int> sc_gen (sc_weights.begin(), sc_weights.end());
    discrete_distribution<int> lc_gen (lc_weights.begin(), lc_weights.end());
    uniform_int_distribution<int> subc_gen(1,9);
    // generator for coordinates
    uniform_int_distribution<int> coord_gen((width*-10)/2, (width*10)/2);

    // DO lc generation first
        // If WD or NS, don't do Spectral
    // ELSE do Spectral Class
    // Calculate multiplicity
    // Do again for remaining components


    int n_stars;   // min stars to place

    // Calculate n_stars
    n_stars = (width * width * width) / SYSTEM_DENSITY;

    //vector<System> systems; // All the systems

    for (int i = 0; i<n_stars; i++)
    {
        StarSystem temp;
        temp.SetNumber(i);
        int arity = arity_gen(engine) + 1;

        // Generate stars in the amount in the system...
        for (int j = 0; j<arity; j++)
        {
            StarData star;
            int spectral = sc_gen(engine);
            int subclass = subc_gen(engine);
            int lumos;
            // L, T, D, X have no luminosity class
            if (spectral < 6)
            {
                lumos = lc_gen(engine);
            }
            else {
                lumos = -1;
            }

            star.SetSpectralInt(spectral);
            star.SetSubClass(subclass);
            star.SetLuminosityInt(lumos);

            temp.AddStar(star);
        }
        // sort vector sp_class, lowest to highest
        temp.SortStars();

        // Generate coordinates
        float temp_x = static_cast<float>(coord_gen(engine)) / 10;
        float temp_y = static_cast<float>(coord_gen(engine)) / 10;
        float temp_z = static_cast<float>(coord_gen(engine)) / 10;

        // assign coordinates
        temp.SetX(temp_x);
        temp.SetY(temp_y);
        temp.SetZ(temp_z);

        //temp.PrintSystemCout(arity);

        /*// print coordinates
        cout << "Coordinates: (" << temp.x << ", " << temp.y << ", " << temp.z << ")" << endl;

        // print system
        for (int k = 0; k<temp.stars.size(); k++)
        {
            cout << "\t[" << k << "] class: " << GetSpectralClass((temp.stars[k]).spectral);
            cout << (temp.stars[k]).sub;
            cout << GetLuminosityClass((temp.stars[k]).luminos) << endl;
            //cout << (temp.stars[k]).luminos << endl;
        }

        cout << endl;*/
        // put system in the outfile
        outFile << temp << endl;
    }



    outFile.close();
























    return 0;
}
