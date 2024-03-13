//Grocery Billing System

#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Bill
{
private:
	string Item;
	int Rate, Quantity;

public:
	Bill() : Item(""), Rate(0), Quantity(0) {}

	void setItem(string item)
	{
		Item = item;
	}

	void setRate(int rate)
	{
		Rate = rate;
	}

	void setQuant(int quant)
	{
		Quantity = quant;
	}

	string getItem()
	{
		return Item;
	}

	int getRate()
	{
		return Rate;
	}

	int getQuant()
	{
		return Quantity;
	}
};

void addItem(Bill b)
{
	bool close = false;
	while (!close)
	{
		int choice;
		cout << "\t1.Add." << endl;
		cout << "\t2.close." << endl;
		cout << "\tEnter Choice: ";
		cin >> choice;
		while(choice != 1 && choice != 2){
			cout << "Your choose Wrong, Please enter 1 or 2: ";
			// cin.clear(); // Xóa trạng thái lỗi của cin
    		// cin.ignore(INT_MAX, '\n'); // Loại bỏ dữ liệu không hợp lệ từ bộ nhớ đệm nhập
			cin >> choice;
		}
		if (choice == 1)
		{
			system("cls");
			string item;
			int rate, quant;

			cout << "\tEnter Item Name: ";
			cin >> item;
			b.setItem(item);

			cout << "\tEnter Rate Of Item: ";
			cin >> rate;
			b.setRate(rate);

			cout << "\tEnter Quantity Of Item: ";
			cin >> quant;
			b.setQuant(quant);

			ofstream out("D:/Bill.txt", ios::app);
			if (!out)
			{
				cout << "\tError: File Can't Open!" << endl;
			}
			else
			{
				out << "\t" << b.getItem() << " : " << b.getRate() << " : " << b.getQuant() << endl
					<< endl;
			}
			out.close();
			cout << "\tItem Added Successfuly" << endl;
			Sleep(1000);
		}
		else if (choice == 2)
		{
			system("cls");
			close = true;
			cout << "\tBack To Main Menu!" << endl;
			//Sleep(100);
		}
	}
}

void printBill(bool exit)
{
	system("cls");
	int count = 0;
	bool close = false;
	while (!close)
	{
		system("cls");
		int choice;
		cout << "\t1.Add Bill." << endl;
		cout << "\t2.Close Session." << endl;
		cout << "\tEnter Choice: ";
		cin >> choice;

		if (choice == 1)
		{
			string item;
			int quant;
			cout << "\tEnter Item: ";
			cin >> item;
			cout << "\tEnter Quantity: ";
			cin >> quant;

			ifstream in("D:/Bill.txt");
			ofstream out("D:/Bill Temp.txt");

			string line;
			bool found = false;

			while (getline(in, line))
			{
				stringstream ss;
				ss << line;
				string itemName;
				int itemRate, itemQuant;
				char delimiter;
				ss >> itemName >> delimiter >> itemRate >> delimiter >> itemQuant;

				if (item == itemName)
				{
					found = true;
					if (quant <= itemQuant)
					{
						int amount = itemRate * quant;
						cout << "\t Item | Rate | Quantity | Amount" << endl;
						cout << "\t" << itemName << "\t " << itemRate << "\t " << quant << "\t " << amount << endl;
						cin.get();//nhấn bất kỳ để tiếp tục
						int newQuant = itemQuant - quant;
						itemQuant = newQuant;
						count += amount;

						out << "\t" << itemName << " : " << itemRate << " : " << itemQuant << endl;
					}
					else
					{
						cout << "\tSorry, " << item << " Ended!" << endl;
					}
				}
				else
				{
					out << line << endl;
				}
			}
			if (!found)
			{
				cout << "\tItem Not Available!" << endl;
			}
			out.close();
			in.close();
			remove("D:/Bill.txt");
			rename("D:/Bill Temp.txt", "D:/Bill.txt");
		}
		else if (choice == 2)
		{
			//close = true;
			cout << "\tCounting Total Bill" << endl;
			int out = 0;
			while(out != 1){
				cout << "\tPress '1' to return to the menu!";
				cin >> out;
			}
			close = true;
		}
		//Sleep(3000);
	}
	system("cls");
	cout << endl
		 << endl;
	cout << "\t Total Bill ----------------- : " << count << endl
		 << endl;
	cout << "\tThanks For Shopping!" << endl;
	Sleep(5000);
}

int main()
{
	Bill b;

	bool exit = false;
	while (!exit)
	{
		system("cls");
		int val;
		cout << "\tWelcome To Grocery Billing System" << endl;
		cout << "\t**************************************" << endl;
		cout << "\t\t1.Add Item." << endl;
		cout << "\t\t2.Print Bill." << endl;
		cout << "\t\t3.Exit." << endl;
		//cout << "Enter Choice: " << endl;
		cin >> val;

		if (val == 1)
		{
			system("cls");
			addItem(b);
		}

		else if (val == 2)
		{
			printBill(exit);
		}

		else if (val == 3)
		{
			system("cls");
			exit = true;
			cout << "\tGood Luck!" << endl;
		}
	}
}
