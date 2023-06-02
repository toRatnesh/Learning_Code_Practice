
struct Data {
    float x;
    int y;
};

const Data & get_data() {
    static Data d{23.5, 6};
    return d;
}
