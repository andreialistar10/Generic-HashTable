#pragma once
#include<fstream>

#include "multime.h"
#include "persoana.h"
#include "exceptiiGenerice.h"

class Repository {
private:
	Multime<Persoana> multimePersoane;

public:

	Repository() : multimePersoane{ Multime<Persoana> () } {}
	Repository(const Repository& repo) = delete;

	virtual void adaugaPersoanaRepo(const Persoana& pers);
	bool existaPersoana(const Persoana& pers) noexcept;
	virtual void stergePersoanaRepo(const Persoana& pers);
	int getDimensiuneMultime() const noexcept;
	Multime<Persoana> getAllPersoaneRepo() const noexcept;
	Persoana cautaPersoanaRepo(const long long& CNP);

	~Repository() = default;
};

class RepoFromFile : public Repository {
private:
	void loadFromFile();
	void writeToFile();
	std::string fileN;
public:

	RepoFromFile(const std::string& fileN) : Repository(), fileN{ fileN } {
		loadFromFile();
	}

	void adaugaPersoanaRepo(const Persoana& pers) override {
		Repository::adaugaPersoanaRepo(pers);
		writeToFile();
	}
	void stergePersoanaRepo(const Persoana& pers) override {
		Repository::stergePersoanaRepo(pers);
		writeToFile();
	}

};

