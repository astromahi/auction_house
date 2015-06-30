


#include "Auction.h"
#include "AuctionMgt.h"
#include "Auctionhouse.h"
#include "libpq-fe.h"
#include <string>
#include <sstream>
#include <boost/lexical_cast.hpp>


std::string AuctionMgt::ConvertInt(int intno)
{
	strs = boost::lexical_cast<std::string>(intno);
	return strs;
}

int AuctionMgt::getCommission(void) const
{
	int commn = (getHamprice() * 10) / 100;
	return commn;

}

int AuctionMgt::getcustPayment(void) const
{
	int custpay = (getHamprice() - (getCommission() + getVat()));
	return custpay;
}

int AuctionMgt::getVat(void) const
{
	int vat = (getHamprice() * 20) / 100;
	return vat;
}


void AuctionMgt::addAuctiontoDB(PGconn *conn)
{

	query.append("INSERT INTO Auction VALUES (");
	query.append(ConvertInt(getAuctionno()));
	query.append(",'");
    query.append(getDate());
	query.append("','");
	query.append(getSlot());
	query.append("','");
	query.append(getState());
	query.append("')");
	PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
	{
		printf("Insert Auction record failed\n");
        PQclear(res);
    }

	printf("Insert Auction record - OK\n");
	PQclear(res);
}


void AuctionMgt::listAuctions(PGconn *conn)
{

	int nFields;

	PGresult *result  = PQexec(conn, "BEGIN");

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        PQclear(result);
		exit(0);
    }
	
	PQclear(result);

    result = PQexec(conn, "DECLARE auctionrec CURSOR FOR SELECT * FROM auction ORDER BY auctionno");
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        printf("Declare auction cursor failed");
        PQclear(result);
    }

    PQclear(result);

    result = PQexec(conn, "FETCH ALL in auctionrec");

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        printf("Fetch all failed");
        PQclear(result);
    }

    nFields = PQnfields(result);

	    printf("Available Auctions :");
		printf("\n----------------------------------------------------------\n");
		for (int i = 0; i < nFields; i++)
		{
			printf("%-15s", PQfname(result, i));
		}

			printf("\n---------------------------------------------------------\n");

    for (int i = 0; i < PQntuples(result); i++)
    {
        for (int j = 0; j < nFields; j++)
		{
            printf("%-15s", PQgetvalue(result, i, j));
		}
		printf("\n");
    }
	printf("---------------------------------------------------------\n");
  
    PQclear(result);

    result = PQexec(conn, "CLOSE auctionrec");
    PQclear(result);

    result = PQexec(conn, "END");

    PQclear(result);
}

void AuctionMgt::deleteAuction(PGconn *conn)
{

	query.append("DELETE FROM auction WHERE auctionno =");
	query.append(ConvertInt(getAuctionno()));

	PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Delete Auction record failed.");
        PQclear(res);
    }

  printf("\nDelete Auction record - OK\n");

  PQclear(res);
}


