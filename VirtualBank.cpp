#include<iostream>  
#include<fstream>    
#include<cctype>     
#include<iomanip>  
using namespace std;

class account    						 //Class definition starts 
{
	int accountnumber;
	char name[100];
	int deposit;
	char type[100];
public:
	void create_account();   			 //function to create a new account
	void show_account() const;    		 //function to show account details
	void modify();   					 //function to modify account details
	void acceptdeposit(int); 		     //function to accept deposit amount
	void withdraw(int);    				 //function to subtract withdrawal amount
	void report() const;   				 //function to show data in tabular format
	int returnaccountnumber() const;  	     //For returning account number
	int returnbalance() const;    			 //For returning balance amount
	char accounttype() const;  		     //For returning type of account
};        								 //Class definition ends


void account::create_account()
{
	cout << "\nEnter The Account Number :";
	cin >> accountnumber;
	cout << "\n\nEnter, Name of The Account Holder : ";
	cin.ignore();
	cin.getline(name, 100);
	cout << "\nEnter Type of Account checking or savings? (checkings/savings) : ";
	cin >> type;
	cout << "\nEnter the minimum amount for checking:500 and for savings:1000 : ";
	cin >> deposit;  //We have set the minimum initial amount for savings be 500 & for current be 1000 
	cout << "\n\n\nthe account has been successfully created....";
}

void account::show_account() const
{
	cout << "\nAccount Number : " << accountnumber;
	cout << "\nAccount Holder Name : ";
	cout << name;
	cout << "\nType of Account : ";
	cout <<type;
	cout << "\nBalance amount : " ;
	cout << deposit;
}


void account::modify()
{
	cout << "\nAccount Number : " << accountnumber;
	cout << "\nModify Account Holder Name : ";
	cin.ignore();
	cin.getline(name, 100);
	cout << "\nModify Type of Account : ";
	cin >> type;
	cout << "\nModify Balance amount : ";
	cin >> deposit;
}

void account::acceptdeposit(int x)
{
	deposit += x;
}

void account::withdraw(int x)
{
	deposit -= x;
}

void account::report() const
{
	cout << accountnumber << setw(10) << " " << name << setw(10) << " " << type << setw(6) << deposit << endl;
}

int account::returnaccountnumber() const
{
	return accountnumber;
}

int account::returnbalance() const
{
	return deposit;
}

char account::accounttype() const
{
	return type[100];
}
void write_acc();    						   	//function to write record in binary file
void display_sp(int);  						    //function to display account details given by user
void modify_acc(int);   					    //function to modify record of file
void delete_acc(int);  						    //function to delete record of file
void display_all();        						//function to display all account details
void deposit_withdraw(int, int); 				// function to desposit/withdraw amount for given account
void intro();  								    //introductory screen function


int main()
{
	char ch;
	int num;
	intro();
	do
	{
		system("cls");   						//Clear The Screen
		cout << "\n\n\n\tBANK MENU";
		cout << "\n\n\t1. NEW ACCOUNT";
		cout << "\n\n\t2. DEPOSIT";
		cout << "\n\n\t3. WITHDRAW";
		cout << "\n\n\t4. BALANCE ENQUIRY";
		cout << "\n\n\t5. COMPLETE ACCOUNT HOLDERS LIST";
		cout << "\n\n\t6. CLOSE AN ACCOUNT";
		cout << "\n\n\t7. MODIFY AN ACCOUNT";
		cout << "\n\n\t8. EXIT";
		cout << "\n\n\tSelect Your Option (1-8) ";
		cin >> ch;
		system("cls");   						//Clear The Screen
		switch (ch)
		{
		case '1':
			write_acc();
			break;
		case '2':
			cout << "\n\n\tEnter The Account Number : "; cin >> num;
			deposit_withdraw(num, 1);
			break;
		case '3':
			cout << "\n\n\tEnter The Account Number : "; cin >> num;
			deposit_withdraw(num, 2);
			break;
		case '4':
			cout << "\n\n\tEnter The Account Number : "; cin >> num;
			display_sp(num);
			break;
		case '5':
			display_all();
			break;
		case '6':
			cout << "\n\n\tEnter The Account Number : "; cin >> num;
			delete_acc(num);
			break;
		case '7':
			cout << "\n\n\tEnter The Account Number : "; cin >> num;
			modify_acc(num);
			break;
		case '8':
			cout << "\n\n\tThank you for Visiting Our Bank!";
			cout << "\n\n\tWe hope this visit has been pleasant";
			cout << "\n\n\tHave a Good Day";
			cout <<"\n";
			cout <<"\n";
			cout <<"\n";
			cout <<"\n";
			cout <<"\n";
			cout <<"\n";
			cout <<"Please press enter to exit\n";
			break;
		default:cout << "\a";
		}
		cin.ignore();
		cin.get();
	} while (ch != '8');
	return 0;
}

												   	// Function To write the account data to .dat file
void write_acc()
{
	account ac;
	ofstream x;
	x.open("account.dat", ios::binary | ios::app);
	ac.create_account();
	x.write(reinterpret_cast<char *> (&ac), sizeof(account));
	x.close();
}


void display_sp(int n)     					   	 //function to retrive a record from file stored
{
	account ac;
	bool flag = false;
	ifstream x;
	x.open("account.dat", ios::binary);
	if (!x)
	{
		cout << "The requested File could not be opened!! Press any Key to exit...";
		return;
	}
	cout << "\nBALANCE DETAILS\n";

	while (x.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.returnaccountnumber() == n)
		{
			ac.show_account();
			flag = true;
		}
	}
	x.close();
	if (flag == false)
		cout << "\n\n The requested Account number does not exist";
}//function to modify record of an account which is stored in file
void modify_acc(int n)
{
	bool found = false;
	account ac;
	fstream x;
	x.open("account.dat", ios::binary | ios::in | ios::out);
	if (!x)
	{
		cout << "The requested File could not be open !! Press any Key...";
		return;
	}
	while (!x.eof() && found == false)
	{
		x.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.returnaccountnumber() == n)
		{
			ac.show_account();
			cout << "\n\nEnter The New Details of account : " << endl;
			ac.modify();
			int pos = (-1)*static_cast<int>(sizeof(account));
			x.seekp(pos, ios::cur);
			x.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	x.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}											
												//function to delete a record from file
void delete_acc(int n)
{
	account ac;
	ifstream x;
	ofstream y;
	x.open("account.dat", ios::binary);
	if (!x)
	{
		cout << "The requested File could not be open !! Press any Key...";
		return;
	}
	y.open("Temp.dat", ios::binary);
	x.seekg(0, ios::beg);
	while (x.read(reinterpret_cast<char *> (&ac), sizeof(account)))
	{
		if (ac.returnaccountnumber() != n)
		{
			y.write(reinterpret_cast<char *> (&ac), sizeof(account));
		}
	}
	x.close();
	y.close();
	remove("account.dat");
	rename("Temp.dat", "account.dat");
	cout << "\n\n\tRecord Deleted ..";
}
												// function to display account details from the stored file
void display_all()
{
	account ac;
	ifstream x;
	x.open("account.dat", ios::binary);
	if (!x)
	{
		cout << "File could not be open !! Press any Key...";
		return;
	}
	cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.      NAME           Type  Balance\n";
	cout << "====================================================\n";
	while (x.read(reinterpret_cast<char *> (&ac),  sizeof(account)))
	{
		ac.report();
	}
	x.close();
}
													// function to withdraw amout from the account
void deposit_withdraw(int n, int option)
{
	int amt;
	bool found = false;
	account ac;
	fstream x;
	x.open("account.dat", ios::binary | ios::in | ios::out);
	if (!x)
	{
		cout << "The requested File could not be open !! Press any Key...";
		return;
	}
	while (!x.eof() && found == false)
	{
		x.read(reinterpret_cast<char *> (&ac), sizeof(account));
		if (ac.returnaccountnumber() == n)
		{
			ac.show_account();
			if (option == 1)
			{
				cout << "\n\n\tTO DEPOSITE AMOUNT ";
				cout << "\n\nEnter The amount to be deposited : ";
				cin >> amt;
				ac.acceptdeposit(amt);
			}
			if (option == 2)
			{
				cout << "\n\n\tTO WITHDRAW AMOUNT ";
				cout << "\n\nEnter The amount to be withdraw : ";
				cin >> amt;
				int bal = ac.returnbalance() - amt;
				if ((bal<500 && ac.accounttype() == 'S') || (bal<1000 && ac.accounttype() == 'C'))
					cout << "Insufficience balance";
				else
					ac.withdraw(amt);
			}
			int pos = (-1)*static_cast<int>(sizeof(ac));
			x.seekp(pos, ios::cur);
			x.write(reinterpret_cast<char *> (&ac), sizeof(account));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}
	x.close();
	if (found == false)
		cout << "\n\n Record Not Found ";
}
													//The Entry/Welcome Screen
void intro()
{
	cout << "\n\n\n\t\t\t\t\tWelcome To UTSA Engineering Programming";
	cout << "\n\n\t\t\t\t\t\t\tC++ project";

	//So Please use with Admin Privilage for the compiled .exe, so that it could access the disk space
	cout << "\n";
	cout << "\n";
	cout << "\n";
	cout << "\nPlease Press Enter To Continue........";
	cin.get();
}