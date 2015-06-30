


#ifndef AUCTIONMGT_H
#define AUCTIONMGT_H
#include "libpq-fe.h"
#include <sstream>
#include "Auction.h"
#include <string>

class AuctionMgt : public Auction

{

private:

	std::string query; 
	std::string strs;

public:

	AuctionMgt() { }
	~AuctionMgt() { }
	std::string ConvertInt(int);
	int getCommission(void) const;
	int getcustPayment(void) const;
	int getVat(void) const;
	void addAuctiontoDB(PGconn *conn);
	void listAuctions(PGconn *conn);  
	void deleteAuction(PGconn *conn);

};
#endif
