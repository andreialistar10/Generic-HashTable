#pragma once
#include "exceptiiGenerice.h"

class Validator {
public:
	void validare(const std::string& CNP, const std::string& numeComplet, const std::string& localitate, const std::string& nrTelefon);
	const std::string validareLongLong(const std::string& longLong, const std::string & entitate) const noexcept;
private:
	const std::string validareString(const std::string& stringulMeul, const std::string & entitate) const noexcept;
	const std::string validareNrTelefon(const std::string& nrTelefon);
};