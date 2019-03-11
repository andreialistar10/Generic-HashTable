#include "persoana.h"

std::ostream & operator<<(std::ostream & out, const Persoana & pers)
{
	out << pers.CNP << std::endl;
	out << pers.numeComplet << std::endl;
	out << pers.localitate << std::endl;
	out << pers.nrTelefon << std::endl;
	return out;
}

bool Persoana::operator==(const Persoana & ot)
{
	return CNP == ot.CNP;
}

Persoana & Persoana::operator=(const Persoana & ot)
{
	this->CNP = ot.CNP;
	this->numeComplet = ot.numeComplet;
	this->nrTelefon = ot.nrTelefon;
	this->localitate = ot.localitate;
	return *this;
}

int Persoana::hashCode() const
{
	auto copieCNP = CNP;
	int sumaCifreCNP{ 0 };
	while (copieCNP != 0) {
		sumaCifreCNP += copieCNP % 10;
		copieCNP /= 10;
	}
	return sumaCifreCNP;
}


