#include "animals.h"
#include "pet_concepts.h"
#include "pet_funcs.h"

int main(){
    elephant dombo;
    cat felix;
    dog tarzan;
    robin tweet;
    Aethalops nr412;
    door_knob front_door;

    std::cout << "============================\n\n\n\n";
    pet(dombo);
    pet(felix);
    pet(tarzan);
    pet(tweet);
    pet(nr412);
    pet(front_door);
}
