#include <iostream>
#include <conio.h>
#include <string>
#include "database.h"

using namespace std;
enum Stat { Rickety, Fine, Good, As_New, New};




void WelcomeFunc(MySQL storesql,int role) {
	system("CLS");
	cout << "          Second Hand Book Store\n\n";
	string endTav = "1";
	string name = "";
	cout << "Enter Your Name: ";
	cin >> name;
	boolean allTime = true;

			while (allTime) {
				string sub_choice = "";
				cout << "1 Check if a book is in stock\n";
				cout << "2 View the oldest client\n";
				cout << "3 View the oldest book\n";
				cout << "4 View active orders\n";
				cout << "5 Several copies of a book have been sold\n";
				cout << "6 The most read authur \n";
				cout << "7 The 3 customers who purchased the most books\n";
				cout << "8 Book with the most translations\n";
				cout << "9 Customer with the most purchases\n";
				cout << "10 Order history for a specific customer\n";
				cout << "11 Shipping cost calculation\n";
				cout << "12 Has Customer X ever split a book purchase for multiple shipments \n";
				cout << "13 What is the current status of a particular shipment \n";
				cout << "14 What is the amount of shipments made by Xpress in a particular month\n";
				cout << "15 The total money transferred to the store account via the Bit app per month a certain\n";
				cout << "16 View transactions made in the past year with a larger-than-average profit\n";
				cout << "17 How much shipments have been made during the last 12 months by company\n";
				cout << "18 All shipments made and included at least 2 editions	Variety of the same book\n";
				cout << "19 Customers who have previously purchased at least one book From the store, and who have not made any purchases during the last 24 months \n";
				cout << "20 Customers who placed orders, the books they ordered came to the store and still did not allow the book \n";
				if (role == 2)
				{
				cout << "21 Number of books in the warehouse on a monthly basis (Manager)\n";
				cout << "22 How many books did the store purchase between D1 and D2, and what was the total The payment for them (Manager)\n";
				cout << "23 The store profits from sales in a particular month (Manager).\n";
				cout << "24 Annual average monthly transactions(Manager).\n";
				cout << "25 The salary of employee X in a particular month (Manager) \n";
				cout << "26 Who sells with the most trades in month X (Manager) \n";
				}
				
				cout << "Enter your choice: ";
				

				cin >> sub_choice;
				system("CLS");
				if (sub_choice == "1") { storesql.IsBookInStock(); }
				else if (sub_choice == "2") { storesql.SelectOldestCustomer(); }
				else if (sub_choice == "3") { storesql.SelectOldestBookinStock(); }
				else if (sub_choice == "4") { storesql.CurrentOrders(); }
				else if (sub_choice == "5") { storesql.BookSumSold(); }
				else if (sub_choice == "6") { cout << "We are very sorry but this option not working right now"; }
				else if (sub_choice == "7") { storesql.Top3CustomerOrder(); }
				else if (sub_choice == "8") { storesql.BiggestBookTranslate(); }
				else if (sub_choice == "9") { storesql.CustomerOrdersHistory(); }
				else if (sub_choice == "10") { storesql.CustomerDeliverdHistory(); }
				else if (sub_choice == "11") { storesql.CalcShipments(); }
				else if (sub_choice == "12") { cout << "We are very sorry but this option not working right now"; }
				else if (sub_choice == "13") { storesql.CheckOrderStatusById(); }
				else if (sub_choice == "14") { storesql.SumXpressShipmentBetweenDates(); }
				else if (sub_choice == "15") { storesql.SumBitPatmentsBetweenDates(); }
				else if (sub_choice == "16") { storesql.DealAboveAvg12Months(); }
				else if (sub_choice == "17") { storesql.ShipmentByCompanyLastYear(); }
				else if (sub_choice == "18") { cout << "We are very sorry but this option not working right now"; }
				else if (sub_choice == "19") { storesql.CustomerNotOrederLast24Month(); }
				else if (sub_choice == "20") { cout << "We are very sorry but this option not working right now"; }
				else if (sub_choice == "21" && role == 2) { storesql.BookInStorage(); }
				else if (sub_choice == "22" && role == 2) { storesql.StoreBuingBooksBteweenDates(); }
				else if (sub_choice == "23" && role == 2) { cout << "We are very sorry but this option not working right now"; }
				else if (sub_choice == "24" && role == 2) { storesql.avgMonthlyOrders(); }
				else if (sub_choice == "25" && role == 2) { storesql.EmpSalaryByMonth(); }
				else if (sub_choice == "26" && role == 2) { storesql.BestSeller(); }
				else if (sub_choice.compare("Q")==0 || sub_choice.compare("exit") == 0) { allTime=false; }
				cin.ignore();

				system("CLS");
			}

		
		
	
}

int main(void)
{
	MySQL Mysql;
	system("CLS");
	int role_type = 1; // 1 = worker | 2 = manager
	cout << "          Second Hand Book Store\n\n";
	string choice = " ";
	cout << "Welcome to our bookstore  \n";
	cout << "1. i'm Employee \n";
	cout << "2. i'm Manager \n";
	cout << "Enter your choice: ";

	cin >> choice;
	if (choice == "2")
	{
		string password;
		char ch;
		const char ENTER = 13;

		std::cout << "enter manager password:(1234) ";

		while ((ch = _getch()) != ENTER)
		{
			password += ch;
			std::cout << '*';
		}
		if (password == "1234")
		{
			role_type =2;
		}
	}


	

	WelcomeFunc(Mysql,role_type);
	//Mysql.ShowTables();

	return 0;
}