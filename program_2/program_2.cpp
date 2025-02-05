#include "data_processor.h"
#include <iostream>
#include <memory> 

int main() {
    short port = 12345;                             // Номер порта (может быть изменен)

    std::unique_ptr<DataProcessor> processor 
        = std::make_unique<DataProcessor>(port);    // Создание экземпляра класса-обработчика

    processor->start();                             // Запуск стартовой функции (запуск сервера)

    return 0;
}
