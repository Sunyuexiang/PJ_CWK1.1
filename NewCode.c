#include<stdio.h>
#include"book_management.h"
#include<stdlib.h>
#include<string.h>
#define M 256
#define  CreateNode(p) p = (Book *)malloc(sizeof(Book))
#define  DeleteNode(p) free((void*)p)

struct user database[M];
struct user check[M];
struct user Librarian;
int count=0;


void Register()
{
    int len,i;
    char inputuser[20],inputpass[20],buf[20];
    printf("Please input your username\n");
    scanf("%s",inputuser);
    len=strlen(inputuser);
    if(strcmp(inputuser,"Librarian") == 0){
        printf("This username is not allowed\n");
        return;
    }
    inputuser[len]='\0';
    printf("Please input your password\n");
    scanf("%s",inputpass);
    FILE *fp;
    fp=fopen("USER.txt","a+");
    while(fgets(buf,M,fp) != NULL){
        len=strlen(buf);
        buf[len-1]='\0';
        if(strcmp(buf,inputuser)==0){
            printf("Same username has been registered!\n");
            return;
        }
    }
    for(i = 0;i <= count; i++){
        if(strcmp(database[i].username,inputuser) == 0){
            printf("Same username has been registered!\n");
            return;
        }
    }
    fseek(fp,0,SEEK_END);
    fputs("\n",fp);
    fputs(inputuser,fp);
    fputs("\n",fp);
    fputs(inputpass,fp);
    fputs("\n",fp);
    strcpy(database[count].username,inputuser);
    strcpy(database[count].password,inputpass);
    count++;
    fclose(fp);
    return;
}
int Login(User *uh)
{
    strcpy(Librarian.username,"Librarian");
    strcpy(Librarian.password,"123456");
    int len,count1 = 0,count2 = 0,i = 0,j = 0,cuse;
    char use[20],pas[20],buf1[20],buf2[20];
    FILE *fp;
    fp=fopen("USER.txt","r");
    fgets(buf1,21,fp);
    while(fgets(buf1,21,fp)!=NULL)
    {
        len=strlen(buf1);
        buf1[len-1]='\0';
        if((count1%3) == 0){
            strcpy(check[i].username,buf1);
            i++;
        }
        count1++;
    }
    fseek(fp,0,SEEK_SET);
    fgets(buf2,21,fp);
    while(fgets(buf2,21,fp)!=NULL)
    {
        len=strlen(buf2);
        buf2[len-1]='\0';
        if((count2%3) == 1){
            strcpy(check[j].password,buf2);
            j++;
        }
        count2++;
    }
    printf("Please input your username here:\n");
    scanf("%s",use);
    len=strlen(use);
    use[len]='\0';
    if(strcmp(use,"Librarian")==0){
        printf("Please input your password:\n");
        scanf("%s",pas);
        len=strlen(pas);
        pas[len]='\0';
        if(strcmp(pas,"123456")==0){
            printf("Login successfully!You are on Librarian account!\n");
            return 2;
        }
    }
    for(cuse = 0;cuse <= i;cuse++){
        if(strcmp(check[cuse].username,use) == 0){
            printf("Please input your password here:\n");
            scanf("%s",pas);
            len=strlen(pas);
            pas[len]='\0';
            if(strcmp(check[cuse].password,pas) == 0){
                printf("Login successfully!\n");
                printf("Welcome,");
                printf("%s",use);
                printf("\n");
                strcpy(uh->username,use);
                return 1;
            }
            else{
                printf("Wrong password!\n");
                return 0;
            }
        }
    }
    cuse++;
    if(cuse>i){
        printf("No user founded!\n");
        return 0;
    }
    return 0;
}
void PrintList(Book *x){
    x=x->next;
    while(x!=NULL){
        printf("Title:  ");printf("%s\n",x->title);
        printf("Authors:  ");printf("%s\n",x->authors);
        printf("Book ID:  ");printf("%d\n",x->id);
        printf("Book's publish year:  ");printf("%d\n",x->year);
        printf("Present copies:  ");printf("%d\n",x->copies);
        printf("\n");
        x=x->next;
    }
}

void PrintNode(Book x){
    printf("Title:  ");printf("%s\n",x.title);
    printf("Authors:  ");printf("%s\n",x.authors);
    printf("Book ID:  ");printf("%d\n",x.id);
    printf("Book's publish year:  ");printf("%d\n",x.year);
    printf("Present copies:  ");printf("%d\n",x.copies);
    printf("\n");
}

int store_books(FILE *file,Book *h, char* bookfile){
    file=fopen(bookfile,"w");
    Book *x;
    int c = 0;
    x = h->next;
    while(1){

        if(!x){
            if(c == 0) {fclose(file); return -1;}
            else {fclose(file); return 0;}
        }

        if(fprintf(file,"%i\n",x->id) <= 0){
            if(c == 0) {fclose(file); return -1;}
            else {fclose(file); return 0;}
        }

        fputs(x->title,file);fputc('\n',file);
        fputs(x->authors,file);fputc('\n',file);
        fprintf(file,"%i\n",x->copies);
        fprintf(file,"%i\n",x->year);
        c++;
        x = x->next;
    }
}

int load_books(FILE *file,Book *h,char *bookfile){
    if((file = fopen(bookfile,"r")) == NULL) {
        printf("Fail to open file!\n");
        file=fopen(bookfile,"w");fclose(file);
        return -1;
    }
    Book *x,*q;
    char *str=(char *)malloc(51*sizeof(char *));
    int c = 0;
    x = h;
    while(1){
        CreateNode(q);
        q->title = (char*)malloc(50*sizeof(char));
        q->authors = (char*)malloc(50*sizeof(char));
        if(!x){
            if(c == 0) {fclose(file); return -1;}
            else {fclose(file); return 0;}
        }
        char a[100];
        if(!fgets(a,100,file)){
            if(c == 0) {fclose(file); return -1;}
            else {fclose(file); x->next=NULL; return 0;}
        }
        a[strlen(a)-1] = '\0';
        q->id = atoi(a);
        fgets(str,50,file);
        str[strlen(str)-1] = '\0';
        strcpy(q->title, str);
        fgets(str,50,file);
        str[strlen(str)-1] = '\0';
        strcpy(q->authors, str);
        char b[100];
        fgets(b,100,file);
        b[strlen(b)-1] = '\0';
        q->copies = atoi(b);
        char d[100];
        fgets(d,100,file);
        d[strlen(d)-1] = '\0';
        q->year = atoi(d);
        c++;
        x->next = q;
        x = x->next;
    }


}

int add_book(Book *book){
    char *t,*a;
    unsigned int i,y,c;
    t=(char *)malloc(51*sizeof(char *));
    a=(char *)malloc(51*sizeof(char *));
    printf("Input book's information\n");
    printf("Input new book's title:\n");
    fflush(stdin);
    fgets(t,51,stdin);
    t[strlen(t)-1] = '\0';
    fflush(stdin);
    Book *q;
    q = book;
    while(q->next){
        q = q->next;
    }
    Book *new;
    CreateNode(new);
    new->title=(char *)malloc(strlen(t)+1);
    strcpy(new->title,t);
    printf("Input new book's authors:\n");
    fflush(stdin);
    fgets(a,51,stdin);
    a[strlen(a)-1] = '\0';
    fflush(stdin);
    new->authors=(char *)malloc(strlen(a)+1);
    strcpy(new->authors,a);
    printf("Input new book's ID:\n");
    scanf("%d",&i);
    new->id=i;
    printf("Input new book's copies:\n");
    scanf("%d",&c);
    new->copies=c;
    printf("Input new book's publish year:\n");
    scanf("%d",&y);
    new->year=y;
    q->next = new;
    new->next = NULL;
    printf("The book has been added successfully!\n");
    return 0;
}

int remove_book(Book *book){
    char find[M];
    int len = strlen(find);
    find[len]='\0';
    Book *prior,*p;
    prior = book;
    p = book->next;
    printf("Please input the book(title) you want to remove:\n");
    scanf("%s",find);
    book->title=(char *)malloc(len+1);
    strcpy(book->title,find);
    while(p != NULL){
        if((p->next == NULL) && strcmp(p->title,find) != 0){
            printf("This book is not found!\n");
            return -1;
        }
        if(strcmp(p->title,find) == 0){
            if((p->next) == NULL){
                while((prior->next) != p)
                {
                    prior = prior->next;
                }
                DeleteNode(p);
                prior->next = NULL;
                printf("The book has been removed successfully!\n");
                return 0;
            }
            else{
                while((prior->next) != p){
                    prior = prior->next;
                }
                prior->next = p->next;
                p->next = NULL;
                DeleteNode(p);
                p=NULL;
                printf("The book has been removed successfully!\n");
                return 0;
            }
        }
        p=p->next;
    }
    return 0;
}

BookList find_book_by_title(const char *title,Book *h){
    int countc=0;
    Book *find;
    BookList BL;
    char x[M];
    find=h->next;
    printf("Please input book's title:\n");
    fflush(stdin);
    gets(x);
    while(find != NULL){
        if(strcmp(x,find->title) == 0){
            PrintNode(*find);
            countc++;
        }
        find=find->next;
    }
    BL.length=countc;
    if(BL.length==0) printf("This Book is not Found!\n");
    return BL;
}

BookList find_book_by_author(const char *author,Book *h){
    int countc=0;
    Book *find;
    BookList BL;
    char x[M];
    find=h->next;
    printf("Please input book's author(all authors):\n");
    fflush(stdin);
    gets(x);
    while(find!=NULL){
        if(strcmp(x,find->authors)==0){
            PrintNode(*find);
            countc++;
        }
        find=find->next;
    }
    BL.length=countc;
    if(BL.length==0) printf("This Author's book is not Found!\n");
    return BL;
}

BookList find_book_by_year (unsigned int year,Book *h){
    int counta=0;
    Book *find;
    find=h->next;
    BookList BL;
    unsigned int fo;
    printf("Please input book's Publish Year:\n");
    scanf("%d",&fo);
    while(find!=NULL){
        if(fo==find->year){
            PrintNode(*find);
            counta++;
        }
        find=find->next;
    }
    BL.length=counta;
    if(BL.length == 0) printf("The book published in this year is not found!\n");
    return BL;
}

void Borrow_book(FILE *file,Book *book,User *uh,Book *ub){
    Book *find = book->next;
    char borr[M],flag,name[100];
    strcpy(name,uh->username);
    strcat(uh->username,"borrow.txt");
    if((file = fopen(uh->username,"r")) == NULL) {
        printf("Not Find the user's borrow history\n");
        fclose(file);
        file = fopen(uh->username,"a");
        fclose(file);
    }
    else{
        load_books(file,ub,uh->username);
    }
    strcpy(uh->username,name);
    printf("Please input the book's title you want to borrow:\n");
    fflush(stdin);
    gets(borr);
    int jud=0;
    while(find != NULL){
        if((strcmp(find->title,borr) == 0) && (find->copies > 0)){
            jud++;
            PrintNode(*find);
            printf("Are you sure borrow this book? Y/N\n");
            scanf("%c",&flag);
            if(flag=='Y'){
                find->copies--;
                char *t,*a;
                Book *new,*last;
                last = ub;
                t=(char *)malloc(51*sizeof(char *));
                a=(char *)malloc(51*sizeof(char *));
                CreateNode(new);
                while(last->next != NULL){
                    last = last->next;
                }
                new->title=(char *)malloc(strlen(t)+1);
                new->authors=(char *)malloc(strlen(a)+1);
                strcpy(new->title,find->title);
                strcpy(new->authors,find->authors);
                new->copies=1;
                new->year=find->year;
                new->id=find->id;
                last->next = new;
                new->next = NULL;
                printf("Borrow successfully\n");
                PrintList(ub);
                store_books(file,ub,uh->username);
                break;
            }
            if(flag=='N'){
                return;
            }
            else{
                printf("Wrong input!");
                return;
            }
        }
        if(find->copies==0){
            jud++;
            printf("This book has no inventory!\n");
            return;
        }
        find = find->next;
    }
    if(jud == 0){
        printf("This book is not found\n");
        return;
    }
    return;
}

void Return_book(FILE *file,Book *book,User *uh,Book *ub){
    Book *find = ub,*last = ub;
    char re[M],flag,name[100];
    strcpy(name,uh->username);
    strcat(uh->username,"borrow.txt");
    if((file = fopen(uh->username,"r")) == NULL) {
        printf("Not Find the user's borrow history\n");
        fclose(file);
        file = fopen(uh->username,"a");
        fclose(file);
    }
    else{
        load_books(file,ub,uh->username);
    }
    strcpy(uh->username,name);
    printf("Please input the book's title you want to return:\n");
    fflush(stdin);
    gets(re);
    int jud = 0;
    while(find != NULL) {
        find = find->next;
        if (strcmp(find->title, re) == 0) {
            jud++;
            PrintNode(*find);
            printf("Are you sure to return this book? Y/N\n");
            scanf("%c", &flag);
            if (flag == 'Y') {
                last->next = find->next;
                Book *prior;
                prior = book->next;
                while (strcmp(prior->title, find->title) != 0) {
                    prior = prior->next;
                }
                prior->copies++;
                PrintList(ub);
                store_books(file, ub, uh->username);
                printf("Return successfully\n");
                break;
            } else if (flag == 'N') {
                return;
            } else {
                printf("Wrong input!");
                return;
            }
        }
        last = last->next;
    }
    if(jud == 0){
        printf("This book is not found\n");
        return;
    }
}

int main(int argc, char *argv[]){
    Book *h=(Book *)malloc(sizeof (Book));
    Book *ub=(Book *)malloc(sizeof (Book));
    User *uh=(User *)malloc(sizeof(User));
    h->next=NULL;
    ub->next = NULL;
    FILE *file;
    char *filename,*author,*title;
    int year;
    filename=(char *)malloc(100*sizeof(char));
    strcpy(filename,argv[1]);
    int a,b,c,d,e,f;
    while(1){
        printf("**********************************\n");
        printf("**     Welcome To Library:      **\n");
        printf("**     You want to:             **\n");
        printf("**     1.Register or Log in     **\n");
        printf("**     2.Search Books           **\n");
        printf("**     3.Exit                   **\n");
        printf("**********************************\n\n");
        scanf("%d",&a);
        if(a != 1 && a != 2 && a != 3){
            printf("Error,Re-Enter!\n");
        }
        else if(a == 1){
            while(1) {
                printf("**********************************\n");
                printf("**     1.Register               **\n");
                printf("**     2.Log in                 **\n");
                printf("**     3.Exit                   **\n");
                printf("**********************************\n\n");
                scanf("%d", &b);
                if (b != 1 && b != 2 && b != 3) {
                    printf("Error,Re-Enter!\n");
                }
                else if (b == 1) {
                    Register();
                }
                else if (b == 2) {
                    d = Login(uh);
                    if(d == 1){
                        while(1){
                            printf("**********************************\n");
                            printf("**     User You want to         **\n");
                            printf("**     1.Borrow Books           **\n");
                            printf("**     2.Return Books           **\n");
                            printf("**     3.Display Books          **\n");
                            printf("**     4.Exit                   **\n");
                            printf("**********************************\n\n");
                            scanf("%d",&f);
                            if (f != 1 && f != 2 && f != 3 && f != 4) {
                                printf("Error,Re-Enter!\n");
                            }
                            else if (f == 1){
                                load_books(file,h,filename);
                                Borrow_book(file,h,uh,ub);
                                store_books(file,h,filename);
                            }
                            else if (f == 2){
                                load_books(file,h,filename);
                                Return_book(file,h,uh,ub);
                                store_books(file,h,filename);
                            }
                            else if(f == 3){
                                load_books(file,h,filename);
                                PrintList(h);
                                store_books(file,h,filename);
                            }
                            else if(f == 4){
                                char name[100];
                                strcpy(name,uh->username);
                                strcat(uh->username,"borrow.txt");
                                FILE *f = fopen(uh->username,"w");
                                Book *now = ub->next;
                                while(now != NULL){
                                    fprintf(f,"%i\n",now->id);
                                    fputs(now->title,f);
                                    fputc('\n',f);
                                    fputs(now->authors,f);
                                    fputc('\n',f);
                                    fprintf(f,"%i\n",now->copies);
                                    fprintf(f,"%i\n",now->year);
                                    now = now->next;
                                }
                                strcpy(uh->username,name);
                                fclose(f);
                                break;
                            }
                        }
                    }
                    if(d == 2){
                        while(1){
                            printf("**********************************\n");
                            printf("**     Librarian You want to:   **\n");
                            printf("**     1.Add Books              **\n");
                            printf("**     2.Delete Books           **\n");
                            printf("**     3.Display Books          **\n");
                            printf("**     4.Exit                   **\n");
                            printf("**********************************\n\n");
                            scanf("%d",&e);
                            if (e != 1 && e != 2 && e != 3 && e !=4){
                                printf("Error,Re-Enter!\n");
                            }
                            else if(e == 1){
                                load_books(file,h,filename);
                                add_book(h);
                                store_books(file,h,filename);
                            }
                            else if(e == 2){
                                load_books(file,h,filename);
                                remove_book(h);
                                store_books(file,h,filename);
                            }
                            else if(e == 3){
                                load_books(file,h,filename);
                                PrintList(h);
                                store_books(file,h,filename);
                            }
                            else if(e == 4){
                                break;
                            }
                        }

                    }
                }
                else if (b == 3) {
                    break;
                }
            }
        }
        else if(a == 2){
            while(1){
                printf("**********************************\n");
                printf("** You want to Search Books By: **\n");
                printf("**     1.Title                  **\n");
                printf("**     2.Authors                **\n");
                printf("**     3.Years                  **\n");
                printf("**     4.Exit                   **\n");
                printf("**********************************\n\n");
                scanf("%d",&c);
                if(c != 1 && c != 2 && c != 3 && c != 4){
                    printf("Error,Re-Enter!\n");
                }
                else if(c == 1){
                    find_book_by_title(title,h);
                }
                else if(c == 2){
                    find_book_by_author(author,h);
                }
                else if(c == 3){
                    find_book_by_year (year,h);
                }
                else if(c == 4){
                    break;
                }
            }
        }
        else if(a == 3){
            break;
        }
    }
    return 0;
}
