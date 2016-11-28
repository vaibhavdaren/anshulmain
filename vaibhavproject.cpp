#include<iostream>
#include<conio.h>
#include <dos.h>
#include<graphics.h>
//Menu Global Item
#define pixTOrc(x) (8*(x-1))  //convert pixel into row and col format
#define INC 5  //Increment Distance Between Menu Items
#define ROW 15 //Row Value for Menu Item
#define COL 8 //Column Value for Menu Item
#define MAXMENU 5 //Total menu items
#define MAXITEM 5
using namespace std;

// To display the Inventory Main menu options
typedef char option[20];


void printline()
{
    for(int i=0;i<14;i++)
        cout<<"*";
    cout<<endl;
}

struct employee
{
    int eno;
    char name[20];
    int salary;
    char phoneno[20];
};

void getdata(employee &e)
{
    cout<<"Enter Employee Number       :";
    cin>>e.eno;
    cout<<endl;
    cout<<"Enter Employee Name       :";
    cin>>e.name;
    cout<<endl;
    cout<<"Enter Employee salary       :";
    cin>>e.salary;
    cout<<endl;
    cout<<"Enter Employee phone       :";
    cin>>e.phoneno;
    cout<<endl;
}

employee e[10];
void displaydata(employee e)
{
    cout<<"Employee Number       :";
    cout<<e.eno;
    cout<<endl;
    cout<<"Employee Name       :";
    cout<<e.name;
    cout<<endl;
    cout<<"Employee salary       :";
    cout<<e.salary;
    cout<<endl;
    cout<<"Employee phone       :";
    cout<<e.phoneno;
    cout<<endl;

}

struct node
{
  employee data;
  struct node *next;
};

employee p;
node *head=NULL;

void printList(struct node *node)
{   employee temp;
    while (node != NULL)
    {
        //printf(" %d ", node->data);
        temp=node->data;
        displaydata(temp);
        printline();
        node = node->next;
    }
}

void append(struct node** head_ref)
{
    employee temp;
    getdata(temp);
    /* 1. allocate node */
    struct node* new_node = (struct node*) malloc(sizeof(struct node));

    struct node *last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    new_node->data  = temp;

    /* 3. This new node is going to be the last node, so make next
          of it as NULL*/
    new_node->next = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }

    /* 5. Else traverse till the last node */
    while (last->next != NULL)
        last = last->next;

    /* 6. Change the next of last node */
    last->next = new_node;
    return;
}
int search(struct node* head)
{
    cout<<"Enter ID of employee:   ";
    int x;
    cin>>x;
    struct node* current = head;  // Initialize current
    while (current != NULL)
    {
    employee temp=current->data;


        if (temp.eno == x){
            cout<<"\nSuccessfull Match"<<endl;
            displaydata(temp);
            return 1;
        }
        current = current->next;
    }
    return 0;
}
void editdata(struct node* head)
{
    cout<<"Enter ID of employee to Edit   ";
    int x;
    int flag=0;
    cin>>x;
    struct node* current = head;  // Initialize current
    while (current != NULL)
    {
    employee temp=current->data;


        if (temp.eno == x){
            flag=1;
            cout<<"\nSuccessfull Match: Now enter new details"<<endl;
            getdata(temp);
            current->data=temp;
        }
        current = current->next;
    }
    if(flag==0)
        cout<<"Entry Not found \n";
}


option MMenu[]= {
             "View ALL",
				"Search Employee",
				"New Employee",
				"Edit Employee",
				"Quit"
		      };
// Function to displays all the menu prompt messages from the pointer array of option a[]
void normalvideo(int x,int y,char *str)
{
   x=pixTOrc(x);
   y=pixTOrc(y);
   outtextxy(x,y,str);
}
// Function to move the cursor on the menu prompt with a reverse video color
void selectedMenu(int x,int y,char *str)
{
   x=pixTOrc(x);
   y=pixTOrc(y);
   setcolor(5);  //Selected Item Color
//   sound(400);
   delay(100);
//   nosound();
   outtextxy(x,y,str);
   setcolor(WHITE); //Unselected Item Color
//   sound(500);
   delay(100);
 //  nosound();
}
//Keep Track of which arrow key is pressed
char menu()
{
   settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
   setcolor(WHITE);  //Initial Menu Item Color
   int i,done;
   for(i = 1; i < MAXMENU; i++)
   normalvideo(COL, (i*INC)+ROW, MMenu[i]);
   selectedMenu(COL,ROW, MMenu[0]);
   i = done = 0;
   do
   {
      /**Status Bar Code**/
      setfillstyle(SOLID_FILL,BLUE);
      settextstyle(SMALL_FONT,HORIZ_DIR,5);
      bar(pixTOrc(2),pixTOrc(52.5),pixTOrc(75),pixTOrc(55));
      setcolor(LIGHTCYAN);
      switch(i)
      {
        case 0 : outtextxy(pixTOrc(5),pixTOrc(52.75),"View ALL --> View all Employees");
                 break;
        case 1 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Search Employee--> Find an Employee in database");
         		  break;


        case 2 : outtextxy(pixTOrc(5),pixTOrc(52.75),"New Employee --> Create a new account for customer");
                 break;
        case 3 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Edit Employee --> Edit an existing account");
                 break;
        case 4 : outtextxy(pixTOrc(5),pixTOrc(52.75),"Close the Program");
                 break;
      }
      /**status Bar ends**/
      setcolor(WHITE);
      settextstyle(TRIPLEX_FONT,HORIZ_DIR,2);
      int key = getch();
      switch (key)
      {
         case 00: key = getch();
            switch (key)
            {
               case 72: normalvideo(COL, (i*INC)+ROW, MMenu[i]);
          	          i--;
             		      if (i == -1)
                           i = MAXITEM-1;
                           selectedMenu(COL,(i*INC)+ROW,MMenu[i]);
                        break;
               case 80: normalvideo(COL, (i*INC)+ROW, MMenu[i]);
           	          i++;
           	          if (i == MAXITEM)
                           i = 0;
                           selectedMenu(COL, (i*INC)+ROW, MMenu[i]);
                        break;
            }
            break;
         case 13: done = 1;
      }
   }
   while (!done);
   return(i+49);
}
//This part you can use for main functionality of the menu
void mainArea()
{
   setcolor(BLUE);
   outtextxy(pixTOrc(30),pixTOrc(20),"daren@gmail.com");
   setcolor(YELLOW);
}
/* Code for displaying the main menu*/
void call_menu()
{
   char choice;
   do
   {
      choice = menu();
      switch (choice)
      {
         case '1': setcolor(BLUE);
                   outtextxy(pixTOrc(40),pixTOrc(15),"View ALL");
                   mainArea();
                   getch();
                   setfillstyle(SOLID_FILL,LIGHTGRAY);
                   bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
                   //displaydata(p);
                   printList(head);
                   mainArea();
                   break;
       	case '2':
                   setcolor(BLUE);
       	         outtextxy(pixTOrc(40),pixTOrc(15),"Search Employee");
       	         mainArea();
       	         getch();
       	         setfillstyle(SOLID_FILL,LIGHTGRAY);
       	         bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
       	         int flag1;
       	         flag1=search(head);
       	         if(flag1==0)
                    cout<<"XXX----Not Found---XXX"<<endl;
       	         mainArea();
       	         break;


       	case '3':

       	         setcolor(BLUE);
       	         outtextxy(pixTOrc(40),pixTOrc(15),"New Employee");
       	         mainArea();
       	         getch();
       	         setfillstyle(SOLID_FILL,LIGHTGRAY);
       	         bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
       	         //getdata(p);
       	         append(&head);
       	         mainArea();
       	         break;
       	case '4':
       	         setcolor(BLUE);
       	         outtextxy(pixTOrc(40),pixTOrc(15),"Edit Employee");
       	         mainArea();
       	         getch();
       	         setfillstyle(SOLID_FILL,LIGHTGRAY);
       	         bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
       	         editdata(head);
       	         mainArea();
       	         break;
       	case '5':    //Close the project
       	         setcolor(BLUE);
       	         outtextxy(pixTOrc(40),pixTOrc(15),"Quit");
       	         mainArea();
       	         delay(1000);
       	         setfillstyle(SOLID_FILL,LIGHTGRAY);
       	         bar(pixTOrc(28),pixTOrc(14),pixTOrc(75),pixTOrc(50));
       	         mainArea();
       	         goto exit;
      }
   } while (choice != MAXITEM);

exit:
    ;
}
int main()
{
   int i,j;
   int gd=DETECT,gm=0;
   initgraph(&gd,&gm,"C:\\TC\\BGI");
   setcolor(BLACK);
   rectangle(0,0,640,480);
   setfillstyle(SOLID_FILL,LIGHTGRAY);
   bar(2,1,637,478);
   setfillstyle(SOLID_FILL,BLACK);
   bar(1,3,637,50);
   settextstyle(BOLD_FONT,HORIZ_DIR,2);
   setcolor(YELLOW);
   outtextxy(pixTOrc(12),pixTOrc(1)," Employee Management System ");
   setfillstyle(CLOSE_DOT_FILL,DARKGRAY);
   bar(pixTOrc(7),pixTOrc(14),pixTOrc(25),pixTOrc(50));
   call_menu();
   closegraph();
   return 0;
}
