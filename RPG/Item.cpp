#include "Item.h"

Item::Item() {

}

void Item::use(Player *p) {

}

void Item::use(Player *p, std::string *str) {
	
}

void Item::changeIsEquript() {
	if (this->isEquipt) {
		this->isEquipt = false;
	}
	else {
		this->isEquipt = true;
	}
}

void Item::setDescription() {
	this->description += "\n\nw“ü: " + std::to_string(this->buyGold);
	this->description += "\n”„‹p: " + std::to_string(this->sellGold);
}