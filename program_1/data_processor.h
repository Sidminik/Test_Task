#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include "library.h"
#include <string>
#include <asio.hpp>
#include <thread>
#include <mutex>
#include <condition_variable>

using asio::ip::tcp;

class DataProcessor {
public:
    DataProcessor();                                        
    void start();                                           // Метод для запуска потоков

private:
    std::mutex mtx;                                         // Мьютекс для синхронизации потоков
    std::condition_variable cv;                             // Условная переменная для приостановки исполнения
    std::string sharedBuffer;                               // Общий буфер для потоков
    bool dataReady;                                         // Флаг - индикатор состояния (готов ли sharedBuffer к обработке)
    bool isConnected;                                       // Флаг - индикатор подключения к Программе 2
    bool ioStatus;                                          // Флаг - индикатор для предотвращения конфликта вывода на консоль
    asio::io_context io_context;                            
    tcp::socket socket;                                     
    tcp::resolver resolver;                                 

    void connectToServer();                                 // Метод подключения к серверу (Программе 2)
    void inputThread();                                     // Метод потока для ввода данных
    void processingThread(asio::ip::tcp::socket& socket);   // Метод потока для обработки данных
};

#endif // DATAPROCESSOR_H
