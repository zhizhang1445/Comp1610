#include <string>
#include <rarray>
#include <random>
#include <iostream>
#include <fstream>
#include "json.hpp"
using json = nlohmann::json;

void initializer(rvector<double> &init_T, rvector<double> &density, rvector<int> &randseed){

    std::ifstream myfile;
    myfile.open("randseed.txt");

    for(int i = 0; i<randseed.size(); i++){
        myfile >> randseed[i];
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
    double runtime = 2000;
    double timestep = 0.025;
    rvector<int> randseed(9);
    double equiltime = 1000;
    std::string traj = "F";

    initializer(init_T, density, randseed);

    std::ofstream resfile;
    resfile.open("results.txt");
    resfile << "Density: " << "Initial Temperature: " << "Average Pressure: " << "\n";

    for(int i = 0; i < init_T.size(); i++){
        for(int j = 0; j < density.size(); j++){
            double avg_pressure = 0;

            for(int k = 0; k < randseed.size(); k++){
                std::string str_temp = std::to_string((int) init_T[i]);
                std::string str_density = std::to_string((int) density[j]);
                std::string str_seed = std::to_string(k);

                foldername = substance + "_T=" + str_temp + "_density=" + str_density + 
                    "_seed#=" + str_seed;
                
                std::string fullname = foldername + "/report.json";

                json data;
                std::ifstream fin;
                fin.open(fullname);
                fin >> data;
                fin.close();

                double pressure = data["measurements"]["pressure"]["value"];
                avg_pressure += pressure;
            }
            avg_pressure = avg_pressure/randseed.size();
            std::cout << avg_pressure << std::endl;
            resfile << density[j] << " " << init_T[i] << " " << avg_pressure << "\n";
        }
    }
    resfile.close();
    // std::cout << std::endl;

}