#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cstring>
#include <stdio.h>
#include <fstream>
#include <cstdio>
#include <time.h>
#include <termios.h>
#include <unistd.h>
#include <limits> // Added for std::numeric_limits and streamsize
using namespace std;

// Cross-platform getch implementation
#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <termios.h>
#include <unistd.h>
int getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int k=7,r=0,flag=0;
ofstream fout;
ifstream fin;

char name1[50],ctn1[50];
int age1,cradit1;
float points1=0,mbuy1=0;

void craditcard();
void admin();
void user();
// Platform-specific clear screen and gotoxy
void design(int a,char ch) {
    cout << "\n\n\n";
#ifdef _WIN32
    system("cls");
#else
    std::cout << "\033[2J\033[1;1H";
#endif
    cout << "\t\t\t" << setw(a+5) << setfill(ch);
    cout << "\n\n\t\t\t\t\tSAHUJI";
    cout << "\n\n\t\t\t" << setw(a) << setfill(ch);
    cout << "\n\n";
}
#ifdef _WIN32
void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
#else
void gotoxy(int x, int y) {
    std::cout << "\033[" << y << ";" << x << "H";
}
#endif

struct date
{
    int mm,dd,yy;
};

// Cross-platform getpass
string getpass(const char *prompt, bool show_asterisk = true) {
#ifdef _WIN32
    const char BACKSPACE=8;
    const char RETURN=13;
    string password;
    unsigned char ch=0;
    cout << prompt << endl;
    DWORD con_mode;
    DWORD dwRead;
    HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);
    GetConsoleMode(hIn, &con_mode);
    SetConsoleMode(hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT));
    while(ReadConsoleA(hIn, &ch, 1, &dwRead, NULL) && ch != RETURN) {
        if(ch==BACKSPACE) {
            if(password.length()!=0) {
                if(show_asterisk) cout << "\b \b";
                password.resize(password.length()-1);
            }
        } else {
            password+=ch;
            if(show_asterisk) cout << '*';
        }
    }
    cout << endl;
    SetConsoleMode(hIn, con_mode);
    return password;
#else
    termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    string password;
    char ch;
    cout << prompt;
    while ((ch = getchar()) != '\n') {
        if (show_asterisk) std::cout << '*';
        password += ch;
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    std::cout << std::endl;
    return password;
#endif
}

// Admin password file path
const string ADMIN_PWD_FILE = "adminpwd.txt";

// Read admin password from file, or create with default if missing
string get_admin_password() {
    ifstream pwdfile(ADMIN_PWD_FILE);
    string pwd;
    if (pwdfile.is_open()) {
        getline(pwdfile, pwd);
        pwdfile.close();
        if (!pwd.empty()) return pwd;
    }
    // If file missing or empty, create with default
    ofstream out(ADMIN_PWD_FILE);
    out << "admin" << endl;
    out.close();
    return "admin";
}

// Set new admin password
void set_admin_password(const string& newpwd) {
    ofstream out(ADMIN_PWD_FILE);
    out << newpwd << endl;
    out.close();
}

class project // base and main class where almost every thing is done.
{
	friend class bill;
	protected:
    int itemno ;
    char name[25];
    date d;
public:
    void add()// member function used to add product in file
    {
        cout<<"\n\n\tItem identification No: ";
        cin>>itemno;

        cout<<"\n\n\tName of the item: ";
        cin>>name;
        cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
        cin>>d.mm>>d.dd>>d.yy;
    }
      void uadd()
    {
        cout<<"\n\n\tName of the item: ";
        cin>>name;
        cout<<"\n\n\tManufacturing Date(dd-mm-yy): ";
        cin>>d.mm>>d.dd>>d.yy;
    }

       void show()// used to display product on screen
    {
        cout<<"\n\tItem identification  No: ";
        cout<<itemno;
        cout<<"\n\n\tName of the item: ";
        cout<<name;
        cout<<"\n\n\tDate : ";
        cout<<d.mm<<"-"<<d.dd<<"-"<<d.yy;
    }
    int retno()// used to calculate grand total amount
    {
        return(itemno);

    }
    void report()
    {
        gotoxy(3,k);
        cout<<itemno;
        gotoxy(13,k);
        puts(name);
    }
}po;

class amount: public project// derived class of base class project
{
	friend class bill;
	protected:
    float mrp,price,qty,tax,gross,dis,iamt,tqty,total;
public:
    void add();
    void show();
    void pay();
    void pay1(int ,int);
    void refille();
    void edt();
    void report();
    void del(int);
    void report1();
    void surv();
    float retiamt()
    {
    	return (iamt);
	}
    void qnt(int a)
      {
      	qty=a;
	  }

	  float rettotal()
	  {
	  	return (total);
	  }
	int retnum()
	{
		return (retno());
	}


} amt;
void amount::add()// used to add numerical part of product to file
{
    project::add();
    cout<<"\n\n\t cost Price: ";
    cin>>price;
    cout<<"\n\n\tMark price: ";
    cin>>mrp;
    cout<<"\n\n\tQuantity: ";
    cin>>qty;
    tqty=qty;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;
    gross=mrp+(mrp*(tax/100));
    iamt=(gross-(gross*(dis/100)));
    total=iamt*qty;
    fout.write((char *)&amt,sizeof(amt));
    fout.close();
}
void amount::edt()
{
	project::uadd();
	cout<<"\n\n\t cost Price: ";
    cin>>price;
    cout<<"\n\n\t Mark Price: ";
    cin>>mrp;
    cout<<"\n\n\tTax percent: ";
    cin>>tax;
    cout<<"\n\n\tDiscount percent: ";
    cin>>dis;
    gross=mrp+(mrp*(tax/100));
    iamt=(gross-(gross*(dis/100)));
	total=iamt*qty;
}
void amount::del(int d)// used to delete unwanted product.
{
           flag=0;
           int ino=d;
           fin.close();
            fstream tmp("temp.dat",ios::binary|ios::out);
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
            }
            fin.seekg(0);
            while(fin.read((char*)&amt, sizeof(amt)))
            {
                int x=amt.project::retno();
                if(x!=ino)
                    tmp.write((char*)&amt,sizeof(amt));
                else
                {
                    flag=1;
                }
            }
            fin.close();
            tmp.close();
            fout.open("itemstore.dat",ios::trunc|ios::binary);
            fout.seekp(0);
            tmp.open("temp.dat",ios::binary|ios::in);
            if(!tmp)
            {
                cout<<"Error in File";
            }
            while(tmp.read((char*)&amt,sizeof(amt)))
                fout.write((char*)&amt,sizeof(amt));
            tmp.close();
            fout.close();
            if(flag==1)
               cout<<"\n\t\tItem Succesfully Deleted";
            else if (flag==0)
                cout<<"\n\t\tItem does not Exist! Please Retry";
            getch();
}

void amount::refille()// used to add number of goods when it is about to empty.
{

    	refi: design(45,'*');
        int inum,quanti;
        cout <<"\t\t\t\n Enter the item identification number:";
        cin>>inum;


        int  pos;
        char ans1,ans2;
	fstream fio;
	  	fio.open("itemstore.dat",ios::in|ios::out|ios::binary);
	 if(!fio)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
        }
	int ans=0;
	fio.seekg(0);
	while(fio.read((char*)&amt,sizeof(amt)))
	{
		pos=fio.tellg();

		if(inum==amt.project::retno())
		{
			ans++;
			cout<<endl<<"Input the quantity to be added"<<endl;
			cin>>quanti;
			fio.seekg(pos-sizeof(amt));
			qty+=quanti;
			total=qty*iamt;
			tqty=qty;
			fio.write((char*)&amt,sizeof(amt));
		}
	}
	if (ans==0)
	{
		cout<<endl<<"You entered invalid choice";
		cout<<endl<<"Do you wish to add quantity (Y/N)";
		cin>>ans1;
	}
	if (ans1=='y'||ans1=='y')
	goto refi;
	cout<<endl<<"do you want add other products(Y/N)";
	cin>>ans2;
	if (ans2=='y'||ans2=='y')
	goto refi;

	fio.close();
}

void amount::show()//used to show numerical portion of product
{
    fin.open("itemstore.dat",ios::binary);
    fin.read((char*)&amt,sizeof(amt));
    project::show();
    cout<<"\n\n\tindividual amount:";
    cout<<iamt;
    cout<<"\n\n\t quantity : ";
    cout<<qty;
    fin.close();
}

void amount::pay()// shows full detail of product in bill formate
{
    show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tCOST PRICE                        :Rs."<<price;
    cout<<"\n\t\tMARK PRICE		          :Rs."<<mrp;
    cout<<"\n\t\tQUANTITY                          :"<<qty;
    cout<<"\n\t\tTAX PERCENTAGE                    :"<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE               :"<<dis;
    cout<<"\n\t\tSELLING PRICE                       :Rs."<<iamt;
    cout<<"\n\t\tprofit                            :Rs."<<qty*(iamt-price);
    cout<<"\n\t\t----------------------------------------------";
    cout<<"\n\t\t*********************************************";
}
void amount::surv()
{
	float a=10*tqty/100;
	if (qty<a)
	{
		cout<<endl;
		cout<<endl<<"You need to add: ";
		project::show();
		cout<<endl<<"\tRemaining: "<<qty;
		cout<<endl;
		cout<<endl;
	}
	else
	{
		cout<<endl<<"You don't need to add";
		project::show();
		cout<<endl<<"\tRemaining: "<<qty;
		cout<<endl;
		cout<<endl;
		}
}

void amount::report()
{
    project::report();
    gotoxy(23,k);
    cout<<price;
    gotoxy(33,k);
    cout<<mrp;
    gotoxy(44,k);
    cout<<qty;
    gotoxy(52,k);
    cout<<tax;
    gotoxy(64,k);
    cout<<dis;
    gotoxy(74,k);
    cout<<iamt;

    k=k+1;
    if(k==50) {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
#ifdef _WIN32
        system("cls");
#else
        std::cout << "\033[2J\033[1;1H";
#endif
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<" ID NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
        gotoxy(80,5);
        cout<<" SELLING PRICE";

    }
}

int main()
{
	int ch;
    float gtotal;
        cout<<"\n \t\t\t=============================================================\n";
        cout<<"\n\t\t\t\t\tWELCOME SAHUJI To Cashier App \n";
        cout<<"\n \t\t\t=============================================================\n\n";
        cout<<"\n\n\n\n\t\t\t\t\t  Made By:";
        cout<<"\n\n\t\t\t\t Name\t\t\t\tMail Address";
		cout<<"\n\t\t\t\t Prarambha Bashyal\t\t\tprarambhabashyal@gmail.com";

		getch();
	while(1)
	{
		menu:
        std::string password,again;
		static int tryd=3;
		design(45,'*');
		cout<<"\n\t\t\t  1. VIEW/GENERATE CUSTOMER ID ";
        cout<<"\n\t\t\t  2. ADMIN ";
        cout<<"\n\t\t\t  3. USER ";
        cout<<"\n\t\t\t  4. EXIT ";
        cout<<"\n\t\t\t Enter Your choice: ";
        cin>>ch;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
        switch(ch)
        {
        	case 1:
        		craditcard();
        		break;
            case 2:
            	if(tryd>=1)
            	{
            		done:
                    password = getpass("\n\n\n\t\t\t\tEnter the password for Admin : ", true);
                    if(password==get_admin_password())
                    {
                        admin();
                        getch();
                        break;
                    }
                    else
                    {
                        tryd--;
                        design(50,'*');
                        if(tryd>=1)
                        {
                            cout<<"\n\n\n\t\t\tWrong password you have "<<tryd<<" chances left:";
                            cout<<"\n\n\n\t\t\t Do you want to try again (y/n) ? ";
                            cin>>again;
                            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
                            if(again=="y"||again=="Y")
                            goto done;
                        }
                        break;
                    }
				}
				else
				cout<<"\n\n\n\t\t\t Password try limit exceeded.";
				getch();
            	break;

              case 3:
               user();
               break;

            case 4:
                design(45,'*');
                gotoxy(20,15);
        cout<<"ARE YOU SURE, YOU WANT TO EXIT (Y/N)?";
        char yn;
        cin>>yn;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
        if((yn=='Y')||(yn=='y'))
        {
            design(45,'*');
            gotoxy(20,15);
            cout <<"|=======================================================================|";
            gotoxy(20,16);
            cout<<"|********************************THANKS*********************************|";
            gotoxy(20,17);
            cout <<"|=======================================================================|";
            getch();
            exit(0);
        }
            else if((yn=='N')||(yn=='n'))
            goto menu;
            else
        {
            goto menu;
        }


              break;
	        default:
                cout<<"\n\n\n\n\t\t\t\t\tEnter valid choice\n";
                getch();
				break;
        	    }
    }
    return 0;
}

 class costumer
 {
 	friend class bill;
 	protected:
 		char name[50],ctn[50];
 		int age,cradit;
 		float points,mbuy;
 		public:

 			void cal()
 			{
 				if(points1<points)
 				{
 					strcpy(name1,name);
 					strcpy(ctn1,ctn);
 					age1=age;
 					cradit1=cradit;
 					points1=points;
 					mbuy1=mbuy;
 				}
 			 }


			int retcradit()
			{
				return cradit;
			}
			void getdata()
			{
				cout<<endl<<"input name of customer :";
				cin>>name;
				cout<<endl<<"input citizenship no.: ";
				cin>>ctn;
				cout<<endl<<"input age:";
				cin>>age;
				calculation();
			}
			void calculation()
			{
				 srand( time(NULL) );
   				 int number = (rand() % 9000)+1000;
				  cradit=number;
			}

			int retcrad()
			{
				return cradit;
			}

			void display()
		{
			cout<<endl<<"\t Name: "<<name;
			cout<<endl<<"\t Citizenship no.: " <<ctn;
			cout<<endl<<"\t Age: "<<age;
			cout<<endl<<"\t Customer ID no. is: "<<cradit;
			cout<<endl<<"\t\t\txxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
	//		cout<<endl<<"\t money used: " <<mbuy;
	//		cout<<endl<<"\t points: "<<points;
		}
		void calc(int,int, int);
}co;

class bill
{
	protected:
	int craditcr, idcr,amtcr,sp,qntcr;
	char nam[50],ctn[50],prodnam[50];
	public:

		void disp()
		{
			cout<<endl;
			if(craditcr!=0)
			cout<<endl<<"costumer name:    "<<nam;
			if(craditcr!=0)
			cout<<endl<<"Customer ID no. :  "<<ctn;
			cout<<endl<<"product name:     "<<prodnam;

			if(craditcr!=0)
			cout<<endl<<"Customer ID no. :  "<<craditcr;
			cout<<endl<<"id of product:    "<<idcr;
			cout<<endl<<"individual price: "<<sp;
			cout<<endl<<"quantity:         "<<qntcr;
			cout<<endl<<"total price:      "<<amtcr;
			cout<<endl;
		}
		void billcalc(int,int,int);
}cr;


void admin_add_product() {
    design(45,'*');
    add1: fout.open("itemstore.dat",ios::binary|ios::app);
    amt.add();
    cout << "\n\t\tItem Added Successfully!";
    char choice;
    cout << " Do you want to add more item(y/n) ?\n";
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    if(choice =='y'||choice =='Y') goto add1;
    getch();
}

void admin_view_product_details() {
    design(45,'*');
    view1: flag=0;
    int ino;
    cout << "\n\n\t\tEnter Item  identification Number : ";
    cin >> ino;
    fin.open("itemstore.dat",ios::binary);
    if(!fin) {
        cout << "\n\nFile Not Found...\nProgram Terminated!";
        return;
    }
    fin.seekg(0);
    while(fin.read((char*)&amt,sizeof(amt))) {
        int x=amt.project::retno();
        if(x==ino) {
            amt.pay();
            flag=1;
            break;
        }
    }
    if(flag==0)
        cout << "\n\t\tItem does not exist....Please Retry!";
    getch();
    fin.close();
    char choice;
    cout << "\n\t do you want to view more item (y/n) ?";
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    if(choice =='y'||choice =='Y') goto view1;
}

void admin_view_all_products() {
    design(45,'*');
    gotoxy(34,3);
    cout<<" <<  BILL DETAILS >> ";
    gotoxy(1,5);
    cout<<"ITEM ID ";
    gotoxy(13,5);
    cout<<"NAME";
    gotoxy(23,5);
    cout<<"COST PRICE";
    gotoxy(33,5);
    cout<<"MRP";
    gotoxy(44,5);
    cout<<"QUANTITY";
    gotoxy(52,5);
    cout<<"TAX %";
    gotoxy(64,5);
    cout<<"DISCOUNT %";
    gotoxy(74,5);
    cout<<"SELLING PRICE";
    fin.open("itemstore.dat",ios::binary);
    if(!fin) {
        cout<<"\n\nFile Not Found...";
        return;
    }
    fin.seekg(0);
    float gtotal=0;
    k=7;
    int ff=0;
    while(!fin.eof()) {
        fin.read((char*)&amt,sizeof(amt));
        if(!fin.eof()) {
            amt.report();
            gtotal+=amt.rettotal();
            ff=0;
        }
        if(ff!=0) gtotal=0;
    }
    gotoxy(17,k);
    cout<<"\n\n\n\t\t\tGrand Total="<<gtotal;
    getch();
    fin.close();
}

void admin_delete_product() {
    view2: design(45,'*');
    flag=0;
    int ino;
    dele: cout<<"\n\n\tEnter Item Number to be deleted :";
    cin>>ino;
    char choice;
    cout<<" Do you want to delete this item(y/n) ?\n";
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    if(choice =='y'||choice =='Y') {
        fstream tmp("temp.dat",ios::binary|ios::out);
        fin.open("itemstore.dat",ios::binary);
        if(!fin) {
            cout<<"\n\nFile Not Found...";
            return;
        }
        fin.seekg(0);
        while(fin.read((char*)&amt, sizeof(amt))) {
            int x=amt.project::retno();
            if(x!=ino)
                tmp.write((char*)&amt,sizeof(amt));
            else
                flag=1;
        }
        fin.close();
        tmp.close();
        fout.open("itemstore.dat",ios::trunc|ios::binary);
        fout.seekp(0);
        tmp.open("temp.dat",ios::binary|ios::in);
        if(!tmp) {
            cout<<"Error in File";
            return;
        }
        while(tmp.read((char*)&amt,sizeof(amt)))
            fout.write((char*)&amt,sizeof(amt));
        tmp.close();
        fout.close();
        if(flag==1)
            cout<<"\n\t\t Item Successfully Deleted";
        else if(flag==0)
            cout<<"\n\t\t Item does not Exist! Please Retry";
        char choice2;
        cout<<"\n\t Do you want to delete more item (y/n) ?";
        cin >> choice2;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
        if(choice2 =='y'||choice2 =='Y') goto view2;
        getch();
    } else {
        goto dele;
    }
}

void admin_edit_product() {
    edta: design(45,'*');
    int inum;
    cout << "\n\n\tEnter Item Number to be edited :";
    cin >> inum;
    int pos;
    char ans1, ans2;
    fstream fio;
    fio.open("itemstore.dat", ios::in | ios::out | ios::binary);
    if (!fio) {
        cout << "\n\nFile Not Found...\nProgram Terminated!";
        return;
    }
    int ans = 0;
    fio.seekg(0);
    while (fio.read((char *)&amt, sizeof(amt))) {
        pos = fio.tellg();
        if (inum == amt.project::retno()) {
            ans++;
            fio.seekg(pos - sizeof(amt));
            amt.edt();
            fio.write((char *)&amt, sizeof(amt));
        }
    }
    if (ans == 0) {
        cout << endl << "You entered invalid choice";
        cout << endl << "Do you wish to edit (Y/N)";
        cin >> ans1;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    }
    if (ans1 == 'y' || ans1 == 'Y') goto edta;
    cout << endl << "Do you want edit other products(Y/N) ?";
    cin >> ans2;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    if (ans2 == 'y' || ans2 == 'Y') goto edta;
    fio.close();
}

void admin_refill_product() {
    amt.refille();
}

void admin_survey() {
    design(45, '*');
    fin.open("itemstore.dat", ios::binary);
    while (fin.read((char *)&amt, sizeof(amt))) {
        amt.surv();
    }
    fin.close();
    getch();
}

void admin_view_bills() {
    design(45, '*');
    fstream em;
    em.open("bill.txt", ios::app | ios::out | ios::binary | ios::in);
    em.seekg(0);
    while (em.read(reinterpret_cast<char *>(&cr), sizeof(cr))) {
        cr.disp();
    }
    em.close();
    getch();
}

void admin_gift_hamper() {
    fstream em;
    em.open("costumer.txt", ios::app | ios::out | ios::in);
    em.read(reinterpret_cast<char *>(&co), sizeof(co));
    while (!em.eof()) {
        co.cal();
        em.read(reinterpret_cast<char *>(&co), sizeof(co));
    }
    em.close();
    design(45, '*');
    cout << endl << "\t\t\t\tCONGRATULATIONS!!!";
    cout << endl << "\n\t\t\t\tCostumer of the year is " << name1;
    cout << endl << "full detail of customer of the year is: ";
    cout << endl << "\t Mr. " << name1;
    cout << endl << "\t Citizenship no.: " << ctn1;
    cout << endl << "\t age :" << age1;
    cout << endl << "\t Customer ID : " << cradit1;
    getch();
}

void admin_change_password() {
    string newpass, confirmpass;
    design(45, '*');
    cout << "\n\t\t\tCHANGE ADMIN PASSWORD";
    newpass = getpass("\n\n\t\tEnter new password: ", true);
    confirmpass = getpass("\n\t\tConfirm new password: ", true);
    if (newpass == confirmpass && !newpass.empty()) {
        set_admin_password(newpass);
        cout << "\n\t\tPassword changed successfully!";
    } else {
        cout << "\n\t\tPasswords do not match or are empty. Try again.";
    }
    getch();
}

void admin() {
    while (true) {
        design(45, '*');
        cout.setf(ios::fixed);
        cout.setf(ios::showpoint);
        cout << setprecision(2);
        cout << "\t\t\t 1. Add product \n ";
        cout << "\t\t\t 2. View desired product details \n ";
        cout << "\t\t\t 3. View product \n ";
        cout << "\t\t\t 4. Delete \n ";
        cout << "\t\t\t 5. Edit \n ";
        cout << "\t\t\t 6. Refill \n ";
        cout << "\t\t\t 7. Survey \n ";
        cout << "\t\t\t 8. View bill \n";
        cout << "\t\t\t 9. Gift hamper \n ";
        cout << "\t\t\t 10. Return to main menu \n ";
        cout << "\t\t\t 11. Change Admin Password \n ";
        cout << "\t\t\t enter your option :\n ";
        int option;
        cin >> option;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
        switch (option) {
            case 1: admin_add_product(); break;
            case 2: admin_view_product_details(); break;
            case 3: admin_view_all_products(); break;
            case 4: admin_delete_product(); break;
            case 5: admin_edit_product(); break;
            case 6: admin_refill_product(); break;
            case 7: admin_survey(); break;
            case 8: admin_view_bills(); break;
            case 9: admin_gift_hamper(); break;
            case 10: return;
            case 11: admin_change_password(); break;
            default:
                cout << "\n\n\n\n\t\t\t\tEnter valid choice\n";
                getch();
                break;
        }
    }
}
// ...existing code...
void craditcard()
{
fstream em;
char ch;
design(45,'*');
gotoxy(1,5);
cout<<"\n Do you want to take membership (y/n) ? ";
cin>>ch;
cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
em.open("costumer.txt",ios::app|ios::out|ios::in);
while(ch=='y'||ch=='Y')
{
 		co.getdata();
 		em.write(reinterpret_cast<char*>(&co),sizeof(co));
	cout<<"\n Do you want to create more credit card no. (y/n) ? ";
	cin>>ch;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
}
	em.close();
	 //em.seekg(0);
		 //	em.read(reinterpret_cast<char*>(&co),sizeof(co));
		 system("clear");
            cout<<"\n\t\t============================================================";
		 	cout<<"\n\t\t\t\t     The Customer ID detail :";
            cout<<"\n\t\t============================================================\n";


	 em.open("costumer.txt",ios::app|ios::out|ios::in);
		 	em.read(reinterpret_cast<char*>(&co),sizeof(co));
		 	while(!em.eof())
		 	{
		 		co.display();
		 		cout<<endl<<endl;
				em.read(reinterpret_cast<char*>(&co),sizeof(co));
			 }
			 getch();
			 em.close();
}

//=========================================================for grnereting bill============

void bill::billcalc(int a,int b,int c)
{
	int crdta=a;
	int quantity=b;
	int idno=c;
	fstream em,eima,eimb,eimc;
	em.open("bill.txt",ios::app|ios::out|ios::binary|ios::in);
	eima.open("costumer.txt",ios::app|ios::out|ios::binary|ios::in);
	eimb.open("itemstore.dat",ios::app|ios::out|ios::binary|ios::in);
	if(!em)
       	{
   			cout<<"\n\nFile Not Found...\nProgram Terminated!";
		}
	while(eimb.read(reinterpret_cast<char*>(&amt),sizeof(amt)))
	{
		if(idno==amt.itemno)
		{
			strcpy(prodnam,amt.name);

			idcr=amt.itemno;
			sp=amt.iamt;
		}

	}
//	if(crdta!=0)
//	{
		while(eima.read(reinterpret_cast<char*>(&co),sizeof(co)))
	{
		if(crdta==co.cradit)
		{
			strcpy(nam,co.name);
				strcpy(ctn,co.ctn);
			craditcr=co.cradit;
		}

	}
//	}
		qntcr=quantity;
		amtcr=sp*quantity;

	em.write(reinterpret_cast<char*>(&cr),sizeof(cr));

	em.close();
	eima.close();
	eimb.close();
		design(45,'*');
disp();

//	getch();
}
//====================================buy wala==================================
   void amount::report1()
{
    project::report();
    gotoxy(23,k);
    cout<<mrp;
    gotoxy(33,k);
    cout<<qty;
    gotoxy(44,k);
    cout<<tax;
    gotoxy(52,k);
    cout<<dis;
    gotoxy(68,k);
	cout<<iamt;
    k=k+1;
    if(k==50)
    {
        gotoxy(25,50);
        cout<<"PRESS ANY KEY TO CONTINUE...";
        getch();
        k=7;
        system("clear");
        gotoxy(30,3);
        cout<<" ITEM DETAILS ";
        gotoxy(3,5);
        cout<<" ID NUMBER";
        gotoxy(13,5);
        cout<<"NAME";
        gotoxy(23,5);
        cout<<"PRICE";
        gotoxy(33,5);
        cout<<"QUANTITY";
        gotoxy(44,5);
        cout<<"TAX";
        gotoxy(52,5);
        cout<<"DEDUCTION";
    }
}

void amount::pay1(int c,int a)
{
	design(45,'*');


    fin.read((char*)&amt,sizeof(amt));
    project::show();
    cout<<"\n\n\n\t\t*********************************************";
    cout<<"\n\t\t                 DETAILS                  ";
    cout<<"\n\t\t*********************************************";
    cout<<"\n\n\t\tPRICE                       :"<<mrp;
    cout<<"\n\n\t\tQUANTITY                    :"<<qty;
    cout<<"\n\t\tTAX PERCENTAGE              :"<<tax;
    cout<<"\n\t\tDISCOUNT PERCENTAGE         :"<<dis;
    cout<<"\n\t\tINDIVIDUAL AMOUNT           :Rs."<<iamt;
    cout<<"\n\t\t*********************************************";
    getch(); cout<<"\n\n\t\tinput the quantity you want to buy ";
     int quantity;
    cin>>quantity;
 //===================================================================
int choice=c;
int  pos;
	fstream fio;
	fio.open("itemstore.dat",ios::in|ios::out|ios::binary);
	while(fio.read((char*)&amt,sizeof(amt)))
	{
		pos=fio.tellg();

		if(choice==amt.project::retno())
		{
			fio.seekg(pos-sizeof(amt));
			qty-=quantity;
			fio.write((char*)&amt,sizeof(amt));
		}
	}
	fio.close();

		int crd=a;

		cr.billcalc(crd,quantity,choice);
		if(crd!=0)
			co.cal();

}
//=============================================================

   void user()
   {
	design(45,'*');
	int idc=0;
	char ans;
	cout<<endl<<"\n\t\t Do you have credit no.(y/n) ? ";
	cin>>ans;
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
	if(ans=='y'||ans=='Y')
	{
		cout<<endl<<" Input your Customer ID number : ";
		cin>>idc;
	}
      bgoto:design(45,'*');
            gotoxy(39,3);
            cout<<" BILL DETAILS ";
            gotoxy(1,5);
            cout<<"ITEM ID";
            gotoxy(13,5);
            cout<<"NAME";
            gotoxy(23,5);
            cout<<"MRP";
            gotoxy(33,5);
            cout<<"QUANTITY";
            gotoxy(44,5);
            cout<<"TAX %";
            gotoxy(52,5);
            cout<<"DISCOUNT %";
            gotoxy(68,5);
            cout<<"PRICE";
            fin.open("itemstore.dat",ios::binary);
            if(!fin)
            {
                cout<<"\n\nFile Not Found...";
            }
            fin.seekg(0);
            k=7;
              while(!fin.eof())
            {
                fin.read((char*)&amt,sizeof(amt));
                if(!fin.eof())
                {
                    amt.report1();
                }
            }
            gotoxy(17,k);
            getch();
            fin.close();
            //int choice=1;
          fstream em("itemstore.dat",ios::binary|ios::app|ios::out|ios::in);
    		//while(choice!=0)
                int choice;
				cout<<"\n Input the product's identification no. you want to buy :";
				cin>>choice;
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
				if(!em)
        {
            cout<<"\n\nFile Not Found...\nProgram Terminated!";
           // break;
        }
        em.seekg(0);
        while(em.read((char*)&amt,sizeof(amt)))
        {
            int x=amt.project::retno();
            if(x==choice)
           {
                amt.pay1(choice,idc);
           	    flag=1;
                break;
            }
        }
        if(flag==0)

			{
				cout<<"\n\t\tItem does not exist....Please Retry!";
        		getch();
			}

        //cout<<"\n press 0 to exit or any thing to continue";
        //cin>>choice;
        //*************************************************
        //char ans;
        cout<<"\n\n press Y to continue and N to exit ? ";
            cin >> ans;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
        if(ans =='y'||ans =='Y')
            {
                goto bgoto;
            }
            else
            em.close();
			 }
void user_show_products() {
    design(45,'*');
    gotoxy(39,3);
    cout << " BILL DETAILS ";
    gotoxy(1,5);
    cout << "ITEM ID";
    gotoxy(13,5);
    cout << "NAME";
    gotoxy(23,5);
    cout << "MRP";
    gotoxy(33,5);
    cout << "QUANTITY";
    gotoxy(44,5);
    cout << "TAX %";
    gotoxy(52,5);
    cout << "DISCOUNT %";
    gotoxy(68,5);
    cout << "PRICE";
    fin.open("itemstore.dat", ios::binary);
    if (!fin) {
        cout << "\n\nFile Not Found...";
        return;
    }
    fin.seekg(0);
    k = 7;
    while (!fin.eof()) {
        fin.read((char *)&amt, sizeof(amt));
        if (!fin.eof()) {
            amt.report1();
        }
    }
    gotoxy(17, k);
    getch();
    fin.close();
}

void user_purchase_product(int idc) {
    fstream em("itemstore.dat", ios::binary | ios::app | ios::out | ios::in);
    int choice;
    cout << "\n Input the product's identification no. you want to buy :";
    cin >> choice;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    if (!em) {
        cout << "\n\nFile Not Found...\nProgram Terminated!";
        return;
    }
    em.seekg(0);
    flag = 0;
    while (em.read((char *)&amt, sizeof(amt))) {
        int x = amt.project::retno();
        if (x == choice) {
            amt.pay1(choice, idc);
            flag = 1;
            break;
        }
    }
    if (flag == 0) {
        cout << "\n\t\tItem does not exist....Please Retry!";
        getch();
    }
    em.close();
}

void user_menu() {
    int idc = 0;
    char ans;
    cout << endl << "\n\t\t Do you have credit no.(y/n) ? ";
    cin >> ans;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
    if (ans == 'y' || ans == 'Y') {
        cout << endl << " Input your Customer ID number : ";
        cin >> idc;
    }
    while (true) {
        user_show_products();
        user_purchase_product(idc);
        cout << "\n\n press Y to continue and N to exit ? ";
        cin >> ans;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover input after choice selection
        if (!(ans == 'y' || ans == 'Y')) break;
    }
}
