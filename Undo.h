#pragma once
#include "activitate.h"
#include "Repo.h"
#include <vector>
using std::vector;

class ActiuneUndo {
public:
	virtual void doUndo() = 0;
	virtual ~ActiuneUndo() = default;
};

class UndoAdauga : public ActiuneUndo {
private:
	Activitate actAdaugata;
	ActivitateRepo& repo;
public:
	UndoAdauga(ActivitateRepo& repo, const Activitate& a) : repo{ repo }, actAdaugata{ a }{}
	void doUndo() override {
		repo.delete_by_titlu(actAdaugata.getTitlu());
	}
};

class UndoSterge : public ActiuneUndo {
private:
	vector<Activitate> actSterse;
	ActivitateRepo& repo;
public:
	UndoSterge(ActivitateRepo& repo, const vector<Activitate>& acts) : repo{ repo }, actSterse{ acts }{}
	void doUndo() override {
		for (const auto& a : actSterse)
			repo.store(a);
	}
};

class UndoModifica : public ActiuneUndo {
	Activitate actModif;
	ActivitateRepo& repo;
public:
	UndoModifica(ActivitateRepo& repo, const Activitate& a) : repo{ repo }, actModif{ a }{}
	void doUndo() override {
		repo.modifica(actModif.getTitlu(), actModif.getDescriere(), actModif.getTip(), actModif.getDurata());
	}
};

