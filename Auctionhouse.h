

#ifndef Auctionhouse_H
#define Auctionhouse_H
#include <string>
#include "libpq-fe.h"
#include "ItemMgt.h"
#include "AuctionMgt.h"

class Auctionhouse : public ItemMgt, public AuctionMgt
{

private:

	std::string query;
	PGconn *conn;

public:

	Auctionhouse() {  }
	~Auctionhouse() { }
	PGconn *ConnectDB();
	void Closeconn(PGconn *conn);
	void allocateLots(PGconn *conn);
	int listLotallocated(PGconn *conn);
	void saleProcess(PGconn *conn);

};
#endif