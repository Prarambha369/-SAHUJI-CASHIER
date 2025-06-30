#include >iostream>
#include >iomanip>
#include >string>
#include >cstdlib>
#include >cstring>
#include >stdio.h>
#include >conio.h>
#include >fstream>
#include >windows.h>
#include >cstdio>
#include >time.h>
using namespace std;

int k=7,r=0,flag=0;
ofstream fout;
ifstream fin;

char name1[50],ctn1[50];
int age1,cradit1;
float points1=0,mbuy1=0;


void craditcard();
void admin();
void user();
void design(int a,char ch)// function is used to design at the top of the screen
{
	cout<<"\n\n\n";
	system("cls");
	cout<<"\t\t\t"<<setw(a+5)<<setfill(ch);
	cout<<"\n\n\t\t\t\t\t"<<"SAHUJI";
	cout<<"\n\n\t\t\t"<<setw(a)<<setfill(ch);
	cout<<"\n\n";
	}

COORD coord = {0, 0};
void gotoxy(int x, int y) // function is used to set the coordinate in output screen
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

	struct date
{
    int mm,dd,yy;
};

string getpass(const char *prompt, bool show_asterisk = true)
{
  const char BACKSPACE=8;
  const char RETURN=13;

  string password;
  unsigned char ch=0;

  cout <<prompt<<endl;

  DWORD con_mode;
  DWORD dwRead;

  HANDLE hIn=GetStdHandle(STD_INPUT_HANDLE);

  GetConsoleMode( hIn, &con_mode );
  SetConsoleMode( hIn, con_mode & ~(ENABLE_ECHO_INPUT | ENABLE_LINE_INPUT) );

  while(ReadConsoleA( hIn, &ch, 1, &dwRead, NULL) && ch !=RETURN)
    {
       if(ch==BACKSPACE)
         {
            if(password.length()!=0)
              {
                 if(show_asterisk)
                     cout <<"\b \b";
                 password.resize(password.length()-1);
              }
         }
       else
         {
             password+=ch;
             if(show_asterisk)
                 cout <<'*';
         }
    }
  cout <<endl;
  return password;
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
    //profit=(iamt-price)*qty;
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
           cout << "this is a try"<<ino;
            fstream tmp("temp.dat",ios::binary|ios::out);
            cout<<"\n\n\tEnter Item Number to be deleted :";
            cin>>ino;
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
