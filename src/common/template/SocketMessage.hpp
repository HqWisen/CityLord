#ifndef SOCKET_MESSAGE_HPP_
#define SOCKET_MESSAGE_HPP_

#include <string>
#include <string.h>
#include <map>
#include <iostream>

#define TOPICSEP "="
#define KEYSEP ":"
#define VALUESEP ";"

/* Topics */

#define LOGIN_REQUEST "login"
#define ACCOUNT_REQUEST "account"
#define QUIT_REQUEST "quit"

#define FAILURE_TOPIC "failure"

class SocketMessage{
	std::string topic;
	std::map<std::string, std::string> data;
	public:
		SocketMessage() = default;
		SocketMessage(std::string);
		void setTopic(std::string);
		std::string getTopic();
		void set(std::string, std::string);
		std::string get(std::string);
		std::string toString();
		static SocketMessage parse(std::string);
};

#endif // SOCKET_MESSAGE_HPP_

