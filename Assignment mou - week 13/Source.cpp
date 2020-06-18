#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <cstring>
#pragma warning(disable: 4996)

using namespace std;

// structure declarations
typedef struct 
{
	char bookName[70];
	char authorName[40];
	char edition[8];
	char publisher[40];
	double price;
	char ibsn[20];
	int noCopy;

} BOOK_TYPE;

// function prototypes
void login(char name[], char student_id[]);
void readBooks(vector<BOOK_TYPE>& book);
void processBookData(vector<BOOK_TYPE>& book);
void displayBookMenu(vector<BOOK_TYPE>& book);
int search_book(vector<BOOK_TYPE>& book);
void delete_book(vector<BOOK_TYPE>& book);
void maintain_book(vector<BOOK_TYPE>& book);
void add_book(vector<BOOK_TYPE>& book);
void compute_bookreport(vector<BOOK_TYPE>&book);

int main(void) 
{
	//defining variables
	vector<BOOK_TYPE> book; //define an vector of structures
	char name[15], student_id[10];//define an array of string for student name and id
	int choice;// user choice for different function of library system
	char option;//user choice for generate book report before exit the system
	cout << fixed << setprecision(2);//to fixed the decimal point of the display letter

	//call to function login
	login(name, student_id);
	system("cls");

	// call to function readBooks
	readBooks(book);
	fflush(stdin);

	
	// call to function processBookData
	processBookData(book);

	system(" color 1D");
	cout << " Welcome " << name << " " << student_id << endl;
	do
	{
		cout << left;
		cout << "\nWhich function do you want to access?\n";
		cout << "1. List books\n";
		cout << "2. Search book(s)\n";
		cout << "3. Delete book\n";
		cout << "4. Borrow or Return book\n";
		cout << "5. Add book\n";
		cout << "6. Exit\n";
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore();

		switch (choice) 
		{

		case 1:
			// call to function displayBookMenu
			displayBookMenu(book);
			fflush(stdin);
			system("pause");
			system("cls");
			break;

		case 2:
			// call to function search_book
			search_book(book);
			system("pause");
			system("cls");
			break;

		case 3:
			// call to function delete_book
			delete_book(book);
			system("pause");
			system("cls");
			break;

		case 4:
			// call to function maintain_book
			maintain_book(book);
			system("pause");
			system("cls");
			break;

		case 5:
			// call to function add_book
			add_book(book);
			system("pause");
			system("cls");
			break;

		case 6:
			//exit the program
			break;

		default:
			// display error message
			cout << "Invalid input!!!\n\n";
			break;
		
		}

	} while (choice!=6);

	//ask user whether he or she want to generate a book report.
	do
	{
		cout << "Do you want to generate a book report ? <y or n> : ";
		cin >> option;
	} while (option != 'y' && option != 'Y' && option != 'n'&& option != 'N');

	if (option == 'y' || option == 'Y')
		//call to function compute book_report
		compute_bookreport(book);

	return 0;
}

// function definitions


//Request for login
void login(char name[], char student_id[])
{
	system(" color 1B");//print colour texts on screen
	time_t curtime;//variables for current time
	time(&curtime);//scan time

	cout << setw(40) << "------------------------------------\n";
	cout << setw(40) << "Welcome to the library system \n";
	cout << setw(36) << ctime(&curtime) << "\n";
	cout << setw(40) << "------------------------------------\n";


	do {
		cout << "Please enter your name (15) : ";
		cin.getline(name, 100);

		if (strlen(name) > 15 || strlen(name) < 1)
		{
			cout << "Please reenter your name within the range of 1 to 15 !!! ";
			cout << endl;
		}

	} while (strlen(name) < 1 || strlen(name) > 15);


	do {
		cout << "Please enter your student id (10): ";
		cin >> student_id;

		if (strlen(student_id) > 10 || strlen(student_id) < 1)
		{
			cout << "Please reenter your student id within the range of 1 to 10 !!! ";
			cout << endl;
		}

	} while (strlen(student_id) < 1 || strlen(student_id) > 10);

	return;
}






// to read in the book info.s and put into the vector
void readBooks(vector<BOOK_TYPE>& book)
{

	ifstream inFile; // create an instance of file stream
	BOOK_TYPE theBook;// temporary variable for storing the data read from the file

	 // inFile.fail() ==> to check if the file opened successfully
	if (inFile.fail()) 
	{
		perror("book.txt"); // display error message based on the file name
		exit(100);
	}

	inFile.open("book.txt"); // to open the file bookInfo.txt

	 // read in data from the file and put into them into a structure and put into vector
	while (inFile >> theBook.bookName >> theBook.authorName >> theBook.edition >> theBook.publisher >> theBook.price >> theBook.ibsn >> theBook.noCopy)
	{
		// put theBook structure into the vector of structure
		book.push_back(theBook);
	}

	inFile.close(); // to close the file
	return;
}


// process the data by replacing the underscore in the values of member elements in each vector element (structure) with spaces
void processBookData(vector<BOOK_TYPE>& book)
{

	// these for loops replace the underscore in the values of member elements in each vector element (structure) with spaces
	for (int i = 0; i < book.size(); i++)
	{

		// loop through each character in book[i].bookName and replace the underscores with spaces
		for (int j = 0; j < strlen(book[i].bookName); j++)
		{
			if (book[i].bookName[j] == '_')
				book[i].bookName[j] = ' ';
		
		}

		// loop through each character in book[i].authorName and replace the underscores with spaces
		for (int j = 0; j < strlen(book[i].authorName); j++)
		{
			if (book[i].authorName[j] == '_')
				book[i].authorName[j] = ' ';
		}

		// loop through each character in book[i].edition and replace the underscores with spaces
		for (int j = 0; j < strlen(book[i].edition); j++)
		{
			if (book[i].edition[j] == '_')
				book[i].edition[j] = ' ';
		}

		// loop through each character in book[i].publisher and replace the underscores with spaces
		for (int j = 0; j < strlen(book[i].publisher); j++) 
		{
			if (book[i].publisher[j] == '_')
				book[i].publisher[j] = ' ';
		}

	}
	return;
}

// display the book list which includes all the related information about books
void displayBookMenu(vector<BOOK_TYPE>& book) 
{

	//heading
	cout << left << fixed << setprecision(2);
	cout << "No.   " << setw(72) << "Book name" << setw(24) << "Author name" << setw(10) << "Edition" << setw(30)
		<< "Publisher" << setw(12) << "Price" << setw(20) << "IBSN" << "Available copy\n";
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

	// display the book info.s in tabular format
	for (int i = 0; i < book.size(); i++) 
	{

		if (i + 1 < 10)//arrangement for the display of book which position within 1 to 10		
		{
			cout << i + 1 << ".    " << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
				<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
				<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;
		}
		else //arrangement for the display of book which position within 11 to 20
		{
			cout << i + 1 << ".   " << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
				<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
				<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;
		}

	}
	cout << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

	cout << endl;
	return;
}



// search book(s) by IBSN, author or title
int search_book(vector<BOOK_TYPE>& book)
 {

	int choice;//choice to pick search book categories (IBSN ,AUTHOR, Book)
	char ibsn[20];
	char authorName[40];
	char bookName[70];
	int noBook = 0;// to determine if the number of books found
	

	cout << "Do you want to search by\n";
	cout << "1. IBSN\n";
	cout << "2. Author name\n";
	cout << "3. Book name\n";
	

	// validate the user choice
	do 
	{
		cout << "Enter your choice: ";
		cin >> choice;
		cin.ignore(); // to ignore the whitespace

		if (choice != 1 && choice != 2 && choice != 3)
			cout << "Invalid choice!!!"<<endl;

	} while (choice != 1 && choice != 2 && choice != 3);

	switch (choice)
	{
	case 1:
		cout << "Enter IBSN to search the book(s): ";
		cin.getline(ibsn, 20);
		goto IBSN;// goto ==> the program will straight jump to the IBSN part and start execute from there
		break;

	case 2:
		cout << "Enter author name to search the book(s): ";
		cin.getline(authorName, 40);
		goto AUTHOR_NAME;
		break;

	case 3:
		cout << "Enter book name to search the book(s): ";
		cin.getline(bookName, 70);
		goto BOOK_NAME;
		break;

	default:
		cout << "Invalid choice!!!\n";
		break;
	}

	

	/*
	strstr ==> find the first occurrence of a substring in a string
	Value returned:
	- If the substring is found, the strstr() function returns the pointer to the first character of the substring in dest.
	- If the substring is not found, a null pointer is returned.
	- If dest points to an empty string, str is returned
	*/

IBSN:
	// display heading 
	cout << "\nPosition in book list\t" << setw(72) << "Book name" << setw(24) << "Author name" << setw(10) << "Edition" << setw(30)
		<< "Publisher" << setw(12) << "Price" << setw(20) << "IBSN" << "Available copy\n";

	for (int i = 0; i < book.size(); i++) 
	{
		// pointer returned != NULL
		if (strstr(book[i].ibsn, ibsn))
		{

			//display book info
			cout << i + 1 << ".\t\t\t" << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
				<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
				<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;

			// update the noBook
			noBook++;

		}
	}

	// to indicate that is no such book
	if (noBook == 0)
		cout << "The book that you want to find is unavailable , sorry \n\n";

	return noBook;

AUTHOR_NAME:
	// display heading 
	cout << "\nPosition in book list\t" << setw(72) << "Book name" << setw(24) << "Author name" << setw(10) << "Edition" << setw(30)
		<< "Publisher" << setw(12) << "Price" << setw(20) << "IBSN" << "Available copy\n";
	
	for (int i = 0; i < book.size(); i++)
	{
		// pointer returned != NULL
		if (strstr(book[i].authorName, authorName)) 
		{

			//display book info
			cout << i + 1 << ".\t\t\t" << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
				<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
				<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;

			// update the noBook
			noBook++;

		}
	}

	if (noBook == 0)
		cout << "The book that you want to find is unavailable , sorry \n\n";

	return noBook;

BOOK_NAME:
	// display heading 
	cout << "\nPosition in book list\t" << setw(72) << "Book name" << setw(24) << "Author name" << setw(10) << "Edition" << setw(30)
		<< "Publisher" << setw(12) << "Price" << setw(20) << "IBSN" << "Available copy\n";
	
	for (int i = 0; i < book.size(); i++) 
	{
		// pointer returned != NULL
		if (strstr(book[i].bookName, bookName)) 
		{

			//display book info
			cout << i + 1 << ".\t\t\t" << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
				<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
				<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;

			// update the noBook
			noBook++;

		}
	}

	if (noBook == 0)
		cout << "The book that you want to find is unavailable , sorry \n\n";


	return noBook;

}


// delete a particular book record
void delete_book(vector<BOOK_TYPE>& book)
{
	int book_pos;// book position
	int no_book;// to store the value returned by search_book function and to determine if there is any book found

	// call to function search book
	no_book = search_book(book);

	if (no_book > 0) 
	{
		do
		{
			cout << "\nEnter the book to delete (book position in the book list): ";
			cin >> book_pos;
		} while (book_pos < 1 || book_pos > book.size());

		// erase the vector book's element at specified index i.e. the index is book_pos - 1
		book.erase(book.begin() + book_pos - 1);// if book_pos - 1 = 16 then 17th element will be erased
	}

}

void maintain_book(vector<BOOK_TYPE>& book)
{
	//declare variables
	int no_book;// to store the value returned by search_book function and to determine if there is any book found
	int index;// book position
	char selection;//selection to return book or borrow book
	no_book = search_book(book);// call to function search book
	if (no_book > 0)
	{
		cout << "Do you want to return or borrow a book? ";
		do
		{
			cout << "\nPress r to return book, b to borrow book : ";
			cin >> selection;
		} while ((selection != 'r' && selection != 'R') && (selection != 'b'&& selection != 'B'));

		if (selection == 'r' || selection == 'R')
		{
			do
			{
				cout << "Enter the book you want to return (book position in the book list) :";//return book
				cin >> index;
			} while (index < 1 || index > book.size());

				book[index - 1].noCopy++;
				cout << "The book is succecssfully returned ! " << endl;
			
		}
		else if (selection == 'b' || selection == 'B')
		{
			do
			{
				cout << "Enter the book you want to borrow (book position in the book list) :";//return book
				cin >> index;
			} while (index < 1 || index > book.size());

			if (book[index - 1].noCopy == 0)
				cout << "There are no available copies for the book you want to borrow!!";

			else
			{
				book[index - 1].noCopy--;
				cout << "The book is succecssfully borrowed ! " << endl;
			}
		}
			
	}
	return;
}



// add a new book record
void add_book(vector<BOOK_TYPE>& book) 
{
	//declare variables
	BOOK_TYPE newBook; // temporary structure for new book
	
	do
	{
		cout << "Book name: ";
		cin.getline(newBook.bookName, 70);

	} while (strlen(newBook.bookName) < 1 || strlen(newBook.bookName) > 60);

	do
	{

		cout << "Book author: ";
		cin.getline(newBook.authorName, 30);

	} while (strlen(newBook.authorName) < 1 || strlen(newBook.authorName) > 20);

	do
	{

		cout << "Book edition (st, nd, rd or th): ";
		cin.getline(newBook.edition, 8);

	} while (strlen(newBook.edition) < 1 || strlen(newBook.edition) > 6);

	do
	{

		cout << "Book publisher: ";
		cin.getline(newBook.publisher, 30);

	} while (strlen(newBook.publisher) < 1 || strlen(newBook.publisher) > 25);


	cout << "Book price: ";
	while (!(cin >> newBook.price))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid input!!!\n\nEnter again: ";
	}


	do
	{

		cout << "Book IBSN (e.g. 978-1-34-789538-8): ";
		cin.getline(newBook.ibsn, 20);

	} while (strlen(newBook.ibsn) < 1 || strlen(newBook.publisher) > 19);

	cout << "Available copies of book: ";
	while (!(cin >> newBook.noCopy))
	{
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cout << "Invalid input!!!\n\nEnter again: ";
	}

	// add the new book to the vector
	book.push_back(newBook);

	// display message
	cout << "\nAdded successfully!!!\n";


	return;
}

void compute_bookreport(vector<BOOK_TYPE>&book)
{

	ofstream outFile; // create an instance of file stream
	BOOK_TYPE theBook;// temporary variable for storing the data read from the file

	// inFile.fail() ==> to check if the file opened successfully
	if (outFile.fail())
	{
		perror("book_report.txt"); // display error message based on the file name
		exit(100);
	}
	else
	{
		outFile.open("book_report.txt"); // to open the file bookInfo.txt

										
		// save the book list which includes all the related information about books in another text file call book_report
		//heading
		outFile << left << fixed << setprecision(2);
		outFile << "No.   " << setw(72) << "Book name" << setw(24) << "Author name" << setw(10) << "Edition" << setw(30)
				<< "Publisher" << setw(12) << "Price" << setw(20) << "IBSN" << "Available copy\n";
		outFile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

			// display the book info.s in tabular format
			for (int i = 0; i < book.size(); i++)
			{

				if (i + 1 < 10)//arrangement for the display of book which position within 1 to 10
				{
					outFile << i + 1 << ".    " << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
						<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
						<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;
				}
				else //arrangement for the display of book which index within 11 to 20
				{
					outFile << i + 1 << ".   " << setw(72) << book[i].bookName << setw(24) << book[i].authorName << setw(10)
						<< book[i].edition << setw(30) << book[i].publisher << "RM" << setw(10) << book[i].price
						<< setw(20) << book[i].ibsn << "\t" << book[i].noCopy << endl;
				}

			}
			outFile << "--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
			
		}

	outFile.close(); // to close the file
	return;
}










