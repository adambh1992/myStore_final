/*
 * ===================================================================
 *
 *       Filename:  database.h
 *
 *    Description:  Declaring MySQL class for using database.
 *
 *        Created:  Friday 22 February 2013 12:48:40  IST
 *       Compiler:  gcc
 *
 *         Author:  Mandeep Kaur, meghasimak@gmail.com
 *        License:  GNU General Public License
 *      Copyright:  Copyright (c) 2013, Great Developers
 *
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  Include database-detail.h and other files
 *------------------------------------------------------------------*/

#include "header.h"
#include "database-detail.h"

/**
 * ===================================================================
 *        Class:  MySQL
 *  Description:  MySQL class for database accessability
 * ===================================================================
 */

class MySQL
{
    protected:
        /** MySQL connectivity Variables */
        MYSQL *connect;
        MYSQL_RES *res_set;
        MYSQL_ROW row;

        unsigned int i;

    public:
        /** MySQL Constructor */
        MySQL();

        /** Function to show tables in database */
        void ShowTables();
        // 1
        void IsBookInStock();
        // 2
        void SelectOldestCustomer();
        //3
        void SelectOldestBookinStock();
        //4
        void CurrentOrders();
        // 5
        void BookSumSold();
        // 6 missing

        // 7 
        void Top3CustomerOrder();
        //8 
        void BiggestBookTranslate();
        // 9
        void CustomerDeliverdHistory();
        // 10
        void CustomerOrdersHistory();
        // 11 
        void CalcShipments();
        // 12 missing

        // 13 
        void CheckOrderStatusById();
        // 14 
        void SumXpressShipmentBetweenDates();
        // 15
        void SumBitPatmentsBetweenDates();
        // 16 
        void DealAboveAvg12Months();
        // 17 
        void ShipmentByCompanyLastYear();
        // 18 missing

        // 19
        void CustomerNotOrederLast24Month();
        // 20 missing

        // 21 
        void BookInStorage();
        // 22
        void StoreBuingBooksBteweenDates();
        // 23

        // 24
        void avgMonthlyOrders();
        // 25
        void EmpSalaryByMonth();
        // 26
        void BestSeller();





        void MaxSold();
        string MonthByNumber(int x);

        

        void CreateCustomer();

        string IsCountry(string name);

        string IsCity(string name, string country_id);

        string IsAddress(string name,string pscode, string city_id);

        MYSQL_RES* executeQuery(string query);

        /** MySQL Destructor */
        ~MySQL();
};
