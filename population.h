//calling POPULATION_H
#ifndef POPULATION_H
#define POPULATION_H

//inclusing genome class
#include "genome.h"

//starting population class
class Population {

//setting up private clas
private:
    genome* individuals;    //array holing individuals in the population
    int nIndividuals;       // number of individuals
    Pixel* targetGenome;    // Target genome pixel
    int imageSize;          // size of the image
    genome* p1;             // parent 1
    genome* p2;             // parent 2
    int nCrossover;         // number of crossover
    double mutationRate;    //mutation rate

public:
    Population();   //constructor
    ~Population();  //destructor

// calling all functions newly created from population.cpp

    void generate_population(int popSize, int nGenes);
    void set_target(Pixel* target, int imageSize);
    void select_parents();
    void roulette_wheel_selection(genome* newIndividuals);

    genome crossover(genome* parent1, genome* parent2);
    void set_nCrossover(int nCrossover);
    int get_nCrossover();
    void set_mutation(double mRate);
    void generate_new_population(int useRoulette);
    double calculate_overall_fitness();
    void print_parents();
    void print_population();
};

#endif
