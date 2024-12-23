/**
* @file DataReader.cpp
*/
#include "DataReader.h"

/**
* @brief Геттер для атрибута FileReader
*/
string DataReader::get_FileReader(){
    return FileReader;
}

/**
* @brief Сеттер для атрибута FileReader
*/
void DataReader::set_FileReader(string file){
    FileReader = file;
}

/**
* @brief Функция для получения БД клиентов
* @return Возвращает два вектора: логины и пароли клиентов
* @throw Errors при возникновении ошибки
*/
pair<vector<string>, vector<string>> DataReader::getClient() {
    vector<string> firstVector;
    vector<string> secondVector;

    ifstream inputFile(get_FileReader());

    if (!inputFile.is_open()) {
        Err.error_recording("критичная", "Fun: getClient. Файла с БД открыть невозможно.");
        throw std::runtime_error("Ошибка открытия файла."); // Или используйте ваш класс ошибок
    }

    if (inputFile.peek() == EOF) {
        Err.error_recording("критичная", "Fun: getClient. Файл с БД пуст.");
        throw std::runtime_error("Файл пуст."); // Или используйте ваш класс ошибок
    }
    
    std::string line;
    while (std::getline(inputFile, line)) {
        std::istringstream ss(line);
        std::string first, second;
        
        // Чтение двух строк, разделенных двоеточием
        if (std::getline(ss, first, ':') && std::getline(ss, second, ':')) {
            firstVector.push_back(first);
            secondVector.push_back(second);
        } else {
            // Логирование или обработка случая, когда строка имеет неправильный формат
            Err.error_recording("предупреждение", "Fun: getClient. Неверный формат строки: " + line);
        }
    }

    return std::make_pair(firstVector, secondVector);
}

