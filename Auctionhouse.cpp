


#include "Auctionhouse.h"
#include "ItemMgt.h"
#include "AuctionMgt.h"
#include <iostream>


PGconn *Auctionhouse::ConnectDB()
{
	conn = NULL;
	conn = PQconnectdb("user=postgres password=root dbname=Auctionhouse hostaddr=127.0.0.1 port=5432");
	
	if (PQstatus(conn) != CONNECTION_OK)
    {
		printf("Connection to database failed\n");
		Closeconn(conn);
    }

	 // printf("\nConnection to database - OK\n");


  return conn;

}

void Auctionhouse::Closeconn(PGconn *conn)
{

	printf("Connection Closed - OK\n");
	PQfinish(conn);

}

void Auctionhouse::allocateLots(PGconn *conn)
{

	query.append("UPDATE item SET state='assigned', auctionno= ");
	query.append(ConvertInt(getAuctionno()));
	query.append(" WHERE lotno= ");
	query.append(convertInt(getLotno()));
	
  // Execute with sql statement
	PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
		printf("Lot has not been assigned\n");
        PQclear(res);
        Closeconn(conn);
    }

	printf("Lot has been assigned - OK\n");

  // Clear result
	PQclear(res);
	query.clear();
}


int Auctionhouse::listLotallocated(PGconn *conn)
{
	
	int nFields, nRows;
	PGresult *result  = PQexec(conn, "BEGIN");

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        PQclear(result);
		Closeconn(conn);
    }
	
	PQclear(result);

	   query.append("DECLARE listlot CURSOR FOR SELECT lotno, type, des, state, resp FROM item WHERE auctionno = ");
	   query.append(ConvertInt(getAuctionno()));
	   query.append(" ORDER BY lotno");

    // Fetch rows from item table
	   result = PQexec(conn, query.c_str());
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        printf("Declare item Cursor failed");
        PQclear(result);
        Closeconn(conn);
    }

      PQclear(result);

    result = PQexec(conn, "FETCH ALL in listlot");

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        printf("FETCH ALL failed");
        PQclear(result);
        Closeconn(conn);
    } 

    // Get the column field name
    nFields = PQnfields(result);

	    printf("Lots Allocated to an Auction: ");
		printf("\n-----------------------------------------------------------\n");
		for (int i = 0; i < nFields; i++)
		{
			printf("%-15s", PQfname(result, i));
		}

			printf("\n-----------------------------------------------------------\n");

			nRows = PQntuples(result);
    for (int i = 0; i < PQntuples(result); i++)
    {
        for (int j = 0; j < nFields; j++)
		{
            printf("%-15s", PQgetvalue(result, i, j));
		}
	     	printf("\n");
    }
  
    PQclear(result);

     result = PQexec(conn, "CLOSE listlot");
     PQclear(result);

     result = PQexec(conn, "END");

  // Clear result
     PQclear(result);
	 query.clear();
	 return nRows;

}


void Auctionhouse::saleProcess(PGconn *conn)

{

	int rows;

	query.append("SELECT * FROM item WHERE lotno=");
	query.append(convertInt(getLotno()));
	query.append(" AND resp <= ");
	query.append(ConvertInt(getHamprice()));
	  
	 PGresult *result = PQexec(conn, query.c_str());

     rows = PQntuples(result);
	 PQclear(result);
	 query.clear();
	 

	if(rows == 0)
	{
		query.append("UPDATE item SET state='unassigned', auctionno=null WHERE lotno=");
		query.append(convertInt(getLotno()));
		PGresult *result = PQexec(conn, query.c_str());
		if (PQresultStatus(result) != PGRES_COMMAND_OK)
		{
			printf("Sale simulation failed\n");
			PQclear(result);
			Closeconn(conn);
	    }
		PQclear(result);
		query.clear();
		printf("Reserve price has not been met\n");

	}
	else
	{
		query.append("UPDATE item SET state='sold', hamp=");
		query.append(ConvertInt(getHamprice()));
		query.append(", comm=");
		query.append(ConvertInt(getCommission()));
		query.append(", vat=");
		query.append(ConvertInt(getVat()));
		query.append(", cusp=");
		query.append(ConvertInt(getcustPayment()));
		query.append(", auctionno=null");
		query.append(" WHERE lotno=");
		query.append(convertInt(getLotno()));

		PGresult *result = PQexec(conn, query.c_str());

		if (PQresultStatus(result) != PGRES_COMMAND_OK)
		{
			printf("Sale simulation failed");
			PQclear(result);
		}
		PQclear(result);
		query.clear();
		printf("The lot has been sold\n");

	}

		query.append("UPDATE auction SET state='past' WHERE auctionno= ");
		query.append(ConvertInt(getAuctionno()));

		result = PQexec(conn, query.c_str());
		if(PQresultStatus(result) != PGRES_COMMAND_OK)
		{
			printf("Auction table Update failed\n");
			PQclear(result);
			Closeconn(conn);
		}
		PQclear(result);
		query.clear();

}


