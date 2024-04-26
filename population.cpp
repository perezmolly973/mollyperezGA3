#include "population.h"
#include <iostream>
#include <cstdlib>
using namespace std; //including std to ouput string

//creating constructor
Population::Population() {
    individuals = nullptr;  //Initialize individuals to null
    nIndividuals = 0;       // Initialize nindividuals to 0
    nCrossover = 1;         //set crossover to 1
    mutationRate = 0.0;     // set mutationrate to 0
}

//Destructor which deletes individuals if not null and sets to Null.
Population::~Population() {
    if (individuals != nullptr) {
        delete[] individuals;
        individuals = nullptr;
    }
    //set nIndividuals to 0
    nIndividuals = 0;
}

// creating void function generate_population which takes two arguments popsize and nGenes
void Population::generate_population(int popSize, int nGenes) {
    // Allocate memory for individuals array
    individuals = new genome[popSize];
    nIndividuals = popSize;

    // Initialize each genome in the population
    for (int i = 0; i < popSize; ++i) {
        individuals[i].allocate(nGenes);
        individuals[i].randomize();
    }
}

//creating void function set_target takes two arguments pixel* target and imagesize
void Population::set_target(Pixel* target, int imageSize) {
    //saving arrray in private array called target genome
    targetGenome = target;
    //sets imagesize to imageSize be used to calculate relative fitness
    this->imageSize = imageSize;
}

//creating void function select_parents
void Population::select_parents() {
    // determains the two best overall individuals in the population
    //sets into p1 and p2, two array pointers
    p1 = &individuals[0];
    p2 = &individuals[1];

    // Iterate through the rest of the individuals to find the two best overall individuals
    for (int i = 2; i < nIndividuals; ++i) {
        // using genome calculate overall fitness to find p1 and p2, taking 2 parameters targetGenome, and imageSize
        if (individuals[i].calculate_overall_fitness(targetGenome, imageSize) > p1->calculate_overall_fitness(targetGenome, imageSize)) {
            p2 = p1; // Move the current p1 to p2
            p1 = &individuals[i]; // Set the new p1
        } else if (individuals[i].calculate_overall_fitness(targetGenome, imageSize) > p2->calculate_overall_fitness(targetGenome, imageSize)) {
            p2 = &individuals[i]; // Set the new p2
        }
    }
}

//creating void function set_nCrossover
void Population::set_nCrossover(int n) {
    // Set the number of crossover points to a positive integer making sure it's positive
    if (n > 0) {
        //if a positive integer continue
        nCrossover = n;
    } else {
        // Set to 1 if n is not positive
        nCrossover = 1;
    }
}

//creating int function get_nCrossover
int Population::get_nCrossover() {
//returns nCrossover points
    return nCrossover;
}

//Creating a void function set_mutation sets mution to individual genome mRate
void Population::set_mutation(double mRate) {
    // Set the mutation rate
    if (mRate >= 0 && mRate <= 1) {
        mutationRate = mRate;
    } else {
        //if the rate is not in range set to 0
        mutationRate = 0.0;
    }
}

// Creating void generate_new_population function
void Population::generate_new_population(int useRoulette) {
    // Create a temporary array to hold the new population
    genome* newIndividuals = new genome[nIndividuals];

    // Roulette wheel selection
    //if useRoulette is 1 we take the simple top two
    if (useRoulette == 1) {
        roulette_wheel_selection(newIndividuals);
    } else {
        // else if useRoulette is not 1
        select_parents();

        // Perform crossover and mutation on the selected parents
        for (int i = 0; i < nIndividuals; ++i) {
            // Select parents for crossover
            genome child = crossover(p1,p2);
            newIndividuals[i] = child;
        }
    }

    // Replace the old population with the new one by deleting and setting individuals to newindividuals
    delete[] individuals;
    individuals = newIndividuals;
}

//Create double function calculate_overall_fitness
double Population::calculate_overall_fitness() {
    double totalFitness = 0.0;

    // Calculate the fitness of each individual and sum them up
    for (int i = 0; i < nIndividuals; ++i) {
        //finding totalfitness for return average val
        totalFitness += individuals[i].calculate_overall_fitness(targetGenome, imageSize);
    }

    // Return the average fitness by totalfitness/ how many nindividuals there are
    return totalFitness / nIndividuals;
}

//Create void function print_parents
void Population::print_parents() {
    //if select_parents is not call and p1 and p2 are null print message
    if (p1 == nullptr || p2 == nullptr) {
        //print No parents yet set
        cout << "No parents yet set." << endl;
    } else {
        //print p1
        cout << "Parent 1:" << endl;
        p1->print();
        //print p2
        cout << "Parent 2:" << endl;
        p2->print();
    }
}

//create void function print_population
void Population::print_population() {
    //print n crossover points
    cout << "Number of crossover points: " << nCrossover << endl;
    //print mutation rate
    cout << "Mutation rate: " << mutationRate << endl;
    //print population 
    cout << "Population:" << endl;
    //also prints out nIndividuals by itterating by nIndividuals 
    for (int i = 0; i < nIndividuals; ++i) {
        cout << "Individual " << i+1 << ":" << endl;
        individuals[i].print();
        cout << endl;
    }
}
