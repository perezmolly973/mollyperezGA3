#ifndef GENOME_H
#define GENOME_H

struct Pixel {
   int red;
   int blue;
   int green;
};

class genome {
public:
    genome(); // constructor
    ~genome(); // destructor
    void allocate( int nGenes );
    void deallocate();
    void randomize();
    void set_red( int index, int value);  // you can add the other two
    void set_green( int index, int value); //adding  set_gren
    void set_blue (int index, int value); // adding set_blue
    int get_red( int index);  // you can add the other two
    int get_green( int index); // adding get_green
    int get_blue ( int index); // adding get_blue
    void print();

// GA program
    void set_mRate(double val); // set mRate = val
    double get_mRate(); // return the current mRat value
    void mutate_gene(int index); // randomly generate a number between 0 and 1
                     // assign the random value if condition met
    void mutate(); // call mutate_gene() function
    double calculate_gene_fitness(int index, Pixel targetPixel);
    double calculate_overall_fitness(Pixel*target, int nPixels);
    void set_pixel(int index, Pixel newPixel); // set the Pixel = [index]
    Pixel get_pixel(int index); // return the pixel value from genes at [index]

private:
    Pixel* genes;
    int nGenes;
    double mRate;
};
#endif
