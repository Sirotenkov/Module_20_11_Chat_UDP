#include "chat.h"
#include "errno.h"

int main(int argc, char** argv)
{
    if (argc != 5)
    {
        std::cout << "Please provide 4 arguments to run this program!" << std::endl;
        return -1;
    }

    #if defined(_WIN32)
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::exception();
        }
    #endif

    Chat* chat = nullptr;

    try
    {
        // Создаю объект класса "Чат"
        // Объект выкинет исключение если возникнут ошибки во время создания.
        chat = new Chat(argv[1], std::stoi(argv[2]), argv[3], std::stoi(argv[4]));
    }
    catch(...)
    {
        // На виндовс тоже есть errno так что тут всё норм.
        // errno показывает последнюю системную ошибку
        std::cout << "Failed to start chat! Error code " << errno << std::endl;
        return -1;
    }

    std::cout << "self address: " << argv[1] << std::endl
        << "self port: " << argv[2] << std::endl
        << "other address: " << argv[3] << std::endl
        << "other port: " << argv[4] << std::endl;

    chat->start();

    while (chat->isChatOpen())  // Пока чат работает
    {
        chat->showLoginMenu();  // Вывожу меню входа в систему

        while (chat->getCurrentUser())  // Пока указатель на текущего пользователя не nullptr
        {
            chat->showUserMenu();  // Вывожу пользовательское меню
        }
    }
    return 0;
}
