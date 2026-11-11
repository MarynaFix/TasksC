#include <iostream>
#include <vector>
int main()
{
    int N = 0;
    std::cout << "Enter the number up to with the calculation will be performed: ";
    std::cin >> N;
    std::vector<int> numbers;
    numbers.reserve(N - 2);
    for (int i = 2; i <= N; i++) {
        numbers.push_back(i);
    }

    for (int j = 0; j < numbers.size(); j++) {
        if (numbers[j] == 0) {
            continue;
        }

        for (int k = j + numbers[j]; k < numbers.size(); k += numbers[j]) {

            if (numbers[k] % numbers[j] == 0) {
                numbers[k] = 0;
            }
        }
    }

    for (int num : numbers) {
        if (num != 0) {
            std::cout << num << " ";
        }
    }
    std::cout << std::endl;
    return 0;
}