#include<iostream>
#include<string>
#include<fstream>
#include<iomanip>
#include<algorithm>
using namespace std;

class bank {
	char name[20], address[30], adhar[20];
	int otp, pin, bank_id;
	double tel_no, balance;
	int count = 0;

public:
	int get_count() {
		return count;
	}
	int get_bankid() {
		return bank_id;
	}
	double get_bal() {
		return balance;
	}

	int get_pin() {
		return pin;
	}

	void report() {
		cout << bank_id << setw(20) << name << setw(15) << "$ "<< balance <<endl;
	}

	void disp_bal()
	{
		cout<<"\n";
		cout<<"Account number "<<"    "<<"Balance"<<endl;
		cout<<bank_id<<setw(20)<<balance;
	}


	void create_Account();

	void deposit(float amount) {
		balance += amount;
		cout<<"New balance is :";
		cout<<"$ "<<(float)balance<<endl;
	}

	void withdraw(double amount) {
		balance -= amount;
		cout<<"New balance is :";
		cout<<"$ "<<(float)balance<<endl;
	}

	void show_Account()
	{
		cout<<"Bank Account Number: "<<bank_id<<endl;
		cout<<"Name: "<<name<<endl;
		cout<<"Adhar Number: "<<adhar<<endl;
		cout<<"Telephone Number : "<<tel_no<<endl;
		cout<<"Current Balance: "<<balance<<endl;
	}

	void modify(int ip)
	{
		int temp_pin;
		bool flag=false;

		if(ip==1)
		{   cout << "Enter name (less than 10 characters):" << endl;
			cin >> name;
			flag=true;
		}
		if(ip==2)
		{
			cout << "Enter address" << endl;
			cin >> address;
			flag=true;
		}
		if(ip==3){
			cout<<"Enter current pin"<<endl;
			cin>>temp_pin;
			if(temp_pin==pin){
			cout << "Enter new security pin" << endl;
			cin >> pin;
			flag=true;
			}
			else{
				cout<<"Wrong pin!"<<endl;
			}
		}
		if(ip==4)
				{	cout << "Enter your mobile number :" << endl;
					cin >> tel_no;
					flag=true;
				}

		if(ip==5)
		{
			flag=true;
		}
		if(flag==true)
		{
			cout<<"\t\tDetails Updates Successfully"<<endl;
		}
		else
		{
			cout<<"\t\tUpdate not successful!"<<endl;
		}
	}

};

void bank::create_Account() {

	cout << "Enter name :" << endl;
	cin >> name;
	cout << "Enter address" << endl;
	cin >> address;
	cout << "Enter Adhar card number :" << endl;
	cin >> adhar;
	cout << "Enter your mobile number :" << endl;
	cin >> tel_no;
	cout << "Your Account number is :" << endl;
	cin >> bank_id;
	count++;
	cout << "Enter security pin" << endl;
	cin >> pin;

	balance = 0.00;
}

void write_Account() {
	bank obj;
	ofstream out;
	out.open("Account.dat", ios::binary | ios::app);
	obj.create_Account();
	out.write((char *) &obj, sizeof(bank));
	out.close();

}

void write_deposit(int n, int option) {
	/*int temp_count;
	 bank obj;
	 fstream out;
	 temp_count=obj.get_count();
	 out.seekg(-sizeof(obj)*temp_count);

	 out.open("Account.dat", ios::in |ios::out| ios::binary);
	 obj.deposit();
	 out.write((char*) &obj, sizeof(bank));
	 out.close();
	 */
	int pin1;
	float amount;
	bool flag = false;
	bank obj;
	fstream out;
	out.open("Account.dat", ios::binary | ios::in | ios::out);
	if (!out) {
	 cout << "Account not found" << endl;
	 return;
	 }
	while (out.read((char*) &obj, sizeof(bank)) && flag == false) {
		if (obj.get_bankid() == n) {
			if (option == 1) {
				cout<<"Enter pin :";
				cin>>pin1;
				if(obj.get_pin()==pin1){
				cout << "\n\nEnter The amount to be deposited";
				cin >> amount;
				obj.deposit(amount);
				flag = true;
				}
				else {
					cout<<"Wrong pin!"<<endl;
				}
			}
			//------ end of deposit
			if (option == 2) {
				cout<<"Enter pin :";
				cin>>pin1;
				if(obj.get_pin()==pin1){
				cout << "\n\nEnter The amount to be withdraw :";
				cin >> amount;
				try {
					if (obj.get_bal() < amount)
						throw obj.get_bal();
					obj.withdraw(amount);
					flag = true;
				} catch (double balance) {
					cout << "Insufficient funds!" << endl;
					return;
				}
				}
			}
			// ----withdraw if ends
		} //   1st if ends

		int pos=(-1)* sizeof(obj);
		out.seekp(pos,ios::cur);
		out.write((char *) &obj, sizeof(bank));

		if(flag==true)
		{
			cout<<"Transaction successful"<<endl;
		}
		else
		{
			cout<<"Transaction failed"<<endl;
		}
	}		//while loop ends
}

void write_show() {
	bank obj;
	ifstream in;
	in.open("Account.dat", ios::binary);
	/*if(!in)
	 {
	 cout<<"File could not be open !! Press any Key...";
	 return;
	 }
	 */
	if(obj.get_count()!=0){
	if(obj.get_pin()!=0){
	cout << "\n\n\t\tAccount HOLDER LIST\n\n";
	cout << "====================================================\n";
	cout << "A/c no.         NAME                Balance    	  \n";
	cout << "====================================================\n";
	while (in.read((char *) &obj, sizeof(bank))) {
		obj.report();
	}
	cout << "=====================================================\n";
	}
	}
	else
	{
		cout<<"\n\n\tNO RECORD FOUND !"<<endl;
	}
	in.close();
	return;
}

void write_balance(int n) {
	 bank obj;

		int flag=0,pin1;
		ifstream in;
		in.open("Account.dat",ios::binary);
		if(!in)
		{
			cout<<"File could not be open !! Press any Key..";
			return;
		}

		while(in.read((char *) &obj, sizeof(bank)))
		{
			if(obj.get_bankid()==n)
			{	cout<<"Enter pin"<<endl;
				cin>>pin1;
				if(obj.get_pin()==pin1){
				cout<<"======================================"<<endl;
				cout<<"BALANCE DETAILS :\n";
				obj.disp_bal();
				cout<<"\n======================================"<<endl;
				flag=1;
				}
			}

		}
		in.close();
		if(flag==0)
			cout<<"\n\nAccount number does not exist";

	}

void write_delete(int n)
{
    	bank obj;
    	bool flag=false;
		ifstream in;
		ofstream out;
		in.open("Account.dat",ios::binary);
		if(!in)
		{
			cout<<"File could not be open !! Press any Key...";
			return;
		}
		out.open("Temp.dat",ios::binary);
		in.seekg(0,ios::beg);
		while(in.read((char *) &obj, sizeof(bank)))
		{
			if(obj.get_bankid()!=n)
			{
				flag=true;
				out.write((char *) &obj, sizeof(bank));
			}
		}
		in.close();
		out.close();
		remove("Account.dat");
		rename("Temp.dat","Account.dat");

		cout<<"\n\n\tRecord Deleted Successfully"<<endl;;
		in.close();
		out.close();
}

void write_modify(int n,int pin1)
{
	bool flag=false;

        bank obj;
        int ip;
		fstream File;
		File.open("Account.dat",ios::binary|ios::in|ios::out);
		if(!File)
		{
			cout<<"File could not be open !! Press any Key...";
			return;
		}
		while(File.read((char *) &obj, sizeof(bank)) && flag==false)
		{
			if(obj.get_bankid()==n)
			{
				if(obj.get_pin()==pin1){
				obj.show_Account();
				cout<<"\n\nSelect The Detail to be updated:"<<endl;
				do{
					cout<<"\n";
				cout<<"1)Name "<<endl;
				cout<<"2)Address "<<endl;
				cout<<"3)Pin "<<endl;
				cout<<"4)Mobile number "<<endl;
				cout<<"5)Return to main menu "<<endl;
				cin>>ip;
				obj.modify(ip);
				}while(ip!=5);
				int pos=(-1)*sizeof(bank);
				File.seekp(pos,ios::cur);
				File.write((char *) &obj, sizeof(bank));
				//cout<<"\n\n\t Record Updated Successfully";
				flag=true;
				}
			}
		}
		File.close();
		if(flag==false)
			cout<<"\n\n Record Not Found ";

}



int main() {
int ch;

do {
	cout << "\n\n\n\t\t\t\t**** MAIN MENU ****";
	cout << "\n\n\t1) NEW ACCOUNT";		//done
	cout << "\t\t\t\t2) DEPOSIT AMOUNT";		//done
	cout << "\n\n\t3) WITHDRAW AMOUNT";		//done
	cout << "\t\t\t4) BALANCE ENQUIRY";       //done
	cout << "\n\n\t5) ALL ACCOUNT HOLDER LIST";   //done
	cout << "\t\t6) CLOSE AN ACCOUNT";           //done
	cout << "\n\n\t7) MODIFY AN ACCOUNT";
	cout << "\t\t\t8) EXIT";
	cout << "\n\t\t\t\t      ********";
	cout << "\n\n\tSelect Your Option (1-8) ";
	cin >> ch;

	switch (ch) {
	case 1:
		cout << "\tWELCOME TO ALCHEMY BANK " << endl;
		write_Account();
		break;

	case 2:
		int num;
		cout << "Enter bank id :" << endl;
		cin >> num;
		write_deposit(num, 1);
		break;

	case 3:

		cout << "Enter bank id :" << endl;
		cin >> num;
		write_deposit(num, 2);
		break;

	case 4:
		int pin1;
		cout<<"Enter Account Number"<<endl;
		cin>>num;
		write_balance(num);
		break;

	case 5:
		write_show();
		break;

	case 6:
		cout<<"Enter Account Number :"<<endl;
		cin>>num;
		write_delete(num);
		break;

	case 7:
		cout<<"Enter Account Number"<<endl;
		cin>>num;
		cout<<"Enter Pin Number "<<endl;
		cin>>pin1;
		write_modify(num,pin1);
		break;

	case 8: cout<<"\t\tTHANK YOU FOR BANKING WITH ALCHEMY BANK"<<endl;
			break;

	default: cout<<"Enter correct option!"<<endl;
	break;
	}
} while (ch != 8);

return 0;
}


