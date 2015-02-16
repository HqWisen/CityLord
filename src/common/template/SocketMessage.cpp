#include "SocketMessage.hpp"

SocketMessage::SocketMessage(std::string topic_){
	topic = topic_;
}

void SocketMessage::setTopic(std::string topic_){
	topic = topic_;
}

std::string SocketMessage::getTopic(){
	return topic;
}

void SocketMessage::set(std::string key, std::string value){
	data[key] = value;
}

std::string SocketMessage::get(std::string key){
	auto search = data.find(key);
	if(search != data.end()){
		return data[key];
	}else{
		return "";
	}
}

std::string SocketMessage::toString(){
	std::string result;
	result += topic + TOPICSEP;
	for (std::map<std::string, std::string>::iterator it=data.begin(); it!=data.end(); ++it){
		result+=it->first + KEYSEP;
		result+=it->second + VALUESEP;
	}
	return result;
}

SocketMessage SocketMessage::parse(std::string source){
	size_t index;
	SocketMessage socketMessage;
	index = source.find(TOPICSEP);
	socketMessage.setTopic(source.substr(0, index));
	source.erase(source.begin(), source.begin() + index + strlen(TOPICSEP));
	std::string key, value;
	while(!source.empty()){
		index = source.find(KEYSEP);
		key = source.substr(0, index);
		source.erase(source.begin(), source.begin() + index + strlen(KEYSEP));
		index = source.find(VALUESEP);
		value = source.substr(0, index);
		source.erase(source.begin(), source.begin() + index + strlen(VALUESEP));
		socketMessage.set(key, value);
	}
	return socketMessage;
}

