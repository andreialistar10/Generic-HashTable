#include "validator.h"

void Validator::validare(const std::string & CNP, const std::string & numeComplet, const std::string & localitate, const std::string & nrTelefon)
{
	std::string mesaj = validareLongLong(CNP, "CNP-ul");
	mesaj += validareString(numeComplet, "Numele");
	mesaj += validareString(localitate, "Localitatea");
	mesaj += validareNrTelefon(nrTelefon);
	if (mesaj.size() > 0)
		throw Exceptii<Validator>(mesaj);
}

const std::string Validator::validareLongLong(const std::string & longLong, const std::string & entitate) const noexcept
{
	std::string mesaj;
	if (longLong.size() != 13) {
		mesaj += entitate + " nu contine 13 cifre! ";
		return mesaj;
	}
	if (longLong.size() == 0) {
		mesaj += entitate + " este vid! ";
		return mesaj;
	}
	char *verif;
	auto n = std::strtoll(longLong.c_str(), &verif, 10);
	if (strlen(verif)>0)
		mesaj += entitate + " este invalid! ";
	return mesaj;
}

const std::string Validator::validareNrTelefon(const std::string & nrTelefon)
{
	std::string mesaj;
	if (nrTelefon.size() != 10) {
		mesaj += "Numarul de telefon nu contine 10 cifre! ";
		return mesaj;
	}
	if (nrTelefon[0] != '0') {
		mesaj += "Numarul de telefon nu incepe cu cifra 0! ";
		return mesaj;
	}
	for (const auto& cifra:nrTelefon)
		if (cifra > '9' || cifra < '0') {
			mesaj += "Numarul de telefon nu contine doar cifre! ";
			return mesaj;
		}
	return mesaj;
}

const std::string Validator::validareString(const std::string & stringulMeul, const std::string & entitate) const noexcept
{
	std::string mesaj;
	if (stringulMeul.size()==0)
		mesaj += entitate + " este invalid/a! ";
	return mesaj;
}
