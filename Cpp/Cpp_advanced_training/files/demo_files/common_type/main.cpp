#include <optional>
#include <type_traits>
#include "tools.h"

int main(){
    std::optional<int> o{33};
    WHAT<std::common_type_t<std::optional<int>, std::nullopt_t>>();
    WHAT<std::common_type_t<int, double>>();
}
