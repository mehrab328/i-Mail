
#include<iostream>
#include<fstream>
#include<iomanip>
#include<windows.h>
#include<conio.h>
using namespace std;


int main();
void gotoxy(int x, int y);
void back_forth();
struct birth_day
{
    int day;
    int month;
    int year;
};

class messaging
{
public:
    void inbox(char *);
    void compose(char *);
    void sent_mail(char *);
    void drafts(char *);
};


class user
{
public:

    char name[15];
    char email[30];
    char password[10];
    char user_gender[7];
    char mobile_no[15];

    birth_day birthday;
    messaging msg;

    user *next;

    void sign_in();
    void sign_up();



};

user *head=NULL;

class ServiceProvider
{

public:
    void message_handling()
    {
        fstream out("sentmail.txt");
        fstream in("inbox.txt");
        char t_frm[20],t_to[20],t_sub[20],t_msg[50];
        while(!out.eof())
        {
            out>>t_frm>>t_to>>t_sub>>t_msg;

            in<<t_frm<<endl<<t_to<<endl<<t_sub<<endl<<t_msg<<"\n\n";
        }
        in.close();
        out.close();


    }
    void add_user()
    {

        user *node=new user;
        node->next=NULL;
        node->sign_up();

    }
    void retreve()
    {
        fstream in("sign_up.txt");
        while(!in.eof())
        {
            char sname[15],semail[20],smobile_no[15],suser_gender[6],spassword[10];
            birth_day sbirthday;
            in>>sname>>semail>>spassword>>sbirthday.day>>sbirthday.month>>sbirthday.year>>suser_gender>>smobile_no;
            user *node=new user;
            node->next=NULL;
            node->birthday.day=sbirthday.day;
            node->birthday.month=sbirthday.month;
            node->birthday.year=sbirthday.year;
            strcpy(node->name,sname);
            strcpy(node->email,semail);
            strcpy(node->mobile_no,smobile_no);
            strcpy(node->password,spassword);
            strcpy(node->user_gender,suser_gender);
            if(head==NULL)head=node;
            else
            {
                user *temp=head;
                while(temp->next!=NULL)
                {
                    temp=temp->next;
                }
                temp->next=node;
            }

        }
        in.close();


    }

    void search_user()
    {
        message_handling();
        char signiname[10];
        char signinpass[10];
        gotoxy(30,10);
        cout<<"Enter Your Name        : ";
        cin>>signiname;
        gotoxy(30,12);
        cout<<"Enter Your Password    : ";
        int j=0;
        char ch;
        do
        {

            if((ch=getch()) == 13)
            {
                signinpass[j]='\0';
                break;
            }
            {
                signinpass[j]=ch;
                j++;
                printf("*");
                fflush(stdin);
            }
        }
        while(1);

        user *temp=head;
        int l=strcmp(signiname,temp->name);
        int k=strcmp(signinpass,temp->password);
        while(l!=0 && k!=0 )
        {
            temp=temp->next;
            if(temp==NULL) break;
            l=strcmp(signiname,temp->name);
            k=strcmp(signinpass,temp->password);
        }
        if(temp!=NULL)
            temp->sign_in();
        else
        {
            gotoxy(30,13);
            cout<<"Wrong Username or Password!";
            Sleep(1000);
            system("cls");
            search_user();
        }
    }

    void display()
    {
        user *temp=head;
        system("cls");
        cout<<"Display :";
        while(temp!=NULL)
        {
            cout<<temp->name<<temp->email<<temp->password<<endl;
            temp=temp->next;
        }
        main();
    }


};




void gotoxy(int x, int y)
{
    HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwCursorPosition = { x,y };
    cout.flush();
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}


char* Color(int color=7, char* Message="")
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
    return Message;
}

void loading()
{
    gotoxy(30,10);
    cout<<"Loading ";
    for(int i=0; i<5; i++)
    {
        if(i%2)
        {
            Color();
            cout<<". ";
        }
        else
        {
            cout<<Color(15,". ");

        }
        Sleep(100);

    }
    gotoxy(30,11);
    for(int i=0; i<16; i++)
    {
        if(i%2)
        {
            Color();
            printf("%c",177);
        }
        else
        {
            cout<<Color(15);
            printf("%c",177);

        }
        Sleep(80);
    }
}




int main()
{
    ServiceProvider obj;

    int choice;
    gotoxy(30,5);
    cout<<"Welcome to I-mail";
    gotoxy(32,10);
    cout<<"Press";
    gotoxy(32,11);
    cout<<"1.Sign In";
    gotoxy(32,12);
    cout<<"2.Sign Up";
    obj.retreve();

    do
    {
        gotoxy(32,16);
        cout<<"Enter Your Choice ";
        cin>>choice;

        if(choice==1)
        {
            system("cls");
            obj.search_user();
        }
        else if(choice==2)
        {
            system("cls");
            obj.add_user();
        }

        if(choice>2)
        {

            gotoxy(32,14);
            cout<<"Invalid Input Try Again!!";
            obj.display();
        }

    }
    while(choice!=1 && choice!=2&&choice!=3);
    return 0;
}


void  user::sign_up()
{

    bool flag_user=false;

    fstream input,output;

    gotoxy(24,2);
    cout<<Color(15,"  ***********************\n\t\t\t  * Fill the Form Below * \n\t\t\t  ***********************");

    Color();
    gotoxy(25,8);
    cout<<"Enter Your Name       : ";   //Name Part
    cin>>name;


    char test_user[20];                 //Username part
    char test_mail[20];
    char const_part[]="@gmail.com";

    do
    {
        output.open("email_password.txt",ios::app | ios::out | ios::in);

        gotoxy(25,10);
        cout<<"Enter Your Username   : ";
        cin>>test_user;
        strcpy(test_mail,test_user);
        strcat(test_user,const_part);

        char email_test[20];
        char password_test[10];

        //system("cls");

        bool flag_check=true;

        while(!output.eof())
        {
            output>>email_test>>password_test;

            if(!strcmp(email_test,test_user))
            {
                int reand1=rand()%1000;
                int reand2=rand()%1000;
                int reand3=rand()%1000;

                gotoxy(20,12);
//
//                cout<<"Checking";
//                Sleep(1000);
                cout<<"     Sorry the Username is already taken\n\t\t\t"<<" Here's some suggestion: "<<test_mail<<reand1
                    <<"\n \t\t\t\t\t\t "<<test_mail<<reand2<<"\n \t\t\t\t\t\t "<<test_mail<<reand3;
                flag_check=false;
            }
        }
        // if(strlen(test_mail)>20) cout<<"Email has exceeded the range";
        if(strlen(test_user)<20 && flag_check )
        {
            flag_user=true;
            for(int i=0; i<150; i++)
                cout<<"       ";

        }

        output.close();

    }
    while(!flag_user);

    strcpy(email,test_user);





    char test_password1[10],test_password2[10];           //Password Part

    do
    {
        gotoxy(25,12);
        int j=0;
        char ch;
        cout<<"Create a Password     : ";
        do
        {
            if((ch=getch()) == 13)
            {
                test_password1[j]='\0';
                break;
            }
            {
                test_password1[j]=ch;
                j++;
                printf("*");
                fflush(stdin);
            }
        }
        while(1);

        gotoxy(25,14);
        j=0;
        cout<<"Confirm Your Password : ";
        do
        {

            if((ch=getch()) == 13)
            {
                test_password2[j]='\0';
                break;
            }
            {
                test_password2[j]=ch;
                j++;
                printf("*");
                fflush(stdin);
            }
        }
        while(1);

        if(strcmp(test_password1,test_password2))
        {
            gotoxy(25,16);
            cout<<"Password didn't Match,Re-enter Password";
        }
        for(int i=0; i<50; i++)
            cout<<"       ";

    }
    while(strcmp(test_password1,test_password2));

    strcpy(password,test_password1);


    bool flag_birthday;                           //BirthDay
    do
    {
        flag_birthday=false;

        gotoxy(25,16);
        cout<<"Birthday [dd/mm/yyyy] : ";
        cin>>birthday.day>>birthday.month>>birthday.year;

        bool test1=birthday.day>31 && (birthday.month==1 || birthday.month==3 || birthday.month==5 || birthday.month==7 ||  birthday.month==8 || birthday.month==10 || birthday.month==12);
        bool test2=birthday.day>30 && (birthday.month==4 || birthday.month==6 || birthday.month==9 || birthday.month==11);
        bool test3=birthday.day>29 &&  birthday.month==2 && ( (birthday.year%400==0 || birthday.year%100!=0) &&(birthday.year%4==0));
        bool test4=birthday.day>28 &&  birthday.month==2 && !( (birthday.year%400==0 || birthday.year%100!=0) &&(birthday.year%4==0));



        if(test1 || test2 || test3 || test4 || birthday.month>12 || (birthday.year<1900 || birthday.year>2015))
        {

            flag_birthday=true;
            gotoxy(25,18);
            cout<<"Invalid Birhday.Please Try Again";
        }

        for(int i=0; i<50; i++)
            cout<<"   ";


    }
    while(flag_birthday);


    gotoxy(25,18);
    cout<<"Gender                : 1.Female";
    gotoxy(49,19);
    cout<<"2.Male";
    int gender_choice;
    do
    {
        gotoxy(25,21);
        cout<<"Enter Your Choice     :";
        cin>>gender_choice;
        if(gender_choice==1) strcpy(user_gender,"Female");
        else if(gender_choice==2) strcpy(user_gender,"Male");
    }
    while(gender_choice!=1 && gender_choice!=2);

    gotoxy(25,23);            //Mobilephone
    Color();
    cout<<"MobilePhone           : ";
    cin>>mobile_no;

    gotoxy(25,25);
    cout<<"1.Save";
    gotoxy(49,25);
    cout<<"2.Back";

    int svae_back;
    do
    {
        gotoxy(25,29);
        cout<<"Enter Your Choice     :";
        cin>>svae_back;

        if(svae_back==1)
        {
            input.open("sign_up.txt",ios::app | ios::out);
            output.open("email_password.txt",ios::out | ios::app );

            output<<email<<"\n"<<password<<"\n\n\n";
            input<<name<<"\n"<<email<<"   "<<password<<"  "<<birthday.day<<" "<<birthday.month<<" "<<birthday.year<<"  "<<user_gender<<"  "<<mobile_no<<"\n\n\n" ;

            output.close();
            input.close();

            gotoxy(25,27);
            cout<<"Data has been Saved";

            if(head==NULL)
            {
                head=this;

            }
            else
            {

                user *temp=head;
                while(temp->next!=NULL)
                {
                    temp=temp->next;

                }
                temp->next=this;

            }

            gotoxy(25,29);
            cout<<"Enter Your Choice     :";
            cin>>svae_back;

            if(svae_back==2)
            {
                system("cls");
                main();

            }

        }

        else if(svae_back==2)
        {
            system("cls");
            main();

        }
    }
    while(svae_back!=1&&svae_back!=2);

}









void user::sign_in()
{
    int choice;


    system("cls");
    gotoxy(30,10);
    cout<<"Press";
    gotoxy(30,11);
    cout<<"1. Compose";
    gotoxy(30,12);
    cout<<"2. Draft";
    gotoxy(30,13);
    cout<<"3. Inbox";
    gotoxy(30,14);
    cout<<"4. Sent Mail";
    gotoxy(30,15);
    cout<<"5. Logout";
    gotoxy(30,16);
    cout<<"Enter Your Choice : ";
    cin>>choice;

    if(choice==1)  msg.compose(email);

    else if(choice==2)
        msg.drafts(email);
    else if(choice==3)
        msg.inbox(email);
    else if(choice==4)
        msg.sent_mail(email);
    else if(choice==5)
        main();
}






void messaging::compose(char p[])
{
    system("cls");
    gotoxy(24,2);
    cout<<Color(15,"  ***********************\n\t\t\t  *    Compose Message  * \n\t\t\t  ***********************");
    Color();

    char to_mail[20];
    gotoxy(24,10);
    cout<<"From : "<<p;
    int l;

    gotoxy(24,11);
    cout<<"To : ";
    cin>>to_mail;

    fstream in("sign_up.txt");
    fstream out("sentmail.txt",ios::app);
    fstream out1("drafts.txt",ios::app);

    while(!in.eof())
    {
        char sname[15],semail[15],smobile_no[15],suser_gender[6],spassword[10];
        birth_day sbirthday;
        in>>sname>>semail>>spassword>>sbirthday.day>>sbirthday.month>>sbirthday.year>>suser_gender>>smobile_no;
        l=strcmp(semail,to_mail);
        if(l==0) break;

    }
    if(l!=0)
    {
        gotoxy(24,13);
        cout<<"Invalid Email";
        Sleep(1000);
        system("cls");
        compose(p);
    }
    in.close();

    char sub[20];
    gotoxy(24,13);
    fflush(stdin);
    cout<<"Subject: ";
    cin.getline(sub,20);

    char msgg[75];
    gotoxy(20,15);

    cout<<"Write Your Message: ";
    gotoxy(20,17);
    fflush(stdin);
    cin.getline(msgg,20);



    gotoxy(20,25);
    cout<<"Press";
    gotoxy(20,26);
    cout<<"1.Send";
    gotoxy(20,27);
    cout<<"2.Save Draft";
    gotoxy(20,28);
    cout<<"3.Back";
    gotoxy(20,29);
    int choice;
    cout<<"Enter Your Choice : ";
    cin>>choice;

    if(choice==1)
    {
        out<<p<<endl<<to_mail<<endl<<sub<<endl<<msgg<<"\n\n";
        gotoxy(20,27);
        cout<<"Message Has been sent successfully";

        Sleep(10000);
        back_forth();
    }
    else if(choice==2)
    {
        out1<<p<<endl<<to_mail<<endl<<sub<<endl<<msgg<<"\n\n";
        gotoxy(20,27);
        cout<<"Message Has been saved successfully";
        Sleep(10000);
        back_forth();
    }
    else if(choice==3) back_forth();

    out.close();
    out1.close();



}



void messaging::drafts(char p[])
{

    system("cls");
    gotoxy(24,2);
    cout<<Color(15,"  ***********************\n\t\t\t  *    Draft Message  * \n\t\t\t  ***********************");
    Color();
    char from_mail[15],to_mail[15],subject[20],msg[50];
    fstream in("drafts.txt");
    gotoxy(30,101);
    while(!in.eof())
    {
        in>>from_mail>>to_mail>>subject>>msg;
        int l=strcmp(p,from_mail);
        if(!l)
        {
            cout<<from_mail<<"\n"<<to_mail<<"\n"<<subject<<"\n"<<msg<<"\n";
        }
    }
    in.close();
}

void messaging::sent_mail(char p[])
{
system("cls");
    gotoxy(24,2);
    char to_mail[20],from_mail[20],subject[20],messag[20];
    cout<<Color(15,"  ***********************\n\t\t\t  *    Inbox Messages  * \n\t\t\t  ***********************");
    Color();
    fstream in("sentmail.txt");
    int i=5;
    while(!in.eof())
    {
        in>>from_mail>>to_mail>>subject>>messag;
        int l=strcmp(p,from_mail);
        if(!l)
        {
            gotoxy(30,++i);
            cout<<from_mail;
            gotoxy(30,++i);
            cout<<to_mail;
            gotoxy(30,++i);
            cout<<subject;
            gotoxy(30,++i);
            cout<<messag;
            i++;
        }
    }

    in.close();
}

void messaging::inbox(char p[])
{
    system("cls");
    gotoxy(24,2);
    char to_mail[20],from_mail[20],subject[20],messag[20];
    cout<<Color(15,"  ***********************\n\t\t\t  *    Inbox Messages  * \n\t\t\t  ***********************");
    Color();
    fstream in("inbox.txt");
    int i=5;
    while(!in.eof())
    {
        in>>from_mail>>to_mail>>subject>>messag;
        int l=strcmp(p,to_mail);
        if(!l)
        {
            gotoxy(30,++i);
            cout<<from_mail;
            gotoxy(30,++i);
            cout<<to_mail;
            gotoxy(30,++i);
            cout<<subject;
            gotoxy(30,++i);
            cout<<messag;
            i++;
        }
    }
    in.close();
}

void back_forth()
{
    user a;
    a.sign_in();
}
