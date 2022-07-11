#pragma once

#include "activitate.h"
#include <vector>
#include <string>

using std::vector;
using std::string;

class ValidationException {

private:
	vector<string> ListaErori;
public:
	ValidationException(vector <string> errmsg) : ListaErori{ errmsg } {}
	string getErrMsg() {
		string err = "";
		for (const string e : ListaErori)
		{
			err += e + '\n';
		}
		return err;
	}
};

/* Valideaza un obiect activitate*/
class ActivitateValidator {
private:
public:
	void valideaza(const Activitate& a)
	{
		vector<string> errors;
		if (a.getTitlu() == "") errors.push_back("Titlul nu poate fi vid!");
		if (a.getDescriere() == "") errors.push_back("Descrierea nu poate fi vida!");
		if (a.getTip() == "") errors.push_back("Tipul nu poate fi vid!");
		if (a.getDurata() < 0) errors.push_back("Durata trebuie sa fie pozitiva!");
		else
			if (a.getDurata() - static_cast<int>(a.getDurata()) > 0.59)
				errors.push_back("Formatul duratei este invalid!");

		if (errors.size() > 0)
			throw ValidationException(errors);
	}
};




