#pragma once
#include<string>
#define MAXIM 23

//functia de hash pentru nr intregi
inline int hashCodeINT(const int& nr) {
	auto copieNR = nr;
	int sumaCifre{ 0 };
	while (copieNR != 0) {
		sumaCifre += copieNR % 10;
		copieNR /= 10;
	}
	return sumaCifre;
}

inline int hashCodeSTRING(const std::string& str) {

	return str.size();
}

template<typename TElement>
class Multime;

template<typename TElement>
class IteratorMultime;

template<typename TElement>
class TNod {
private:
	TElement element;
	TNod<TElement>* urmator;
public:
	friend class Multime<TElement>;
	friend class IteratorMultime<TElement>;
	TNod(const TElement& element, TNod<TElement>* urmator) : element{ element }, urmator{ urmator } {}
};

//Multime pe tabela de dispersie rezolvare coliziuni prin liste independete
template<typename TElement>
class Multime {
private:
	int maxim;
	TNod<TElement>* lista[MAXIM];
	int functieDispersie(const TElement& element);

	//Functia de hashCode pentru elementul de tip TElement
public:
	//constructor multime
	Multime<TElement>();
	//functia de adaugare a unui element
	void adaugaElement(const TElement el);

	//functia de stergere a unui element
	void stergeElement(const TElement el);

	//functia de cautare a unui element
	bool cautaElement(const TElement el) noexcept;

	//functia de returnare a dimensiunii multimii
	int dimensiune() const noexcept;

	//functia returneaza true daca multimea este vida si false altfel
	bool vida();

	//se returneaza iteratorul pe multime
	IteratorMultime<TElement> iterator() const noexcept;
	friend IteratorMultime<TElement>;

	//destructorul multimii
	~Multime<TElement>();

	//Pentru a rezolva problema in stil POO

	Multime<TElement>(const Multime<TElement>& ot) noexcept;

	Multime<TElement>(const Multime<TElement>&& ot) noexcept;

	IteratorMultime<TElement> begin();
	IteratorMultime<TElement> end();
};
template<typename TElement>
Multime<TElement>::Multime()
{
	maxim = MAXIM;
	//Initializam lista la una vida
	for (int i = 0; i < maxim; ++i)
		lista[i] = NULL;
}

template<typename TElement>
int Multime<TElement>::functieDispersie(const TElement& element)
{
	return element.hashCode() % maxim;
}
template<>
inline int Multime<int>::functieDispersie(const int& element)
{
	return hashCodeINT(element);
}

template<>
inline int Multime<std::string>::functieDispersie(const std::string& str)
{
	return hashCodeSTRING(str);
}

template<typename TElement>
void Multime<TElement>::adaugaElement(const TElement el)
{
	//verificam daca exista elementul in multime si il adaugam in caz negativ
	if (!cautaElement(el)) {

		TElement element = el;
		//aflam pozitia in lista cu functia de dispersie
		int poz = functieDispersie(element);
		//creem un nou nod ce contine valoarea elementului si il adaugam in capul listei de pe pozitia poz
		TNod<TElement>* nodElement = new TNod<TElement>(element, NULL);
		nodElement->urmator = lista[poz];
		lista[poz] = nodElement;
	}
}

template<typename TElement>
void Multime<TElement>::stergeElement(const TElement el)
{
	//verificam daca exista elementul in multime si il eliminam in caz afirmativ
	if (cautaElement(el)) {
		TElement element = el;
		//aflam pozitia pe care elementul apare in lista, folosind functia de dispersie
		int poz = functieDispersie(element);
		TNod<TElement>* nodElement = lista[poz];
		TNod<TElement>* nodElementUrmator = lista[poz]->urmator;
		if (nodElement->element == el) {
			delete nodElement;
			lista[poz] = nodElementUrmator;
			return;
		}
		while (nodElementUrmator->urmator != NULL)
		{
			if (nodElementUrmator->element == el) {
				nodElement->urmator = nodElementUrmator->urmator;
				delete nodElementUrmator;
				return;
			}
			nodElement = nodElement->urmator;
			nodElementUrmator = nodElementUrmator->urmator;
		}
		delete nodElementUrmator;
		nodElement->urmator = NULL;
	}
}

template<typename TElement>
bool Multime<TElement>::cautaElement(const TElement el) noexcept
{
	TElement element = el;
	//aflam pozitia pe care ar trebui sa o ocupe elementul in lista din multime
	int poz = functieDispersie(element);
	//cautam elementul in lista l[poz].

	TNod<TElement>* nodElementCautat = lista[poz];
	while (nodElementCautat != NULL) {
		if (nodElementCautat->element == el)
			return true;
		nodElementCautat = nodElementCautat->urmator;
	}
	return false;
}

template<typename TElement>
int Multime<TElement>::dimensiune() const noexcept
{
	int dim{ 0 };
	for (int i = 0; i < maxim; ++i) {
		TNod<TElement>* nodCurent = lista[i];
		while (nodCurent != NULL) {
			dim++;
			nodCurent = nodCurent->urmator;
		}
	}
	return dim;
}

template<typename TElement>
bool Multime<TElement>::vida()
{
	for (int i = 0; i < maxim; ++i)
		if (lista[i] != NULL)
			return false;
	return true;
}

template<typename TElement>
IteratorMultime<TElement> Multime<TElement>::iterator() const noexcept
{
	return IteratorMultime<TElement>(*this);
}

template<typename TElement>
Multime<TElement>::~Multime()
{
	//eliberam memoria
	for (int i = 0; i < maxim; ++i) {
		while (lista[i] != NULL) {
			TNod<TElement>* nod = lista[i];
			lista[i] = lista[i]->urmator;
			delete nod;
		}
	}
}

//Pentru stil POO multime

template<typename TElement>
IteratorMultime<TElement> Multime<TElement>::begin()
{
	return IteratorMultime<TElement>(*this);
}

template<typename TElement>
IteratorMultime<TElement> Multime<TElement>::end()
{
	IteratorMultime<TElement> it(*this);

	/*int ultimaPoz = 0;
	for (int i = 0; i < maxim; ++i)
		if (lista[i] != NULL)
			ultimaPoz = i;
	TNod<TElement>* ultimulNod = lista[ultimaPoz];
	while (ultimulNod != NULL)
		ultimulNod = ultimulNod->urmator;
	it.pozCurent = ultimaPoz;
	it.curent = ultimulNod;*/

	it.curent=NULL;
	return it;
}

template<typename TElement>
Multime<TElement>::Multime(const Multime<TElement>& ot) noexcept
{
	maxim = ot.maxim;
	for (int i = 0; i < maxim; ++i) {
		if (ot.lista[i] == NULL) {
			lista[i] = NULL;
			continue;
		}
		TNod<TElement>* nodOt = ot.lista[i];
		lista[i] = new TNod<TElement>(nodOt->element, NULL);
		TNod<TElement>* nodListaThis = lista[i];
		while (nodOt->urmator != NULL)
		{
			nodOt = nodOt->urmator;
			TNod<TElement>* nodNou = new TNod<TElement>(nodOt->element, NULL);
			nodListaThis->urmator = nodNou;
			nodListaThis = nodListaThis->urmator;
		}
	}
}

template<typename TElement>
Multime<TElement>::Multime(const Multime<TElement>&& ot) noexcept
{
	maxim = ot.maxim;
	functieDispersie = ot.functieDispersie;
	for (int i = 0; i < maxim; ++i) {
		lista[i] = ot.lista[i];
		ot.lista[i] = nullptr;
	}
}

//Iterator pe multime
template<typename TElement>
class IteratorMultime {
private:
	const Multime<TElement>& multime;
	int pozCurent;
	TNod<TElement>* curent;

	//Constructorul iteratorului
	IteratorMultime<TElement>(const Multime<TElement>& multime);

	//gaseste prima lista inlantuita nevida incepand cu locatia poz din tabela de dispersie
	void deplasare();
public:


	//reseteaza pozitia iteratorului la inceputul multimii
	void prim();

	//muta iteratorul pe pozitia urmatoare in multime
	void urmator();

	//verifica daca iteratorul indica un element al multimii
	bool valid() const;

	//returneaza valoarea curenta a elementului din multime
	TElement& element() const;

	friend class Multime<TElement>;

	//Pentru POO
	//Suprascriem operatorii pentru a putea itera multimea cu for in range
	TElement& operator*();
	IteratorMultime<TElement> operator++();
	bool operator==(const IteratorMultime<TElement>& ot) noexcept;
	bool operator!=(const IteratorMultime<TElement>& ot) noexcept;
};

template<typename TElement>
void IteratorMultime<TElement>::deplasare()
{
	while (pozCurent < multime.maxim && multime.lista[pozCurent] == NULL)
		pozCurent++;
	if (pozCurent < multime.maxim)
		curent = multime.lista[pozCurent];
}

template<typename TElement>
IteratorMultime<TElement>::IteratorMultime(const Multime<TElement>& multime) : multime{ multime }
{
	pozCurent = 0;
	deplasare();
}

template<typename TElement>
void IteratorMultime<TElement>::prim()
{
	pozCurent = 0;
	deplasare();
}

template<typename TElement>
void IteratorMultime<TElement>::urmator()
{
	curent = curent->urmator;
	if (curent == NULL)
	{
		pozCurent++;
		deplasare();
	}
}

template<typename TElement>
bool IteratorMultime<TElement>::valid() const
{
	return (pozCurent < multime.maxim && curent != NULL);
}

template<typename TElement>
TElement& IteratorMultime<TElement>::element() const
{
	return curent->element;
}

//Pentru stil POO iterator (ne ajuta pentru a itera cu for in range)

template<typename TElement>
TElement& IteratorMultime<TElement>::operator*()
{
	return element();
}

template<typename TElement>
IteratorMultime<TElement> IteratorMultime<TElement>::operator++()
{
	urmator();
	return (*this);
}

template<typename TElement>
bool IteratorMultime<TElement>::operator==(const IteratorMultime<TElement>& ot) noexcept
{
	if (ot.curent == NULL && curent != NULL)
		return false;
	if (ot.curent == NULL && curent == NULL)
		return true;
	return (ot.curent->element == curent->element);
}

template<typename TElement>
bool IteratorMultime<TElement>::operator!=(const IteratorMultime<TElement>& ot) noexcept
{
	return !(*this == ot);
}