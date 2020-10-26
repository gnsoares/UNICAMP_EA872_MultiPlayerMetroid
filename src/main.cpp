#include <iostream>
#include "models.hpp"

int main() {

    Samus samus(5, 7);

    std::cout << samus.rect.x << ", " << samus.rect.y << std::endl;

    return 0;
}