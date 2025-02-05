#include "data_processor.h"

DataProcessor::DataProcessor(short port)
    : acceptor_(io_context_, tcp::endpoint(tcp::v4(), port)) {
    acceptor_.listen();                                                             // Прослушивание на указанном порту
}

void DataProcessor::start() {
    std::cout << "Программа 2 запущена. Ожидание стороннего подключения...\n";
    while (true) {
        acceptConnection();                                                         // Запуск цикла принятия подключений
    }
}

void DataProcessor::acceptConnection() {
    tcp::socket socket(io_context_);                                                
    acceptor_.accept(socket);                                                       
    std::cout << "Программа 1 подключена" << std::endl;
    handleClient(std::move(socket));                                                // Запуск обработки подключения Программы 1
}

void DataProcessor::handleClient(tcp::socket socket) {
    try {
        handleMessages(socket);                                                     // Запуск обработки входящих сообщений от Программы 1
    }
    catch (const std::exception& e) {
        std::cerr << "Исключение: " << e.what() << std::endl;
    }
    closeSocket(socket);                                                            // Запуск обработки закрытия сокета
}

void DataProcessor::handleMessages(tcp::socket& socket)
{
    std::array<char, 1024> buffer;                                                  // Буфер для получения входящих сообщений
    while (true) {                                                                  // Запуск цикла принятия входящих сообщений
        std::size_t length = socket.read_some(asio::buffer(buffer));
        std::string input(buffer.data(), length);                                  

        if (!input.empty()) {                                                       // Обработка строки полученного сообщения
            bool result = analysisLength(input);
            if (result) {
                std::cout << "Получены следующие данные: " << input << std::endl;
            }
            else {
                std::cout << "При получении сообщения из Программы 1 обнаружена ошибка данных!" << std::endl;
            }                                                               
            std::string response = "dataOK";                                        // Подготовка ответного сообщения клиенту
            asio::write(socket, asio::buffer(response));                            // Возврат клиенту сообщения об успешном получении
        }
    }
}

void DataProcessor::closeSocket(tcp::socket& socket)                                // Обработка закрытия сокета
{
    try {
        socket.close();
        std::cout << "Сокет закрыт" << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при закрытии сокета: " << e.what() << std::endl;
    }
}
