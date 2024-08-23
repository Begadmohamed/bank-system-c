#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
typedef struct
{
    int month;
    int year;
} DOP;
typedef struct
{
    char account_number[15];
    char name[20];
    char address[30];
    double balance;
    char mobile[12];
    DOP date_opened;
} accounts;
typedef struct
{
    char user[15];
    char password[15];
} loginInformation;
int countLines(char* file)
{
    FILE* f1 = fopen(file, "r");
    if (f1 == NULL) return -1; // Return -1 to indicate an error in file opening

    int n = 0;
    char buffer[100];

    while (fgets(buffer, sizeof(buffer), f1) != NULL)
    {
        if (buffer[0] == '\n') continue;
        n++;
    }

    fclose(f1);
    return n;
}

accounts acc[100];
char accountsfilename[]="accounts.txt";
char usersfilename[]="users.txt";

void load(char *file)
{
    int i=0;
    int n =countLines(accountsfilename);
    FILE *f = fopen(file, "r");
    if (f == NULL)
    {
        printf("Error opening file \n");
        exit(2);
    }
    for(i; i<n; i++)
    {
        fscanf(f,"%[^,],%[^,],%[^,],%lf,%[^,],%d-%d\n",&acc[i].account_number,&acc[i].name,&acc[i].address,&acc[i].balance,&acc[i].mobile,&acc[i].date_opened.month,&acc[i].date_opened.year);
    }

    fclose(f);
}
int check_account_number(char *acc_num)
{
    int n=countLines(accountsfilename);
    int x = 0,i;
    for (i = 0; i < n; i++)
    {
        if (strcmp(acc[i].account_number, acc_num) == 0)
            x = 1;
    }
    return x;
}
void validateName(char *name)
{
    int i=0;
    int j=0;

    while(name[i]!='\0')
    {

        if(name[i]!=' '||(i>0&&name[i-1]!=' ')) //
        {
            name[j]=name[i];
            j++;
        }
        i++;
    }
    name[j]='\0';
    if(name[j-1]==' ') name[j-1]='\0';
    name[0]=toupper(name[0]);
    for (i = 1; i < strlen(name)-1; i++)
    {

        if (isspace(name[i]))
        {
            name[i + 1] = toupper(name[i + 1]);
            i++;
        }

        else
        {
            name[i] = tolower(name[i]);
        }
    }
    name[strlen(name)-1]=tolower(name[strlen(name)-1]);
}
int isAccountNumberReport(char n[20])
{
    int lines=countLines(accountsfilename);
    if(strlen(n)==0)
    {
        return 0;
    }
    if(strlen(n)!=10)
    {
        printf("account number is only 10 digits\n");
        return 0;
    }
    for(int i=0; i<strlen(n); i++)
    {
        if(isdigit(n[i])==0)
        {
            printf("invalid you should enter digits only\n");
            return 0;
        }
    }
    for(int i=0; i<lines; i++)
    {
        if(strcmp(n,acc[i].account_number)==0) return 1;
    }
    printf("account number not found\n");
    return 0;
}
int isAccountNumberadd(char n[20])
{
    int lines=countLines(accountsfilename);
    if(strlen(n)==0)
    {
        return 0;
    }//ensures that entered string is not empty
    if(strlen(n)!=10)
    {
        printf("account number is only 10 digits\n");
        return 0;
    }//ensure that it is only 10 digits
    for(int i=0; i<strlen(n); i++)
    {
        if(isdigit(n[i])==0)
        {
            printf("invalid you should enter digits only\n");
            return 0;
        }
    }//ensures that is digits only
    for(int i=0; i<lines; i++)
    {
        if(strcmp(n,acc[i].account_number)==0)
        {
            printf("account number is already used\n");//check duplicate
            return 0;
        }
    }//ensures that it is not duplicated
    return 1;
}
int isNameadd(char n[100])
{

    int scount=0;
    for(int j=0; j<strlen(n); j++)
    {
        if(n[j]==' ') scount++;
    }
    if(scount==strlen(n)) return 0;
    if(strlen(n)==0)
    {
        return 0;
    }
    for(int i=0; i<strlen(n); i++)
    {
        if(n[i]==' ') continue;//skip spaces
        if(isalpha(n[i])) continue;//ensures input is alphapetical
        else
        {
            printf("Entered invalid name\n");
            return 0;
        }
    }
    return 1;
}
int isEmailadd(char* str)
{
    char* atptr=strchr(str,'@');//pointer to first @
    int atc=0;//counter for @
    for(int i=0; i<strlen(str); i++)
    {
        if(str[i]==' '||str[i]==',') return 0;//ensures that it doesn't have spaces or comaas
        if(str[i]=='@') atc++;
    }
    if(atc!=1) return 0;//ensures that it have only one @
    if(str==atptr) return 0; //ensures that entered email has username
    if(*(atptr+1)=='.'||*(atptr+1)=='\0' ) return 0; //ensures that entered email has domain
    char temp[20];//temp to save email
    char dom[20];// save domain part
    strcpy(temp,str);
    char *token=strtok(temp,"@");
    token=strtok(NULL,"\0");//tokenize part after @
    strcpy(dom,token);
    int dotc=0;//counter for .
    for(int j=0; j<strlen(dom); j++)
    {
        if(dom[j]=='.') dotc++;
    }
    if(dotc!=1) return 0;
    token =strtok(dom,".");//string from @ to .
    if(strlen(token)<2) return 0;// check if string after @ have at least 2 charcters
    token =strtok(NULL,"\0");
    if(token==NULL) return 0;//if user entered username@domain.
    if(strlen(token)<2) return 0; //// check if string after . have at least 2 charcters


    return 1;
}
int isBalanceadd(char n[50])
{
    if(n[0]=='0')
    {
        printf("enter correct number\n");// 0000242142  011
        return 0;
    }
    int i=0;
    if(strlen(n)==0) return 0;
    if(n[i]=='-') i=i+1;
    for(; i<strlen(n); i++)
    {
        if(isdigit(n[i])==0 && n[i]!='.')
        {
            printf("please enter digits only \n");
            return 0;
        }
    }


    return 1;

}
int isMobileadd(char n[100])
{
    if(strlen(n)==0)
    {
        return 0;
    }
    for(int i=0; i<strlen(n); i++)
    {
        if(isdigit(n[i])==0)
        {

            printf("please enter digits only\n");
            return 0;
        }
    }//ensures entered string is only numbers
    if(strlen(n)!=11)
    {
        printf("invalid phone number\n");

        return 0;
    }//ensures it is 11 numbers
    for(int i=0; i<100; i++) //countlines
    {

        if(strcmp(n,acc[i].mobile)==0)
        {
            printf("phone number is already used\n");
            return  0;
        }

    }//check for duplicated
    return 1;
}
void capatilize(char*str)
{
    while(*str)
    {
        *str=toupper((char)*str);
        str++;
    }
}
void save(char*accname,int n)
{
    FILE*accf=fopen(accname,"w");
    for(int i=0; i<n; i++)
    {
        fprintf(accf,"%s,",acc[i].account_number);
        fprintf(accf,"%s,",acc[i].name);
        fprintf(accf,"%s,",acc[i].address);
        fprintf(accf,"%.2lf,",acc[i].balance);
        fprintf(accf,"%s,",acc[i].mobile);
        fprintf(accf,"%d-",acc[i].date_opened.month);
        fprintf(accf,"%d\n",acc[i].date_opened.year);
    }
    fclose(accf);
    load(accname);
}
void add()
{
    typedef struct
    {
        char accountNumber[20];
        char nam [500];
        char email[50];
        char bal[50];
        char mob[20];
    } temp ;
    temp t;//temporary struct to store entered data without make any change until user choose to save
    char strtemp[100];
    while(1)
    {
        printf("Enter account number: ");
        fgets(t.accountNumber,20,stdin);
        t.accountNumber[strcspn(t.accountNumber, "\n")] = '\0';//ensures that the newline character enterd from fgets is removed
        if(isAccountNumberadd(t.accountNumber)) break;//check account number

    }
    while(1)
    {
        int c=0;
        printf("Enter First Name and Last Name : ");
        fgets(t.nam,50,stdin);
        t.nam[strcspn(t.nam, "\n")] = '\0';//ensures that the newline character is removed
        if(isNameadd(t.nam)==0) continue;//check name
        validateName(t.nam);//validate it (removing extra spaces-capitalize every char of each sub string

        for(int i=0; i<strlen(t.nam); i++)
        {
            if(t.nam[i]==' ') c++;
        }
        if(c==0||c>1)
        {
            continue;
        }//ensures that user only entered first and last name
        strcpy(strtemp,t.nam);
        char sub1[20];
        char sub2[20];
        char *token=NULL;
        token=strtok(t.nam," ");
        strcpy(sub1,token);
        token=strtok(NULL,"\0");
        strcpy(sub2,token);
        if(strlen(sub1)<3||strlen(sub2)<3)
        {
            printf("please enter only first and last name\n");
            continue;
        }//ensures that each name is at least 3 charcters
        break;
    }

    while(1)
    {
        printf("Enter E-mail: ");
        fgets(t.email,50,stdin);
        t.email[strcspn(t.email, "\n")] = '\0';
        if(isEmailadd(t.email)) break;
        else
        {
            printf("invalid Email\n");
        }
    }
    while (1)
    {

        printf("Enter Balance: ");
        fgets(t.bal,15,stdin);
        t.bal[strcspn(t.bal, "\n")] = '\0';
        if(isBalanceadd(t.bal)) break;
    }

    while(1)
    {
        printf("Enter Mobile: ");
        fgets(t.mob,20,stdin);
        t.mob[strcspn(t.mob, "\n")] = '\0';
        if(isMobileadd(t.mob)) break;
    }
    time_t const currenttime=time(NULL);//data type (time_t)?? time() returns no of seconds  since the epoch (00:00:00 Coordinated Universal Time (UTC), January 1, 1970)
    struct tm *date=localtime(&currenttime);// localtime takes seconds and return pointer to struct tm
    system("cls");
    printf("- Add -\n");
    int choice;
    do
    {
        printf("\033[1;31m");
        printf("Warning !\n");
        printf("you are going to add this account\n");
        printf("1 - Save\n");
        printf("2 - Discard\n");
        printf("\033[0m");
        printf("Enter your choice:");
        scanf("%d",&choice);
        fflush(stdin);
        if(choice==1)
        {
            char id[20];
            strcpy(id,t.accountNumber);
            strcat(id,".txt");
            FILE *f=fopen(id,"w");
            fclose(f);
            int n=countLines(accountsfilename);
            strcpy(acc[n].account_number,t.accountNumber);
            strcpy(acc[n].name,strtemp);
            strcpy(acc[n].address,t.email);
            acc[n].balance=atof(t.bal);
            strcpy(acc[n].mobile,t.mob);
            acc[n].date_opened.month=(date->tm_mon)+1;
            acc[n].date_opened.year=(date->tm_year)+1900;
            save(accountsfilename,n+1);
            printf("\033[1;32m");
            system("cls");
            printf("Added successfully \n");
            printf("\033[0m");
        }
        else if(choice==2)
        {
            system("cls");
            printf("- add\n");
            printf("added discarded !\n");
        }
        else
        {
            system("cls");
            printf("- add\n");
            printf("invalid choice try again !\n");
        }
    }
    while(choice!=1&&choice!=2);
}
void query_search()
{
    int size=countLines(accountsfilename);
    char acc_num[50];
    int i;
    int index;
    printf("Enter the account Number : ");
    fgets(acc_num,50,stdin);
    acc_num[strcspn(acc_num,"\n")]='\0';
    fflush(stdin);
    for(i=0; i<size; i++)
        if(strcmp(acc_num,acc[i].account_number)==0)
        {
            index=i;
            break;
        }
    if(i==size)
        printf("The account is not found!");
    else
    {
        printf("\nAccount Number:%s\n",acc[index].account_number);
        printf("Name:%s\n",acc[index].name);
        printf("E-mail:%s\n",acc[index].address);
        printf("Balance:%lf\n",acc[index].balance);
        printf("Mobile:%s\n",acc[index].mobile);
        printf("Date opened:%d/%d\n",acc[index].date_opened.month,acc[i].date_opened.year);
    }
}
int helping_func_for_advancedsearch(char *strsource,char *str)
{
    char str1[25];
    char str2[25];
    strcpy(str1,strsource);
    strcpy(str2,str);
    capatilize(str1);
    capatilize(str2);
    char*ptrl=NULL;
    ptrl=strstr(str1,str2);
    if(ptrl==NULL)
        return 0;
    else
        return 1;

}
void advanced_search()
{
    int size=countLines(accountsfilename);
    char name[25];
    do
    {
        printf("Enter keyword(at least 3 characters) : ");
        fflush(stdin);
        fgets(name,25,stdin);
        name[strcspn(name,"\n")]='\0';
        fflush(stdin);
    }
    while(strlen(name)<3);
    int i;
    int flag=1;
    printf("\033[1;32m");
    printf("\nSearch results:\n");
    printf("\033[0m");
    for(i=0; i<size; i++)
    {
        if(helping_func_for_advancedsearch(acc[i].name,name))
        {
            flag=0;
            printf("\nAccount Number : %s\n",acc[i].account_number);
            printf("Name:%s\n",acc[i].name);
            printf("E-mail:%s\n",acc[i].address);
            printf("Balance:%.2lf\n",acc[i].balance);
            printf("Mobile:%s\n",acc[i].mobile);
            printf("Date opened:%d/%d\n",acc[i].date_opened.month,acc[i].date_opened.year);
        }
    }
    if(flag)
        printf("NO data related to this keword!");

}
void  deletefun()
{

    int lines=countLines(accountsfilename);
    char id[15];
    int i;
    int flag=0;
    int flag2=0;
    int index=0;
    do
    {
        flag =0;
        printf("Please, Enter account number you want to delete ( M - return menu ) :");
        fgets(id,15,stdin);
        id[strcspn(id,"\n")]='\0';
        fflush(stdin);
        if(!strcasecmp(id,"M"))
        {
            system("cls");
            menu();
        }
        for(i=0; i<lines; i++)
            if(!strcmp(id,acc[i].account_number))
            {
                flag=1;
                index=i;
                break;
            }
        if(flag==0)
        {
            system("cls");
            printf("- Delete\n");
            printf("The account you looking for doesn't exist\n");
        }
        if(acc[i].balance!=0)
        {
            system("cls");
            printf("- Delete\n");
            printf("Reject removing, account's balance bigger than zero\n");
        }
    }
    while(acc[index].balance!=0||flag==0);
    system("cls");
    printf("- Delete -\n");
    int choice;
    do
    {
        printf("\033[1;31m");
        printf("Warning !\n");
        printf("you are going to Delete %s\n",acc[index].account_number);
        printf("1 - Save\n");
        printf("2 - Discard\n");
        printf("\033[0m");
        printf("Enter your choice:");
        scanf("%d",&choice);
        fflush(stdin);
        if(choice==1)
        {
            flag2=1;
            accounts x;
            for(i=index; i<lines; i++)
            {
                x=acc[i+1];
                acc[i+1]=acc[i];
                acc[i]=x;
            }
            char accnu[15];
            strcpy(accnu,id);
            strcat(accnu,".txt");
            remove(accnu);
            save(accountsfilename,lines-1);
            printf("\033[1;32m");
            system("cls");
            printf("Account removed successfully\n");
            printf("\033[0m");

        }
        else if(choice==2)
        {
            flag2=1;
            system("cls");
            printf("- Delete\n");
            printf("Delete discarded !");
        }
        else
        {
            system("cls");

            printf("- Delete\n");
            printf("Enter invalid choice ! try again \n");
        }
    }
    while(!flag2);

}
void deposit()
{
    int lines=countLines(accountsfilename);
    char id[15];
    int index,i;
    char input[10];
    double money;
    do
    {
        printf("Please, enter account id you want to deposit : ");
        scanf("%s",id);
        for(i=0; i<lines; i++)
            if(!strcmp(id,acc[i].account_number))
            {
                index=i;
                printf("Account name : %s\nCurrent balance : %.2lf$\n",acc[index].name,acc[index].balance);
                break;
            }
        if(i==lines)
        {
            system("cls");
            printf("- DEPOSIT -\n");
            printf("Account number not found!\n");
        }
    }
    while(strcmp(id,acc[index].account_number));
    while(1)
    {
        printf("Enter amount of money you want to deposit (Maximum 10000$ per transaction) : \n");
        scanf("%s", input);
        fflush(stdin);
        int j=0;
        int validInput = 1;
        while (input[j] != '\0')
        {
            if (!isdigit(input[j])&&input[j]!='.'&&strcasecmp(input,"M"))
            {
                validInput = 0;
                printf("Invalid input. Please enter a valid number.\n");
                break;
            }
            j++;
        }
        if (validInput)
        {
            sscanf(input,"%lf", &money);
            if(!strcasecmp(input,"M"))
            {
                system("cls");
                menu();
            }
            if (money > 10000 || money <= 0)
            {
                printf("Invalid amount. Please enter an amount between 0 and 10000 ( M - menu )\n");
            }
            else
            {
                break;
            }
        }
    }
    system("cls");
    printf("- Deposit -\n");
    int choice;
    do
    {
        printf("\033[1;31m");
        printf("Warning !\n");
        printf("you are going to Deposit %.2lf to account %s\n",money,acc[index].account_number);
        printf("1 - Save\n");
        printf("2 - Discard\n");
        printf("\033[0m");
        printf("Enter your choice:");
        scanf("%d",&choice);
        fflush(stdin);
        if(choice==1)
        {
            acc[index].balance+=money;
            save(accountsfilename,lines);
            printf("\033[1;32m");
            system("cls");
            printf("Deposit done successfully\n");
            printf("\033[0m");
            printf("Balance after deposit : %.2lf",acc[index].balance);
            FILE *facc;
            char accnum[19];
            strcpy(accnum,acc[index].account_number);
            strcat(accnum,".txt");
            facc=fopen(accnum,"a");
            fprintf(facc,"Deposit,%s,%.2lf,%.2lf\n",acc[index].account_number, acc[index].balance-money, acc[index].balance);
            fclose(facc);
        }
        else if(choice==2)
        {
            system("cls");
            printf("- Deposit\n");
            printf("Deposite discarded !");
        }
        else
        {
            system("cls");
            printf("- Deposit\n");
            printf("Enter invalid choice try again !\n");

        }
    }
    while(choice!=1&&choice!=2);
}
void Withdraw()
{
    int i,n=countLines(accountsfilename);
    char input[10];
    double money;
    char acc_num[15];
    int index;
    int choice;
    printf("Please enter account number : ");
   fgets(acc_num,15,stdin);
    acc_num[strcspn(acc_num,"\n")]='\0';
    if(check_account_number(acc_num))
    {

        for(i=0; i<n; i++)
        {
            if (strcmp(acc[i].account_number, acc_num) == 0)
            {
                index=i;
                break;
            }

        }
        if (acc[index].balance <= 0)
        {
            char menuChoice;
            do
            {
                printf("Transaction failed\nCurrent balance is %.2lf$!! You can't do any withdrawals.\n", acc[index].balance);
                printf("Press 'M' to go back to the menu: ");
                scanf("%c", &menuChoice);
                fflush(stdin);
                if (toupper(menuChoice) == 'M')
                {
                    system("cls");
                    menu();
                    return;
                }
            }
            while (menuChoice!='m'||menuChoice!='M');
        }

        printf("Account name: %s\nCurrent balance: %.2lf$\n", acc[index].name, acc[index].balance);
        while(1)
        {
            printf("Enter amount of money you want to withdraw (Maximum 10000$ per transaction) : \n");
            fgets(input,10,stdin);
            input[strcspn(input,"\n")]='\0';//new
            if(strlen(input)==0) continue;//new
            int j=0;
            int validInput = 1;
            while (input[j] != '\0')
            {
                if (!isdigit(input[j])&&input[j]!='.'&&strcasecmp(input,"M"))
                {
                    validInput = 0;
                    printf("Invalid input. Please enter a valid number \n");
                    break;
                }
                else if(!strcasecmp(input,"M"))
                {
                    system("cls");
                    menu();
                }
                j++;
            }
            if (validInput)
            {
                sscanf( input,"%lf", &money);
                if (money > 10000 || money <= 0)
                {
                    printf("Invalid amount. Please enter an amount between 0 and 10000 ( M - menu )\n");
                }
                else
                {
                    break;
                }
            }
        }
        if(money>acc[index].balance)
        {
            system("cls");
            printf("Transaction failed !\n");
            printf("Not enough balance");
        }

        else
        {
            system("cls");
            printf("- Withdraw -\n");
            int choice;
            do
            {
                printf("\033[1;31m");
                printf("Warning !\n");
                printf("you are going to Withdraw %.2lf from %s\n",money,acc[index].account_number);
                printf("\033[0m");
                printf("1 - Save\n");
                printf("2 - Discard\n");
                printf("\033[0m");
                printf("Enter your choice:");
                scanf("%d",&choice);
                fflush(stdin);
                if(choice==1)
                {
                    acc[index].balance-=money;
                    save(accountsfilename,n);
                    printf("\033[1;32m");
                    system("cls");
                    printf("Withdraw done successfully\n");
                    printf("\033[0m");
                    printf("Balance after withdraw : %.2lf",acc[index].balance);
                    char accid[19];
                    strcpy(accid,acc_num);
                    strcat(accid,".txt");
                    FILE *facc = fopen(accid, "a");
                    fprintf(facc, "Withdraw,%s,%.2lf,%.2lf\n", acc_num, acc[index].balance+money, acc[index].balance);
                    fclose(facc);

                }
                else if(choice==2)
                {
                    system("cls");
                    printf("- Withdraw\n");
                    printf("Withdraw discarded !");
                }
                else
                {
                    system("cls");
                    printf("- Withdraw\n");
                    printf("Enter invalid choice try again !\n");
                }
            }
            while(choice!=1&&choice!=2);
        }
    }
    else
    {
        system("cls");
        printf("- WITHDRAW -\n");
        printf("Invalid account number\n");
        Withdraw();
    }
}
void modify() // n is size of accounts array
{
    int c=0;
    int n = countLines(accountsfilename);
    char acc_num[50];
    char modified_name[50];
    char newphone[50];
    char new_address[50];
    int i,indicator,name_indicator,newphone_indicator,index,indicator_email;
    do
    {
        indicator=0;
        printf("Enter the account number : ");
        fflush(stdin);
        fgets(acc_num,50,stdin);
        acc_num[strcspn(acc_num,"\n")]='\0';
        for(i=0; i<n; i++)
            if(!strcmp(acc_num,acc[i].account_number))
            {
                index=i;
                break;
            }
        if(i==n)
        {
            printf("this account number does not exist!\n");
            fflush(stdin);
            while(1)
            {
                printf("1 - Enter number again\n2-Menu\n");
                printf("Enter your choice : ");
                scanf("%d",&indicator);
                fflush(stdin);
                if(indicator==1||indicator==2)
                    break;
                else printf("you entered invalid choice\n");
            }
        }
        if(indicator==2)
        {
            system("cls");
            menu();
        }
    }
    while(indicator==1);
    do
    {
        name_indicator=0;
        printf("Enter the (modified) new name:");
        fflush(stdin);
        gets(modified_name);
        if(!isNameadd(modified_name))
        {
            fflush(stdin);
            while(1)
            {
                printf("1-Enter a name\n2-Menu\n");
                printf("Enter your choice : ");
                scanf("%d",&name_indicator);
                fflush(stdin);
                if(name_indicator==1||name_indicator==2)
                    break;
                else printf("you entered invalid choice\n");
            }
        }
        if(name_indicator==2)
        {
            system("cls");
            menu();
        }
        validateName(modified_name);
        for(int s=0; s<strlen(modified_name); s++)
        {
            if(modified_name[s]==' ') c++;
        }
        if(c==0)
        {
            printf("Pleas enter first and last name\n");
            fflush(stdin);
        }
    }
    while(name_indicator==1||c==0);
    do
    {
        newphone_indicator=0;
        printf("Enter the (modified) new phone number:");
        fflush(stdin);
        fgets(newphone,50,stdin);
        newphone[strcspn(newphone,"\n")]='\0';
        fflush(stdin);
        if(!isMobileadd(newphone))
        {
            while(1)
            {
                printf("1-Enter another phone\n2-Menu\n");
                printf("Enter your choice : ");
                scanf("%d",&newphone_indicator);
                fflush(stdin);
                if(newphone_indicator==1||newphone_indicator==2)
                    break;
                else printf("you entered invalid choice\n");
            }
        }
        if(newphone_indicator==2)
        {
            system("cls");
            menu();
        }

    }
    while(newphone_indicator==1);
    do
    {
        indicator_email=0;
        printf("Enter the (modified) new E-mail: ");
        fflush(stdin);
        fgets(new_address,50,stdin);
        new_address[strcspn(new_address, "\n")] = '\0';
        if(!isEmailadd(new_address))
        {
            printf("the email entered is not valid\n");
            fflush(stdin);
            while(1)
            {
                printf("1-Enter another email\n2-Menu\n");
                printf("Enter your choice : ");
                scanf("%d",&indicator_email);
                fflush(stdin);
                if(indicator_email==1||indicator_email==2)break;
                else printf("you entered invalid choice\n");
            }
        }
        if(indicator_email==2)
        {
            system("cls");
            menu();
        }
    }
    while(indicator_email==1);
    system("cls");
    printf("- Modify -\n");
    int choice;
    do
    {
        printf("\033[1;31m");
        printf("Warning !\n");
        printf("you are going to modify account number %s data\n",acc[index].account_number);
        printf("1 - Save\n");
        printf("2 - Discard\n");
        printf("\033[0m");
        printf("Enter your choice:");
        scanf("%d",&choice);
        fflush(stdin);
        if(choice==1)
        {
            printf("test\n");
            validateName(modified_name);
            strcpy(acc[index].address,new_address);
            strcpy(acc[index].mobile,newphone);
            strcpy(acc[index].name,modified_name);
            save(accountsfilename,n);
            printf("\033[1;32m");
            system("cls");
            printf("Account modified successfully\n");
            printf("\033[0m");
        }
        else if(choice==2)
        {
            system("cls");
            printf("- Modify\n");
            printf("Modifying discarded !\n");
        }
        else
        {
            system("cls");
            printf("- Modify\n");
            printf("Enter invalid choice try again !\n");

        }
    }
    while(choice!=1&&choice!=2);
}
void transfer()
{
    int i;
    int index=0;
    int index2=0;
    char accNumF[11];
    char accNumT[11];
    int flag;
    double balance;
    int choice;
    char input[20];
    int lines = countLines(accountsfilename);
    do
    {
        printf("Enter Account Number to transfer from (M - to return menu): \n");
        fgets(accNumF,sizeof(accNumF),stdin);
        accNumF[strcspn(accNumF,"\n")]='\0';
        fflush(stdin);
        if(!strcasecmp(accNumF,"M"))
        {
            system("cls");
            menu();
        }
        for(i=0; i<lines; i++)
            if(!strcmp(accNumF,acc[i].account_number)) //validate
            {
                index=i;
                break;
            }
        if(acc[index].balance==0)
        {
            system("cls");
            printf("- TRANSFER -\n");
            printf("can't transfer from account has 0 balance ! \n");
        }
        if(i==lines)
        {
            system("cls");
            printf("- TRANSFER -\n");
            printf("Account number not found! ( M - menu )\n");
        }
    }
    while(strcmp(accNumF,acc[index].account_number)||acc[index].balance==0);
    do
    {
        printf("Enter Account Number to transfer To : \n");
        fgets(accNumT,sizeof(accNumT),stdin);
        accNumT[strcspn(accNumT,"\n")]='\0';
        fflush(stdin);
        if(!strcmp(accNumF,accNumT))
        {
            system("cls");
            printf("- TRANSFER -\n");
            printf("same account number ! ");

        }
        for(i=0; i<lines; i++)
        {
            if(!strcmp(accNumT,acc[i].account_number)&&strcmp(accNumF,accNumT))
            {
                index2=i;
                break;
            }
        }
        if(i==lines)
        {
            system("cls");
            printf("- TRANSFER -\n");
            printf("Account number not found! \n");
        }
    }
    while(strcmp(accNumT,acc[index2].account_number)&&!strcmp(accNumF,accNumT));
    do
    {
        printf("Acoount balance : %.2lf$ \n",acc[index].balance);
        printf("Enter amount of money you want to transfer : ");
        while(1)
        {
            fgets(input,sizeof(input),stdin);
            input[strcspn(input,"\n")]='\0';
            fflush(stdin);
            int j=0;
            int validInput = 1;
            while (input[j] != '\0')
            {
                if (!isdigit(input[j])&&input[j]!='.')
                {
                    validInput = 0;
                    printf("Invalid input. Please enter a valid number : \n");
                    break;
                }
                j++;
            }
            if (validInput)
            {
                sscanf( input,"%lf", &balance);
                break;
            }
        }
        if(balance>acc[index].balance)
        {
            system("cls");
            printf("- TRANSFER -\n");
            printf("can't transfer balance aren't enough ! \n");
            flag=1;
        }
        else if (balance < 0) printf("can't transfer negative !\n");
        else if(balance==0) printf("can't transfer 0 !\n");
        else
        {
            system("cls");
            printf("- TRANSFER -\n");

            do
            {
                flag=0;
                printf("\033[1;31m");
                printf("Warning !\n");
                printf("you are going to transfer %.2lf from %s to %s\n",balance,acc[index].account_number,acc[index2].account_number);
                printf("1 - save \n");
                printf("2 - discard \n");
                printf("\033[0m");
                printf("Enter your choice : ");
                scanf("%d",&choice);
                fflush(stdin);
                if(choice==1)
                {
                    acc[index].balance-=balance;
                    acc[index2].balance+=balance;
                    save(accountsfilename,lines);
                    printf("\033[1;32m");
                    system("cls");
                    printf("Transfer done successfully\n");
                    printf("\033[0m");
                    char accnumfrom[19];
                    strcpy(accnumfrom,acc[index].account_number);
                    strcat(accnumfrom,".txt");
                    FILE*from=fopen(accnumfrom,"a");
                    fprintf(from,"Transfer,");
                    fprintf(from,"%s,",acc[index].account_number);
                    fprintf(from,"%s,",acc[index2].account_number);
                    fprintf(from,"%.2lf,",acc[index].balance+balance);
                    fprintf(from,"%.2lf\n",acc[index].balance);;
                    fclose(from);

                    char accnumto[19];
                    strcpy(accnumto,acc[index2].account_number);
                    strcat(accnumto,".txt");
                    FILE*to=fopen(accnumto,"a");
                    fprintf(to,"Transfer,");
                    fprintf(to,"%s,",acc[index].account_number);
                    fprintf(to,"%s,",acc[index2].account_number);
                    fprintf(to,"%.2lf,",acc[index2].balance-balance);
                    fprintf(to,"%.2lf.\n",acc[index2].balance);;
                    fclose(to);

                }
                else if(choice==2)
                {
                    system("cls");
                    printf("- TRANSFER\n");
                    printf("Transfer discarded !");
                }
                else
                {
                    system("cls");
                    printf("- TRANSFER\n");
                    printf("Enter invalid choice try again !\n");
                }
            }
            while(choice!=1&&choice!=2);
        }
    }
    while(flag==1||balance<=0);
}
void report()
{

    char accno[20];
    while (1)
    {
        printf("Please enter account number: ");
        fgets(accno, 20, stdin);
        accno[strcspn(accno, "\n")] = '\0';
        fflush(stdin);
        if(isAccountNumberReport(accno)) break;
    }
    char id[20];
    strcpy(id,accno);
    strcat(id,".txt");
    FILE *f = fopen(id,"r");
    if (f == NULL)
    {
        printf("Account doesn't make any transactions .\n");
        return ;
        // Exit the function
    }

    int n = countLines(id);
    if (n == 0)
    {
        printf("Account doesn't make any transactions .\n");//for add (no transaction)
        fclose(f);
        return; // Exit the function
    }
    char str[100][100];
    char str1[100];
    char str2[100];
    char balbef[50];
    char balaft[50];

    for (int i = 0; i < n; i++)
    {
        fgets(str[i],100,f);
        str[i][strcspn(str[i], "\n")] = '\0';
    }
    fclose(f);
    int j =n-1;
    int end;
    if(n<5)
    {
        end =n;
    }
    else
    {
        end=5;
    }
    for (int i = 0; i <end; i++)
    {

        char *token = strtok(str[j], ",");
        if (strcmp(token, "Transfer") == 0)
        {
            token = strtok(NULL, ",");
            strcpy(str1, token);//from
            token = strtok(NULL, ",");
            strcpy(str2, token);//to
            token = strtok(NULL, ",");
            strcpy(balbef, token);//balance before
            token = strtok(NULL, "\n");
            strcpy(balaft, token);//balance after

            if (strcmp(accno, str1) == 0)
            {
                printf("\nAccount %s transferred %.2lf to account %s Balance before: %s Balance after: %s", accno, atof(balbef) - atof(balaft), str2, balbef, balaft);
            }
            else
            {
                printf("\nAccount %s received %.2lf from account %s Balance before: %s Balance after: %s", accno, atof(balaft) - atof(balbef), str1, balbef, balaft);
            }
        }
        else if (strcmp(token, "Withdraw") == 0)
        {
            token = strtok(NULL, ",");
            strcpy(str1, token);
            token = strtok(NULL, ",");
            strcpy(balbef, token);
            token = strtok(NULL, "\n");
            strcpy(balaft, token);
            printf("\nAccount %s has withdrawn %.2lf Balance before: %s Balance after: %s", accno, atof(balbef) - atof(balaft), balbef, balaft);
        }
        else if (strcmp(token, "Deposit") == 0)
        {
            token = strtok(NULL, ",");
            strcpy(str1, token);
            token = strtok(NULL, ",");
            strcpy(balbef, token);
            token = strtok(NULL, "\n");
            strcpy(balaft, token);
            printf("\nAccount %s has deposited %.2lf Balance before: %s Balance after: %s", accno, atof(balaft) - atof(balbef), balbef, balaft);
        }
        j--;
    }
}
void sortByName()
{
    accounts temp;
    int i,j,n=countLines(accountsfilename);
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(strcmp(acc[j].name,acc[j+1].name)==1)
            {
                temp=acc[j];
                acc[j]=acc[j+1];
                acc[j+1]=temp;
            }
        }
    }
    printf("\nNames in sorted manner: \n");
    for(i=0; i<n; i++)
    {
        printf("\nAccount Number : %s\n",acc[i].account_number);
        printf("Name:%s\n",acc[i].name);
        printf("E-mail:%s\n",acc[i].address);
        printf("Balance:%.2lf\n",acc[i].balance);
        printf("Mobile:%s\n",acc[i].mobile);
        printf("Date opened:%d/%d\n",acc[i].date_opened.month,acc[i].date_opened.year);
    }

}
int compareDates(int y1,int m1,int y2,int m2)
{
    struct tm date1= {0};
    struct tm date2= {0};
    date1.tm_year=y1-1900;
    date1.tm_mon=m1;
    date2.tm_year=y2-1900;
    date2.tm_mon=m2;
    time_t time1=mktime(&date1);
    time_t time2=mktime(&date2);
    double diff=difftime(time1,time2);
    if(diff>0)
        return 1 ;        //printf("date 1 is later");
    else if(diff<0)
        return -1;                //printf("date 1 is earlier");
    else return 0;                   //the same
}
void sortByDate()
{
    int i,j,n=countLines(accountsfilename);
    accounts tempTime;
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(compareDates(acc[j].date_opened.year,acc[j].date_opened.month,acc[j+1].date_opened.year,acc[j+1].date_opened.month)>0)
            {
                tempTime=acc[j];
                acc[j]=acc[j+1];
                acc[j+1]=tempTime;
            }
        }
    }
    printf("\nDates opened in sorted manner : \n");

    for(i=0; i<n; i++)
    {
        printf("\nAccount Number : %s\n",acc[i].account_number);
        printf("Name:%s\n",acc[i].name);
        printf("E-mail:%s\n",acc[i].address);
        printf("Balance:%.2lf\n",acc[i].balance);
        printf("Mobile:%s\n",acc[i].mobile);
        printf("Date opened:%d/%d\n",acc[i].date_opened.month,acc[i].date_opened.year);
    }
}
void sortByBalance()
{
    accounts temp;
    int i,j,n=countLines(accountsfilename);
    for(i=0; i<n-1; i++)
    {
        for(j=0; j<n-i-1; j++)
        {
            if(acc[j].balance<acc[j+1].balance)
            {
                temp=acc[j];
                acc[j]=acc[j+1];
                acc[j+1]=temp;
            }
        }
    }
    printf("\nBalance in sorted manner : \n");
    for(i=0; i<n; i++)
    {
        printf("\nAccount Number : %s\n",acc[i].account_number);
        printf("Name:%s\n",acc[i].name);
        printf("E-mail:%s\n",acc[i].address);
        printf("Balance:%.2lf\n",acc[i].balance);
        printf("Mobile:%s\n",acc[i].mobile);
        printf("Date opened:%d/%d\n",acc[i].date_opened.month,acc[i].date_opened.year);
    }
}
void printsort()
{
    int n;
    do
    {

        printf("1 - Names\n2 - Date opened\n3 - Balance\nPlease choose what do you want to print in a sorted manner : ");
        scanf("%d",&n);
        getchar();
        if(n==1)
        {
            system("cls");
            printf("- PRINT\n");
            sortByName();
        }
        else if(n==2)
        {

            system("cls");
            printf("- PRINT\n");
            sortByDate();
        }
        else if(n==3)
        {

            system("cls");
            printf("- PRINT\n");
            sortByBalance();
        }
        else
        {
            system("cls");
            printf("- PRINT\n");
            printf("Enter invalid choice try again ! \n");
        }
    }
    while(n>3 || n<1);

    load(accountsfilename);
}
void Quit()
{
    exit(1);
}


void menu ()
{
    int choice;
    char c;
    printf("\033[1;32m");
    printf("\t\t\t\tM A I N  M E N U  B A N K\n");
    printf("\t\t\t\t-------------------------\n\n");
    printf("\033[0m");
    printf("1- ADD\n");
    printf("2- DELETE\n");
    printf("3- MODIFY\n");
    printf("4- SEARCH\n");
    printf("5- ADVANCED SEARCH\n");
    printf("6- WITHDRAW\n");
    printf("7- DEPOSIT\n");
    printf("8- TRANSFER\n");
    printf("9- REPORT\n");
    printf("10- PRINT\n");
    printf("11- QUIT\n");
    do
    {
        load(accountsfilename);
        printf("Enter Your choice :");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice)
        {
        case 1:
                system("cls");
                printf("- ADD \n");
                add();
                do
                {
                    printf("A - ADD another account\nM - return menu\n");
                    printf("Enter char :");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='A'||c=='a')
                    {
                        system("cls");
                        printf("- ADD \n");
                        add();
                    }
                    else
                    {
                        system("cls");
                        printf("- ADD \n");
                        printf("Enter invalid order try again\n");
                    }
                }
                while(c!='M'||c!='m'||c!='A'||c!='a');
            break;
        case 2:
                system("cls");
                printf("- DELETE\n");
                deletefun();
                do
                {
                    printf("\nM - return menu\nD - delete another account\n");
                    printf("Enter char :");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='D'||c=='d')
                    {
                        system("cls");
                        printf("- DELETE\n");
                        deletefun();
                    }
                    else
                    {
                        system("cls");
                        printf("Enter invalid char \n");
                    }
                }
                while(c!='M'||c!='m'||c!='D'||c!='d');

            break;
        case 3:
                system("cls");
                printf("- MODIFY\n");
                modify();
                do
                {

                    printf("M - return menu\nE - modyfy again\n");
                    printf("Enter char : ");

                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='E'||c=='e')
                    {
                        system("cls");
                        printf("- MODIFY\n");
                        modify();
                    }
                    else
                    {
                        system("cls");
                        printf("- MODIFY\n");
                        printf("invalid order !\n");
                    }
                }
                while(c!='M'||c!='m'||c!='E'||c!='e');
            break;
        case 4:
                system("cls");
                printf("- SEARCH\n");
                query_search();
                do
                {
                    printf("\nS - search another account\nM - return menu \n");
                    printf("Enter char :");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='S'||c=='s')
                    {
                        system("cls");
                        printf("- SEARCH\n");
                        query_search();
                    }
                    else
                    {
                        system("cls");
                        printf("- SEARCH\n");
                        printf("Enter invalid order !");
                    }
                }
                while(c!='S'||c!='s'||c!='m'||c!='M');

            break;
        case 5:

                system("cls");
                printf("- ADVANCED SEARCH -\n");
                advanced_search();
                do
                {
                    printf("\nS - search again\nM - return menu \n");
                    printf("Enter char :");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='S'||c=='s')
                    {
                        system("cls");
                        printf("- ADVANCED SEARCH\n");
                        advanced_search();
                    }
                    else if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else
                    {

                        printf("- ADVANCED SEARCH -\n");
                        system("cls");
                        printf("Enter invalid order ! ");


                    }
                }
                while(c!='M'||c!='m'||c!='S'||c!='s');

            break;
        case 6:


                system("cls");
                printf("- WITHDRAW\n");
                Withdraw();
                do
                {
                    printf("\nM - return menu\nW - withdraw again\n");
                    printf("Enter char : ");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='W'||c=='w')
                    {
                        system("cls");
                        printf("- WITHDRAW\n");
                        Withdraw();
                    }
                    else
                    {
                        system("cls");
                        printf("invalid order !");
                    }
                }
                while(c!='M'||c!='m'||c!='W'||c!='w');
            break;
        case 7:
                system("cls");
                printf("- DEPOSIT\n");
                deposit();
                do
                {
                    printf("\nM - return menu\nD - DEPOST again\n");
                    printf("Enter char : ");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='D'||c=='d')
                    {
                        system("cls");
                        printf("- DEPOSIT\n");
                        deposit();
                    }
                    else
                    {
                        system("cls");
                        printf("- DEPOSIT\n");
                        printf("Enter invalid order !\n");
                    }
                }
                while(c!='M'||c!='m'||c!='D'||c!='d');
            break;
        case 8:
                system("cls");
                printf("- TRANSFER -\n");
                transfer(countLines(accountsfilename));
                do
                {
                    printf("\nM - return menu\nT - transfer again\n");
                    printf("Enter char :");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='T'||c=='t')
                    {
                        system("cls");
                        printf("- TRANSFER\n");
                        transfer(countLines(accountsfilename));
                    }
                    else
                    {
                        system("cls");
                        printf("invalid order !");
                    }
                }
                while(c!='M'||c!='M'||c!='T'||c!='t');
            break;
        case 9:
                system("cls");
                printf("- REPORT\n");
                report();
                do
                {
                    printf("\nM - return menu\nR - report again\n");
                    printf("Enter your choice : ");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='R'||c=='r')
                    {
                        system("cls");
                        printf("- REPORT\n");
                        report();
                    }
                    else
                    {
                        system("cls");
                        printf("- REPORT\n");
                        printf("invalid order try again !\n ");
                    }
                }
                while(c!='M'||c!='m'||c!='R'||c!='r');
            break;
        case 10:
                system("cls");
                printf("- PRINT\n");
                printsort();
                do
                {
                    printf("\nM - return menu\nP - print again\n");
                    printf("Enter char : ");
                    scanf("%c",&c);
                    fflush(stdin);
                    if(c=='M'||c=='m')
                    {
                        system("cls");
                        menu();
                    }
                    else if(c=='P'||c=='p')
                    {
                        system("cls");
                        printsort();
                    }
                    else
                    {
                        system("cls");
                        printf("- PRINT\n");
                        printf("invalid order !");
                    }
                }
                while(c!='M'||c!='m'||c!='P'||c!='p');
            break;
        case 11:
            system("cls");
            main();
            break;
        default :
            system("cls");
            printf("\033[1;32m");
            printf("\t\t\t\tM A I N  M E N U  B A N K\n");
            printf("\t\t\t\t-------------------------\n\n");
            printf("\033[0m");
            printf("1- ADD\n");
            printf("2- DELETE\n");
            printf("3- MODIFY\n");
            printf("4- SEARCH\n");
            printf("5- ADVANCED SEARCH\n");
            printf("6- WITHDRAW\n");
            printf("7- DEPOSIT\n");
            printf("8- TRANSFER\n");
            printf("9- REPORT\n");
            printf("10- PRINT\n");
            printf("11- QUIT\n");
            printf("Enter invalid choice ! \n");
        }
    }
    while(choice<1||choice>11);
}
loginInformation x;
void loginprint()
{
    do
    {
        system("cls");
        printf("\033[1;32m");
        printf("\t\t\t\tW E L C O M E  I N  B A N K\n");
        printf("\t\t\t\t---------------------------\n\n");
        printf("\033[0m");
        printf("- Login -\n");
        printf("Enter username ( Q for Quit ) : ");
        scanf("%s",x.user);
        if(strcasecmp(x.user,"Q")==0)
            Quit();
        printf("Enter password : ");
        scanf("%s",x.password);
        if(!checkLogin(countLines(usersfilename)))
        {
            system("cls");
            printf("\033[1;32m");
            printf("\t\t\t\tW E L C O M E  I N  B A N K\n");
            printf("\t\t\t\t---------------------------\n\n");
            printf("\033[0m");
            printf("- Login -\n");
            printf("incorrect username or password try again ! \n");
            printf("Enter username ( Q for Quit ) : ");
            scanf("%s",x.user);
            if(strcasecmp(x.user,"Q")==0)
                Quit();
            printf("Enter password : ");
            scanf("%s",x.password);
        }
    }
    while(!checkLogin(countLines(usersfilename)));
}
int checkLogin (int n)
{
    char users[n][15],passwords[n][15];
    int i=0,fU=0,fP=0;
    FILE *list=fopen(usersfilename,"r");
    if(list == NULL)
    {
        printf("can't open file");
        Quit;
    }
    while(!feof(list))
    {
        fscanf(list,"%s %s",users[i],passwords[i]);
        i++;
    }
    fclose(list);
    for(i=0; i<n; i++)
    {
        if(!strcmp(x.user,users[i]))
        {
            fU=1;
            if(!strcmp(x.password,passwords[i])) fP=1;
            break;
        }
    }
    if(fU&&fP) return 1;
    return 0;
}
int main()
{
    int choice;
    printf("\033[1;32m");
    printf("\t\t\t\tW E L C O M E  I N  B A N K\n");
    printf("\t\t\t\t---------------------------\n\n");
    printf("\033[0m");
    printf("1- Login\n");
    printf("2- Quit\n");
    do
    {
        printf("Enter Your Choice : ");
        scanf("%d",&choice);
        getchar();
        switch(choice)
        {
        case 1:
            do
            {
                system("cls");
                loginprint();
                if(checkLogin(countLines(usersfilename)))
                {
                    system("cls");
                    menu();
                }
            }
            while(!checkLogin(countLines(usersfilename)));
            break;
        case 2:
            Quit();
            break;
        default:
            system("cls");
            printf("\033[1;32m");
            printf("\t\t\t\tW E L C O M E  I N  B A N K\n");
            printf("\t\t\t\t---------------------------\n\n");
            printf("\033[0m");
            printf("1- Login\n");
            printf("2- Quit\n");
            printf("you Entered invalid order try again ! ");
        }
    }
    while(choice!=1||choice!=2);
    return 0;
}
