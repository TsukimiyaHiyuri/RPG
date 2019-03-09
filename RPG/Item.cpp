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
	if (this->canEquip) {
		this->description += "\n\nUŒ‚—Í: +" + std::to_string(this->str);
		this->description += "\n–hŒä—Í: +" + std::to_string(this->def);
	}
	this->description += "\n\nw“ü: " + std::to_string(this->buyGold);
	this->description += "\n”„‹p: " + std::to_string(this->sellGold);
}