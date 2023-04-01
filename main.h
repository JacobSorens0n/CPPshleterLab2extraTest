//
// Created by jacob on 3/26/2023.
//

#ifndef CPPSHLETERLAB2EXTRATEST_MAIN_H
#define CPPSHLETERLAB2EXTRATEST_MAIN_H

#include <string>
#include <iostream>

const int max_pets = 10;
const int max_adopters = 3;


class Adopter
{
public:
    Adopter(std::string name, int phone_num)
            : name_(name), phone_num_(phone_num)
    {}

    std::string get_adopt_name()
    { return this->name_; }

    int get_phone_num()
    { return this->phone_num_; }


private:
    std::string name_;
    int phone_num_;
};

class Pet
{
public:
    Pet(int type, std::string name, int id, int days_in_shelter, std::string color, int age)
            : type_(type), name_(name), id_(id), days_in_shelter_(days_in_shelter), color_(color), age_(age)
    {
        this->adopters = new Adopter *[max_adopters];
        for (int i = 0; i < max_adopters; i++)      //initializes all positions of adopters[] with null pointers cause there was some weird stuff happening without it
        {
            this->adopters[i] = nullptr;
        }
        this->num_of_adopters = 0;
    }


    ~Pet()
    {
        for (int i = 0; i < get_num_of_adopters(); ++i)     //should delete the adopters when the object is deleted
        {
            delete adopters[i];
        }
    };


    void add_adopter(Adopter *adopter) //adds a new adopter with inputted info in array of adopters and increases # of adopters
    {
        adopters[num_of_adopters] = adopter;
        num_of_adopters++;
    };


    void saveAdopterLine(std::ofstream &outputFile, int index)    //outputs data of adopter at index of array along with type for indentification when reading
    {
        outputFile << 3 << " " << adopters[index]->get_adopt_name() << " " << adopters[index]->get_phone_num()
                   << std::endl;
    };

    void savePetLine(std::ofstream &outputFile)                 //outputs all info for Cat/Dog that belongs to the base class
    {
        outputFile << getType() << " " << getName() << " " << getId() << " " << getDaysInShelter() << " " << getColor()
                   << " " << getAge() << " ";
    };

    void saveCatLine(std::ofstream &outputFile)                 // outputs Cat specific info to file after Pet info
    {
        outputFile << getSound() << " " << getLegs() << std::endl;
    };

    void saveDogLine(std::ofstream &outputFile)                 // outputs Dog specific info to file after Pet info
    {
        outputFile << getActivity() << " " << getWeight() << std::endl;
    };


    virtual std::string getSound()             //calls this function from main and is overwritten by info from Cat class
    {
        return "generic pet sound placeholder";
    }

    virtual int getLegs() = 0;                 //calls this function from main and is overwritten by info from Cat class

    virtual std::string getActivity()          //calls this function from main and is overwritten by info from Dog class
    {
        return "activity placeholder";
    }

    virtual int getWeight() = 0;               //calls this function from main and is overwritten by info from Dog class


    int getType() const
    {
        return type_;
    }

    std::string getName() const
    { return name_; }

    int getId() const
    { return id_; }

    void increaseDays()
    {
        days_in_shelter_++;
    }

    int getDaysInShelter() const
    { return days_in_shelter_; }

    std::string getColor() const
    { return color_; }

    int getAge() const
    { return age_; }


    int get_num_of_adopters() const
    {
        return num_of_adopters;
    }


    Adopter **adopters;//dynamic array of pointers

private:
    int type_;
    int num_of_adopters;
    std::string name_;
    int id_;
    int days_in_shelter_;
    std::string color_;
    int age_;
};


class Dog : public Pet
{
public:
    Dog(std::string name, int id, int days_in_shelter, std::string color, int age, std::string activity, double weight)
            : Pet(2, name, id, days_in_shelter, color, age)
    {
        this->activity = activity;
        this->weight = weight;
    }

    std::string getActivity() override //included the virtual functions from Dog as well because it complained otherwise, overwrites info from functions in Pet
    { return activity; }

    int getWeight() override
    { return weight; }

    std::string getSound() override
    { return activity; }

    int getLegs() override
    { return weight; }

private:
    std::string activity;
    double weight;
};


class Cat : public Pet
{
public:
    Cat(std::string name, int id, int days_in_shelter, std::string color, int age, std::string sound, int num_of_legs)
            : Pet(1, name, id, days_in_shelter, color, age)
    {
        this->sound = sound;
        this->num_of_legs = num_of_legs;

    }

    std::string getActivity() override //included the virtual functions from Cat as well because it complained otherwise, overwrites info from functions in Pet
    { return sound; }

    int getWeight() override
    { return num_of_legs; }

    std::string getSound() override
    { return sound; }

    int getLegs() override
    { return num_of_legs; }

private:
    std::string sound;
    int num_of_legs;
};


class Shelter
{
public:
    Shelter(std::string name, int capacity)
    {
        this->pet_roster = new Pet *[capacity];
        this->num_of_pets = 0;
        this->capacity = capacity;
    }


    int add_pet(Pet *pet)       //checks if pet_roster still has room, if yes adds Pet object to roster; if no, does nothing
    {
        if (num_of_pets >= capacity)
        {
            return 0;
        }
        pet_roster[num_of_pets] = pet;
        num_of_pets++;
        return 1;
    };

    void remove_pet(int id)   //goes through all pets to match id, once id is found deltes that obect and shifts all other pets 1 space to make a continuous list
    {
        for (int i = 0; i < num_of_pets; ++i)
        {
            if (pet_roster[i]->getId() == id)
            {
                std::cout << "adopting:" << pet_roster[i]->getName();
                delete pet_roster[i];
                for (int j = i + 1; j < num_of_pets; ++j)
                {
                    pet_roster[j - 1] = pet_roster[j];
                }
                num_of_pets--;
            }
        }
    };


    Pet **pet_roster;//dynamic array of pointers

private:
    int num_of_pets;
    int capacity;

};


#endif //CPPSHLETERLAB2EXTRATEST_MAIN_H
