#include <iostream>
#include<cstdlib>
#include<ctime>
#include <string>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <time.h>
#include <fstream>
#include<list>
#pragma warning (disable:4996)
#define filename "libsys.txt"

using namespace std;

struct Node
{
	string book_name;
	string author_name;
	string isbn;
	string year;
	Node* next;
	Node()
	{
		book_name = "";
		author_name = "";
		isbn = "";
		year = "";
		next = NULL;
	}
	Node(string bkname, string athname, string num, string y)
	{
		book_name = bkname;
		author_name = athname;
		isbn = num;
		year = y;
		next = NULL;
	}
};

class Library
{
public:
	Library()
	{
		fstream obj;
		obj.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
		if (!obj)
		{
			obj.open(filename, fstream::in | fstream::out | fstream::trunc);
			obj.close();
		}
	}
	void addBook(list<Node*> & L1)
	{
		int year, month, day;
		time_t t = time(NULL);
		struct tm tm = *localtime(&t);
		year = tm.tm_year + 1900;
		month = tm.tm_mon + 1;
		day = tm.tm_mday;

		ofstream file(filename, ios::out);
		if (!file.is_open())
		{
			cout << "Error opening file" << endl;
			return;
		}

		Node* datasep;
		typename list<Node*> ::iterator it;
		for (it = L1.begin(); it != L1.end(); ++it)
		{
			datasep = *(it);
			file << datasep->book_name << ",";
			file << datasep->author_name << ",";
			file << datasep->isbn << ",";
			file << datasep->year << ",";
			file << day << "-";
			file << month << "-";
			file << year << "-";
			file << "\n";
		}

		file.close();

		cout << "\n Data added Successfully !!" << endl;
	}

	void deleteBook(list<Node*> & L1, string sbn)
	{
		bool recordfound = false;
		list<Node*> L2;
		while (!L1.empty())
		{
			Node* datasep = L1.front();
			L1.pop_front();
			if (datasep->isbn != sbn)
			{
				L2.push_back(datasep);
			}
			else
			{
				recordfound = true;
			}
		}
		if (recordfound == true)
		{
			L1 = L2;
			int year, month, day;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			year = tm.tm_year + 1900;
			month = tm.tm_mon + 1;
			day = tm.tm_mday;

			ofstream file(filename, ios::out);
			if (!file.is_open())
			{
				cout << "Error opening file" << endl;
				return;
			}

			Node* datasep;
			typename list<Node*> ::iterator pt;
			for (pt = L1.begin(); pt != L1.end(); ++pt)
			{
				datasep = *(pt);
				file << datasep->book_name << ",";
				file << datasep->author_name << ",";
				file << datasep->isbn << ",";
				file << datasep->year;
				file << day << "-";
				file << month << "-";
				file << year << "-";

				file << "\n";
			}

			file.close();
			cout << "\n Data deleted Successfully !!" << endl;
		}
		else
		{
			cout << "Record not found!" << endl;
		}


	}

	void searchBook(list<Node*> & L1)
	{
		string keyword;
		int choice = 0;
		bool flag = false;
		int dsp = 0;
		string stype = "";

		cout << "1- Search by name" << endl;
		cout << "2- Search by author" << endl;
		cout << "3- search by isbn" << endl;
		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice)
		{
		case 1:
		{
			cin.ignore();
			cout << "Enter Book Name: ";
			getline(cin, keyword);
			bool recordfound = false;
			Node* datasep;

			typename list<Node*> ::iterator it;
			cout << endl;
			for (it = L1.begin(); it != L1.end(); ++it)
			{
				datasep = *(it);
				if (datasep->book_name == keyword)
				{
					cout << "Book Name: \t" << datasep->book_name << endl;
					cout << "Author Name: \t" << datasep->author_name << endl;
					cout << "Book ISBN: \t" << datasep->isbn << endl;
					cout << "Book Year: \t" << datasep->year << endl;
					cout << endl;
					recordfound = true;
				}
			}
			if (recordfound == false)
			{
				cout << "No record found :(" << endl;
			}
			break;
		}
		case 2:  // Filteration done: Check author name and then ask 
				 // The year of which you want to search books of that author
		{
			bool check = false;
			cin.ignore();
			cout << "Enter Author Name: ";
			getline(cin, keyword);
			Node* datasep;
			typename list<Node*> ::iterator it;
			list<Node*>temp_authors;
			cout << endl;
			for (it = L1.begin(); it != L1.end(); ++it)
			{
				datasep = *(it);
				if (datasep->author_name == keyword)
				{
					temp_authors.push_back(datasep);
					check = true;
				}
			}
			if (check == false)
			{
				cout << "No record found :(" << endl;
			}
			else
			{
				string y;
				check = false;
				typename list<Node*> ::iterator it;
				cout << "Records found." << endl;
				cout << "Enter year you want to search of that author:";
				getline(cin, y);
				for (it = temp_authors.begin(); it != temp_authors.end(); ++it)
				{
					datasep = *(it);
					if (datasep->year == y)
					{
						cout << "Record Found." << endl;
						cout << "Book Name: \t" << datasep->book_name << endl;
						cout << "Author Name: \t" << datasep->author_name << endl;
						cout << "Book ISBN: \t" << datasep->isbn << endl;
						cout << "Book Year: \t" << datasep->year << endl;
						cout << endl;
						check = true;
					}
				}
				if (check == false)
				{
					cout << "No record found :(" << endl;
				}

			}
			break;
		}
		case 3:
		{
			cin.ignore();
			cout << "Enter ISBN: ";
			getline(cin, keyword);
			bool recordfound = false;
			Node* datasep;

			typename list<Node*> ::iterator it;
			cout << endl;
			for (it = L1.begin(); it != L1.end(); ++it)
			{
				datasep = *(it);
				if (datasep->isbn == keyword)
				{
					cout << "Book Name: \t" << datasep->book_name << endl;
					cout << "Author Name: \t" << datasep->author_name << endl;
					cout << "Book ISBN: \t" << datasep->isbn << endl;
					cout << "Book Year: \t" << datasep->year << endl;
					cout << endl;
					recordfound = true;
				}
			}
			if (recordfound == false)
			{
				cout << "No record found :(" << endl;
			}
			break;
		}
		case 0:
		{
			break;
		}
		default:
		{
			return;
		}
		}

	}

	void updateBook(list<Node*> & L1, string sbn)
	{
		string bname, aname;
		int y;
		bool recordfound = false;
		Node* datasep;
		typename list<Node*> ::iterator it;
		for (it = L1.begin(); it != L1.end(); ++it)
		{
			datasep = *(it);
			if (datasep->isbn == sbn)
			{
				cin.ignore();
				cout << "Please enter Book name(to update): ";
				getline(cin, bname);
				cout << "Please enter Author name(to update): ";
				getline(cin, aname);
				cout << "Please enter Year(to update): ";
				cin >> y;
				datasep->year = y;
				datasep->book_name = bname;
				recordfound = true;
			}
		}
		if (recordfound == false)
		{
			cout << "No record found!" << endl;
		}
		else
		{
			int year, month, day;
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			year = tm.tm_year + 1900;
			month = tm.tm_mon + 1;
			day = tm.tm_mday;

			ofstream file(filename, ios::out);
			if (!file.is_open())
			{
				cout << "Error opening file" << endl;
				return;
			}

			Node* datasep;
			typename list<Node*> ::iterator pt;
			for (pt = L1.begin(); pt != L1.end(); ++pt)
			{
				datasep = *(pt);
				file << datasep->book_name << ",";
				file << datasep->author_name << ",";
				file << datasep->isbn << ",";
				file << datasep->year << ",";
				file << day << "-";
				file << month << "-";
				file << year;
				file << "\n";
			}

			file.close();

			cout << "\n Data updated Successfully !!";
		}
	}

	void listOfAllBooks(list<Node*> & L1)
	{
		if (!L1.empty())
		{
			int i = 0;
			Node* temp;
			typename list<Node*> ::iterator it;
			for (it = L1.begin(); it != L1.end(); ++it)
			{
				temp = *(it);
				cout << "Record : " << i + 1 << endl;
				cout << "Book Name: \t" << temp->book_name << endl;
				cout << "Author Name: \t" << temp->author_name << endl;
				cout << "Book ISBN: \t" << temp->isbn << endl;
				cout << "Book Year: \t" << temp->year << endl;
				cout << endl;
				i++;
			}
		}
		else
		{
			return;
		}
	}

	void readfile(list<Node*> & L1)
	{
		string temp, bookname, authorname, sbn;
		string yr;
		int index = 0;
		ifstream obj;
		obj.open(filename);
		getline(obj, temp);
		while (!obj.eof())
		{
			index = temp.find(',');
			bookname = temp.substr(0, index);

			temp = temp.substr(index + 1);
			index = temp.find(',');
			authorname = temp.substr(0, index);

			temp = temp.substr(index + 1);
			index = temp.find(',');
			sbn = temp.substr(0, index);

			temp = temp.substr(index + 1);
			index = temp.find(',');
			yr = temp.substr(0, index);

			Node * currdata = new Node(bookname, authorname, sbn, yr);
			L1.push_back(currdata);
			getline(obj, temp);
		}
		obj.close();

	}
};

int main()
{
	list<Node*> L;
	Library C;
	C.readfile(L);
	cout << "Welcome to Library Information System" << endl << endl;
	cout << "Following is the list of all available books" << endl;
	C.listOfAllBooks(L);
	int outerChoice = 0;
	while (outerChoice != 9)
	{
		int innerChoice = 0;
		while (innerChoice != 9)
		{
			cout << "Welcome to Library Information System" << endl;
			cout << "1. Add Book" << endl;
			cout << "2. Search Book" << endl;
			cout << "3. Update Book" << endl;
			cout << "4. Delete Book" << endl;
			cout << "5. List of All Books" << endl;
			cout << "0. Exit" << endl;
			cout << "\n Enter your choice : ";

			cin >> innerChoice;
			string bookname, bookauthor, bookisbn, bookyear;

			switch (innerChoice)
			{
			case 1:
			{
				cin.ignore();
				cout << "\n ---- Add a new Book ----";
				cout << "\n Enter book name : ";
				getline(cin, bookname);
				cout << "\n Enter book author : ";
				getline(cin, bookauthor);
				cout << "\n Enter SBN Number: ";
				getline(cin, bookisbn);
				cout << "\n Enter Year: ";
				getline(cin, bookyear);
				Node* temp = new Node(bookname, bookauthor, bookisbn, bookyear);
				L.push_back(temp);
				C.addBook(L);
				break;
			}
			case 2:
			{
				C.searchBook(L);
				break;
			}
			case 3:
			{
				cout << "Enter ISBN number of book to Update: ";
				cin >> bookisbn;
				C.updateBook(L, bookisbn);
				break;
			}
			case 4:
			{
				cin.ignore();
				cout << "Enter ISBN number of book to delete: ";
				getline(cin, bookisbn);
				C.deleteBook(L, bookisbn);
				break;
			}
			case 5:
			{
				C.listOfAllBooks(L);
				break;
			}
			case 0:
			{
				return 0;
			}
			default:
			{
				cout << "\n\n Invalid Choice. Press any key to continue..";
				getchar();
			}
			}
		}
	}
}
