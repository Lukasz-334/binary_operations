#include <iostream>
#include <string>

uint32_t GetBitsFromUint32(uint32_t inputValue, uint8_t bitOffset, uint8_t bitLength) {
    return (inputValue >> bitOffset & ((1 << bitLength) - 1));
}

uint32_t GetBitsFromUint32(const char* inputValue, uint8_t bitOffset, uint8_t bitLength) {
    return GetBitsFromUint32(std::stoul(inputValue, nullptr, 0), bitOffset, bitLength);
}

template <typename T>
void test(uint32_t expectedResult, T testedNumber, uint8_t bitOffSet, uint8_t bitLenght) {
    try {
        uint32_t number = GetBitsFromUint32(testedNumber, bitOffSet, bitLenght);
        if ((expectedResult == number)) {
            std::cout << "number " << std::hex << std::uppercase << testedNumber << " after a bit shift bit length = " << number << '\n';
            std::cout << "correct result" << '\n';

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
    test(0x00000EF1, 0xABCDEF12, 4, 12);
    test(0x00000EF1, "025363367422", 4, 12);
    test(0x00000EF1, "2882400018", 4, 12);
    test(0x00000EF1, "0xABCDEF12", 4, 12);

    return 0;
}
