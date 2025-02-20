#include <iostream>
#include <fstream>
#include <vector>
#include <future>
#include <cstdlib>
#include <ctime> 

using namespace std;

void writeNumbers(const string& filename, int count) {
    ofstream file(filename);
    if (!file) {
        cerr << "Ошибка создания файла!" << endl;
        return;
    }

    srand(time(0));

    for (int i = 0; i < count; ++i) {
        int number = rand() % 100 + 1; 
        file << number << "\n";       
    }
}

int calculateSum(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка чтения файла!" << endl;
        return 0;
    }

    int sum = 0;
    int number;
    while (file >> number) { 
        sum += number;
    }
    return sum;
}

long long calculateProduct(const string& filename) {
    ifstream file(filename);
    if (!file) {
        cerr << "Ошибка чтения файла!" << endl;
        return 0;
    }

    long long product = 1;
    int number;
    bool first = true;

    while (file >> number) { 
        if (first) {
            first = false; 
        }
        product *= number;
    }
    return product;
}

int main() {
    const string filename = "numbers.txt";
    const int count = 10; 

    vector<future<void>> tasks;

    tasks.emplace_back(async(launch::async, [&]() {
        writeNumbers(filename, count);
        cout << "Числа записаны в файл.\n";
    }));

    tasks.back().get();

    tasks.emplace_back(async(launch::async, [&]() {
        int sum = calculateSum(filename);
        cout << "Сумма чисел: " << sum << "\n";
    }));

    tasks.emplace_back(async(launch::async, [&]() {
        long long product = calculateProduct(filename);
        cout << "Произведение чисел: " << product << "\n";
    }));

    for (auto& task : tasks) {
        if (task.valid()) {
            task.get();
        }
    }

    cout << "Все задачи выполнены." << endl;

    return 0;
}