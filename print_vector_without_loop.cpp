#include <iostream>
#include <vector>

void reversePrint(const std::vector<char>& vec) {
    static long index = vec.size() - 1;

    if (index >= 0) {
        std::cout << vec[index];
        index--;
        reversePrint(vec);
    }
}

void test() {
    std::vector<char> v{'a','b','c','d','e','f','g','h','i',};

    std::cout<<"vector before reverse ";
    for(const auto& el : v){
        std::cout<<el;
    }
    std::cout<<'\n';
    std::cout<<"vector  after reverse ";

    reversePrint(v);
    std::cout<<'\n';
}

int main() {
    test();

    return 0;
}
