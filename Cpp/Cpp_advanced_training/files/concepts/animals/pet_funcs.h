#pragma once
#include "animals.h"
#include "tools.h"

void pet(animal_like auto a){
    std::cout << "careful!\n";
}

void pet(cat_like auto a){
    std::cout << "stroke gently\n";
}

void pet(dog_like auto a){
    std::cout << "ruffle fur\n";
}

void pet(bird_like auto a){
    std::cout << "don't ruffle the feathers\n";
}

void pet(strange_thing_like auto a){
    std::cout << "have no idea what this is!!!!!\n";
}

void pet(auto a){
    WHAT<decltype(a)>("template version of pet()");
    //std::basic_ofstream<char8_t> stream("/dev/tty");
    // slightly violent:
    std::cout << reinterpret_cast<const char *>(u8"\U0001f600\n");
}
