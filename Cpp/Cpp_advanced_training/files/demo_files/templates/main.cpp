#include <iterator>
#include <iostream>
#include <vector>
//import <vector>;
//#include <fmt/core.h>

template <typename InputIt, typename OutputIt>
void dup_17(InputIt in_start, InputIt in_end, OutputIt out){
    for(;in_start!=in_end;++in_start, ++out) *out = *in_start;
}
// <iterator>
template <std::input_iterator InputIt,
          std::output_iterator<
                typename std::iterator_traits<InputIt>::value_type> OutputIt>
void dup_20(InputIt in_start, InputIt in_end, OutputIt out){
                typename std::iterator_traits<InputIt>::value_type v;
    for(;in_start!=in_end;++in_start, ++out) *out = *in_start;
}

struct Point {
    int x;
    int y;
};

int main(){
    std::vector v{3, 5, 8, 12};
    std::vector<int> w;
    std::vector<Point> pv(10);
    w.resize(40);
    dup_17(v.begin(), v.end(), std::back_inserter(w));
    dup_20(v.begin(), v.end(), std::back_inserter(w));
    dup_20(v.begin(), v.end(), w.begin());
    dup_20(w.begin(), w.end(), std::ostream_iterator<int>(std::cout, "\n"));
    //dup_20(v.begin(), v.end(), pv.begin());
    //dup_20(v, v, w);
//    std::cout << fmt::format({":*^60\n}", "hi");
}
    
