#include <cstdlib>
#include <iostream>

int main ()
{
    int value;
    char string[6] = "";
    setlocale(LC_ALL, "Russian");
    std::cout << "¬ведите число: ";
    std::cin >> value;
    std::cout << itoa(value, string, 10);

    return 0;
}
