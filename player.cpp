
#include <vector>
#include <iostream>

#include "glm/vec2.hpp"

int main555()
{
    std::vector<int> vec;
    glm::vec2 myvec(1, 3);
    std::cout << myvec.x << " " << myvec.y << std::endl;

    std::cout << "WIN" << vec.size() << std::endl;
    return 0;
}
