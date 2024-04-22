#include <iterator>
#include <list>
#include <utility>
#include <vector>

#include "tools.h"

int main(){
    static_assert(std::indirectly_writable<int *, int>);
    static_assert(!std::indirectly_writable<const int *, int>);
    static_assert(std::indirectly_writable<int * const, int>); // why
    static_assert(std::indirectly_writable<std::vector<int>::iterator, int>);
    static_assert(!std::indirectly_writable<std::vector<int>::const_iterator, int>);
    static_assert(std::indirectly_writable<const std::vector<int>::iterator, int>);
    static_assert(std::indirectly_writable<std::vector<int>::iterator, double>);
    static_assert(!std::indirectly_writable<std::vector<int>::iterator, std::pair<double,int>>);
    static_assert(std::indirectly_copyable<std::vector<int>::iterator, std::list<double>::iterator>);
    static_assert(std::indirectly_movable<std::vector<int>::iterator, std::list<double>::iterator>);
    WHAT<std::add_pointer_t<int *>>();
    WHAT<const std::iter_reference_t<int * const>&&>();
    WHAT<const std::iter_reference_t<const std::vector<int>::iterator>&&>();
}
