#include <string>
#include <rarray>
#include <random>
#include <iostream>
#include <fstream>

void initializer(rvector<double> &init_T, rvector<double> &density, rvector<int> &randseed){
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,9);

    std::ofstream myfile;
    myfile.open("randseed.txt");

    for(int i = 0; i<randseed.size(); i++){
        randseed[i] = distribution(generator);
        myfile << randseed[i] << "\n";
    }
    myfile.close();

    for(int i = 0; i<init_T.size(); i++){
        init_T[i] = 80 + 30*i;
    }

    for(int i = 0; i<density.size(); i++){
        density[i] = 1.0 + 1.0*i;
    }
}

int main(void) {
    std::string foldername;
    std::string substance = "Ar";
    rvector<double> init_T(10);
    rvector<double> density(10);
    int n_atoms = 500;
    double runtime = 2000;
    double timestep = 0.025;
    rvector<int> randseed(9);
    double equiltime = 1000;
    std::string traj = "F";

    initializer(init_T, density, randseed);

    std::ofstream myfile;
    myfile.open("subjob");

    for(int i = 0; i < init_T.size(); i++){
        for(int j = 0; j < density.size(); j++){
            for(int k = 0; k < randseed.size(); k++){

                std::string str_temp = std::to_string((int) init_T[i]);
                std::string str_density = std::to_string((int) density[j]);
                std::string str_seed = std::to_string(k);

                foldername = substance + "_T=" + str_temp + "_density=" + str_density + 
                    "_seed#=" + str_seed;
                
                myfile << "./lj " << foldername << " " << substance << " " << str_temp 
                    << " " << str_density << " " << n_atoms << " " << runtime << " " << timestep 
                    << " " << str_seed << " " << equiltime << " " << traj << "\n";
            }
        }
    }

    myfile.close();

}