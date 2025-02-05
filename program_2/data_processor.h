#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include "library.h"
#include <iostream>
#include <string>
#include <asio.hpp>

using asio::ip::tcp;

class DataProcessor {
public:
    DataProcessor(short port);                  // Конструктор (принимает порт)
    void start();                               // Стартовый метод запуска цикла создания и установки подключений

private:
    asio::io_context io_context_;               
    tcp::acceptor acceptor_;                    

    void acceptConnection();                    // Метод обработки входящих соединений 
    void handleClient(tcp::socket socket);      // Метод обработки подключения Программы 1
    void handleMessages(tcp::socket& socket);   // Метод обработки входящих сообщений от Программы 1
    void closeSocket(tcp::socket& socket);      // Метод обработки закрытия сокета
};

#endif // DATAPROCESSOR_H