/* GenStar Program
 * Version 1.2
 * Author: Giancarlo Whitaker
 * Date: January 4, 2020
 *
 * Main modifications:
 * 1) Remove B class stars
 * 2) Make quinary, sexary systems less likely
 * 3) Make coordinates real numbers
 * 4) Print the seed to the outfile
 * 5) Cubical and spherical modes
 */

#include <iostream>
#include <random>
#include <array>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>          // file output
#include <cctype>			// for TOLOWER function
#include <cmath>			// for trig functions and pow
#include "StarData.h"
#include "StarSystem.h"
using namespace std;

const int SYSTEM_DENSITY = 375;
const float PI = 3.14159265359;

void CubicalVolume(int s, ofstream & outs);
void SphericalVolume(int s, ofstream & outs);

int main()
{
    cout << "Hello!" << endl;
	cout << "Welcome to GenStar Version 1.2!" << endl;
	cout << "(c) 2020 Giancarlo Whitaker" << endl << endl;

    cout << "Please specify the name of a file for the output:\n";
    ofstream outFile;
    string file_out;
    getline(cin, file_out);
    outFile.open(file_out.c_str());

    if (outFile.fail()) {
        cout << "Could not open output file.\n";
        exit(1);
    }

    cout << "Please specify the seed:\n";
    int seed;
    cin >> seed;
	// Print the seed to the output file
	outFile << "SEED: " << seed << endl;

	// Case-switch structure
	cout << endl << "Select A for cubic space, B for spherical:" << endl;
	char voltype;
	cin >> voltype;
	voltype = tolower(voltype);

	if (voltype == 'a') {
		CubicalVolume(seed, outFile);
	}
	else if (voltype == 'b') {
		SphericalVolume(seed, outFile);
		//cout << "Not supported!" << endl;
		//exit(3);
	}
	else {
		cout << "Invalid selection!" << endl;
		exit(2);
	}


    outFile.close();
	cout << "Goodbye, and good luck!" << endl;

    
    return 0;
}

void CubicalVolume(int s, ofstream & outs) {
	//construct the random generator
    //int seed = 333;
    default_random_engine engine(s);

    // array of probabilities
    array<double, 6> arity_weights = { 40, 40, 10, 9.45, 0.5, 0.05 };
        // [0] = single star, [1] = double, up to sextuple.
        // originally the last three were 5,3,2, too much...
    array<double, 10> sc_weights = { 0.0, 0.9, 2.6, 6, 11.4, 57.8, 8.8, 4.4, 7.9, 0.1 };
        // Classes in order: BAFGKMLTDX
        // O class not presently supported
    array<double, 3> lc_weights = { 0.1, 1.1, 98.8 };
        // Supported classes: III, IV, V
        // Classes I, II not presently supported

	cout << "Please specify the width of the cube:\n";
    int width;
    cin>>width;

    // discrete generators
    discrete_distribution<int> arity_gen (arity_weights.begin(), arity_weights.end());
    discrete_distribution<int> sc_gen (sc_weights.begin(), sc_weights.end());
    discrete_distribution<int> lc_gen (lc_weights.begin(), lc_weights.end());
    uniform_int_distribution<int> subc_gen(1,9);
    // generator for coordinates
    uniform_real_distribution<> coord_gen(-width/2, width/2);
	//cout << -width/2 << endl; cout << width/2 << endl;

    // DO lc generation first
        // If WD or NS, don't do Spectral
    // ELSE do Spectral Class
    // Calculate multiplicity
    // Do again for remaining components

    int n_stars;   // min stars to place

    // Calculate n_stars
    n_stars = (width * width * width) / SYSTEM_DENSITY;
	//n_stars = 3;

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
        float temp_x = coord_gen(engine);
        float temp_y = coord_gen(engine);
        float temp_z = coord_gen(engine);

        // assign coordinates
        temp.SetX(temp_x);
        temp.SetY(temp_y);
        temp.SetZ(temp_z);

        //temp.PrintSystemCout(arity);

        outs << temp << endl;
    }
}

void SphericalVolume(int s, ofstream & outs) {
	//construct the random generator
    //int seed = 333;
    default_random_engine engine(s);

    // array of probabilities
    array<double, 6> arity_weights = { 40, 40, 10, 9.45, 0.5, 0.05 };
        // [0] = single star, [1] = double, up to sextuple.
        // originally the last three were 5,3,2, too much...
    array<double, 10> sc_weights = { 0.0, 0.9, 2.6, 6, 11.4, 57.8, 8.8, 4.4, 7.9, 0.1 };
        // Classes in order: BAFGKMLTDX
        // O class not presently supported
    array<double, 3> lc_weights = { 0.1, 1.1, 98.8 };
        // Supported classes: III, IV, V
        // Classes I, II not presently supported

	cout << "Please specify the radius of the sphere:\n";
    int radius;
    cin>>radius;

    // discrete generators
    discrete_distribution<int> arity_gen (arity_weights.begin(), arity_weights.end());
    discrete_distribution<int> sc_gen (sc_weights.begin(), sc_weights.end());
    discrete_distribution<int> lc_gen (lc_weights.begin(), lc_weights.end());
    uniform_int_distribution<int> subc_gen(1,9);
    // generators for coordinates
    uniform_real_distribution<> phi_gen(0.0, 2 * PI);
	uniform_real_distribution<> costheta_gen(-1.0, 1.0);
	uniform_real_distribution<> u_gen(0.0, 1.0);

    // DO lc generation first
        // If WD or NS, don't do Spectral
    // ELSE do Spectral Class
    // Calculate multiplicity
    // Do again for remaining components

    int n_stars;   // min stars to place
	float volume;	// volume of the sphere

    // Calculate n_stars
	volume = (4.0/3.0) * PI * pow(radius, 3.0);
	//cout << "Volume: " << volume << endl;
    n_stars = volume / SYSTEM_DENSITY;
	//n_stars = 3;

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
		// https://stackoverflow.com/questions/5408276/sampling-uniformly-distributed-random-points-inside-a-spherical-volume

		float phi = phi_gen(engine);
		float costheta = costheta_gen(engine);
		float u = u_gen(engine);
		float theta = acos(costheta);
		float r = radius * cbrt(u);

        float temp_x = r * sin(theta) * cos(phi);
        float temp_y = r * sin (theta) * sin(phi);
        float temp_z = r * cos(theta);

        // assign coordinates
        temp.SetX(temp_x);
        temp.SetY(temp_y);
        temp.SetZ(temp_z);

        //temp.PrintSystemCout(arity);

        outs << temp << endl;
    }
}
