struct Point {
    int x;
    int y;
};

int main(){
    constexpr Point p = { .x = 5 };
    static_assert(p.x == 5);
    static_assert(p.y == 0);
    //constexpr Point q = { .y = 3, .x = 5 };
    //constexpr Point r = { .x = 5, 3 };
}
