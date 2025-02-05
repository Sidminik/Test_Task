#include "data_processor.h"
#include <iostream>
#include <memory> 

int main() {
    std::unique_ptr<DataProcessor> processor 
        = std::make_unique<DataProcessor>();    // Создание экземпляра класса-обработчика

    processor->start();                         // Запуск стартовой функции (создания двух потоков)

    return 0;
}