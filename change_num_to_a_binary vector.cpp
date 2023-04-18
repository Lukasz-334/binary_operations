#include <iostream>
#include <string>
#include <variant>
#include <vector>

std::vector<bool> GetBitsVector(uint32_t inputValue) {
    std::vector<bool> result;

    while (inputValue > 0) {
        result.push_back(inputValue & 1);
        inputValue >>= 1;
    }

    return result;
}

std::vector<bool> GetBitsVector(std::string inputValue) {
    return GetBitsVector(std::stoul(inputValue, nullptr, 0));
}

template <typename T>
void test(const std::vector<bool>& expectedResult, T testedNumber) {
    try {
        auto result = GetBitsVector(testedNumber);
        if (expectedResult == result) {
            std::cout << "number " << testedNumber << " binary = ";
            for (const auto& el : result) {
                std::cout << el << ',';
            }
            std::cout << "  correct result" << '\n';
        } else {
            std::cout << "incorrect result" << '\n';
        }
    } catch (const std::invalid_argument& ex) {
        std::cout << ex.what();
    } catch (const std::out_of_range& ex) {
        std::cout << ex.what();
    }
}

int main() {
    std::vector<bool> result({1, 0, 1, 0, 1, 0, 0, 1});

    test(result, 0225);
    test(result, 149);
    test(result, 0x95);
    test(result, "0225");
    test(result, "149");
    test(result, "0x95");

    return 0;
}
