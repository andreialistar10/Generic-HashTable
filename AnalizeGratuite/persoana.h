#pragma once
#include <string>
#include <fstream>

class Persoana {
private:
	long long CNP;
	std::string numeComplet;
	std::string localitate;
	std::string nrTelefon;
public:
	Persoana() = default;
	Persoana(const long long& CNP, const std::string& numeComplet, const std::string& localitate, const std::string& nrTelefon) :
		CNP{ CNP }, numeComplet{ numeComplet }, localitate{ localitate }, nrTelefon{ nrTelefon } {}
	Persoana(const Persoana& pers) : CNP{ pers.CNP }, numeComplet{ pers.numeComplet }, localitate{ pers.localitate }, nrTelefon{ pers.nrTelefon } {}
	const long long& getCNP() const {
		return CNP;
	}
	const std::string& getNumeComplet() const {
		return numeComplet;
	}
	const std::string& getLocalitate() const {
		return localitate;
	}
	const std::string& getNrTelefon() const {
		return nrTelefon;
	}
	bool operator==(const Persoana& ot);
	Persoana& operator=(const Persoana& ot);
	friend std::ostream& operator<<(std::ostream& out, const Persoana& pers);
	int hashCode() const;
};