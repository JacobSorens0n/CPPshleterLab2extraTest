//
// Created by jacob on 3/26/2023.
//

#ifndef CPPSHLETERLAB2EXTRATEST_MAIN_H
#define CPPSHLETERLAB2EXTRATEST_MAIN_H

#include <string>

const int max_pets = 10;
const int max_adopters = 3;


class Adopter
{
public:
    Adopter(std::string name, int phone_num);

    std::string get_name()
    {
        return this->name;
    }

    int get_phone_num()
    {
        return this->phone_num;
    }

private:
    std::string name;
    int phone_num;
};

class Pet
{
public:
    Pet(int type, std::string name, int id, int days_in_shelter, std::string color, int age)
            : type_(type), name_(name), id_(id), days_in_shelter_(days_in_shelter), color_(color), age_(age)
    {
        this->adopters = new Adopter *[max_adopters];
        num_of_adopters = 0;
    }

    ~Pet()
    {
        for (int i = 0; i < num_of_adopters; ++i)
        {
            delete adopters[i];
        }
        delete adopters;
    };

    // Getters
    int getType() const
    {
        return type_;
    }

    std::string getName() const
    { return name_; }

    int getId() const
    { return id_; }

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

    int add_adopter(Adopter *adopter)
    {
        if (num_of_adopters >= max_adopters)
        {
            return 0;
        }
        adopters[num_of_adopters] = adopter;
        num_of_adopters++;
        return 1;
    };

private:
    int type_;
    Adopter** adopters;
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
            : Pet(name, id, days_in_shelter, color, age)
    {
        this->activity = activity;
        this->weight = weight;
    }

private:
    std::string activity;
    double weight;
};


class Cat : public Pet
{
public:
    Cat(std::string name, int id, int days_in_shelter, std::string color, int age, std::string sound, int num_of_legs)
            : Pet(name, id, days_in_shelter, color, age)
    {
        this->sound = sound;
        this->num_of_legs = num_of_legs;
    }

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


    int get_num_of_pets() const
    {
        return num_of_pets;
    }

    int add_pet(Pet *pet)
    {
        if (num_of_pets >= capacity)
        {
            return 0;
        }
        pet_roster[num_of_pets] = pet;
        num_of_pets++;
        return 1;
    };

    void remove_pet(int id)
    {
        for (int i = 0; i < num_of_pets; ++i)
        {
            if (pet_roster[i]->getId() == id)
            {
                std::cout << "deleting:" << pet_roster[i]->getName();
                delete pet_roster[i];
                for (int j = i + 1; j < num_of_pets; ++j)
                {
                    pet_roster[j - 1] = pet_roster[j];
                }
                num_of_pets--;
            }
        }
    };

    void print_roster() const
    {
//        std::cout << "Course Name: " << this->course_name << endl;
//        std::cout << "Instructor: " << this->instructor->get_name() << endl;
        for (int i = 0; i < this->num_of_pets; i++)
        {
//            this->pet_roster[i]->print();
        }
    }

private:
    Pet **pet_roster; //dynamic array of pointers
    int num_of_pets;
    int capacity;

};

#endif //CPPSHLETERLAB2EXTRATEST_MAIN_H
