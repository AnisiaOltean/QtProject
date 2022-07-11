#pragma once
#include <string>
using std::string;

class DTO {
private:
	string tip;
	int nr;
public:
	DTO() = default;
	DTO(string tip, int nr) :tip{ tip }, nr{ nr }{};

	DTO(const DTO& ot) :tip{ ot.tip }, nr{ ot.nr }{};

	string getTip() {
		return this->tip;
	}

	int getNr() {
		return this->nr;
	}
};


