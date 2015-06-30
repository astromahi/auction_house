


#ifndef ITEMMGT_H
#define ITEMMGT_H
#include "libpq-fe.h"
#include <sstream>
#include "Item.h"

class ItemMgt : public Item

{

private:

	std::string strings;
	std::string query;

public:

	ItemMgt() { }
	~ItemMgt() { }
	void addItemtoDB(PGconn *conn);
	std::string convertInt(int);
	std::string convertDouble(double);
	void listLots(PGconn *conn);
	void deleteItem(PGconn *conn);

};
#endif
