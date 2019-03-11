#pragma once
#include <string>

template<typename TExceptie>
class Exceptii {
	std::string mesajExceptie;
public:
	Exceptii<TExceptie>(const std::string& mesajExceptie) : mesajExceptie{ mesajExceptie } {}
	const std::string& getMesajExceptie() const {
		return mesajExceptie;
	}
};