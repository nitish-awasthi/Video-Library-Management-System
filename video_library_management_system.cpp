//Video Library Management System
// Declaration of header files
#include <iostream.h>
#include <fstream.h>
#include <process.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <iomanip.h>
#include <graphics.h>

typedef char option[150];
const int ROW = 10, COL = 10;

int scan;    // To hold the special characters for moving the prompt in menu
int ascii;

// To display the main menu options
option a[]= {
	      "NEW CASSETTE PURCHASE",
	     "LIST OF PURCHASE",
	     "DAILY CASSETTE PURCHASE",
	     "SALES REPORT",
	     "ADD OTHER EXPENSE",
	     "OTHER EXPENSE REPORT",
	     "CLOSING STOCK",
	     "MONTHLY PROFIT",
	     "EXIT"
	};


// Function used to do screening
class main_menu
{
    int i,done;

    public:
	void normalvideo(int x,int y,char *str);
	void reversevideo(int x,int y,char *str);
	void box(int x1,int y1,int x2,int y2);
	char menu();
	void control_menu();
	void help(void);
};

/* Class member functions for drawing boxes */
class shape
{
    public:
	void line_hor(int, int, int, char);
	void line_ver(int, int, int, char);
	void box(int, int, int, int, char);
};


// Class contains the cassettes/CDs deposit of customers
class cassettes
{
    public:
	void new_cassettes(void);    // Function to add new cassettes/CDs in music shop
	// For cassettes/CDs entry into the cassettes.dat data file
	void add_to_file(int, char t_Cass_name[30], char t_Comp_name[30], int, int, int, int, float);
	void display_list(void); // Displaying the cassettes/CDs list
	void delete_cassette(int); // Deletes the temporary cassette record
	int last_cas_code(void); // if the file is exist or not
	char *return_name(int); // Function for validation entry of name
	char *return_address(int); // Function for validation entry of address
	int recordno(int);
	void display(int); // To display the cassette/CD information account

    private:
	// Data Members of cassette.dat data file

	int cas_code;    // cassette/CD code - film, nonfilm, religious
	char Cass_name[30];    // Title of the cassette/CD
	char Comp_name[30];    // cassette/CD company
	int tot_cassette;    // Total cassette/CD purchased
	int dd, mm, yy;    // Date of purchase
	float price;    // Price per cassette/CD
};

class balance
{
    public:
	void add_to_file(int, int, int, int, int, float);    // Add record for balance cassette/CD
	void balance_cassette(void);    // Function to display the balance cassette/CD
	void delete_balance(int);    // Deleting the balance from Tbal.dat
	int give_balance(int);    // returns the current balance of a particular
				// cassette/CD code
	void Update_balance(int, int, int , int , int, float); // Function to update balance after cassette/CD sale
	float return_price(int);    // Return the cassette/CD price

	void monthly_profit(void);    // Monthly profit after every transaction

    private:

	// Data members of Tbal.dat data file
	int cas_code;    // cassette/CD code to be balance
	int cas_bal;    // Total number of cassettes/CDs in balance
	int dd;    // Balance date
	int mm;
	int yy;
	float price;    // Unit price of cassettes/CDs on code wise

};


// Class contains the customers daily cassette/CD transaction entry
class account
{
    public:
	void new_account(void);  // Function to sale cassettes/CDs
	void close_account(void);    // Function to close the cassette/CD purchase
	void clear(int, int); // Function to perform a clear screen function
	void Display_sales(void);    // Displaying the sales report of cassettes/CDs
	int last_cas_code(void); // if the file is exist or not
	float sales_status(int m1, int y1, float cod1, float cod2, float cod3);
    private:
	void add_to_file(int, char tP_name[30], char tP_address[30],int, int, int, int); // Function to add transaction records
	void delete_account(int); // Function to delete a transaction record

	// Data members of person.dat data file
	int cas_code;        // cassette/CD code - film, nonfilm, religious
	char P_name[30];    // Person Name
	char P_address[30];    // Person Address
	int No_cass;        // Number of cassette/CD
	int dd, mm, yy;     // To store the system date/ purchase date
};

class other
{
    public :
	// Function to display other expense screen like salary,
	// electricity bill, telephone and miscellaneous expences
	void Expense_other(void);

	// Add the data to Other.dat data file
	void add_to_file(int, char tNat_Expen[30], int, int, int, float);
	void display_expense(void);    // Display the expenses
	float other_status(int m1, int y1);

    private :
	// Data members of other.dat data file
	int O_code;        // Other expence code
	/* The other expence code as :
	    1     -    Salary to workers,
	    2    -    Electricity bill
	    3    -    Telephone bills
	    4    -    Miscellaneous expenses    */
	char Nat_Expen[30];    // Nature of expense description
	int dd, mm, yy;    // Expense date
	float amount;    // Expense amount
};

// Function to displays all the menu prompt messages
// from the pointer array of option a[]
void main_menu::normalvideo(int x,int y,char *str)
{
   gotoxy(x,y);
   cprintf("%s",str);
}

// Function to move the cursor on the menu prompt
// with a reverse video color
void main_menu::reversevideo(int x,int y,char *str)
{
    textcolor(5+143);
    textbackground(WHITE);
    gotoxy(x,y);
    cprintf("%s",str);
    textcolor(GREEN);
    textbackground(BLACK);
}

void main_menu::box(int x1,int y1,int x2,int y2)
{
     for(int col=x1;col<x2;col++)
     {
	   gotoxy(col,y1);
	   cprintf("%c",196);
	   gotoxy(col,y2);
	   cprintf("%c",196);
     }

     for(int row=y1;row<y2;row++)
     {
	   gotoxy(x1,row);
	   cprintf("%c",179);
	   gotoxy(x2,row);
	   cprintf("%c",179);
     }
     gotoxy(x1,y1);
     cprintf("%c",218);
     gotoxy(x1,y2);
     cprintf("%c",192);
     gotoxy(x2,y1);
     cprintf("%c",191);
     gotoxy(x2,y2);
     cprintf("%c",217);
}

// Displaying the main menu of music system
char main_menu::menu()
{
    clrscr();

    textcolor(22);
    box(20, 6, 65, 20);
    box(18, 4, 67, 22);
    textcolor(5+143);
    gotoxy(36, 5);
    textbackground(BLUE);
    cprintf("M U S I C");
    textbackground(BLACK);
    textcolor(22);
    for(i = 1; i < 9; i++)
	normalvideo(32, i+10, a[i]);
    reversevideo(32, 10, a[0]);
    i = done = 0;
    _setcursortype(_NOCURSOR);
    do
    {
	int key = getch();

	switch (key)
	{
	    case 00:
		key = getch();

		switch (key)
		{
		    case 72:
			normalvideo(32, i+10, a[i]);
			i--;
			if (i == -1)
			    i = 8;
			reversevideo(32,i+10, a[i]);
			break;
		    case 80:
			normalvideo(32, i+10, a[i]);
			i++;
			if (i == 9)
			    i = 0;
			reversevideo(32, i+10, a[i]);
			break;
		}
		break;
	    case 13:
		done = 1;
	}
    } while (!done);

    _setcursortype(_NOCURSOR);
    return(i+49);
}

/* The function main_menu() is used to display the main menu system */
void main_menu::control_menu()
{

    char choice;
    cassettes cas;
    account a;
    balance bal;
    other oth;

    do
    {
	choice = menu();
	clrscr();

	switch (choice)
	{
	    case '1':
		_setcursortype(_NORMALCURSOR);
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);

		cas.new_cassettes(); // New cassette/CD entry function
		break;
	    case '2':
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);
		cassettes ini;
		ini.display_list(); // Glogal list of cassettes/CDs function
		break;
	    case '3':
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);

		 _setcursortype(_NORMALCURSOR);

		a.new_account(); // Enter the personwise sale cassette/CD
		break;
	    case '4':
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);

		account a;
		_setcursortype(_NORMALCURSOR);
		a.Display_sales(); // Displays the sales cassettes/CDs
		break;
	    case '5':
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);

		_setcursortype(_NORMALCURSOR);
		oth.Expense_other(); // Entry of other expenses
		break;
	    case '6':
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);
		gotoxy(10,10);
		oth.display_expense();    // Displays the expenses
		break;
	    case '7':
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);
		gotoxy(10,10);
		bal.balance_cassette(); // Function to display the balance cassettes/CDs in shop
		break;
	    case '8' :
		box(3, 1, 75, 24);
		box(5, 2, 73, 23);
		gotoxy(10,10);
		// Monthly profit after every transaction
		bal.monthly_profit();
		break;
	    case '9' :exit(0);
	   }
      } while (choice != 8);
}

/* Function to draw horizontal line for menu*/
void shape::line_hor(int column1, int column2, int row, char c)
{
    for (column1; column1 <= column2; column1++)
    {
	gotoxy(column1, row);
	cout << c;
    }
}

/* Function to draw vertical line for menu */
void shape::line_ver(int row1, int row2, int column, char c)
{
    for (row1; row1 <= row2; row1++)
    {
	gotoxy(column, row1);
	cout << c;
    }
}

/* Function for drawing boxes for menu */
void shape::box(int column1, int row1, int column2, int row2, char c)
{
    char ch = 218;
    char c1, c2, c3, c4;
    char l1 = 196, l2 = 179;
    if (c == ch)
    {
	c1 = 218;
	c2 = 191;
	c3 = 217;
	c4 = 217;
	l1 = 196;
	l2 = 179;
    }
    else
    {
	c1 = c;
	c2 = c;
	c3 = c;
	c4 = c;
	l1 = c;
	c2 = c;
    }

    gotoxy(column1, row1);
    cout << c1;
    gotoxy(column2, row1);
    cout << c2;
    gotoxy(column1, row2);
    cout << c3;
    gotoxy(column2, row2);
    cout << c4;
    column1++;
    column2--;
    line_hor(column1, column2, row1, l1); //Horizontal line
    line_hor(column1, column2, row2, l1);
    column1--;
    column2++;
    row1++;
    row2--;
    line_ver(row1, row2, column1, l2); // Vertical line
    line_ver(row1, row2, column2, l2);
}

/* Function to display help about this project */
void main_menu::help(void)
{
    clrscr();

    setbkcolor(7);
    settextstyle(7,HORIZ_DIR,5);
    outtextxy(70,20,"Welcome to Video Shop");
    settextstyle(2,HORIZ_DIR,5);
    outtextxy(60,100, "This project can keep record of daily music cassettes/CDs ");
    delay(2);
    outtextxy(60,130, "transaction. This program is capable of holding any no. of cassettes/CDs.");
    delay(2);
    outtextxy(60,160, "-In first option you can enter new cassette/CD information");
    delay(2);
    outtextxy(60,190, "-In second option you can see the list of all the cassettes/CDs");
    delay(2);
    outtextxy(60,220,"-In third option you can sales the cassettes/CDs according to demand");
    delay(2);
    outtextxy(60,250, "-Through fourth optiion you can see the sales status");
    delay(2);
    outtextxy(60,280, "In the fifth option enter your daily other expenses");
    delay(2);
    outtextxy(60,310, "-In fifth option you can take monthWise individual account report");
    delay(2);
    outtextxy(60,340,"-In sixth option you can take reports of other expenses");
    delay(2);
    outtextxy(60,370, "Note-: Enter only valid data while you maintain this package");
    delay(2);
    outtextxy(60,400, "-And last option is Quit (Exit From Music Window)");
    delay(2);

    settextstyle(7,HORIZ_DIR,4);
    outtextxy(80,420,"Press any key to continue...");
    getch();

}

/* Function for displaying a cassette/CD information when required */
void cassettes::display(int t_cas_code)
{
    fstream file;
    file.open("cassettes.dat", ios::in);
    file.seekg(0, ios::beg);

    // Displays the record contents matching
    // with t_cas_code from cassettes.dat data file
    while (file.read((char *)this, sizeof(cassettes)))
    {
	if (t_cas_code == cas_code)
	{
	    gotoxy(8, 5);
	    cout << "Account no. " << cas_code;
	    gotoxy(10, 8);
	    cout << "Name : ";
	    puts(Cass_name);
	    gotoxy(10, 9);
	    cout << "Comany Name : ";
	    puts(Comp_name);

	    gotoxy(10, 10);
	    cout << "Price : " << setw(15)    // setwidth
			<< setprecision(2)    // set position of decimal point
			<< setiosflags(ios::left)   // set left justified output
			<< setiosflags(ios::showpoint)  // always show decimal point
                        << setiosflags(ios::fixed)    // set fixed notation for display
                        << price;
            break;
        }
    }

    file.close();
}

/* Function to find is their records in cassette.dat file or not */

int cassettes::last_cas_code(void)
{
    fstream file;
    file.open("cassettes.dat", ios::in);
    file.seekg(0, ios::beg);
    int tcount = 0;
    int count = 0;

    // Founds the last account no.
    while (file.read((char *)this, sizeof(cassettes)))
    {
        tcount = cas_code;
        count = count + tcount;
    }

    file.close();
    return count;
}

/* Function to find is their records in file person.dat or not */

int account::last_cas_code(void)
{
    fstream file;
    file.open("Person.dat", ios::in);
    file.seekg(0, ios::beg);
    int tcount = 0;
    int count = 0;
    // Founds the last account no.
    while (file.read((char *)this, sizeof(account)))
    {
        tcount = cas_code;
        count = count + tcount;
    }
    file.close();
    return count;
}


/* Function for returning balance cassette/CD.
This function returns the balance cassette/CD on code wise
to know the current balance from "Tbal.dat" data file. */

int balance::give_balance(int t_cas_code)
{
    fstream file;
    file.open("Tbal.dat", ios::in);
    file.seekg(0, ios::beg);
    int t_balance = 0;

    // Gives the last balance of an individual account
    while (file.read((char *)this, sizeof(balance)))
    {
        if (file.eof())
            break;

        if (cas_code == t_cas_code)
        {
            t_balance = cas_bal;
            break;
        }
    }
    file.close();
    return t_balance;
}

// Function to return the cassette/CD price
float balance::return_price(int t_cas_code)
{
    float t_price = 0.0;
    fstream file;
    file.open("Tbal.dat", ios::in);
    file.seekg(0, ios::beg);

    // Gives the last balance of an individual account
    while (file.read((char *)this, sizeof(balance)))
    {
        if (file.eof())
            break;

        if (cas_code == t_cas_code)
        {
            t_price = price;
            break;
        }
    }
    file.close();
    return t_price;
}

/* This function add_to_file() is used to create
new/fresh record in the data file */

void cassettes::add_to_file(int t_cas_code, char t_Cass_name[30],
char t_Comp_name[30], int t_cas, int tdd, int tmm, int tyy, float t_price)
{
    cas_code = t_cas_code;
    strcpy(Cass_name, t_Cass_name);
    strcpy(Comp_name, t_Comp_name);
    tot_cassette = t_cas;
    dd = tdd;
    mm = tmm;
    yy = tyy;
    price = t_price;

    fstream file;

    // Appends new account record with the price into cassettes.dat data file
    file.open("cassettes.dat", ios::out|ios::app);
    file.write((char *)this, sizeof(cassettes));
    file.close();
}

/* This function add_to_file() is used to
create new/fresh record in the data file */

void balance::add_to_file(int t_cas_code,
int t_cas, int tdd, int tmm, int tyy, float t_price)
{
    int bal = give_balance(t_cas_code);

    if (bal > 0)
    {
        fstream file;
        file.open("Tbal.dat", ios::in);
        fstream temp;
        temp.open("TEMP.dat", ios::out);
        file.seekg(0,ios::beg);

        // Uses a copy method to delete the cassette/CD
        // from cassette.dat data file
        while (!file.eof())
        {
            file.read((char *)this, sizeof(balance));
            if (file.eof())
                break;
            if (cas_code != t_cas_code)
                temp.write((char *)this, sizeof(balance));
            else
            {
                cas_code = t_cas_code;
                cas_bal = t_cas + bal;
                dd = tdd;
                mm = tmm;
                yy = tyy;
                price = t_price;
                temp.write((char *)this, sizeof(balance));
            }
        }

        file.close();
        temp.close();
        file.open("Tbal.dat", ios::out);
        temp.open("TEMP.dat", ios::in);
        temp.seekg(0, ios::beg);

        // Copy the TEMP.dat contents into cassette.dat data file
        while (!temp.eof())
        {
            temp.read((char *)this, sizeof(balance));
            if (temp.eof())
                break;
            file.write((char *)this, sizeof(balance));
        }
        file.close();
        temp.close();
    }
    else
    {
        cas_code = t_cas_code;
        cas_bal = t_cas;
        dd = tdd;
        mm = tmm;
        yy = tyy;
        price = t_price;
        fstream file;

        // Appends new account record with the
        // price into cassettes.dat data file
        file.open("Tbal.dat", ios::out|ios::app);
        file.write((char *)this, sizeof(balance));
        file.close();
    }
}

// Function for deleting a account from cassettes.dat file
void cassettes::delete_cassette(int t_cas_code)
{
    fstream file;
    file.open("cassettes.dat", ios::in);
    fstream temp;
    temp.open("TEMP.dat", ios::out);
    file.seekg(0,ios::beg);

    // Uses a copy method to delete the account
    // from cassette.dat data file
    while (!file.eof())
    {
        file.read((char *)this, sizeof(cassettes));
        if (file.eof())
            break;
        if (cas_code != t_cas_code)
            temp.write((char *)this, sizeof(cassettes));
    }

    file.close();
    temp.close();
    file.open("cassettes.dat", ios::out);
    temp.open("TEMP.dat", ios::in);
    temp.seekg(0, ios::beg);

    // Copy the TEMP.dat contents into cassette.dat data file
    while (!temp.eof())
    {
        temp.read((char *)this, sizeof(cassettes));
        if (temp.eof())
            break;
        if (cas_code != t_cas_code)
            file.write((char *)this, sizeof(cassettes));
    }

    file.close();
    temp.close();
}

// Function for deleting a balance from Tbal.dat file
void balance::delete_balance(int t_cas_code)
{
    fstream file;
    file.open("Tbal.dat", ios::in);
    fstream temp;
    temp.open("TEMP.dat", ios::out);
    file.seekg(0,ios::beg);

    // Uses a copy method to delete the account from Tbal.dat data file
    while (!file.eof())
    {
        file.read((char *)this, sizeof(balance));
        if (file.eof())
            break;
        if (cas_code != t_cas_code)
            temp.write((char *)this, sizeof(balance));
    }
    file.close();
    temp.close();
    file.open("Tbal.dat", ios::out);
    temp.open("TEMP.dat", ios::in);
    temp.seekg(0, ios::beg);

    // Copy the TEMP.dat contents into Tbal.dat data file
    while (!temp.eof())
    {
        temp.read((char *)this, sizeof(balance));
        if (temp.eof())
            break;
        if (cas_code != t_cas_code)
            file.write((char *)this, sizeof(balance));
    }

    file.close();
    temp.close();
}

/* Function for add an account details of
daily tranaction into person.dat file. */

void account::add_to_file(int t_cas_code, char tP_name[30],
char tP_address[30],int tNo_cass, int d1, int m1, int y1)
{

    cas_code = t_cas_code;
    strcpy(P_name, tP_name);
    strcpy(P_address, tP_address);
    No_cass = tNo_cass;
    dd = d1;
    mm = m1;
    yy = y1;

    fstream file;

    // Appends the transaction record into person.dat data file
    file.open("person.dat", ios::out|ios::app);
    file.write((char *)this, sizeof(account));
    file.close();
}

/* Function for deleting an account from person.dat file. */
void account::delete_account(int t_cas_code)
{
    fstream file;
    file.open("person.dat", ios::in); // Open to read records
    fstream temp;
    temp.open("TEMP.dat", ios::out); // Open to write records
    file.seekg(0, ios::beg);    // Positioned from begining of the file

    // Uses the copy method for deleting the
    // transaction record from person.dat data file
    while (!file.eof())
    {
        file.read((char *)this, sizeof(account));
        if (file.eof())
            break;
        if (cas_code != t_cas_code)
            temp.write((char *)this, sizeof(account));
    }

    file.close();
    temp.close();
    file.open("person.dat", ios::out);
    temp.open("TEMP.dat", ios::in);
    temp.seekg(0, ios::beg);

    // Uses copy method to transfer the record
    // from TEMP.dat file to person.dat data file
    while (!temp.eof())
    {
        temp.read((char *)this, sizeof(account));
        if (temp.eof())
            break;
        if (cas_code != t_cas_code)
            file.write((char *)this, sizeof(account));
    }

    file.close();
    temp.close();
}

// Function for add an other expenses details in other.dat data file
void other::add_to_file(int tO_code, char tNat_Expen[30],
int d1, int m1,  int y1, float tamount)
{
    O_code = tO_code;
    strcpy(Nat_Expen, tNat_Expen);
    dd = d1;
    mm = m1;
    yy = y1;
    amount = tamount;

    fstream file;

    // Appends the transaction record into other.dat data file
    file.open("other.dat", ios::out|ios::app);
    file.write((char *)this, sizeof(other));
    file.close();
}

/* Function for displaying an account from "cassettes.dat". */
void cassettes::display_list(void)
{
    clrscr();
    int flag;
    float tot_price = 0.0, tot_balance = 0.0;
    fstream file;
    gotoxy(25,2);

    cout << "List of cassettes/CDs in Music Shop";
    gotoxy(25, 3);
    cout << "===============================";
    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;
    gotoxy(62, 3);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;
    gotoxy(1, 4);
    for (int j = 1; j <= 79; j++)
        cout << "=";

    gotoxy(1, 5);
    cout << "Code #";
    gotoxy(9, 5);
    cout << "Cassette/CD Name";
    gotoxy(34, 5);
    cout << "Company Name";
    gotoxy(55, 5);
    cout << "Qty";
    gotoxy(61, 5);
    cout << "Price";
    gotoxy(72, 5);
    cout << "Total";
    gotoxy(1, 6);
    for (j = 1; j <= 79; j++)
        cout << "=";

    file.open("cassettes.dat", ios::in);
    file.seekg(0,ios::beg);
    int row = 7;

    // Reads all the records to display on the screen
    while (file.read((char *)this, sizeof(cassettes)))
    {
        tot_price = 0.0;
        flag = 0;
        delay(2);
        gotoxy(3, row);
        cout << cas_code;
        gotoxy(9, row);
        puts(Cass_name);
        gotoxy(34, row);
        puts(Comp_name);
        gotoxy(55, row);
        cout << tot_cassette;

        gotoxy(61, row);
        cout <<  setw(15)
            << setprecision(2)
            << setiosflags(ios::left)
            << setiosflags(ios::showpoint)
            << setiosflags(ios::fixed)
            << price;

        tot_price = tot_cassette * price;

        gotoxy(72, row);
        cout <<  setw(15)
            << setprecision(2)
            << setiosflags(ios::left)
            << setiosflags(ios::showpoint)
            << setiosflags(ios::fixed)
            << tot_price;

        tot_balance = tot_balance + tot_price;

        row++;
        if (row > 23)
        {
            flag = 1;
            row = 6;
            gotoxy(4, 24);
            cout << "Press any key to continue.... ";
            getch();
            clrscr();
        }
    }

    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;
    gotoxy(3, row);
    cout << "Total price of cassettes/CDs is : ";

    gotoxy(72, row);
    cout << setw(15)
        << setprecision(2)
        << setiosflags(ios::left)
        << setiosflags(ios::showpoint)
        << setiosflags(ios::fixed)
        << tot_balance;

    file.close();
    if (!flag)
    {
        gotoxy(4, 24);
        cout << "Press any key to continue...";
        getch();
    }
    getch();
}

/* Function for displaying an cassette/CD sales on day wise */
void account::Display_sales(void)
{
    clrscr();
    int flag;
    fstream file;

    int tcas_code;
    int xdd, xmm, xyy;
    clrscr();
    gotoxy(10, 8);
    cout << "Enter the cassette/CD Code ";
    gotoxy(10, 9);
    cout <<"As 1 or 2 or 3 ";
    gotoxy(10, 11);
    cout << "Enter the date " ;
    gotoxy(30, 9);
    cin >> tcas_code;
    gotoxy(30, 11);
    cin >> xdd;
    gotoxy(32, 11);
    cout << "-";
    gotoxy(33, 11);
    cin >> xmm;
    gotoxy(35, 11);
    cout << "-";
    gotoxy(36, 11);
    cin >> xyy;
    if (tcas_code < 1)
    {
        gotoxy(5, 23);
        cout << "Your entry is not valid";
        getch();
        return;
    }
    else
        if (tcas_code > 3)
        {
            gotoxy(5, 23);
            cout << "Your entry is not valid";
            getch();
            return;
        }

    clrscr();
    gotoxy(25, 2);
    cout << "Sales Report in Music Shop";
    gotoxy(25, 3);
    cout << "==========================";
    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;
    gotoxy(62, 3);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;
    gotoxy(1, 5);
    for (int j = 1; j <= 79; j++)
        cout << "=";

    gotoxy(1, 6);
    cout << "Code #";
    gotoxy(9, 6);
    cout << "Name";
    gotoxy(34, 6);
    cout << "Address";
    gotoxy(55, 6);
    cout << "Qty";
    gotoxy(61, 6);
    cout << "Date";

    gotoxy(1, 7);
    for (j = 1; j <= 79; j++)
        cout << "=";
    file.open("Person.dat", ios::in);
    file.seekg(0,ios::beg);
    int row = 8;

    // Reads all the records to display on the screen
    while (file.read((char *)this, sizeof(account)))
    {
        if ((tcas_code == cas_code) && (xmm == mm) && (xyy == yy))
        {
            flag = 0;
            delay(2);
            gotoxy(3, row);
            cout << cas_code;
            gotoxy(9, row);
            puts(P_name);
            gotoxy(34, row);
            puts(P_address);
            gotoxy(55, row);
            cout << No_cass;

            gotoxy(61, row);
            cout << dd << "-" << mm << "-" << yy;
            ++row;
            if (row > 23)
            {
                flag = 1;
                row = 6;
                gotoxy(4, 24);
                cout << "Press any key to continue.... ";
                getch();
                clrscr();
            }
        }
    }

    ++row;

    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;

    file.close();
    if (!flag)
    {
        gotoxy(4, 24);
        cout << "Press any key to continue...";
        getch();
    }
    getch();
}

/* Function for displaying other expenses in shop */
void other::display_expense(void)
{
    clrscr();
    int flag;
    fstream file;

        /* The other expence code as :
            1     -    Salary to workers,
            2    -    Electricity bill
            3    -    Telephone bills
            4    -    Miscellaneous expenses    */


    int tO_code;
    int xdd, xmm, xyy;
    clrscr();
    gotoxy(10, 8);
    cout << "Enter the Expense Code ";
    gotoxy(10, 9);
    cout <<"1 Salary to Worker ";
    gotoxy(10, 10);
    cout <<"2 Electricity bill ";
    gotoxy(10, 11);
    cout <<"3 Telephone bill ";
    gotoxy(10, 12);
    cout <<"4 Miscellaneous ";

    gotoxy(10, 13);
    cout <<"Enter your Choice";

    gotoxy(10, 14);
    cout << "Enter the date " ;
    gotoxy(30, 13);
    cin >> tO_code;
    gotoxy(30, 14);
    cin >> xdd;
    gotoxy(32, 14);
    cout << "-";
    gotoxy(33, 14);
    cin >> xmm;
    gotoxy(35, 14);
    cout << "-";
    gotoxy(36, 14);
    cin >> xyy;
    if (tO_code < 1)
    {
        gotoxy(5, 23);
        cout << "Your entry is not valid";
        getch();
        return;
    }
    else
        if (tO_code > 4)
        {
            gotoxy(5, 23);
            cout << "Your entry is not valid";
            getch();
            return;
        }

    clrscr();

    gotoxy(25, 2);
    cout << "Other Expenses in Music Shop";
    gotoxy(25, 3);
    cout << "============================";
    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;

    gotoxy(62, 3);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;

    gotoxy(1, 5);
    for (int j = 1; j <= 79; j++)
        cout << "=";

    gotoxy(1, 6);
    cout << "Code #";
    gotoxy(9, 6);
    cout << "Nature Expense";
    gotoxy(34, 6);
    cout << "Date";
    gotoxy(55, 6);
    cout << "Amount";

    gotoxy(1, 7);
    for (j = 1; j <= 79; j++)
        cout << "=";

    file.open("other.dat", ios::in);
    file.seekg(0,ios::beg);
    int row = 8;

    // Reads all the records to display on the screen
    while (file.read((char *)this, sizeof(other)))
    {

        if ((tO_code == O_code) && (xmm == mm) && (xyy == yy))
        {
            flag = 0;
            delay(2);
            gotoxy(3, row);

            cout << O_code;
            gotoxy(9, row);
            puts(Nat_Expen);
            gotoxy(34, row);
            cout << dd << "-" << mm << "-" << yy;
            gotoxy(55, row);
            cout << setw(15)
                << setprecision(2)
                << setiosflags(ios::left)
                << setiosflags(ios::showpoint)
                << setiosflags(ios::fixed)
                << amount;

            ++row;
            if (row > 23)
            {
                flag = 1;
                row = 6;
                gotoxy(4, 24);
                cout << "Press any key to continue.... ";
                getch();
                clrscr();
            }
        }
    }

    ++row;
    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;

    file.close();
    if (!flag)
    {
        gotoxy(4, 24);
        cout << "Press any key to continue...";
        getch();
    }
    getch();
}


/* Function for clearing specified row and column. */
void account::clear(int col, int row)
{
    for (int j = col; j <= 79; j++)
    {
        gotoxy(j, row);
        cout << " ";
    }
}

/* Function for return name of the account
holder from cassettes.dat. */
char *cassettes::return_name(int t_cas_code)
{
    fstream file;
    file.open("cassettes.dat", ios::in);
    file.seekg(0, ios::beg);
    char t_Cass_name[30];

    // Return the name to display at report screen if found
    while (file.read((char *)this, sizeof(cassettes)))
    {
        if (cas_code == t_cas_code)
        {
            strcpy(t_Cass_name, Cass_name);
            break;
        }
    }
    file.close();
    return t_Cass_name;
}

/* Function for return Comp_name of the account holder from cassettes.dat. */
char *cassettes::return_address(int t_cas_code)
{
    fstream file;
    file.open("cassettes.dat", ios::in);
    file.seekg(0, ios::beg);
    char t_Comp_name[30];

    // Return the Comp_name to display at report screen if found
    while (file.read((char *)this, sizeof(cassettes)))
    {
        if (cas_code == t_cas_code)
        {
            strcpy(t_Comp_name, Comp_name);
            break;
        }
    }
    file.close();
    return t_Comp_name;
}

void balance::monthly_profit()
{

    clrscr();
    int flag;
    fstream file;
    gotoxy(25,1);

    cout << "Monthly Profit Statement";
    gotoxy(25, 2);
    cout << "========================";

    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);

    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;

    float T_bal = 0.0;
    float G_bal = 0.0;
    gotoxy(55, 3);
    cout << "As on Date: " << d1 << "/" << m1 << "/" << y1;

    gotoxy(1, 4);
    for (int j = 1; j <= 79; j++)
        cout << "=";

    gotoxy(1, 5);
    cout << "Code #";
    gotoxy(15, 5);
    cout << "Total Balance";
    gotoxy(40, 5);
    cout << "Date";

    gotoxy(50, 5);
    cout << "Unit Price";

    gotoxy(65, 5);
    cout << "Total Amount";

    gotoxy(1, 6);
    for (j = 1; j <= 79; j++)
        cout << "=";

    file.open("Tbal.dat", ios::in);
    file.seekg(0,ios::beg);
    int row = 7;

    float cod1=0.0;
    float cod2=0.0;
    float cod3=0.0;
    // Reads all the records to display on the screen
    while (file.read((char *)this, sizeof(balance)))
    {
        flag = 0;
        if (cas_code == 1)
            cod1 = price;
        else
            if (cas_code == 2)
                cod2 = price;
            else
                cod3 = price;
        T_bal = cas_bal * price;
        delay(2);
        gotoxy(3, row);
        cout << cas_code;
        gotoxy(20, row);
        cout << cas_bal;
        gotoxy(40, row);
        cout << dd <<"-"<< mm << "-" << yy;
        gotoxy(53, row);
        cout << setw(15)
            << setprecision(2)
            << setiosflags(ios::left)
            << setiosflags(ios::showpoint)
            << setiosflags(ios::fixed)
            << price;
        G_bal = G_bal + T_bal;

        gotoxy(68, row);
        cout << setw(15)
            << setprecision(2)
            << setiosflags(ios::left)
            << setiosflags(ios::showpoint)
            << setiosflags(ios::fixed)
            << T_bal;
        T_bal = 0.0;
        row++;
        if (row > 23)
        {
            flag = 1;
            row = 6;
            gotoxy(4, 24);
            cout << "Press any key to continue.... ";
            getch();
            clrscr();
        }
    }

    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;
    gotoxy(50, row);
    cout << "Grand Total";
    gotoxy(68, row);
    cout << setw(15)
        << setprecision(2)
        << setiosflags(ios::left)
        << setiosflags(ios::showpoint)
        << setiosflags(ios::fixed)
        << G_bal;

    file.close();
    row++;
    float saltotal = 0.0;
    account a;
    saltotal = a.sales_status(m1, y1, cod1, cod2, cod3);    // Will display the sales status
    row++;

    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;
    gotoxy(5, row);
    cout << "This month's Sales Amount";
    gotoxy(50, row);
    cout << setw(15)
        << setprecision(2)
        << setiosflags(ios::left)
        << setiosflags(ios::showpoint)
        << setiosflags(ios::fixed)
        << saltotal;

    float gother = 0.0;
    other oth;
    gother =  oth.other_status(m1, y1);
    row = row + 2;
    gotoxy(5, row);
    cout << "Other expenses ";
    gotoxy(50, row);
    cout << setw(15)
        << setprecision(2)
        << setiosflags(ios::left)
        << setiosflags(ios::showpoint)
        << setiosflags(ios::fixed)
        << gother;


    row++;

    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;
    gotoxy(5, row);
    cout << "Net Profit";

    float net_bal = 0.0;
    net_bal = (G_bal + saltotal) - gother;
    gotoxy(50, row);
    cout << setw(15)
        << setprecision(2)
        << setiosflags(ios::left)
        << setiosflags(ios::showpoint)
        << setiosflags(ios::fixed)
        << net_bal;

    if (!flag)
    {
        gotoxy(4, 24);
        cout << "Press any key to continue...";
        getch();
    }
    getch();
}

// Function to find the sales total value
float account::sales_status(int m1, int y1, float cod1, float cod2, float cod3)
{
    fstream file;
    file.open("Person.dat", ios::in);
    file.seekg(0,ios::beg);
    // Reads all the records to display on the screen
    float ts = 0.0;
    float gts = 0.0;
    while (file.read((char *)this, sizeof(account)))
    {
        if ((m1 == mm) && (y1 == yy))
        {
            if (cas_code == 1)
                ts = No_cass * cod1;
            else
                if (cas_code == 2)
                    ts = No_cass * cod2;
                else
                    ts = No_cass * cod3;
            gts = gts + ts;
            ts = 0;
        }
    }
    file.close();
    return gts;
}

// Function to find the other status
float other::other_status(int m1, int y1)
{
    fstream file;
    file.open("other.dat", ios::in);
    file.seekg(0,ios::beg);
    // Reads all the records to display on the screen
    float goth = 0.0;
    while (file.read((char *)this, sizeof(other)))
    {
        if ((m1 == mm) && (y1 == yy))
        {
            goth = goth + amount;
        }
    }
    file.close();
    return goth;
}

// Function to display the balance cassette/CD in music shop

void balance::balance_cassette(void)
{

    clrscr();
    int flag;
    fstream file;
    gotoxy(25,1);

    cout << "List of Balance cassettes/CDs";
    gotoxy(25, 2);
    cout << "=========================";
    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;

    float T_bal = 0.0;
    float G_bal = 0.0;
    gotoxy(55, 3);
    cout << "As on Date: " << d1 << "/" << m1 << "/" << y1;

    gotoxy(1, 4);
    for (int j = 1; j <= 79; j++)
        cout << "=";

    gotoxy(1, 5);
    cout << "Code #";
    gotoxy(15, 5);
    cout << "Total Balance";
    gotoxy(40, 5);
    cout << "Date";

    gotoxy(50, 5);
    cout << "Unit Price";

    gotoxy(65, 5);
    cout << "Total Amount";

    gotoxy(1, 6);
    for (j = 1; j <= 79; j++)
        cout << "=";

    file.open("Tbal.dat", ios::in);
    file.seekg(0,ios::beg);
    int row = 7;

    // Reads all the records to display on the screen
    while (file.read((char *)this, sizeof(balance)))
    {
        flag = 0;
        T_bal = cas_bal * price;
        delay(2);
        gotoxy(3, row);
        cout << cas_code;
        gotoxy(20, row);
        cout << cas_bal;
        gotoxy(40, row);
        cout << dd <<"-"<< mm << "-" << yy;
        gotoxy(53, row);
        cout << setw(15)
            << setprecision(2)
            << setiosflags(ios::left)
            << setiosflags(ios::showpoint)
            << setiosflags(ios::fixed)
            << price;
        G_bal = G_bal + T_bal;

        gotoxy(68, row);
        cout << setw(15)
            << setprecision(2)
            << setiosflags(ios::left)
            << setiosflags(ios::showpoint)
            << setiosflags(ios::fixed)
            << T_bal;
        T_bal = 0.0;
        row++;
        if (row > 23)
        {
            flag = 1;
            row = 6;
            gotoxy(4, 24);
            cout << "Press any key to continue.... ";
            getch();
            clrscr();
        }
    }

    gotoxy(1, row);
    for (j = 1; j <= 79; j++)
        cout << "=";
    row++;
    gotoxy(50, row);
    cout << "Grand Total";
    gotoxy(68, row);
    cout << setw(15)
        << setprecision(2)
        << setiosflags(ios::left)
        << setiosflags(ios::showpoint)
        << setiosflags(ios::fixed)
        << G_bal;

    file.close();
    if (!flag)
    {
        gotoxy(4, 24);
        cout << "Press any key to continue...";
        getch();
    }
    getch();
}

/* Function for recording the new cassettes/CDs in shop */
void cassettes::new_cassettes(void)
{
    char ch;
    int i, valid;
    clrscr();

    // Declaring the class objects for different operations with
    // member functions

    account a;
    balance bal;
    cassettes ini;

    shape s;
    s.box(2, 1, 79, 25, 218);
    s.box(25, 2, 54, 4, 219);

    gotoxy(65, 2);
    cout << "<0>=Exit";

    gotoxy(3,3);
    for (i = 1; i<= 76; i++)
        cprintf(" ");
    textbackground(BLACK);
    textcolor(BLACK+BLINK);
    textbackground(WHITE);
    gotoxy(30, 3);
    cprintf("Add New cassette/CD");
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    int d1, m1, y1;        // Declare the variable for purchase date of cassette/CD
    struct date d;        // For extracting system date

    getdate(&d);        // Extract the system.date
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;

    // Declaring the temporary variables for cassette/CD entry

    char c_code[10];

    int t_cas_code;
    char t_Cass_name[30];
    char t_Comp_name[30];
    int t_cas;
    int tdd, tmm, tyy;
    float t_price;

    t_cas_code = ini.last_cas_code();

    // Appends and deletes a false record
    // to create primary position in data files
    if (t_cas_code == 0)
    {
        ini.add_to_file(t_cas_code, "abc", "xyz", 1, 1, 1, 1, 1.1);
        ini.delete_cassette(t_cas_code);
        bal.add_to_file(t_cas_code, 0, 0, 0, 0, 0.0);
        bal.delete_balance(t_cas_code);
    }

    gotoxy(4, 6);
    cout << "Date: " << d1 << '/' << m1 << '/' << y1;

    gotoxy(5, 8);
    cout << "Cassette/CD Code # ";
    gotoxy(5, 10);
    cout << "Cassette/CD Name : ";
    gotoxy(5, 12);
    cout << "Company Name : ";
    gotoxy(5, 14);
    cout << "Total cassettes/CDs: ";
    gotoxy(5, 16);
    cout << "Individual Cassette/CD price : ";
    gotoxy(5, 18);
    cout << "Enter the Date ";

    // Steps to enter the Cassette/CD code either 1 - 2 - 3.
    do
    {
        a.clear(22, 8);
        a.clear(5, 23);        // Clears the buttom message
        gotoxy(5, 23);
        cout << "Enter cassettes/CDs Code either 1/2/3 ";
        valid = 1;
        gotoxy(22, 8);
        gets(c_code);
        t_cas_code = atoi(c_code);

        if (t_cas_code <= 0)
        {
            valid = 0;
            a.clear(5, 23);
            gotoxy(5, 23);
            cprintf("\7Should not other than 1, 2, 3");
            getch();
            gotoxy(5, 23);
            cout << "Enter cassettes/CDs Code either 1/2/3 ";

        }
    } while (!valid);
    a.clear(5, 23);

    // Steps to enter the Cassette/CD name
    do
    {
        a.clear(22, 10);
        a.clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter Name of the Cassette/CD";
        valid = 1;
        gotoxy(22, 10);
        gets(t_Cass_name);
        strupr(t_Cass_name);
        if (t_Cass_name[0] == '0')
            return;
        if (strlen(t_Cass_name) == 0 || strlen(t_Cass_name) > 25)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7Cassette/CD Name should not greater than 25");
            getch();
        }
    }while (!valid);
    a.clear(5, 23);

    // Steps to enter company name
    do
    {
        a.clear(22, 12);
        a.clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter Company Name ";
        valid = 1;
        gotoxy(22, 12);
        gets(t_Comp_name);
        strupr(t_Comp_name);
        if (t_Comp_name[0] == '0')
            return;
        if (strlen(t_Comp_name) == 0 || strlen(t_Comp_name) > 25)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7Company Name should not greater than 25");
            getch();
        }
    }while (!valid);
    a.clear(5, 23);

    // Steps to enter the total cassettes/CDs purchased
    do
    {
        a.clear(22, 14);
        a.clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter Total number of cassettes/CDs purchased";
        valid = 1;
        gotoxy(22, 14);
        gets(c_code);
        t_cas = atoi(c_code);
        if (t_cas == 0)
        {
            valid = 0;
            a.clear(5, 23);
            gotoxy(5, 23);
            cprintf("\7Enter valid Cassette/CD number");
            getch();
            gotoxy(5, 23);
            cout << "Enter Total number of cassettes/CDs purchased";

        }
    }while (!valid);
    a.clear(5, 23);

    // Steps to enter the Cassette/CD/price
    do
    {
        a.clear(35, 16);
        a.clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter individual Cassette/CD price";
        valid = 1;
        gotoxy(35, 16);
        gets(c_code);
        t_price = atof(c_code);
        if (t_price <= 0)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7Enter valid price for Cassette/CD");
            getch();
        }
    }while (!valid);
    a.clear(5, 23);

    // Steps to enter the purchase date
    a.clear(22, 18);
    a.clear(5, 23);
    gotoxy(5, 23);
    cout << "Enter date on which the Cassette/CD is purchase";
    valid = 1;
    gotoxy(22, 18);
    cin >> tdd;
    gotoxy(25, 18);
    cout << "-";
    gotoxy(26, 18);
    cin >> tmm;
    gotoxy(28, 18);
    cout << "-";
    gotoxy(29, 18);
    cin >> tyy;
    a.clear(5, 23);

    do
    {
        a.clear(5, 20);
        valid = 1;
        gotoxy(5, 20);
        cout << "Do you want to save the record <Y/N>: ";
        ch = getche();
        if (ch == '0')
            return;
        ch = toupper(ch);
    }while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return;

    // Appends the records contents into
    // both cassettes.dat and person.dat data files
    ini.add_to_file(t_cas_code, t_Cass_name, t_Comp_name,
        t_cas, tdd, tmm, tyy, t_price);

    bal.add_to_file(t_cas_code, t_cas, tdd, tmm, tyy, t_price);
}

/* This function update_balance() is used to update the
balance Cassette/CD in Tbal.dat data file */

void balance::Update_balance(int t_cas_code,
int t_cas, int tdd, int tmm, int tyy, float t_price)
{
    int bal = give_balance(t_cas_code);

    if (bal > 0)
    {
        fstream file;
        file.open("Tbal.dat", ios::in);
        fstream temp;
        temp.open("TEMP.dat", ios::out);
        file.seekg(0,ios::beg);

        // Uses a copy method to delete the account from Tbal.dat data file
        while (!file.eof())
        {
            file.read((char *)this, sizeof(balance));
            if (file.eof())
                break;
            if (cas_code != t_cas_code)
                temp.write((char *)this, sizeof(balance));
            else
            {
                cas_code = t_cas_code;
                cas_bal = bal - t_cas;
                dd = tdd;
                mm = tmm;
                yy = tyy;
                price = t_price;
                temp.write((char *)this, sizeof(balance));
            }
        }

        file.close();
        temp.close();
        file.open("Tbal.dat", ios::out);
        temp.open("TEMP.dat", ios::in);
        temp.seekg(0, ios::beg);

        // Copy the TEMP.dat contents into Tbal.dat data file
        while (!temp.eof())
        {
            temp.read((char *)this, sizeof(balance));
            if (temp.eof())
                break;
            file.write((char *)this, sizeof(balance));
        }

        file.close();
        temp.close();
    }
    else
    {
        cas_code = t_cas_code;
        cas_bal = t_cas;
        dd = tdd;
        mm = tmm;
        yy = tyy;
        price = t_price;
        fstream file;

        // Appends new account record with the price
        // into cassettes.dat data file
        file.open("Tbal.dat", ios::out|ios::app);
        file.write((char *)this, sizeof(balance));

        file.close();
    }
}


/* Function for creating new account for new customer. */
void account::new_account(void)
{
    char ch;
    int i, valid;
    clrscr();
    balance bal;

    shape s;
    s.box(2, 1, 79, 25, 218);
    s.box(25, 2, 54, 4, 219);

    gotoxy(65, 2);
    cout << "<0>=Exit";

    gotoxy(3,3);
    for (i = 1; i<= 76; i++)
        cprintf(" ");
    textbackground(BLACK);
    textcolor(BLACK+BLINK);
    textbackground(WHITE);
    gotoxy(30, 3);
    cprintf("Sales of cassettes/CDs");
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;
    int t_cas_code;

    int C_bal = 0;
    float t_price;
    char c_code[2];
    char tP_name[30];    // Person Name
    char tP_address[30];    // Person Address
    int tNo_cass;        // Number of Cassette/CD

    t_cas_code = last_cas_code();

    // Appends and deletes a false record to create
    // primary position in data files
    if (t_cas_code == 0)
    {
        add_to_file(t_cas_code, "xxxx", "xxxxx", 1, 1, 1, 1);
        delete_account(t_cas_code);
    }

    gotoxy(5, 6);
    cout << "Date: " << d1 << '/' << m1 << '/' << y1;
    gotoxy(5, 8);
    cout << "Cassette/CD Code ";
    gotoxy(5, 10);
    cout << "Name of Person : ";
    gotoxy(5, 12);
    cout << "Address : ";

    gotoxy(5, 14);
    cout << "Total Cassette/CD : ";

    // Steps to enter the Cassette/CD code either 1 - 2 - 3.
    do
    {
        clear(22, 8);
        clear(5, 23);        // Clears the buttom message
        gotoxy(5, 23);
        cout << "Enter cassettes/CDs Code either 1/2/3 ";
        valid = 1;
        gotoxy(22, 8);
        gets(c_code);
        t_cas_code = atoi(c_code);

        if (t_cas_code <= 0)
        {
            valid = 0;
            clear(5, 23);
            gotoxy(5, 23);
            cprintf("\7Should not other than 1, 2, 3");
            getch();
            gotoxy(5, 23);
            cout << "Enter cassettes/CDs Code either 1/2/3 ";
        }
        else
        {
            C_bal = bal.give_balance(t_cas_code);
            t_price = bal.return_price(t_cas_code);
            if (C_bal > 0)
            {
                gotoxy(40, 8);
                cout << "Total cassettes/CDs in Shop : " << C_bal;
                break;
            }
            else
            {
                cout << "There is no Cassette/CD in shop";
                return;
            }
        }
    } while (!valid);
    clear(5, 23);

    // Steps to enter the name of the purchase person
    do
    {
        clear(22, 10);
        clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter Name of the Person";
        valid = 1;
        gotoxy(22, 10);
        gets(tP_name);
        strupr(tP_name);
        if (tP_name[0] == '0')
            return;
        if (strlen(tP_name) == 0 || strlen(tP_name) > 25)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7Name should not greater than 25");
            getch();
            clear(5, 23);
        }

    }while (!valid);
    clear(5, 23);

    // Steps to enter the address of the purchase person
    do
    {
        clear(22, 12);
        clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter Name of the Person";
        valid = 1;
        gotoxy(22, 12);
        gets(tP_address);
        strupr(tP_address);
        if (tP_address[0] == '0')
            return;
        if (strlen(tP_address) == 0 || strlen(tP_address) > 25)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7Address should not greater than 25");
            getch();
            clear(5, 23);
        }

    }while (!valid);
    clear(5, 23);

    do
    {
        clear(22, 14);
        clear(5, 23);
        gotoxy(5, 23);
        cout << "No. of Cassette/CD ";
        valid = 1;
        gotoxy(22, 14);
        cin >> tNo_cass;
        if (tNo_cass > C_bal)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7The availability of Cassette/CD is not sufficient");
            getch();
        }
    }while (!valid);
    clear(5, 23);

    do
    {
        clear(5, 17);
        valid = 1;
        gotoxy(5, 17);
        cout << "Do you want to save the record <Y/N>: ";
        ch = getche();
        if (ch == '0')
            return;
        ch = toupper(ch);
    }while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return;

    // Updates the new balance after deducting the current sales

    // Appends the records contents into both person.dat data files
    add_to_file(t_cas_code, tP_name, tP_address, tNo_cass, d1, m1,  y1);

    bal.Update_balance(t_cas_code, tNo_cass, d1, m1, y1, t_price);
}

/* Function for enter the other expences in other.dat data file. */
void other::Expense_other(void)
{
    char ch;
    int i, valid;
    clrscr();
    account a;

    shape s;
    s.box(2, 1, 79, 25, 218);
    s.box(25, 2, 54, 4, 219);

    gotoxy(65, 2);
    cout << "<0>=Exit";
    gotoxy(3,3);
    for (i = 1; i<= 76; i++)
        cprintf(" ");
    textbackground(BLACK);
    textcolor(BLACK+BLINK);
    textbackground(WHITE);
    gotoxy(30, 3);
    cprintf("Other Expence in Shop");
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    int d1, m1, y1;
    struct date d;        // For extracting system date
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;

    char c_code[2];
    int tO_code;        // Other expence code
    char tNat_Expen[30];    // Nature of expense description
    float tamount;    // Expense amount

    gotoxy(5, 6);
    cout << "Date: " << d1 << '/' << m1 << '/' << y1;
    gotoxy(5, 8);
    cout << "Expense Code ";
    gotoxy(5, 10);
    cout << "Nature of Expense : ";
    gotoxy(5, 12);
    cout << "Amount : ";

    // Steps to enter the other expense code
    do
    {
        a.clear(22, 8);
        a.clear(5, 23);        // Clears the buttom message
        gotoxy(5, 23);
        cout << "Enter Expense code Code either 1/2/3/4 ";
        valid = 1;
        gotoxy(22, 8);
        gets(c_code);
        tO_code = atoi(c_code);

        if (tO_code <= 0)
        {
            valid = 0;
            a.clear(5, 23);
            gotoxy(5, 23);
            cprintf("\7Expence code should not other than 1/2/3/4");
            getch();
            gotoxy(5, 23);
            cout << "Enter other expense Codes either 1/2/3/4 ";
        }
    } while (!valid);
    a.clear(5, 23);

    // Steps to enter the nature of expense
    do
    {
        a.clear(22, 10);
        a.clear(5, 23);
        gotoxy(5, 23);
        cout << "Enter the Nature of expense";
        valid = 1;
        gotoxy(22, 10);
        gets(tNat_Expen);
        strupr(tNat_Expen);
        if (tNat_Expen[0] == '0')
            return;
        if (strlen(tNat_Expen) == 0 || strlen(tNat_Expen) > 25)
        {
            valid = 0;
            gotoxy(5, 23);
            cprintf("\7Nature of expense not greater than 25");
            getch();
            a.clear(5, 23);
        }

    }while (!valid);
    a.clear(5, 23);

    gotoxy(22, 12);
    cin >> tamount;

    do
    {
        a.clear(5, 17);
        valid = 1;
        gotoxy(5, 17);
        cout << "Do you want to save the record <Y/N>: ";
        ch = getche();
        if (ch == '0')
            return;
        ch = toupper(ch);
    }while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return;

    // Appends the records contents into both person.dat data files
    if (tamount > 0)
        add_to_file(tO_code, tNat_Expen, d1, m1,  y1, tamount);
}

/* Function for returning the record no. for updating price */
int cassettes::recordno(int t_cas_code)
{
    fstream file;
    file.open("cassettes.dat", ios::in);
    file.seekg(0, ios::beg);
    int count = 0;

    // Finds the record position in cassettes.dat data file
    while (file.read((char *)this, sizeof(cassettes)))
    {
        count++;
        if (t_cas_code == cas_code)
            break;
    }
    file.close();
    return count;
}

/* Function for closing any account after inputing account number. */
void account::close_account(void)
{
    clrscr();
    char t_acc[10];
    int t, t_cas_code;
    gotoxy(71, 1);
    cout << "<0>=Exit";
    gotoxy(5, 5);
    cout << "Enter the account no. ";
    gets(t_acc);
    t = atoi(t_acc);
    t_cas_code = t;
    if (t_cas_code == 0)
        return;
    clrscr();
    cassettes ini;
    balance bal;

    if (!bal.give_balance(t_cas_code))
    {
        gotoxy(5, 5);
        cout << "\7Account not found ";
        getch();
        return;
    }
    gotoxy(71, 1);
    cout << "<0>=Exit";
    gotoxy(3, 3);
    textbackground(WHITE);
    for (int i = 1; i <= 76; i++)
        cprintf(" ");
    textbackground(BLACK);
    textcolor(BLACK+BLINK);
    textbackground(WHITE);
    gotoxy(30, 3);
    cprintf("Close account screen");
    textcolor(LIGHTGRAY);
    textbackground(BLACK);
    int d1, m1, y1;
    struct date d;
    getdate(&d);
    d1 = d.da_day;
    m1 = d.da_mon;
    y1 = d.da_year;
    gotoxy(5, 6);
    cout << "Date: " << d1 << "/" << m1 << "/" << y1;
    char ch;

    ini. display(t_cas_code);

    do
    {
        clear(5, 15);
        gotoxy(5, 15);
        cout << "Close this account <y/n?? ";
        ch = getche();
        if (ch == '0')
            return;
        ch = toupper(ch);
    }while (ch != 'N' && ch != 'Y');

    if (ch == 'N')
        return;

    // Function calls to delete the existing account no.
    ini.delete_cassette(t_cas_code);
    delete_account(t_cas_code);
    gotoxy(5, 20);
    cout << "\7Account Deleted";
    gotoxy(5, 23);
    cout << "Press any key to continue...";
    getch();
}

// Main program logic which control the class members and member functions.
void main(void)
{
    main_menu  m_menu;
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, "..\\bgi");

    m_menu.help();
    closegraph();
    m_menu.control_menu();
}
