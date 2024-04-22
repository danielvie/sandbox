#include <iostream>
#include <vector>
#include <optional>
#include <algorithm>

std::optional<int> double_if_present(std::optional<int> num)
{
    if (num) { return num.value() * 2; }
    return std::nullopt;
}

int main(int argc, char const *argv[])
{
    
    std::vector<std::optional<int>> numbers = {1, std::nullopt, 3, std::nullopt, 5};
    std::vector<std::optional<int>> doubled_numbers;

    std::transform(numbers.begin(), numbers.end(),
                    std::back_inserter(doubled_numbers),
                    double_if_present);
    

    for (auto num : doubled_numbers) {
        if (num) { std::cout << num.value() << std::endl; }
        else { std::cout << "nullopt" << std::endl; }
    }

        
    return 0;
}
