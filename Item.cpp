


#include "Item.h"


void Item::setLotno(std::istream& in, std::ostream& out)
{
	out << "Enter Lot no : ";
	in >> lotno;
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int Item::getLotno(void) const
{
	return lotno;
}

void Item::setDescription(std::istream& in, std::ostream& out)
{
	out << "Enter Description of Item : ";
	getline (in, description);
}

std::string Item::getDescription(void) const
{
	return description;
}

void Item::setType(std::istream& in, std::ostream& out)
{
	
	out << "Enter Type of Item : ";
	getline(in, type);
}

std::string Item::getType(void) const
{
	return type;
}

void Item::setItemstate(std::istream& in, std::ostream& out)
{
	out << "Enter State of Item : ";
	getline (in, itemstate);
}

std::string Item::getItemstate(void) const
{
	return itemstate;
}

void Item::setResprice(std::istream& in, std::ostream& out)
{
	out.flush();
	out << "Enter Reserve Price : ";
	in >> resprice;
}

int Item::getResprice(void) const
{
	return resprice;
}



