/*****

References

    episode:    https://www.youtube.com/watch?v=Gr0aI-TPRiQ
    Path coverage in gcc - Jørgen Kvalsvik - NDC TechTown 2024 | https://www.youtube.com/watch?v=kkAsakZCCAY
    Path coverage in gcc - Jørgen Kvalsvik - NDC TechTown 2025 | https://www.youtube.com/watch?v=xYMkWT3ipRs

Line coverage:

Path coverage:
    path coverage of individual function

Branch coverage:


path coverage is always stronger than branch coverage and 
branch coverage is always stronger than line coverage


**********/

#include <iostream>

struct Data {
    int     m_data{0};
};

Data createData(const bool c1, const bool c2, int input) {
    if(c1) {
        input += 2;
    } else {
        input -= 2;
    }

    if(c2) {
        input *= 2;
    } else {
        input /= 2;
    }

    return Data{input};
}


Data getData(const bool c1, const bool c2, int input) {
    return createData(c1, c2, input);
}

int main() {

    [[maybe_unused]] auto val1 = getData(false, false, 8);
    [[maybe_unused]] auto val2 = getData(false, true, 16);
    [[maybe_unused]] auto val3 = getData(true, false, 32);
    [[maybe_unused]] auto val4 = getData(true, true, 64);

	return 0;
}

/*****
    END OF FILE
**********/

