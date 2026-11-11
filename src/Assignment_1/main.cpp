#include <iostream>
int main()
{
    std::cout << "Hello" << std::endl;
    std::cout << "Geben Sie die Temperatur in Celsius: ";
    double celsius;
    std::cin >> celsius;
    double fahrenheit = celsius * 9.0 / 5.0 + 32;
    if (celsius < -273.15) {
        std::cout << "Die Temperatur kann nicht weniger als -273 Grad Celsius sein" << std::endl;
        return 1;
    }
    double kelvin = celsius + 273.15;
    std::cout << "Fahrenheit: " << fahrenheit << std::endl;
    std::cout << "Kelvin: " << kelvin << std::endl;
    std::cout << "Auf Wiedersehen!";
    return 0;
}