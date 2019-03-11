#include "repository.h"

void Repository::adaugaPersoanaRepo(const Persoana & pers)
{
	if (multimePersoane.cautaElement(pers))
		throw Exceptii<Repository>(pers.getNumeComplet() + " este deja inscris/a in setul gratuit de analize!");
	multimePersoane.adaugaElement(pers);
}

bool Repository::existaPersoana(const Persoana & pers) noexcept
{
	return multimePersoane.cautaElement(pers);
}

void Repository::stergePersoanaRepo(const Persoana & pers)
{
	if (!multimePersoane.cautaElement(pers))
		throw Exceptii<Repository>(pers.getNumeComplet() + " nu este inscris/a in setul gratuit de analize!");
	multimePersoane.stergeElement(pers);
}

int Repository::getDimensiuneMultime() const noexcept
{
	return multimePersoane.dimensiune();
}

Multime<Persoana> Repository::getAllPersoaneRepo() const noexcept
{
	return multimePersoane;
}

Persoana Repository::cautaPersoanaRepo(const long long & CNP)
{
	for (const auto& pers : multimePersoane)
		if (pers.getCNP() == CNP)
			return pers;
	throw Exceptii<Repository>("Nu exista nicio persoana cu CNP-ul dat! ");
}

void RepoFromFile::loadFromFile()
{
	std::ifstream in(fileN);
	if (!in.is_open())
		throw Exceptii<RepoFromFile>("Fisierul " + fileN + " nu exista pe disk!");
	while (!in.eof()) {
		long long CNP{ 0 };
		std::string numeComplet, localitate, nrTelefon;
		in >> CNP;
		in.ignore();
		std::getline(in, numeComplet, '\n');
		std::getline(in, localitate, '\n');
		std::getline(in, nrTelefon, '\n');
		if (in.eof())
			break;
		Repository::adaugaPersoanaRepo(Persoana(CNP, numeComplet, localitate, nrTelefon));
	}
	in.close();
}

void RepoFromFile::writeToFile()
{
	std::ofstream out(fileN);
	for (const auto& persoana : getAllPersoaneRepo()) {
		out << persoana;
	}
}
