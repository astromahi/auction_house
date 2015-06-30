


#ifndef AUCTION_H
#define AUCTION_H
#include <string>


class Auction
{

private:

	int auctionno;
	int hamprice;
	std::string date;
	std::string slot;
	std::string state;

public:

	Auction() { }
	~Auction() { }
	void setAuctionno(std::istream&, std::ostream&);
	int getAuctionno(void) const;
	void setDate(std::istream&, std::ostream&);
	std::string getDate(void) const;
	void setSlot(std::istream&, std::ostream&); 
	std::string getSlot(void) const;
	void setState(std::istream&, std::ostream&);
	std::string getState(void) const;
	void setHamprice(std::istream&);
	int getHamprice(void) const;

};
#endif