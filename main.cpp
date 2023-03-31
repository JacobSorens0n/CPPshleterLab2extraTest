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
    char addPetCheck = 1;
    std::string name;
    int id;
    int days_in_shelter;
    std::string color;
    int age;
    std::string sound;
    int num_of_legs;
    std::string activity;
    int weight;
    int phone_num;
    int num_pets = 0;
    int type;
    std::string typeCheck;

    char previousInventory = 'n';
    std::string fileName;
    std::ofstream outputFile;
    std::ifstream inputFile;

    Shelter shelter("shelter", max_pets);

    std::cout
            << "Tracker for animals in a pet shelter.\nCan add or delete pets from the list and keeps track of interested buyers\n";
    std::cout << "Do you have previous inventory? y/n \n";
    std::cin >> previousInventory;
    std::cout << "Enter the name of the data file to analyze:\n";
    std::cin >> fileName;

    if (previousInventory == 'y' || previousInventory == 'Y')
    {
        inputFile.open(fileName);
        if (inputFile)
        {
            std::cout << "The file " << fileName << " has been successfully opened." << std::endl;

            while (inputFile >> type) //reads values from file to store into array of Pet[]
            {
                if (type == 1)//cat
                {
                    inputFile >> name >> id >> days_in_shelter >> color >> age >> sound >> num_of_legs;
                    shelter.add_pet(new Cat(name, id, days_in_shelter, color, age, sound, num_of_legs));
                    num_pets++;
                }
                if (type == 2)//dog
                {
                    inputFile >> name >> id >> days_in_shelter >> color >> age >> activity >> weight;
                    shelter.add_pet(new Dog(name, id, days_in_shelter, color, age, activity, weight));
                    num_pets++;
                }
                if (type == 3) //adopter
                {
                    //name, phone
                    inputFile >> name >> phone_num;
                    shelter.pet_roster[num_pets]->add_adopter(new Adopter(name, phone_num));
                }


            }
        }
    }

    std::cout << "add pet?\n";
    std::cin >> addPetCheck;
    while (addPetCheck == 'y' || addPetCheck == 'Y')
    {

        std::cout << "type? 1-Cat 2-Dog";
        std::cin >> type;
        if (type == 1)
        {
            std::cout << "name:\n";
            std::cin >> name;
            std::cout << "id: \n";
            std::cin >> id;
            std::cout << "days in shelter: \n";
            std::cin >> days_in_shelter;
            std::cout << "color: \n";
            std::cin >> color;
            std::cout << "age: \n";
            std::cin >> age;
            std::cout << "sound: \n";
            std::cin >> sound;
            std::cout << "# of legs: \n";
            std::cin >> num_of_legs;
            shelter.add_pet(new Cat(name, id, days_in_shelter, color, age, sound, num_of_legs));
            num_pets++;
        }
        if (type == 2)
        {
            std::cout << "name:\n";
            std::cin >> name;
            std::cout << "id: \n";
            std::cin >> id;
            std::cout << "days in shelter: \n";
            std::cin >> days_in_shelter;
            std::cout << "color: \n";
            std::cin >> color;
            std::cout << "age: \n";
            std::cin >> age;
            std::cout << "activity: \n";
            std::cin >> activity;
            std::cout << "weight: \n";
            std::cin >> weight;
            shelter.add_pet(new Dog(name, id, days_in_shelter, color, age, activity, weight));
            num_pets++;
        }
        std::cout << "add pet?\n";
        std::cin >> addPetCheck;
    }


    shelter.remove_pet(456); //works good, veery nice
    num_pets--;

    outputFile.open(fileName);
    for (int i = 0; i < num_pets; ++i)
    {

        shelter.pet_roster[i]->savePetLine(outputFile);

        if (shelter.pet_roster[i]->getType() == 1)
        {
            shelter.pet_roster[i]->saveCatLine(outputFile);
        }
        if (shelter.pet_roster[i]->getType() == 2)
        {
            shelter.pet_roster[i]->saveDogLine(outputFile);
        }

    }
    outputFile.close();


    return 0;
};
//n asgdsg.txt name 1 2 brown 3 loud 4 n