#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <conio.h>
#include <windows.h>
#include <direct.h>

typedef struct{
    int index;
    char title[50];
    char isbn[50];
}titleisbn;
typedef struct{
    int d;
    int m;
    int y;
}date;
typedef struct{
    char title[100];
    char author[50];
    char publisher[50];
    char isbn[15];
    char dop[15];
    char copies[10];
    char remcopies[10];
    char ctg[50];
    int state;
    int m;
}book;
typedef struct{
    char isbn[50];
    char userID[15];
    char di2[50];
    char dd2[50];
    char dr2[50];
    date di;
    date dd;
    date dr;
    int state;
}borrow;
typedef struct{
    char bnum[5];
    char zone[50];
    char city[50];
}address;
typedef struct{
    char fname[25];
    char lname[25];
    char id[15];
    address adrs;
    char phonenum[20];
    char age[5];
    char email[50];
    int state;
}member;
book bookarr[100];
member memarr[100];
borrow borarr[100];
int bubble[100];
int n1,n2,n3;
char currentisbn[15];

int validate(char* str){

    int i;
    int nums=0,letters=0,dashes=0,at=0,dots=0,slashes=0,garbage=0,spaces=0;
    int len=strlen(str);
    for(i=0;i<len;i++){
        if(str[i]>=48&&str[i]<=57){nums++;}
        else if((str[i]>=65&&str[i]<=90)||(str[i]>=97&&str[i]<=122)){letters++;}
        else if(str[i]==47){slashes++;}
        else if(str[i]==45){dashes++;}
        else if(str[i]==46){dots++;}
        else if(str[i]==64){at++;}
        else if(str[i]==32){spaces++;}
        else{garbage++;}
    }
    if(nums==len){return 1;}
    else if(slashes==2&&nums==len-2){return 2;} ///Date Confirmed
    else if(dashes==3&&nums==len-3){return 3;}  ///ISBN Confirmed
    else if(dots==1&&at==1){return 4;}  ///Email Confirmed
    else if (letters==len||(letters>0&&spaces+nums==len-letters)){return 5;} ///Publisher
    else {return 0;}
}

void bubbleSort(){
    int holder=0,done=0,i;
    while(1){
        for(i=0;i<n1;i++){
            if(bubble[i]<bubble[i+1]){
                holder=bubble[i];
                bubble[i]=bubble[i+1];
                bubble[i+1]=holder;
                done++;
            }
        }
        if(done==0){break;}else{done=0;}
    }
}
date add_day(date date1,int n){
    date dd;
    time_t now = time(0);
    struct tm now_tm = *localtime( &now);

    now_tm.tm_mday += n;   // add 50 seconds to the time
    mktime( &now_tm);
    dd.d= now_tm.tm_mday;
    dd.m= now_tm.tm_mon +1;
    dd.y= now_tm.tm_year +1900;
    //printf( "%s\n", asctime( &now_tm));
    return dd;
}
date get_date(){
    time_t rawtime;
    struct tm * timeinfo;
    date md;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    md.d = timeinfo->tm_mday;
    md.m = timeinfo->tm_mon + 1;
    md.y = timeinfo->tm_year +1900;
    return md;
}
void insrt_book()
{
    printf("Enter the info of book\n");//getc(stdin);
    st:printf("Title:");gets(bookarr[n1].title);
    if(validate(bookarr[n1].title)!=5){printf("Invalid input\n");goto st;}
    sa:printf("Author:");gets(bookarr[n1].author);
    if(validate(bookarr[n1].author)!=5){printf("Invalid input\n");goto sa;}
    sp: printf("Publisher:");gets(bookarr[n1].publisher);
    if(validate(bookarr[n1].publisher)!=5){printf("Invalid input\n");goto sp;}

    si:printf("ISBN: (Enter R to generate random ISBN): ");gets(bookarr[n1].isbn);
    if(stricmp(bookarr[n1].isbn,"R")==0){
        int r1,r2;char risbn[20],r11[20],r22[20];risbn[0]='\0';
        srand(time(NULL));
        r1=rand() % (9 - 1 + 1) + 1;
        r2=rand() % (99999 - 10000 + 1) + 10000;
        itoa(r1,r11,10);itoa(r2,r22,10);
         strcat(risbn,"0-17-");strcat(risbn,r11);strcat(risbn,r22);strcat(risbn,"-");strcat(risbn,r11);
        strcpy(bookarr[n1].isbn,risbn);
        printf("Generated ISBN is %s\n",bookarr[n1].isbn);
    }
    else{
        if(validate(bookarr[n1].isbn)!=3){printf("Invalid input\n");goto si;}
    }


    sd:printf("Date of publishing:");gets(bookarr[n1].dop);
    if(validate(bookarr[n1].dop)!=2){printf("Invalid input\n");goto sd;}
    sc:scopies:printf("Copies:");gets(bookarr[n1].copies);
    if(validate(bookarr[n1].copies)!=1){printf("Invalid input\n");goto sc;}
    ///sr:printf("Remaining Copies:");gets(bookarr[n1].remcopies);
    ///if(validate(bookarr[n1].remcopies)!=1){printf("Invalid input\n");goto sr;}
    strcpy(bookarr[n1].remcopies,bookarr[n1].copies);
    sca:printf("Category:");gets(bookarr[n1].ctg);
    if(validate(bookarr[n1].ctg)!=5){printf("Invalid input\n");goto sca;}
    bookarr[n1].m=0;
    bubble[n1]=bookarr[n1].m;
    n1++;
    printf("Book inserted\n");
    bookMgmt();
}
void most()
{
    printf("*****************************************\n");
    printf("**          Most Popular Books         **\n");
    printf("*****************************************\n\n");
    int i,j;
    for(i=0;i<5;i++){
            if(bubble[i]==bubble[i+1]){bubble[i+1]=-1;}
            for(j=0;j<n1;j++){
                if(bookarr[j].m==bubble[i]){printf("%s\n",bookarr[j].title);}
        }
    }
    printf("\n\n");
}
void search_book_title(char a[50])
{
    int i,j,c,selection=0,counter=0,b=0;
    titleisbn rr[100];
    for(i=0;i<n1;i++){
        if(strnicmp(bookarr[i].title,a,strlen(a))==0){
                strcpy(rr[counter].title,bookarr[i].title);
                strcpy(rr[counter].isbn,bookarr[i].isbn);
                rr[counter].index=counter+1;
        counter++;
        }
        }
    if(!counter){
               printf("Book is not found ");
    }
    else{
            printf("Books with this title (%s):\n",a);
            for(i=0;i<counter;i++){
                printf("%d) %s\n",i+1,rr[i].title);
            }

            printf("Select book to show its details:");
            sertit:
            scanf("%d",&c);getc(stdin);
            for(j=0;j<counter;j++){
                if(rr[j].index==c){
                    clrscr2();
                    search_book_isbn(rr[j].isbn,0);
                    selection=1;
                    strcpy(currentisbn,rr[j].isbn);
                    copytocb(currentisbn);
                    printf("The ISBN of the book (%s) has been copied to the clipboard!\n\n",rr[j].title);
                }
            }
            if(!selection){printf("Enter a valid number please\n"); goto sertit;}
        }
}
void copytocb(char * output){
const size_t len = strlen(output) + 1;
HGLOBAL hMem =  GlobalAlloc(GMEM_MOVEABLE, len);
memcpy(GlobalLock(hMem), output, len);
GlobalUnlock(hMem);
OpenClipboard(0);
EmptyClipboard();
SetClipboardData(CF_TEXT, hMem);
CloseClipboard();
}
int search_book_isbn(char a[50],int b)
{

    if(strlen(a)==13){
    int i,d=0;
    for(i=0;i<n1;i++){
        if(stricmp(bookarr[i].isbn,a)==0){
                d=1;if(b==1||b==2||b==3){return 1;}
               printf("Book info:\n");
               printf("Title: %s\n",bookarr[i].title);
               printf("Author: %s\n",bookarr[i].author);
               printf("Publisher: %s\n",bookarr[i].publisher);
               printf("ISBN: %s\n",bookarr[i].isbn);
               printf("Date of publishing: %s\n",bookarr[i].dop);
               printf("Copies: %s\n",bookarr[i].copies);
               printf("Remaining Copies: %s\n",bookarr[i].remcopies);
               printf("Category: %s\n",bookarr[i].ctg);
               return;
        }
    }
    if(!d){
               printf("Book is not found\n");
               return;
    }
  }
  else{printf("Invalid ISBN\n");return;} ///bookMgmt();}
}
void search_book_author(char a[50])
{
    char r[1000][100];
    int i,counter=0;
        for(i=0;i<n1;i++){
        if(strnicmp(bookarr[i].author,a,strlen(a))==0){
                strcpy(r[counter],bookarr[i].title);counter++;}
        }
    if(!counter){
               printf("Book is not found ");
    }
    else{
        printf("Books by author (%s):\n",a);
  for(i=0;i<counter;i++){printf("%s\n",r[i]);}}
}
void search_book_ctg(char a[50])
{
    char r[1000][100];
    int i,counter=0;
        for(i=0;i<n1;i++){
        if(stricmp(bookarr[i].ctg,a)==0){
                strcpy(r[counter],bookarr[i].title);counter++;}
        }
  if(!counter){printf("there is not books in this category\n");}
  else{
  printf("Books in category (%s):\n",a);
  for(i=0;i<counter;i++){printf("%s\n",r[i]);}}
}
void search_member_id(char a[50])
{
    if(strlen(a)==5){
    int d=0,co=0,i;
    for(i=0;i<n2;i++){if(stricmp(memarr[i].id,a)==0){printf("This user is already exist\n");return;}}
   }
    else{printf("Invalid ID\n");return;}///membertrn();}
}
    ///for(i=0;i<n3;i++){if(strcmp(borarr[i].userID,a)==0){printf("ahmed");}}
void Add_new_copy(char a[50],char b[50], int c)
{
    if(strlen(a)==13){
    int i,d=0,co=0;
    for(i=0;i<n1;i++){
        if(stricmp(bookarr[i].isbn,a)==0){
                d=1;
                if(c==-1){co=atoi(bookarr[i].remcopies);co--;itoa(co,bookarr[i].remcopies,10);return;}
                if(c==1){co=atoi(bookarr[i].remcopies);co++;itoa(co,bookarr[i].remcopies,10);return;}
                strcpy(bookarr[i].remcopies,b);return;
        }
    }
    if(!d){
               printf("Book is not found\n");
               return;
    }
  }
  else{printf("Invalid ISBN\n");return;} ///bookMgmt();}gmt();}
}
void delete_book(char a[50]){
    int i,s;
    char isbn[20];
    if(strlen(a)!=13){printf("ISBN Error!\n");return;}
    for(i=0;i<n1;i++){
        strcpy(isbn,bookarr[i].isbn);
       if(strstr(isbn,a)!=NULL){
            bookarr[i].state =2;
            printf("Book deleted\n");
            return;
            n1--;
       }
    }
    printf("Book not found\n");
}

void Borrow_book()///lazm nehandlha bel main function n5aleh ye search w ba3deen ya5d el isbn w ykml borrowing
{
    char isbn[50],id[50];isbn[0]='\0';id[0]='\0';
    date b,c;
    int i,n = n3;
    brisbn:
    printf("Enter ISBN:");scanf("%s",isbn);getc(stdin);
    if(validate(isbn)!=3){printf("Invalid ISBN\n");goto brisbn;}
    brid:
    printf("Enter ID:");scanf("%s",id);getc(stdin);if(strlen(id)!=5){printf("Invalid ID");goto brid;}
    for(i=0;i<n2;i++){
        if(strcmp(memarr[i].id,id)==0){


    for(i=0;i<n3;i++){
        if(strcmp(borarr[i].userID,id)==0 && strcmp(borarr[i].isbn,isbn)==0){
            printf("This user already borrowed this book!\n");
            return;
        }
    }
    strcpy(borarr[n3].isbn,isbn);strcpy(borarr[n3].userID,id);
    if(search_book_isbn(borarr[n3].isbn,1)==1){
    b=get_date();
    borarr[n3].di.d = b.d;borarr[n3].di.m = b.m;borarr[n3].di.y = b.y;
    //printf("%d %d %d ",borarr[n3].di.d,borarr[n3].di.m,borarr[n3].di.y);
    c=add_day(b,7);
    borarr[n3].dd.d = c.d;borarr[n3].dd.m = c.m;borarr[n3].dd.y = c.y;
    borarr[n3].dr.d =11;borarr[n3].dr.m =11;borarr[n3].dr.y =1111;
        Add_new_copy(borarr[n3].isbn," ",-1);
        printf("Book is borrowed\n");}
        n3++;
        return;
        }}
        printf("No member with this id!\n");
}
void return_book(char id[15],char isbn[15]){
   date today = get_date();
   int i;
    char a[50],b[50];
   for(i=0;i<n3;i++){
        strcpy(a,borarr[i].userID);
        if(borarr[i].dr.y==1111){
            if(strcmp(borarr[i].userID,id)==0){
                    if(strcmp(borarr[i].isbn,isbn)==0){
                        borarr[i].dr.d= today.d;borarr[i].dr.m= today.m;borarr[i].dr.y= today.y;
                        Add_new_copy(borarr[i].isbn," ",1);
                        printf("Book Returned!\n");
                    }
            }
        }

   }

}
void insrt_member()
{
    int i;
    printf("Enter member's info\n");
    sf:printf("first name:");gets(memarr[n2].fname);
    if(validate(memarr[n2].fname)!=5){printf("Invalid input\n");goto sf;}
    sl:printf("last name:");gets(memarr[n2].lname);
    if(validate(memarr[n2].lname)!=5){printf("Invalid input\n");goto sl;}
    sa:printf("Age:");gets(memarr[n2].age);
    if(validate(memarr[n2].age)!=1||strlen(memarr[n2].age)!=2){printf("Invalid input\n");goto sa;}
    sd:printf("ID:");gets(memarr[n2].id);
    for(i=0;i<n2;i++){if(strcmp(memarr[i].id,memarr[n2].id)==0){printf("This user is already exist\n");goto sd;}}
    if(validate(memarr[n2].id)!=1||strlen(memarr[n2].id)!=5){printf("Invalid input\n");goto sd;}
    sbn:printf("building number:");gets(memarr[n2].adrs.bnum);
    if(validate(memarr[n2].adrs.bnum)!=1){printf("Invalid input\n");goto sbn;}
    sz:printf("zone:");gets(memarr[n2].adrs.zone);
    if(validate(memarr[n2].adrs.zone)!=5){printf("Invalid input\n");goto sz;}
    sc:printf("City:");gets(memarr[n2].adrs.city);
    if(validate(memarr[n2].adrs.city)!=5){printf("Invalid input\n");goto sc;}
    sph:printf("phone number:");gets(memarr[n2].phonenum);
    if(validate(memarr[n2].phonenum)!=1||strlen(memarr[n2].phonenum)!=11){printf("Invalid input\n");goto sph;}
    se:printf("Email:");gets(memarr[n2].email);
    if(validate(memarr[n2].email)!=4){printf("Invalid input\n");goto se;}
    n2++;
    printf("Member inserted! \n");
}
void delete_member(char a[50]){

    int i,s;
    if(strlen(a)!=5){printf("ID Error!\n");return;}
    for(i=0;i<n3;i++){if(strcmp(borarr[i].userID,a)==0){printf("ahmed");return;}}
    for(i=0;i<n2;i++){
       if(strstr(memarr[i].id,a)!=NULL){
            memarr[i].state =2;
            printf("Member deleted\n");
            return;
            n2--;
       }
    }
    printf("Member not found\n");
}
void gb(int n){
   if (n==1){
        clrscr2();
        bookMgmt();
   }
}
void clrscr2(){
    system("@cls||clear");
}
void addcpy(){

}

void bookMgmt(){
     char a[50],b[50];
    printf("****************************************\n");
    printf("**          Book Management           **\n");
    printf("****************************************\n\n");
    printf("|| 1. Insert book\n|| 2. Search book\n|| 3. Add new copy\n|| 4. Delete\n|| 5. Main Menu\n");
    int c;
    bookmg:
    c=getch();//scanf("%d",&c);
    if(c ==48){return;};
    switch(c){

        case 49:
            clrscr2();
            ///getc(stdin);
            insrt_book();
            mainmenu();
        case 50:

            clrscr2();
            bbsearch();
        case 51:

            clrscr2();
            printf("Enter ISBN of the book:");scanf("%s",a);getc(stdin);
            printf("enter the new number of copies:");scanf("%s",b);getc(stdin);
            Add_new_copy(a,b,0);
            bookMgmt();
        case 52:
            clrscr2();
            del:
            printf("Enter ISBN of the book:");scanf("%s",a);getc(stdin);
            if(validate(a)!=3){printf("Invalid input\n");goto del;}
            delete_book(a);
            bookMgmt();
        case 53:
            clrscr2();
            mainmenu();
            break;
        default:

            printf("select a correct number\n");
            goto bookmg ;
            //bookMgmt();
            break;
    }

}
void bbsearch(){
    char a[50];
    printf("****************************************\n");
    printf("**            Search Book             **\n");
    printf("****************************************\n");
    printf("|| 1. Search by ISBN\n|| 2. Search by Title\n|| 3. Search by Category\n|| 4. Search by Author\n|| 5. Back\n|| 6. Main Menu\n");
    int c;
    searchmenu:
    c=getch();
    ///scanf("%d",&c);getc(stdin);
    if(c ==48){return;};
    switch(c){

        case 49:
            clrscr2();
            printf("Enter the ISBN of the book:");gets(a);
            search_book_isbn(a,0);
            bbsearch();
        case 50:
            clrscr2();
            printf("Enter the title (or part of it) of the book:");gets(a);
            search_book_title(a);
            bbsearch();
        case 51:
            clrscr2();
            printf("Enter the category of the book:");gets(a);
            search_book_ctg(a);
            bbsearch();
        case 52:
            clrscr2();
            printf("Enter author's name:");gets(a);
            search_book_author(a);
            bbsearch();
        case 53:
            gb(1);
        case 54:
            clrscr2();
            mainmenu();
        default:
            printf("select a correct number\n");
            goto searchmenu;
    }
}
void membertrn(){
    printf("*****************************************\n");
    printf("**          Member Management          **\n");
    printf("***************************************\n\n");
    printf("|| 1. Register\n|| 2. Remove Member\n|| 3. Main Menu\n");
    int c;char a[50],b[50];
    membermenu:
    c=getch();
    ///scanf("%d",&c);getc(stdin);
    if(c ==48){return;};
    switch(c){
        case 49:
            clrscr2();
            insrt_member();
            membertrn();
        case 50:
            clrscr2();
             printf("Enter the ID of member:");gets(a);
             delete_member(a);
            membertrn();
        case 51:
            clrscr2();
            mainmenu();
        default:
            printf("select a correct number\n");
            goto membermenu;
    }
}
void bormgmt(){
    printf("*****************************************\n");
    printf("**          Borrow Management          **\n");
    printf("***************************************\n\n");
    printf("|| 1. Borrow\n|| 2. Return\n|| 3. Main Menu\n");
    int c;char a[50],b[50];
    bormenu:
    c=getch();
    ///scanf("%d",&c);getc(stdin);
    if(c ==48){return;};
    switch(c){
        case 49:
            clrscr2();
            Borrow_book();
            bormgmt();
        case 50:
            clrscr2();
            printf("Enter the ISBN of the book:");scanf("%s",a);getc(stdin);
            printf("Enter the ID of the member:");scanf("%s",b);getc(stdin);
            return_book(b,a);
            bormgmt();
        case 51:
            clrscr2();
            mainmenu();
        default:
            printf("select a correct number\n");
            goto bormenu;
    }
}
void adminactions(){
    printf("*****************************************\n");
    printf("**            Admin Actions            **\n");
    printf("***************************************\n\n");
    printf("|| 1. Most Popular Books\n|| 2. Overdue\n|| 3. Print Books\n|| 4. Print Members\n|| 5. Print Borrows\n|| 6. Main Menu\n|| 0. Terminate\n");
    int c;char a[50],b[50];
    admenu:
    ///scanf("%d",&c);getc(stdin);
    c=getch();
    if(c ==48){return;};
    switch(c){
        case 49:
            clrscr2();
            most();
            adminactions();
        case 50:
            clrscr2();
            check_over();
            adminactions();
        case 51:
            clrscr2();
            print_books(bookarr,n1);
            adminactions();
        case 52:
            clrscr2();
            print_members(memarr,n2);
            adminactions();
        case 53:
            clrscr2();
            print_borrows(borarr,n3);
            adminactions();
        case 54:
            clrscr2();
            mainmenu();
        default:
            printf("select a correct number\n");
            goto admenu;
    }
}
void exitmenu(){
    printf("|| 1. Save and exit\n|| 2. Exit without saving\n|| 3. Cancel\n");
    int c;char a[50],b[50];
    exmenu:
    ///scanf("%d",&c);getc(stdin);
    c=getch();
    if(c ==48){return;};
    switch(c){
        case 49:
            clrscr2();
            save_books("books.txt");
            save_members("members.txt");
            save_borrows("borrow.txt");
            printf("changes saved!\n");
            printf("Thank You!");
            exit(1);
        case 50:
            exit(1);
        case 51:
            clrscr2();
            mainmenu();
        default:
            printf("select a correct number\n");
            goto exmenu;
    }
}


void mainmenu(){
    int c=0;
    printf("        ****************************************\n");
    printf("        ||          Library System            ||\n");
    printf("        ****************************************\n");
    printf("Main Menu \n\n");
    printf("|| 1. Book Management\n|| 2. Member Management\n|| 3. Borrow Management\n|| 4. Administrative Actions\n|| 5. Save Changes\n|| 6. Exit\n");
    mainmenuu:
    c=getch();//scanf("%d",&c);
    if(c ==48){printf("Thank you\n");return;};
    switch(c){
        case 49:
            clrscr2();
            bookMgmt();
        case 50:
            clrscr2();
            membertrn();
        case 51:
            clrscr2();
            bormgmt();
        case 52:
            clrscr2();
            adminactions();
        case 53:
            clrscr2();
            save_books("books.txt");
            save_members("members.txt");
            save_borrows("borrow.txt");
            printf("changes saved!\n");
            mainmenu();
        case 54:;
            clrscr2();
            exitmenu();
        default:
            printf("Invalid choice!");
            goto mainmenuu;
    }
}
int countln(char* filename){
    FILE *fp;
    char c;
    int count = 1;  // Line counter
    fp = fopen(filename, "r");
    for (c = getc(fp); c != EOF; c = getc(fp)) //loop on all characters in the file
        if (c == '\n') // Check for new line
            count = count + 1; //increase no. of lines by 1
    fclose(fp);
    return count;
}

book *read_books(char* filename, int n){
    FILE *fp = fopen(filename,"r");

    int i;
    for(i=0;i<n;i++){
        fscanf(fp,"%[^,]",bookarr[i].title);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",bookarr[i].author);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",bookarr[i].publisher);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",bookarr[i].isbn);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",bookarr[i].dop);
        fseek(fp,1,1);
        /*fscanf(fp,"%[^/]",bookarr[i].ddop.d);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",bookarr[i].ddop.m);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",bookarr[i].ddop.y);
        fseek(fp,1,1);*/
        fscanf(fp,"%[^,]",bookarr[i].copies);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",bookarr[i].remcopies);
        fseek(fp,1,1);
        fscanf(fp,"%s",bookarr[i].ctg);
        fgetc(fp);
        bookarr[i].m = atoi(bookarr[i].copies)-atoi(bookarr[i].remcopies);
        bubble[i]=bookarr[i].m;
    }
    fclose(fp);
    return bookarr;
}
void print_books(book *array,int n){
    int i;
    printf("BOOK TITLE\tAUTHOR\tPUBLISHER\tISBN\tDATE\tCOPIES\tREM.COPIES\tCATEGORY\n");
     for(i=0;i<n;i++){
        printf("%s\t%s\t%s\t\t%s\t%s\t%s\t%s\t%s\n",array[i].title,array[i].author,array[i].publisher,array[i].isbn,array[i].dop,array[i].copies,array[i].remcopies,array[i].ctg);
        //printf("Student (%d) Name: %s, ID: %d, GPA: %.2f, Grade: %c \n",i+1,array[i].name,array[i].id,array[i].gpa,grade);
    }
    printf("\n");
}
void save_books(char *filename){
    FILE *fp = fopen(filename,"w+");
    int i,s;
    for(i=0;i<n1;i++){
            s =bookarr[i].state;
            if(s!=2){
            fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s",bookarr[i].title,bookarr[i].author,bookarr[i].publisher,bookarr[i].isbn,bookarr[i].dop,bookarr[i].copies,bookarr[i].remcopies,bookarr[i].ctg);
            if(i!=n1-1){ //to make sure there is no new line at the end of the file
                fprintf(fp,"\n");
            }
        }
        //printf("%s\t%s\t%s\t\t%s\t%s\t%s\t%s\t%s\n",array[i].title,array[i].author,array[i].publisher,array[i].isbn,array[i].dop,array[i].copies,array[i].remcopies,array[i].ctg);
    }
    fclose(fp);
}
member *read_members(char* filename, int n){
    FILE *fp = fopen(filename,"r");
    int i;
    for(i=0;i<n;i++){
        fscanf(fp,"%[^,]",memarr[i].fname);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].lname);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].id);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].adrs.bnum);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].adrs.zone);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].adrs.city);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].phonenum);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",memarr[i].age);
        fseek(fp,1,1);
        fscanf(fp,"%s",memarr[i].email);
        fgetc(fp);
    }
    fclose(fp);
    return memarr;
}
void print_members(member *array,int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s %s %s %s %s %s %s %s\n",array[i].fname,array[i].lname,array[i].id,
               array[i].adrs.bnum,array[i].adrs.zone,array[i].adrs.city,array[i].phonenum,array[i].age,array[i].email);
    }
    printf("\n");
}
void save_members(char *filename){
    FILE *fp = fopen(filename,"w+");
    int i,s;
    for(i=0;i<n2;i++){
        s =memarr[i].state;
        if(s!=2){
            fprintf(fp,"%s,%s,%s,%s,%s,%s,%s,%s,%s",memarr[i].fname,memarr[i].lname,memarr[i].id,memarr[i].adrs.bnum,memarr[i].adrs.zone,memarr[i].adrs.city,memarr[i].phonenum,memarr[i].age,memarr[i].email);
            if(i!=n2-1){ //to make sure there is no new line at the end of the file
                fprintf(fp,"\n");
            }
        }
    }
    fclose(fp);
}
borrow *read_borrows(char* filename, int n){
    FILE *fp = fopen(filename,"r");
    int i;char d[10],m[10],y[10];
    for(i=0;i<n;i++){
        fscanf(fp,"%[^,]",borarr[i].isbn);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",borarr[i].userID);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",d); borarr[i].di.d=atoi(d);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",m); borarr[i].di.m=atoi(m);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",y); borarr[i].di.y=atoi(y);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",d); borarr[i].dd.d=atoi(d);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",m); borarr[i].dd.m=atoi(m);
        fseek(fp,1,1);
        fscanf(fp,"%[^,]",y); borarr[i].dd.y=atoi(y);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",d); borarr[i].dr.d=atoi(d);
        fseek(fp,1,1);
        fscanf(fp,"%[^/]",m); borarr[i].dr.m=atoi(m);
        fseek(fp,1,1);
        fscanf(fp,"%s",y); borarr[i].dr.y=atoi(y);
        fgetc(fp);
    }
    fclose(fp);
    return borarr;
}
void print_borrows(borrow *array,int n){
    int i;
    for(i=0;i<n;i++){
        printf("%s %s %d/%d/%d %d/%d/%d %d/%d/%d\n",array[i].isbn,array[i].userID,array[i].di.d,array[i].di.m,array[i].di.y,array[i].dd.d,array[i].dd.m,array[i].dd.y,array[i].dr.d,array[i].dr.m,array[i].dr.y);
    }
    printf("\n");
}
void save_borrows(char *filename){
    FILE *fp = fopen(filename,"w");
    int i,s;
    for(i=0;i<n3;i++){
        s =borarr[i].state;
        if(s!=2){
            fprintf(fp,"%s,%s,%d/%d/%d,%d/%d/%d,%d/%d/%d",borarr[i].isbn,borarr[i].userID,borarr[i].di.d,borarr[i].di.m,borarr[i].di.y,borarr[i].dd.d,borarr[i].dd.m,borarr[i].dd.y,borarr[i].dr.d,borarr[i].dr.m,borarr[i].dr.y);
            if(i!=n3-1){ //to make sure there is no new line at the end of the file
                fprintf(fp,"\n");
            }
        }
    }
    fclose(fp);
}


int days_in_month[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
int leap_year(int year) {
    if(year%400==0) return 1;
    if(year%4==0 && year%100!=0) return 1;

    return 0;
}
int number_of_days(date d) {
    int result = 0;
    int i;

    for(i=1; i < d.y; i++) {
        if(leap_year(i))
            result += 366;
        else
            result += 365;
    }

    for(i=1; i < d.m; i++) {
        result += days_in_month[i];

        if(leap_year(d.y) && i == 2) result++;
    }

    result += d.d;
    return result;
}
int cmp_date(date d1,date d2){
    return number_of_days(d2)-number_of_days(d1);
}
char *get_title_from_borrow(char a[20]){
     if(strlen(a)==13){
    int i,d=0;
    for(i=0;i<n1;i++){
        if(stricmp(bookarr[i].isbn,a)==0){
                d=1;
               return bookarr[i].title;
        }
    }
    if(!d){
               printf("Book is not found\n");
               return;
    }
  }
  else{printf("Invalid ISBN\n");return;} ///bookMgmt();}
}
void check_over(){
    int diff=0,i,counter=0;
    date today = get_date();
    printf("****************************************\n");
    printf("**           Overdue Books            **\n");
    printf("****************************************\n");
    for(i=0;i<n3;i++){
        if(borarr[i].dr.d==11 && borarr[i].dr.m==11,borarr[i].dr.y==1111){
            diff=cmp_date(borarr[i].di,today);
            if(diff>7){
                counter++;
                printf("%d)%s\n",counter,get_title_from_borrow(borarr[i].isbn));
            }
        }

   }
   printf("\n\n");
}

void password(){
    int i=0;
    char temp;
    char* psw;
    char ag[16]="ACCESS GRANTED\n";
    psw=(char *) malloc(12);
    printf("Enter password(sofckinsafe):");
    for(i=0;1;i++){
        temp=getch();
        if(temp=='\b'){
            printf("\b \b");
            psw[i-1]='z';
            i--;
        }else if(temp!=13){
            printf("%c",temp);
            Sleep(200);
            printf("\b \b*");
            psw[i]=temp;}
        else{break;}
    }
    psw[11]='\0';
    if(strcmp(psw,"sofckinsafe")==0){
        for(i=0;i<15;i++){
            printf("%c",ag[i]);
            Sleep(100);
        }
        return;
    }
    else{printf("Wrong Password!\n");password();}
}



int main()
{
    //password();
    char a[50];
    n1=countln("Books.txt");
    n2=countln("Members.txt");
    n3=countln("borrow.txt");
    read_books("Books.txt",n1);
    read_members("Members.txt",n2);
    read_borrows("borrow.txt",n3);
    mainmenu();
    return 0;
}
