#include <iostream>
#include <map>
#include <ranges>
#include <string>
#include <tuple>
#include <vector>

int main(){
    std::vector<std::tuple<int, double, std::string>> v
        {{1,1.1,"one"}, {2, 2.2, "two"}, {3, 3.3, "three"}};
    std::map<int, double> m
        {{1,1.11}, {2,2.22}, {3,3.33}};

    std::cout << "vector, element<2>\n";
    for(const auto& val: v|std::views::elements<2>){
        std::cout << val << ' ';
    }
    std::cout << '\n';
    std::cout << "vector, element<0>\n";
    for(const auto& val: v|std::views::elements<0>){
        std::cout << val << ' ';
    }
    std::cout << '\n';

    std::cout << "map, keys\n";
    for(auto& val: m|std::views::keys){
        std::cout << val << ' ';
	//val++;
    }
    std::cout << '\n';
    std::cout << "map, values\n";
    for(const auto& val: m|std::views::values){
        std::cout << val << ' ';
    }
    std::cout << '\n';

    std::cout << "vector, keys == element<0>\n";
    for(auto& val: v|std::views::keys){
        std::cout << val << ' ';
	val++;
    }
    std::cout << '\n';
    std::cout << "vector again, keys == element<0>\n";
    for(auto& val: v|std::views::keys){
        std::cout << val << ' ';
	val++;
    }
    std::cout << '\n';
    std::cout << "vector, values == element<1>\n";
    for(const auto& val: v|std::views::values){
        std::cout << val << ' ';
    }
    std::cout << '\n';

}
