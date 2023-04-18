#include <algorithm>
#include <bitset>
#include <iostream>
#include <memory>
#include <vector>

class BitStream {
private:
    const static int bitsetSize_ = 40;
    std::bitset<bitsetSize_> stream;
    uint32_t bitsAdded_ = 0;
    uint32_t remainingNumberOfBits_ = bitsetSize_;
    uint64_t actualPositionAfterAddingData_ = stream.size() - 1;
    uint64_t posAfterReadingBits_ = stream.size() - 1;
    uint32_t counterOfReadBits_ = 0;

public:
    template <typename T>
    std::vector<bool> GetBitsVector(T inputValue) {
        std::vector<bool> result;

        while (inputValue > 0) {
            result.push_back(inputValue & 1);
            inputValue >>= 1;
        }
        return result;
    }
    template <typename T>
    uint32_t Add(uint32_t bitLength, void* dataAddr) {
        if (dataAddr) {
            auto* ptr = static_cast<T*>(dataAddr);

            std::vector<bool> vec = GetBitsVector(*ptr);

            uint64_t j = vec.size() - 1;
            bitLength = std::min(static_cast<uint32_t>(vec.size()), bitLength);
            bitLength--;
            int size = actualPositionAfterAddingData_ - bitLength;

            for (int i = actualPositionAfterAddingData_; i >= size; i--) {
                stream[i] = vec[j];
                bitsAdded_++;
                remainingNumberOfBits_--;
                j--;
                actualPositionAfterAddingData_--;
            }

            return bitsAdded_;
        }
        return actualPositionAfterAddingData_;
    }

    template <typename T>
    uint32_t Get(uint32_t bitLength, void* dataAddr) {
        if (dataAddr) {
            std::bitset<bitsetSize_> bit;
            int j = bitLength - 1;
            auto uintDataAddr = static_cast<T*>(dataAddr);
            bitLength--;
            uint64_t size = posAfterReadingBits_ - bitLength;

            for (uint64_t i = posAfterReadingBits_; i >= size; i--) {
                bit[j] = stream[i];
                j--;
                posAfterReadingBits_--;
                counterOfReadBits_++;
            }
            *uintDataAddr = bit.to_ulong();
            if (posAfterReadingBits_ == 0) {
                posAfterReadingBits_ = stream.size() - 1;
            }
            return counterOfReadBits_;
        }
        return counterOfReadBits_;
    }

    template <typename T>
    uint32_t GetData(void* addr, uint32_t maxBitLength) {
        if (addr) {
            auto uintDataAddr = static_cast<T*>(addr);
            auto str = stream;
            uint32_t currentSize = std::min(bitsAdded_, maxBitLength);
            uint32_t bitsetSize = bitsetSize_;
            int shift = bitsetSize - currentSize;
            str >>= shift;
            *uintDataAddr = str.to_ullong();
            return currentSize;
        }
        return bitsAdded_;
    }

    uint32_t GetBitLength() {
        return bitsAdded_;
    }

    void ResetData() {
        bitsAdded_ = 0;
        remainingNumberOfBits_ = bitsetSize_;
        actualPositionAfterAddingData_ = stream.size() - 1;
        posAfterReadingBits_ = stream.size() - 1;
        counterOfReadBits_ = 0;
        stream.reset();
    }

    void print() {
        for (int i = stream.size() - 1; i >= 0; i--) {
            std::cout << stream[i];
        }
        std::cout << '\n';
    }
};

void test() {
    std::unique_ptr<BitStream> bitStream = std::make_unique<BitStream>();
    uint64_t testValue = 821831448415;
    std::bitset<40> testBitsetContainer(testValue);

    bitStream->Add<uint64_t>(40, &testValue);
    std::cout << "  My Bit Stream 64-bit =";
    bitStream->print();

    std::cout << "Original Bitset 64-bit =" << testBitsetContainer;
    std::cout << '\n';

    bitStream->ResetData();

    uint32_t expectedGetNumber = 3061;
    uint32_t expectedGetDataNumber = 3210279095;
    uint32_t getDataNumber = 0;
    uint32_t getNumber = 0;
    uint32_t amountOfAddedBits = 40;

    uint8_t Var0 = 11;
    uint8_t Var1 = 3;
    uint8_t Var2 = 52;
    uint8_t Var3 = 1;
    uint8_t Var4 = 143;
    uint16_t Var5 = 35701;
    uint8_t Var6 = 15;

    bitStream->Add<uint8_t>(4, &Var0);    // adds 4 bits of Var0 to a data stream / buffer
    bitStream->Add<uint8_t>(2, &Var1);    // adds 2 bits of Var1 to a data stream / buffer
    bitStream->Add<uint8_t>(5, &Var2);    // adds 5 bits of Var2 to a data stream / buffer
    bitStream->Add<uint8_t>(1, &Var3);    // adds 1 bit of Var3 to a data stream / buffer
    bitStream->Add<uint8_t>(8, &Var4);    // adds 8 bits of Var4 to a data stream / buffer
    bitStream->Add<uint16_t>(16, &Var5);  // adds 16 bits of Var5 to a data stream / buffer
    bitStream->Add<uint8_t>(4, &Var6);    // adds 4 bits of Var6 to a data stream / buffer

    bitStream->Get<uint32_t>(12, &getNumber);
    bitStream->GetData<uint32_t>(&getDataNumber, 32);

    if (getNumber == expectedGetNumber) {
        std::cout << "correct result of the function Get " << '\n';
    }
    if (amountOfAddedBits == bitStream->GetBitLength()) {
        std::cout << "correct result of the function GetBitLength" << '\n';
    }

    if (getDataNumber == expectedGetDataNumber) {
        std::cout << "correct result of the function getData" << '\n';
    }
    std::cout << "stream after adding data" << '\n';
    bitStream->print();
    std::cout << "stream after data reset" << '\n';
    bitStream->ResetData();
    bitStream->print();
}
int main() {
    
    test();

    return 0;
}
