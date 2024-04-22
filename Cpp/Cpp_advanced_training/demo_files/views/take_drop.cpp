#include <iostream>
#include <ranges>
#include <string_view>

void show(std::string_view sv,
          std::ranges::range auto r){
    std::cout <<  sv << '\n';
    for(const auto& el : r){
        std::cout << el << ' ';
    }
    std::cout << '\n';
}

int main(){
    auto first_4 = std::views::iota(5,100)
        | std::views::take(4);
    show("first 4", first_4);
    auto while_small = std::views::iota(5,100)
        | std::views::take_while(
                [limit=15](const auto& n){ return n < limit;}
            );
    show("while small", while_small);
    auto skip_40= std::views::iota(5,100)
        | std::views::drop(40);
    show("skip 40", skip_40);
    auto go_big = std::views::iota(5,100)
        | std::views::drop_while(
                [limit=75](const auto& n){ return n < limit;}
            );
    show("go big", go_big);
}
