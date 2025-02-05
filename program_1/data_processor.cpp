#include "data_processor.h"
#include "library.h"
#include <iostream>
#include <thread>
#include <chrono>

using asio::ip::tcp;

DataProcessor::DataProcessor() 
    : dataReady(false), isConnected(false), ioStatus(true), socket(io_context), resolver(io_context) {}

void DataProcessor::start() {
    std::thread inputThread(&DataProcessor::inputThread, this);                                 // Запуск Потока 1
    std::thread processingThread(&DataProcessor::processingThread, this, std::ref(socket));     // Запуск Потока 2

    inputThread.join();
    processingThread.join();       
}

void DataProcessor::connectToServer()                                                           // Обработка подключения к серверу
{
    while (!isConnected) {                                                                      // Цикл подключения
        try {
            if (socket.is_open()) {
                socket.close();
            }

            tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "12345");

            asio::connect(socket, endpoints);
            isConnected = true;

            std::cout << "Программа 2 подключена. Возможно продолжение ввода: " << std::endl;
        }
        catch (const std::exception& e) {                                                       // Обработка ошибки подключения
            isConnected = false;
            std::this_thread::sleep_for(std::chrono::seconds(1));                               // Интервал повторного подключения (можно изменить)
        }
    }
}

void DataProcessor::inputThread() {                                                             // Обработка ввода данных
    while (true) {
        if (ioStatus)
        {
            std::lock_guard<std::mutex> lock(mtx);                                              // Блокировка мьютекса
            std::string input;
            std::cout << "Введите строку (только цифры, не более 64 символов): " << std::endl;
            std::getline(std::cin, input);
            ioStatus = false;
            
            if (input.length() <= 64        
                && std::all_of(input.begin(), input.end(), ::isdigit)) {                        // Проверка на соответствие условиям
                sortAndChange(&input);                
                sharedBuffer = input;                                                           // Помещение данных в общий буфер
                dataReady = true;                                                               
                cv.notify_one();                                                                // Уведомление потока processingThread 
                                                                                                // о готовности данных
            }
            else {  
                std::cerr << "Ошибка: строка должна состоять только из цифр и не превышать 64 символа.\n";
                ioStatus = true;
            }
        }
    }
}

void DataProcessor::processingThread(asio::ip::tcp::socket& socket) {                           // Обработка данных общего буфера
    connectToServer();
    while (true) {
        std::string dataToSend;

        {
            std::unique_lock<std::mutex> lock(mtx);                                             // Блокировка мьютекса
            cv.wait(lock, [this] { return dataReady; });                                        // Ожидание, пока данные будут готовы
            dataToSend = sharedBuffer;                                                          // Извлечение данных из общего буфера
            sharedBuffer.clear();                                                               // Очистка общего буфера
            dataReady = false; 
        }

        std::cout << "Полученные данные: " << dataToSend << std::endl;      
        ioStatus = true;

        int response = calcSumNum(dataToSend);                                                  // Вызов Функции 2 

        bool dataTransfer = false;
        try {
            while (!dataTransfer)                                                               // Цикл передачи данных в Программу 2
            {
                asio::write(socket, asio::buffer(std::to_string(response)));                    // Отправка данных в Программу 2 (сервер)
                std::array<char, 128> buf;                                                      // Создание буфера для чтения ответа от сервера
                size_t len = socket.read_some(asio::buffer(buf));                               
                std::string message(buf.data(), len);
                if (message == "dataOK")
                {
                    dataTransfer = true;
                }
                                                                                                // Повторное соединение при отсутсвии ответа
                else
                {
                    isConnected = false;
                    connectToServer();
                }
            }
        }
        catch (const std::exception& e) {
            std::cout << "Последние введенные данные не были переданы (сбой Программы 2)" << std::endl;
            std::cout << "Если необходимо, повторите последний ввод и/или продолжайте ввод следующих данных" << std::endl;
            std::cout << "Все введенные с этого момента данные будут переданы в Программу 2 при восстановлении подключения" << std::endl;
            isConnected = false;
            connectToServer();
        }
    }
}
