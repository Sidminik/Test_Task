#include "library.h"
#include <iostream>
#include <sstream>
#include <algorithm>

void sortAndChange(std::string* input) {
    // Сортировка строки по убыванию
    std::sort(input->begin(), input->end(), std::greater<>());

    // Замена четных символов в строке
    for (size_t i = 0; i < input->length(); i++) {
        if (((*input)[i] - '0') % 2 == 0) {
            (*input)[i] = 'K'; 
            input->insert(i + 1, "B"); 
            i++;
        }
    }
}

int calcSumNum(std::string input) {
    int sum = 0;

    // Суммирование всех чисел, выбранных из символов входящей строки
    for (char c : input)
    {
        if (isdigit(c))
        {
            sum += (c - '0');
        }
    }
    return sum;
}

bool analysisLength(std::string input) {
    
    // Проверка условий и возвращение булевого значения
    return (input.length() > 2 
        && input.length() % 32 == 0);
}
