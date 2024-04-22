#include <iterator>
#include <string>
#include <vector>

int main(){
    using namespace std;
    static_assert(random_access_iterator<int *>);
    static_assert(random_access_iterator<
		  decltype(declval<vector<int>>().begin())>);
    static_assert(random_access_iterator<vector<int>::iterator>);

    static_assert(!random_access_iterator<vector<int>>);
    static_assert(!random_access_iterator<string>);
}
