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