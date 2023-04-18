#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Tree {
public:
    Tree(const std::string& name)
        : name_{name} {}

    Tree* AddSub(const std::string& name) {
        children_.emplace_back(std::make_unique<Tree>(name));
        return children_.back().get();
    }

    uint32_t GetSubCount() const {
        return static_cast<uint32_t>(children_.size());
    }

    uint32_t GetAllSubCount() const {
        uint32_t init = 0;
        for (const auto& child : children_) {
            init += child->GetAllSubCount();
        }
        return static_cast<uint32_t>(init + children_.size());
    }

    bool Del(const uint32_t index) {
        if (index >= children_.size()) {
            return false;
        }
        children_.erase(children_.begin() + index);
        return true;
    }

    void print(uint32_t depth, bool printNumbers) const {
        std::cout << name_ << '\n';
        static std::vector<uint32_t> numbers{};
        numbers.push_back(1);
        depth += 1;
        for (const auto& child : children_) {
            std::cout << std::string(depth, ' ');
            if (printNumbers) {
                for (auto number : numbers) {
                    std::cout << number << '.';
                }
                std::cout << ' ';
            }
            child->print(depth, printNumbers);
            ++numbers.back();
        }
        numbers.pop_back();
    }

private:
    std::string name_;
    std::vector<std::unique_ptr<Tree>> children_;
};

int main() {
    Tree* root = new Tree("tree name");
    [[maybe_unused]] Tree* galaz1 = root->AddSub("galaz 1");
    [[maybe_unused]] Tree* galaz2 = root->AddSub("galaz 2");
    [[maybe_unused]] Tree* galaz3 = root->AddSub("galaz 3");
    [[maybe_unused]] Tree* galaz1_1 = galaz1->AddSub("galaz 1.1");
    [[maybe_unused]] Tree* galaz2_1 = galaz2->AddSub("galaz 2.1");
    [[maybe_unused]] Tree* galaz2_2 = galaz2->AddSub("galaz 2.2");
    [[maybe_unused]] Tree* galaz2_1_2 = galaz2_1->AddSub("galaz 2.1.1");

    root->print(2, true);
    std::cout << '\n';

    uint32_t rootChildrenCnt = root->GetSubCount();
    std::cout << "rootChildrenCnt = " << rootChildrenCnt << '\n';

    uint32_t galaz1childrenCount = galaz1->GetSubCount();
    std::cout << "galaz1childrenCount = " << galaz1childrenCount << '\n';

    uint32_t countOfAllChildren = root->GetAllSubCount();
    std::cout << "countOfAllChildren = " << countOfAllChildren << '\n';

    root->Del(1);
    std::cout << '\n';
    root->print(2, true);
    std::cout << '\n';

    uint32_t rootChildrenCnt_v2 = root->GetSubCount();
    std::cout << "rootChildrenCnt_v2 = " << rootChildrenCnt_v2 << '\n';

    uint32_t countOfAllChildren_v2 = root->GetAllSubCount();
    std::cout << "countOfAllChildren_v2 = " << countOfAllChildren_v2 << '\n';

    delete (root);
    return 0;
}
