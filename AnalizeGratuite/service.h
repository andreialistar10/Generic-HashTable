#pragma once
#include "repository.h"
#include "validator.h"
#include "observer.h"

class Service:public Observable {
private:
	Repository& repo;
	Validator validator;
public:
	Service(Repository& repo, const Validator& validator) : repo{ repo }, validator{ validator } {}

	Persoana creeazaPersoana(const std::string& CNP, const std::string& numeComplet, const std::string& localitate, const std::string& nrTelefon);

	Multime<Persoana> getAllPersoaneService() const noexcept;

	void adaugaService(const Persoana& pers);

	void stergeService(const Persoana& pers);

	Persoana cautaPersoanaPeCNP(const std::string& cnp);

	int getNrTotalPersoane() const noexcept;

	~Service() = default;
};