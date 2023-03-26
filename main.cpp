#include <iostream>
#include <fstream>

#include "main.h"
/**
 * Author: Jacob Sorenson
 * Date: March 26, 2023
 * Project: CS-116 Lab 2, pet shelter cont.
 */



int main()
{
    std::string trait1;
    int trait2;
    int trait3;
    std::string trait4;
    int trait5;
    std::string trait6;
    int trait7;
    int num_pets;
    int type;
    char previousInventory = 'n';
    std::string fileName;
    std::ifstream inputFile;

    Shelter shelter("shelter", max_pets);

    std::cout << "Tracker for animals in a pet shelter.\nCan add or delete pets from the list and keeps track of interested buyers\n";
    std::cout << "Do you have previous inventory? y/n \n";
    std::cin >> previousInventory;
    std::cout << "Enter the name of the data file to analyze:\n";
    std::cin >> fileName;

    inputFile.open(fileName);

    if (inputFile) {
        std::cout << "The file " << fileName << " has been successfully opened." << std::endl;

        while (inputFile >> type >> trait1 >> trait2 >> trait3 >> trait4 >> trait5 >> trait6 >> trait7) //reads values from file to store into array of pets[]
        {
            if (type == 1) //cat
            {
                //name, id, days_in_shelter, color, age, sound, num_of_legs
                shelter.Pet[num_pets] = new Pet(trait1, trait2, trait4, trait4, trait5, trait6, trait7);
                num_pets++;
            }
            if (type == 2) //dog
            {
                //name, id, days_in_shelter, color, age, activity, weight
                Pet[num_pets] = new Pet(trait1, trait2, trait4, trait4, trait5, trait6, trait7);
                num_pets++;
            }
            if (type == 3) //adopter
            {
                //name, phone
                Pet[num_pets] = new Pet(trait1, trait2);
                num_pets++;
            }
        }
    }
};