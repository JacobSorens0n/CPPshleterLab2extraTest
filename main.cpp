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
    char runProgram = 'y';
    bool adoptNumCheck;
    char addAdopterCheck = 'h';
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
    int phone_num = 0;
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

    while (runProgram == 'y' || runProgram == 'Y')    // repeats the entire program while the input is 'y' after stuff is outputted to file
    {

        std::cout << "Do you have previous inventory? y/n \n";
        std::cin >> previousInventory;
        std::cout << "Enter the name of the data file to analyze:\n";
        std::cin >> fileName;

        if (previousInventory == 'y' || previousInventory == 'Y') //starts to read file fileName and inputs them into objects in arrays
        {
            inputFile.open(fileName);
            if (inputFile)
            {
                std::cout << "The file " << fileName << " has been successfully opened." << std::endl;

                while (inputFile >> type)   // reads type before the rest of the line
                {
                    if (type == 1)  //cat; reads from file and makes new Cat:Pet object that it passes to add_pet
                    {
                        inputFile >> name >> id >> days_in_shelter >> color >> age >> sound >> num_of_legs;
                        shelter.add_pet(new Cat(name, id, days_in_shelter, color, age, sound, num_of_legs));
                        num_pets++;
                    }
                    if (type == 2)  //dog; reads from file and makes new Dog:Pet object that it passes to add_pet
                    {
                        inputFile >> name >> id >> days_in_shelter >> color >> age >> activity >> weight;
                        shelter.add_pet(new Dog(name, id, days_in_shelter, color, age, activity, weight));
                        num_pets++;
                    }
                    if (type == 3)  //adopter; reads from file and makes new Adopter object that it passes to add_adopter
                    {
                        //name, phone
                        inputFile >> name >> phone_num;
                        shelter.pet_roster[num_pets - 1]->add_adopter(new Adopter(name, phone_num));
                    }
                }
            }
        }

        std::cout << "add pet?\n";
        std::cin >> addPetCheck;
        while (addPetCheck == 'y' || addPetCheck == 'Y') // repeats asking about adding pets while the input is 'y' after a pet is added
        {

            std::cout << "type? 1-Cat 2-Dog";
            std::cin >> type;
            if (type == 1)      //manually make new Cat object that it passes to add_pet
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
            if (type == 2)      //manually make new Dog object that it passes to add_pet
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

            for (int i = 0; i < 3; ++i) //asks 3(max_adopters) times to make new Adopter object that it passes to add_adopter
            {
                std::cout << "add adopter?\n";
                std::cin >> addAdopterCheck;
                if (addAdopterCheck == 'y' || addAdopterCheck == 'Y')
                {
                    std::cout << "name:\n";
                    std::cin >> name;
                    std::cout << "phone number:\n";
                    std::cin >> phone_num;
                    shelter.pet_roster[num_pets - 1]->add_adopter(new Adopter(name, phone_num));
                }
            }
            std::cout << "add pet?\n";
            std::cin >> addPetCheck;
        }

        for (int i = 0; i < num_pets; ++i)  //increases day count for all Pets in the array
        {
            shelter.pet_roster[i]->increaseDays();
        }

        for (int i = 0; i < num_pets; ++i)  //checklist for grooming, weekly checkups, and deleting after 10/15 days
        {
            int days = shelter.pet_roster[i]->getDaysInShelter();
            if (shelter.pet_roster[i]->getType() == 1) // for cats, need to be groomed every 3 days
            {
                if (days % 3 == 0)
                {
                    std::cout << shelter.pet_roster[i]->getName() << " needs grooming\n";
                }
            }
            if (shelter.pet_roster[i]->getType() == 2)// for dogs, need to be groomed every 1 days
            {
                if (days % 1 == 0)
                {
                    std::cout << shelter.pet_roster[i]->getName() << " needs grooming\n";
                }
            }
            if (days % 7 == 0) // both types of animals, need a weekly checkup
            {
                std::cout << shelter.pet_roster[i]->getName() << " needs a weekly checkup\n";
            }
            if (days % 10 == 0) // if the pet has an adopter, the pet will be removed after 10 days and the first adopter in the array will have info displayed
            {
                if (shelter.pet_roster[i]->get_num_of_adopters() > 0)
                {
                    std::cout << "Adopter: \n";
                    std::cout << shelter.pet_roster[i]->adopters[0]->get_adopt_name() << std::endl;
                    std::cout << shelter.pet_roster[i]->adopters[0]->get_phone_num() << std::endl;
                    shelter.remove_pet(shelter.pet_roster[i]->getId());
                    num_pets--;
                }

            }

            if (days >= 15) // both types of pet, will delete Pet including adopter info, after 15 days
            {
                shelter.remove_pet(shelter.pet_roster[i]->getId()); //works good, veery nice
                num_pets--;

            }

        }


        outputFile.open(fileName); //just clears the file before writing to it, don't know if there's a better way
        outputFile.close();
        outputFile.open(fileName);


        for (int i = 0; i < num_pets; ++i) //outputs info to file
        {

            shelter.pet_roster[i]->savePetLine(outputFile);     //outputs all info stored in the base class for that pet

            if (shelter.pet_roster[i]->getType() == 1)   //outputs data from derived Cat class, followed by the list of adopters for that Pet object
            {
                shelter.pet_roster[i]->saveCatLine(outputFile);
                for (int j = 0; j < shelter.pet_roster[i]->get_num_of_adopters(); ++j)
                {
                    shelter.pet_roster[i]->saveAdopterLine(outputFile, j);
                }
            }
            if (shelter.pet_roster[i]->getType() == 2)   //outputs data from derived Dog class, followed by the list of adopters for that Pet object
            {
                shelter.pet_roster[i]->saveDogLine(outputFile);
                for (int j = 0; j < shelter.pet_roster[i]->get_num_of_adopters(); ++j)
                {
                    shelter.pet_roster[i]->saveAdopterLine(outputFile, j);
                }

            }

        }
        outputFile.close();
        std::cout << "\nrun program again?\n";
        std::cin >> runProgram;


    }

    return 0;
};