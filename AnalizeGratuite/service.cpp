#include "service.h"

Persoana Service::creeazaPersoana(const std::string & CNP, const std::string & numeComplet, const std::string & localitate, const std::string & nrTelefon)
{
	validator.validare(CNP, numeComplet, localitate, nrTelefon);
	long long CNPnr = std::atoll(CNP.c_str());
	return Persoana(CNPnr, numeComplet, localitate, nrTelefon);
}

Multime<Persoana> Service::getAllPersoaneService() const noexcept
{
	return repo.getAllPersoaneRepo();
}

void Service::adaugaService(const Persoana & pers)
{
	repo.adaugaPersoanaRepo(pers);
	modificare();
}

void Service::stergeService(const Persoana & pers)
{
	repo.stergePersoanaRepo(pers);
	modificare();
}

Persoana Service::cautaPersoanaPeCNP(const std::string & cnp)
{
	validator.validareLongLong(cnp,"CNP-ul");
	const auto CNP = std::atoll(cnp.c_str());
	return repo.cautaPersoanaRepo(CNP);
}

int  Service::getNrTotalPersoane() const noexcept
{
	return repo.getDimensiuneMultime();
}
