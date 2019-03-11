#pragma once
#include <vector>
#include "multime.h"
class Observer {
public:
	virtual void update() = 0;
};

class Observable {
private:
	std::vector<Observer*> listaObserver;
	//Multime<Observer*> listaObserver;
	void notify() {
		for (auto& observer : listaObserver)
			observer->update();
	}
public:
	void addObserver(Observer* observer) {
		//listaObserver.adaugaElement(observer);
		listaObserver.push_back(observer);
	}
	void modificare() {
		notify();
	}
};