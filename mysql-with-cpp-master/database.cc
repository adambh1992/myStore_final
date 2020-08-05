/*
 * ===================================================================
 *
 *       Filename:  database.cc
 *
 *    Description:  Definition of MySQL Class for accessing database
 *
 *        Created:  Friday 22 February 2013 02:07:49  IST
 *       Compiler:  gcc
 *
 *         Author:  Mandeep Kaur, meghasimak@gmail.com
 *        License:  GNU General Public License
 *      Copyright:  Copyright (c) 2013, Great Developers
 *
 * ===================================================================
 */

/**-------------------------------------------------------------------
 *  Include mysql.h file local header file(declaration of class)
 *------------------------------------------------------------------*/

#include "database.h"

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: MySQL()
 * Description:  Constructor to initialize database conectivity
 *--------------------------------------------------------------------
 */

MySQL :: MySQL()
{
    connect = mysql_init(NULL);
    if ( !connect )
    {
        cout << "MySQL Initialization Failed";
    }   

    connect = mysql_real_connect(connect, SERVER, USER, PASSWORD, DATABASE, 0,NULL,0);
    
    if ( connect )
    {
        cout << "Connection Succeeded\n";
    }
    
    else
    {
        cout << "Connection Failed\n";
    }
}

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: ShowTables()
 * Description:  Show tables in database
 
 *--------------------------------------------------------------------
 */





void MySQL :: ShowTables()
{
    /** Add MySQL Query */
    mysql_query (connect,"show tables");                              
                                                                          
    i = 0;
                                                                         
    res_set = mysql_store_result(connect);                              
                                                                          
    unsigned int numrows = mysql_num_rows(res_set);                   
                                                                          
    cout << " Tables in " << DATABASE << " database " << endl;        
                                                                         
    while (((row=mysql_fetch_row(res_set)) != NULL))
    {                                                                 
        cout << row[i] << endl;                                       
    }

    system("pause");
}

/**
 *--------------------------------------------------------------------
 *       TYPE:  Books
 *--------------------------------------------------------------------
 */

void MySQL::SelectOldestBookinStock()
{
    /** Add MySQL Query */
    mysql_query(connect, "select book_name, Recive_date from books,stock where books.book_id = stock.book_id order by Recive_date limit 1;");


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Oldest Book in Stock " << DATABASE << " database " << endl;


    int num_fields = mysql_num_fields(res_set);
    // Print all columns
    for (int i = 0; i < num_fields; i++)
    {


        cout << row[i] << std::endl;

    }

    system("pause");
}


void MySQL::IsBookInStock()
{
    /** Add MySQL Query */
    string book_name = "";
    cout << "Enter book name :\n" << endl;
    cin >> book_name;
    string query = "select book_name,Quantity,Conditions from books,stock where books.book_id = stock.book_id AND books.book_name LIKE '%";
    query.append(book_name + "%';");
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        cout << "Book name: " << row[0] << " | Quantity: " << row[1] << " | Conditions: " << row[2] << "\n" << endl;
        isFound = true;
    }
    if (!isFound) {
        cout << "Book wasn't found in our stock" << endl;
    }

    system("pause");
}



/**
 *--------------------------------------------------------------------
 *       TYPE:  Customers
 *--------------------------------------------------------------------
 */

void MySQL::SelectOldestCustomer()
{
    /** Add MySQL Query */
    mysql_query(connect, "select First_name,Last_name,Customer_email,Customer_phone,join_date,Address_PCode,Address_street,City_name,Country_name from customers join address join city join country on customers.Address_id = address.Address_id and address.City_id = city.City_id and city.Country_id = country.Country_id order by join_date asc limit 1;");


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Oldest customer in " << DATABASE << " database " << endl;


    int num_fields = mysql_num_fields(res_set);
    // Print all columns
    for (int i = 0; i < num_fields; i++)
    {


        cout << row[0] << row[i] << std::endl;

    }

    system("pause");
}



void MySQL::CreateCustomer() {
    string name, number, id, address, dob;
    cout << "Enter Customer's name:\t";
    cin >> name;
    cout << "\nEnter phone number:\t";

    string q1 = "INSERT INTO `bookstoredb`.`customer_phone` (`PhoneNumber`, `Address`) VALUES ('" + number + "', '" + address + "');";
    string q2 = "INSERT INTO `bookstoredb`.`customer` (`CustomerID`, `PhoneNumber`, `Name`, `Books_Bought`, `DOB`, `Reg_date`) VALUES ('" + id + "', '" + number + "', '" + name + "', '0', '" + dob + "', current_timestamp());";
    executeQuery(q1);
    executeQuery(q2);

    cout << "Customer created in database";
}



/**
 *--------------------------------------------------------------------
 *       TYPE:  Orders
 *--------------------------------------------------------------------
 */

void MySQL::CurrentOrders()
{
    /** Add MySQL Query */
    mysql_query(connect, "select First_name,Last_name,Order_date,Payment_type,Order_status from orders join customers on orders.Customer_ID= customers.Customer_ID where Order_status !='Deliverd' order by Order_date asc;");


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Currnet orders " << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        
        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i]  << " " ;

        }
        cout << endl;

    }
    // Print all columns
    

    system("pause");
}

void MySQL::BookSumSold()
{
    string book_name = "";
    cout << "Enter book name :\n" << endl;
    cin >> book_name;
    string query = "select Book_name,sum(Quantity) as Sold from book_order join books on book_order.Book_id = books.Book_id where Book_name LIKE '%";
    query.append(book_name + "%';");
    mysql_query(connect, query.c_str());

    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Currnet orders " << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }
    // Print all columns


    system("pause");
}

void MySQL:: MaxSold()
{
       mysql_query(connect, " select Book_name, sum(Quantity) as Sold from book_order join books on book_order.Book_id = books.Book_id   group by book_order.Book_id order by Sold desc limit 1;");


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Currnet orders " << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }
    // Print all columns


    system("pause");
}

void MySQL::Top3CustomerOrder()
{
    /** Add MySQL Query */
    mysql_query(connect, "select first_name,last_name,count(book_order.book_order_id) as books_order from customers join orders join book_order on customers.customer_id = orders.customer_id and book_order.order_id = orders.order_id group by customers.first_name order by count(orders.order_id) desc limit 3; ");


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Top 3 customer  " << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }
    // Print all columns


    system("pause");
}

void MySQL::CustomerNotOrederLast24Month()
{
    /** Add MySQL Query */
    string query = "select * from customers join orders ";
    query += "on orders.customer_id = customers.customer_id ";
    query += "where customers.customer_id ";
    query += "in (select customers.customer_id from orders join customers on customers.customer_id = orders.customer_id where order_status = 'Deliverd' group by customer_id order by Order_date desc ) ";
    query += "and DATEDIFF(curdate(), Order_date) >= 730;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);

    cout << " Top 3 customer  " << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }
    // Print all columns


    system("pause");
}

void MySQL::CustomerDeliverdHistory()
{
    /** Add MySQL Query */
    string fname = "",lname="";
    cout << "Enter customer first name :\n" << endl;
    cin >> fname;
    string query = "select book_name,Order_date,Sell_price as price ";
    query += "from book_order ";
    query += "join orders ";
    query += "join customers ";
    query += "join stock ";
    query += "join books ";
    query += "on book_order.order_id = orders.order_id ";
    query += "and orders.customer_id = customers.customer_id ";
    query += "and stock.stock_id = book_order.order_id ";
    query += "and stock.book_id = books.book_id ";
    query += "where orders.order_status = 'Deliverd' ";
    query += "and customers.first_name = '";
    query += fname+"' ";
    query += "and customers.last_name = '";
    query += lname + "' ";
    query += "order by Order_date; ";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}

void MySQL::CustomerOrdersHistory()
{
    /** Add MySQL Query */
    string fname = "", lname = "";
    cout << "Enter customer first name :\n" << endl;
    cin >> fname;
    string query = "select book_name,Order_date,Sell_price as price ";
    query += "from book_order ";
    query += "join orders ";
    query += "join customers ";
    query += "join stock ";
    query += "join books ";
    query += "on book_order.order_id = orders.order_id ";
    query += "and orders.customer_id = customers.customer_id ";
    query += "and stock.stock_id = book_order.order_id ";
    query += "and stock.book_id = books.book_id ";
    query += "where customers.first_name = '";
    query += fname + "' ";
    query += "and customers.last_name = '";
    query += lname + "' ";
    query += "order by Order_date; ";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}

void MySQL::SumXpressShipmentBetweenDates()
{
    /** Add MySQL Query */
    string date1 = "", date2 = "";
    cout << "Enter first date (format: YYYY-MM-DD) :\n" << endl;
    cin >> date1;
    cout << "Enter second date (format: YYYY-MM-DD) :\n" << endl;
    cin >> date2;
    string query = "select sum(total_price) from orders join shipments join company join shipment_type ";
    query += "on orders.order_id = shipments.order_id ";
    query += "and shipments.Shipment_type_id = shipment_type.Shipment_type_id ";
    query += "and Shipment_type.Company_id = company.Company_id ";
    query += "where orders.Order_status = 'Deliverd' ";
    query += "and company_name = 'Xpress' ";
    query += "and orders.Order_date>='";
    query += date1 + "' ";
    query += "and orders.Order_date<='";
    query += date2 + "' ;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}

void MySQL::SumBitPatmentsBetweenDates()
{
    /** Add MySQL Query */
    string date1 = "", date2 = "";
    cout << "Enter first date (format: YYYY-MM-DD) :\n" << endl;
    cin >> date1;
    cout << "Enter second date (format: YYYY-MM-DD) :\n" << endl;
    cin >> date2;
    string query = "select sum(total_price) ";
    query += "from orders ";
    query += "where Payment_type = 'bit' ";
    query += "and orders.Order_date>='";
    query += date1 + "' ";
    query += "and orders.Order_date<='";
    query += date2 + "' ;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}


void MySQL::CheckOrderStatusById()
{
    /** Add MySQL Query */
    cout << "Enter Order Id : (int)" << endl;
    string id = "";
    cin >> id;

    string query = "select order_status from orders where order_id=";
    query += id +";";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}


/**
 *--------------------------------------------------------------------
 *       TYPE:  Genere
 *--------------------------------------------------------------------
 */



void MySQL::BookInStorage()
{
    /** Add MySQL Query */
    string query = "select year(recive_date),MONTH(recive_date),count(stock_id),sum(Quantity) ";
    query += "from stock where Location='Storage' ";
    query += "group by year(recive_date),MONTH(recive_date);";


    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}


void MySQL::CalcShipments()
{
    /** Add MySQL Query */
    string query = "select orders.order_id,sum(books.Wieght),shipment_type.kg_price,sum(books.Wieght*shipment_type.kg_price) ";
    query += "from orders join shipments join shipment_type join book_order join books ";
    query += "on orders.Order_id = shipments.Order_id and shipments.Shipment_type_id = shipment_type.Shipment_type_id and orders.Order_id = book_order.order_id and books.Book_id = book_order.Book_id ";
    query += "group by orders.order_id; ;";
  

    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}


void MySQL::BestSeller()
{
    /** Add MySQL Query */
    string  year = "", month = "";
    cout << "Enter year (format: YYYY) :\n" << endl;
    cin >> year;
    cout << "Enter month (format: MM) :\n" << endl;
    cin >> month;
    string query = "select Employee_fname as 'Name',Employee_lname as 'Last name',count(orders.order_id) as 'Orders' ";
    query += "from employees join orders on employees.employee_id = orders.employee_id ";
    query += "where month(orders.order_date) = ";
    query += month + " ";
    query += "and year(orders.order_date) = ";
    query += year + " ";
    query += "group by orders.employee_id limit 1;";

    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}

void MySQL::EmpSalaryByMonth()
{
    /** Add MySQL Query */
    string mail = "",year="",month="";
    int _d_month,d_month;
    cout << "Enter year (format: YYYY) :\n" << endl;
    cin >> year;
    cout << "Enter month (format: MM) :\n" << endl;
    cin >> d_month;
    cout << "Enter employee mail :\n" << endl;
    cin >> mail;
    _d_month = d_month;
    month = MonthByNumber(_d_month);
    string query = "select salaries.Hours * salaries.Salary_hourly as salary from salaries join employees on salaries.Employee_id = employees.Employee_id ";
    query += "where employees.employee_email= '";
    query += mail + "' ";
    query += "and salaries.Salary_month = '";
    query += month + "' ";
    query += "and salaries.Salary_year = '";
    query += month + "' ; ";

    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}

void MySQL::avgMonthlyOrders()
{
    /** Add MySQL Query */
    string year = "";
    cout << "Enter year (format: YYYY) :\n" << endl;
    cin >> year;
    string query = "select count(Order_id)as Num_of_orders,(total_price) as Avg_price,month(order_date) as 'Month',year(order_date) as 'Year' ";
    query += "from orders where year(order_date) = '";
    query += year + "' ";
    query += "group by month(order_date);";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}
void MySQL::StoreBuingBooksBteweenDates()
{
    /** Add MySQL Query */
    string date1 = "", date2 = "";
    cout << "Enter first date (format: YYYY-MM-DD) :\n" << endl;
    cin >> date1;
    cout << "Enter second date (format: YYYY-MM-DD) :\n" << endl;
    cin >> date2;
    string query = "select sum(Quantity) as amount ,sum(buy_price*Quantity) as Total_buy ";
    query += "from stock ";
    query += "where Recive_date >='";
    query += date1 + "' ";
    query += "and Recive_date <='";
    query += date2 + "' ;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}


void MySQL::BiggestBookTranslate()
{
    /** Add MySQL Query */

    string query = "select book_name,count(book_translate.book_id) as num_of_taranslte ";
    query += "from book_translate join books join stock ";
    query += "on books.book_id= book_translate.book_id and stock.Book_id = books.Book_id ";
    query += "where Quantity>0'";
    query += "group by book_translate.book_id ";
    query += "order by num_of_taranslte desc limit 1 ;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}



void MySQL::DealAboveAvg12Months()
{
    /** Add MySQL Query */

    string query = "select orders.* from orders join book_order join books join stock ";
    query += "on books.Book_id = book_order.Book_id and book_order.order_id = orders.order_id and books.Book_id = stock.Book_id  ";
    query += "where (sell_price-buy_price)	> ";
    query += "(SELECT avg(sell_price-buy_price) FROM orders join books join book_order join stock ";
    query += "on books.Book_id = book_order.Book_id and book_order.order_id = orders.order_id and books.Book_id = stock.Book_id ";
    query += "where DATEDIFF(curdate(), Order_date) <= 365) ";
    query += "group by order_id;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}

void MySQL::ShipmentByCompanyLastYear()
{
    /** Add MySQL Query */

    string query = "select company_name,count(shipments.shipment_id) as amount from orders join shipments join company join shipment_type ";
    query += "on orders.order_id = shipments.order_id   ";
    query += "and shipments.Shipment_type_id = shipment_type.Shipment_type_id ";
    query += "and shipment_type.company_id = company.Company_id ";
    query += "where orders.order_status = 'Deliverd' ";
    query += "where DATEDIFF(curdate(), Order_date) <= 365) ";
    query += "group by company_name;";
    mysql_query(connect, query.c_str());


    res_set = mysql_store_result(connect);

    unsigned int numrows = mysql_num_rows(res_set);
    boolean isFound = false;
    cout << " Result" << DATABASE << " database " << endl;
    int num_fields = mysql_num_fields(res_set);
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {

        for (int i = 0; i < num_fields; i++)
        {


            cout << row[i] << " ";

        }
        cout << endl;

    }

    system("pause");
}


string MySQL::IsCountry(string name)
{
    string query = "SELECT bookstore.country_id FROM country WHERE LOWER(Country_name) = LOWER(" + name + ")";
    mysql_query(connect, query.c_str());
    res_set = mysql_store_result(connect);
    unsigned int numrows = mysql_num_rows(res_set);
    cout << " Oldest book in " << DATABASE << " database " << endl;
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        return (string)row[0];
    }
    
    query = "INSERT INTO bookstore.Country(Country_name) VALUES('" + name + "')";
    mysql_query(connect, query.c_str());
    res_set = mysql_store_result(connect);
    if((row = mysql_fetch_row(res_set))!= NULL)
        return (string)row[0];
    cout << "There was an error please try again" << endl;
    return (NULL);
}

string MySQL::IsCity(string name, string country_id)
{
    string query = "SELECT bookstore.city_id FROM city WHERE LOWER(city_name) = LOWER(" + name + ")";
    mysql_query(connect, query.c_str());
    res_set = mysql_store_result(connect);
    unsigned int numrows = mysql_num_rows(res_set);
    cout << " Oldest book in " << DATABASE << " database " << endl;
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        return (string)row[0];
    }

    query = "INSERT INTO bookstore.City(City_name,Country_id) VALUES('" + name + "'," + country_id + ")";
    mysql_query(connect, query.c_str());
    res_set = mysql_store_result(connect);
    if ((row = mysql_fetch_row(res_set)) != NULL)
        return (string)row[0];
    cout << "There was an error please try again" << endl;
    return (NULL);
}

string MySQL::IsAddress(string name,string pscode, string city_id)
{
    string query = "SELECT bookstore.address_id FROM address WHERE LOWER(city_name) = LOWER(" + name + ")";
    mysql_query(connect, query.c_str());
    res_set = mysql_store_result(connect);
    unsigned int numrows = mysql_num_rows(res_set);
    cout << " Oldest book in " << DATABASE << " database " << endl;
    while ((row = mysql_fetch_row(res_set)) != NULL)
    {
        return (string)row[0];
    }

    query = "INSERT INTO bookstore.Address(Address_PCode,Address_street,City_id) VALUES('" + pscode + "','" + name + "'," + city_id + ")";
    mysql_query(connect, query.c_str());
    res_set = mysql_store_result(connect);
    if ((row = mysql_fetch_row(res_set)) != NULL)
        return (string)row[0];
    cout << "There was an error please try again" << endl;
    return (NULL);
}

string MySQL::MonthByNumber(int  x)
{
    string month = "January";
    switch (x)
    {
    case 1:   month = "January"; break;
    case 2:   month = "February"; break;
    case 3: month = "March"; break;
    case 4:   month = "April"; break;
    case 5:   month = "May"; break;
    case 6: month = "June"; break;
    case 7:   month = "July"; break;
    case 8:   month = "August"; break;
    case 9: month = "September"; break;
    case 10:   month = "October"; break;
    case 11:   month = "November"; break;
    case 12: month = "December"; break;
    }
    return month;
}

MYSQL_RES* MySQL::executeQuery(string query) {
    mysql_query(connect, query.c_str());
    MYSQL_RES* res = mysql_store_result(connect);
    return res;
}

/**
 *--------------------------------------------------------------------
 *       Class:  MySQL
 *      Method:  MySQL :: ~MySQL()
 * Description:  Destructor of MySQL class for closing mysql
 *               connection
 *--------------------------------------------------------------------
 */

MySQL :: ~MySQL()
{
    mysql_close (connect);
}
