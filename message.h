#pragma once
#include "user.h"

class Message
{
private:
	//const std::string _from;      // От кого
	//const std::string _to;        // Кому
	//const std::string _message;   // Текст сообщения
    std::string _data;
public:
    Message()
    {}

	Message(const std::string& from, const std::string& to, const std::string& message) {
		_data = from + to + message;
    }

    const std::string& getUserData() const
    {
        return _data;
    }

	const std::string& getUserFrom() const
	{
		return "";
	}

	const std::string& getUserTo() const
	{
		return "";
	}

	const std::string& getUserMessage() const
	{
		return "";
	}
};
