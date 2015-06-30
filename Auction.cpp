


#include "Auction.h"
#include <iostream>


void Auction::setAuctionno(std::istream& in, std::ostream& out)
{
	out << "Enter Auction no : ";
	in >> auctionno;
}

int Auction::getAuctionno(void) const
{
	return auctionno;
}

void Auction::setDate(std::istream& in, std::ostream& out)
{
	out << "Enter Date : ";
	in >> date;
}

std::string Auction::getDate(void) const
{
	return date;
}

void Auction::setSlot(std::istream& in, std::ostream& out)
{
	out << "Enter Slot(am/pm) : ";
	in >> slot;
}

std::string Auction::getSlot(void) const
{
	return slot;
}

void Auction::setState(std::istream& in, std::ostream& out)
{
	out << "Enter State : ";
	in >> state;
}

std::string Auction::getState(void) const
{
	return state;
}

void Auction::setHamprice(std::istream& in)
{
	printf(" Enter your Bid : ");
	in >> hamprice;
}

int Auction::getHamprice(void) const 
{
	return hamprice;
}







