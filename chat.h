#pragma once
#include <vector>
#include <exception>
#include <memory>
#include "message.h"
#include "sha1.h"
#include "udp.h"
#include <cstring>

struct UserLoginExceptions : public std::exception  //
{                                                   //
	const char* what() const noexcept override      //
	{                                               //  обработка исключений
		return "Error! Login failure!";             //
	}                                               //
};                                                  //

class Chat
{
private:
	bool _isChatOpen = false;                       // переменная-флаг, показывающая, открыт чат или нет
	std::vector<User> _users;                       // контейнер пользователей vector
	//std::vector<Message> _messages;                 // контейнер сообщений vector
	User const* _currentUser = nullptr;             // указатель на текущего пользователя
    Udp _sock;

    std::string _self_addr;
    std::uint8_t _self_port;

    std::string _other_addr;
    std::uint8_t _other_port;

	void login();                                   // объявление функции входа в систему
	void signUp();                                  // объявление функции регистрации пользователя
	void showChat();                                // объявление функции отображения меню чата
	void showAllUsers();                            // объявление функции отображения всех пользователей системы
	void addMessage();                              // объявление функции добавления сообщений

	std::vector<User>& getAllUsers()
	{
		return _users;
	}

	std::vector<Message> getAllMessages()
	{
		return { };
	}

	User const* getUserByLogin(const std::string& login) const;  // объявление функции возвращения указателя на пользователя по логину

public:
    Chat(char const* self_addr, std::uint8_t self_port, char const* other_addr, std::uint8_t other_port):
        _sock(self_addr, self_port)
        , _self_addr(self_addr)
        , _self_port(self_port)
        , _other_addr(other_addr)
        , _other_port(other_port)
        {

        }

	void start();  // объявление функции, показывающей работает чат или нет

	bool isChatOpen() const
	{
		return _isChatOpen;
	}

	User const* getCurrentUser() const  // метод, возвращающий указатель на текущего пользователя
	{
		return _currentUser;
	}

	void showLoginMenu();                // метод, отображающий меню входа в систему

	void showUserMenu();                 // метод, отображающий пользовательское меню

	bool isEqualPassword(std::string password, uint const* hash)  // метод, сравнивающий хэши паролей для валидации пользователя
	{
		uint* passwordHash = sha1((char*)password.data(), password.size());  // переменная со значением хэша введенного пароля
		int res = memcmp(passwordHash, hash, SHA1HASHLENGTHUINTS);           // переменная со значением результата сравнения вычисленного хэша с хранящимся
		delete[] passwordHash;                                               // удаление хэша введенного пароля
		return res == 0;                                                     // если результат равен нулю, то сравниваемые значения совпали
	};
};
