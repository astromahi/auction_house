

#include "libpq-fe.h"
#include "Auction.h"
#include "Item.h"
#include "Auctionhouse.h"
#include "ItemMgt.h"
#include "AuctionMgt.h"
#include <iostream>
#include <string>

using namespace std;

void fmain(void);
void f01main(void);
void f02main(void);
void f03main(void);
void f04main(void);
void f05main(void);

PGconn *conn = NULL;
bool menu = false;


int main(void)
{
	
	cout <<endl;
	Auctionhouse db;;
	cout << "AUCTION and LOT Maintenance System";
	conn = db.ConnectDB();
	cout <<endl;
	fmain();
	db.Closeconn(conn);
	return 0;
}


void fmain(void)
{

	std::string choice;
	cout << "+++++++++++++++++++++++++++++++++++++++++++\n";
    cout << "F01 - Listing of Auction & Lots.\n";
    cout << "F02 - Add/Delete of Auction & Lots.\n";
    cout << "F03 - Allocate Lots to Auction.\n";
    cout << "F04 - List lots allocated to particular auction.\n";
    cout << "F05 - The Sale Process.\n";
	cout << "  E - Exit.\n" <<endl;
    cout << " Enter Option : ";
    cin >> choice;
	if(choice.compare("F01") == 0 || choice.compare("f01") == 0 )
	{
		 f01main();
	}
	else if (choice.compare("F02") == 0 || choice.compare("f02") == 0)
	{
		 f02main();
	}
	else if (choice.compare("F03") == 0 || choice.compare("f03") == 0)
	{
		 f03main();
	}
	else if (choice.compare("F04") == 0 || choice.compare("f04") == 0)
	{
		 f04main();
	}
	else if (choice.compare("F05") == 0 || choice.compare("f05") == 0)
	{
		 f05main();
	}
	else if (choice.compare("E") == 0 || choice.compare("e") == 0)
	{
		exit(0);
	}
}

void f01main(void)
{
	//listing of auction and lots
	Auctionhouse db;
	int option;
	cout <<endl;
	cout << "------F01 Listing Auctions & Lots------\n";
	cout << "1. List Auctions\n";
	cout << "2. List Lots\n";
	cout << "3. Main Menu\n" <<endl;
	cout << " Enter Option : ";
	cin >> option;
	cout <<endl;
	switch (option)
	{
	case 1:
		
		db.listAuctions(conn);
		menu = true;
		break;

	case 2:

		db.listLots(conn);
		menu = true;
		break;

	case 3:

		fmain();
		menu = false;
		break;
	}

	if(menu)
	{
		f01main();
	}
}

void f02main(void)
{
	//Add/Delete Auction or lot
	Auctionhouse db;
	int choice;
	cout <<endl;
	cout << "------F02 Add/Delete Auction or Lot------\n";
	cout << "1. Add Auction\n";
	cout << "2. Add Lot\n";
	cout << "3. Delete Auction\n";
	cout << "4. Delete Lot\n";
	cout << "5. Main Menu\n" <<endl;
	cout << " Enter option : ";
	cin >> choice;
	cout <<endl;
	switch (choice)
	{
	case 1:
		
		db.setAuctionno(cin, cout);
		db.setDate(cin, cout);
		db.setSlot(cin, cout);
	    db.setState(cin, cout);
		db.addAuctiontoDB(conn);
		menu = true;
		break;

	case 2:

		 db.setLotno(cin, cout);
		 db.setType(cin, cout);
		 db.setDescription(cin, cout);
		 db.setItemstate(cin, cout);
		 db.setResprice(cin, cout);
		 db.addItemtoDB(conn);
		 menu = true;
		 break;

	case 3:

		db.setAuctionno(cin, cout);
		db.deleteAuction(conn);
		menu = true;
		break;

	case 4:

		db.setLotno(cin, cout);
		db.deleteItem(conn);
		menu = true;
		break;
	case 5:
		fmain();
		menu = false;
		break;
	}

	if(menu)
	{
		f02main();
	}
}

void f03main(void)

{
	//Allocate lots to auction
	Auctionhouse db;
	int option;
	cout <<endl;
	cout << "------F03 Allocate Lot to Auction------\n";
	cout << "1. Available Auctions & Lots\n";
	cout << "2. Main Menu\n" <<endl;
	cout << " Enter Option : ";
	cin >> option;
	cout <<endl;
	switch (option)
	{
	case 1:
		
		db.listAuctions(conn);
		cout <<endl;
		db.listLots(conn);
		cout <<endl;
		db.setLotno(cin, cout);
		db.setAuctionno(cin, cout);
		db.allocateLots(conn);
		menu = true;
		break;

	case 2:

		fmain();
		menu = false;
		break;
	}

	if(menu)
	{
		f03main();
	}
}

void f04main(void)
{
	Auctionhouse db;
	int option;
	cout <<endl;
	cout << "---F04 - List lots allocated to a particular auction---\n";
	cout << "1. List lots Allocated\n";
	cout << "2. Main Menu\n" <<endl;
	cout << " Enter Option : ";
	cin >> option;
	cout <<endl;
	switch (option)
	{
	case 1:
		
		db.listAuctions(conn);
		cout <<endl;
		db.setAuctionno(cin, cout);
		db.listLotallocated(conn);
		menu = true;
		break;

	case 2:

		fmain();
		menu = false;
		break;
	}

	if(menu)
	{
		f04main();
	}
}

void f05main(void)
{
	Auctionhouse db;
	int option, rows = 0;
	cout <<endl;
	cout << "---F05 - Simulate Sale Process---\n";
	cout << "1. Sale Process\n";
	cout << "2. Main Menu\n" <<endl;
	cout << " Enter Option : ";
	cin >> option;
	cout <<endl;
	switch (option)
	{
	case 1:
		db.setAuctionno(cin, cout);
	    rows = db.listLotallocated(conn);
		//printf(" N-main tuples : %d", rows);
		for (int i=0; i<rows; i++)
		{
			db.setLotno(cin, cout);
			db.setHamprice(cin);
			db.saleProcess(conn);
		}
		cout<<endl;
		menu = true;
	case 2:
		fmain();
		menu = false;
	}

	if(menu)
	{
		f05main();
	}

}

