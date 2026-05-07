struct fr{
    int x,y;
    bool operator<(const fr& oth)const{
        return 1LL * x * oth.y < 1LL * oth.x * y;
    }
};