# GenStar

This is a C++ console application which creates a volume of randomly-generated star systems.  The program takes in a seed volume and the dimensions of a volume of space, and then randomly places star systems throughout that volume.  The output of the program is then exported to a CSV file, which can be processed in any spreadsheet software suite.

The spectral classes and types of star systems are based on the distribution of real stars.  The program determines the number of systems to place in the given volume by assuming a density of 375 cubic light-years per system, i.e. by calculating `NUMBER OF SYSTEMS = VOLUME SPECIFIED / 375`.

Presently, only the spectral types of each system are recorded; the relationship of the stars to each other are not.  So if, for instance, a system is returned that says it has a G2V and a K9V star, the program does not tell you if they orbit close together or far apart.

Also, O-type stars, B-type stars, bright giants, supergiants, and black holes are not generated by the program.  They are rare enough that I decided that the end user can place them by hand if using the output for, e.g., a space-based role-playing game.

## Installation

The program can be compiled by running the `make` command.  An executable called `GenStar2` will be created.

## Usage

```
user@machine: $ ./GenStar2
Hello!
Welcome to GenStar Version 1.2!
(c) 2020 Giancarlo Whitaker

Please specify the name of a file for the output:
// user input
Please specify the seed:
// user input

Select A for cubic space, B for spherical:
// user input
Please specify the radius of the sphere:
// user input
Goodbye, and good luck!
user@machine: $
```

The following is sample output:

```
SEED: 1
0,-7.8586,-16.5105,-4.38099,M5V
1,-3.18013,-7.57936,13.9066,M1V
2,-3.15925,3.56813,17.5632,M9V,M3V
3,1.25239,-12.0407,-7.45658,T3
4,-0.715673,7.031,14.2223,T1,M5V
5,1.48075,-11.6014,-13.232,M5V
6,8.32206,-12.8424,-2.62733,M9V,M5V
7,16.332,-4.70477,1.86659,M8V
8,-9.68377,5.78516,5.21502,M2V
9,-16.5184,0.0268775,2.92519,M2V
10,6.5798,6.66559,-3.63144,D4,M3V
...
```

The output fields are an ID number, the X, Y, and Z coordinates, and the spectral classes of the star(s) in the system.

Note that there is nothing special about the origin of the coordinate system; no star is placed at (0, 0, 0).

**BE WARNED:** There is nothing stopping you from inputting a *very* large volume and the program from attempting to generate a *very* large number of stars.  For instance, a run of a 300 x 300 x 300 light-year cube produced a 10 megabyte CSV file containing 69,550 star systems.  I could easily have specified a cube *30,000* light years a side, and the program would attempt to generate ~72 billion systems!

## Future Development

**THIS PROJECT IS CURRENTLY ON HOLD!**  I am not actively developing it.  However, I have always hoped to:

* Randomly generate orbital configurations between the stars in each system.
* Randomly generate planets and moons.
* Export to Celestia-compatible files.

If anyone wants to develop this project further, **please** fork the project and let me know!  However, I may do it myself in the future.

## License

This project is licensed under the MIT License.

---

(c) 2016-2023 Giancarlo Whitaker
