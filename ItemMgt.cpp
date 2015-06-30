

#include "Item.h"
#include "ItemMgt.h"
#include "Auctionhouse.h"
#include "libpq-fe.h"
#include <string>
#include <sstream>
#include <iostream>
#include <boost/lexical_cast.hpp>


std::string ItemMgt::convertInt(int intno)
{
	strings = boost::lexical_cast<std::string>(intno);
	return strings;
}

std::string ItemMgt::convertDouble(double dblno)
{
	strings = boost::lexical_cast<std::string>(dblno);
	return strings;
}

void ItemMgt::addItemtoDB(PGconn *conn)
{

	query.append("INSERT INTO item (lotno, type, des, state, resp) VALUES(");
	query.append(convertInt(getLotno()));
	query.append(",'");
    query.append(getType());
	query.append("','");
	query.append(getDescription());
	query.append("','");
	query.append(getItemstate());
	query.append("',");
	query.append(convertInt(getResprice()));
	query.append(")");
  
	PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)

    {
		printf("Insert Item record failed");
        PQclear(res);
    }

	printf("Insert Item record - OK\n");
	 
  // Clear result
	PQclear(res);
	query.clear();
}


void ItemMgt::listLots(PGconn *conn)
{

	int nFields;
	PGresult *result  = PQexec(conn, "BEGIN");

    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        PQclear(result);
		exit(0);
    }
	
	PQclear(result);
	query.append("DECLARE itemrec CURSOR FOR SELECT lotno,type,des,state,resp,hamp,comm,cusp,vat FROM item ORDER BY lotno");
   
	result = PQexec(conn, query.c_str() );
    if (PQresultStatus(result) != PGRES_COMMAND_OK)
    {
        printf("Declare item Cursor failed");
        PQclear(result);
    }

    PQclear(result);

    result = PQexec(conn, "FETCH ALL in itemrec");

    if (PQresultStatus(result) != PGRES_TUPLES_OK)
    {
        printf("FETCH ALL failed");
        PQclear(result);
    }

    nFields = PQnfields(result);

	    printf("Available Lots : ");
		printf("\n-----------------------------------------------------------\n");
		for (int i = 0; i < nFields; i++)
		{
			printf("%-15s", PQfname(result, i));
		}

			printf("\n-----------------------------------------------------------\n");

    for (int i = 0; i < PQntuples(result); i++)
    {
        for (int j = 0; j < nFields; j++)
		{
            printf("%-15s", PQgetvalue(result, i, j));
		}
		printf("\n");
    }
  
    PQclear(result);

    result = PQexec(conn, "CLOSE itemrec");
    PQclear(result);

    result = PQexec(conn, "END");

    PQclear(result);
	query.clear();
}

void ItemMgt::deleteItem(PGconn *conn)
{

	query.append("DELETE FROM item WHERE lotno = ");
	query.append(convertInt(getLotno()));

	std::cout<<"Query is : " << query;

	PGresult *res = PQexec(conn, query.c_str());

    if (PQresultStatus(res) != PGRES_COMMAND_OK)
    {
        printf("Delete Lot failed.");
        PQclear(res);
    }

  printf("\nDelete lot - OK\n");
  PQclear(res);
}


