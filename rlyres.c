#include <stdio.h>
#include "rlyres.h"
#include "conio2.h"
#include <windows.h>
#include <string.h>
#include <ctype.h>
//#include "graphics.h"

int enterchoice() {
       int choice;
       printf("\n \n \t Select an option : \n");
       printf("\t 1- View Trains \n");
       printf("\t 2- Book Ticket \n");
       printf("\t 3- View Ticket \n");
       printf("\t 4- Search Ticket No \n");
       printf("\t 5- View All Bookings \n");
       printf("\t 6- View Train Bookings \n");
       printf("\t 7- Cancel Ticket \n");
       printf("\t 8- Cancel Train \n");
       printf("\t 9-  Quit \n");
       printf("\n \t Enter choice: ");
       scanf("%d", &choice);
       return choice;
}

int book_ticket(Passenger psg) {

       textcolor(LIGHTGRAY);
       int ticket_count = get_booked_ticket_count(psg.train_no, psg.P_class);

       if(ticket_count == 2) {
              textcolor(LIGHTRED);
              clear_char(70, 28, 64);
              printf("All seats full in Train no. %s in %c class!\n", psg.train_no, psg.P_class);
              return -1;
       }

       int ticket_no = last_ticket_no() + 1;
       psg.ticket_no = ticket_no;
       FILE* fp = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "ab");
       if(fp == NULL) {
              textcolor(LIGHTRED);
              clear_char(70, 28, 64);
              gotoxy(80, 28);
              printf("Sorry! File cannot be opened");
              return -1;
       }
       fwrite(&psg, sizeof(Passenger), 1, fp);
       fclose(fp);
       return ticket_no;
}

void add_trains() {
       clrscr();
       FILE* fp;
       textcolor(WHITE);
       gotoxy(90, 28);
       fp = fopen("D:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\alltrains.dat", "rb");
       if(fp != NULL) {
              printf("\t File already present \n");
              fclose(fp);
              gotoxy(45, 15);
              system("pause");
              return;
       }
       fp = fopen("D:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\alltrains.dat", "wb");

       Train alltrains[4] = {
              {"123", "BPL", "GWA", 2100, 1500},
              {"546", "BPL", "DEL", 3500, 2240},
              {"345", "HBJ", "AGR", 1560, 1135},
              {"896", "HBJ", "MUM", 4500, 3360},
       };
       fwrite(alltrains, sizeof(alltrains), 1, fp);
       printf("\t File Saved Successfully \n");
       fclose(fp);
       gotoxy(55, 15);
       system("pause");
}

void view_trains() {
       clrscr();
       gotoxy(50, 3);
       textcolor(CYAN);
       printf("Railway Reservation System \n");
       for(int i = 0; i < 120; i++) {
              printf("-");
       }
       printf("\n \n");

       textcolor(LIGHTGREEN);
       printf("\t TRAIN NO\t\t FROM\t\t TO\t\t FIRST AC FARE\t\t\t SECOND AC FARE\n");
       for(int i = 0; i < 120; i++) {
              printf("-");
       }
       printf("\n");

       FILE* fp = fopen("D:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\alltrains.dat", "rb");
       Train train;

       while(fread(&train, sizeof(Train), 1, fp) == 1) {
              printf("\t %s\t\t\t %s\t\t %s\t\t %d\t\t\t\t %d\n", train.train_no, train.from, train.to, train.fac_fare, train.sac_fare);
       }

       gotoxy(85, 28);
       fclose(fp);
       textcolor(WHITE);
       printf("press any key to go the main screen. \n");
       getch();
}

int check_train_no(char* train_no) {
       FILE* fp = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\alltrains.dat", "rb");
       Train train;
       while(fread(&train, sizeof(Train), 1, fp) == 1) {
                     if(strcmp(train.train_no, train_no) == 0) {
                            fclose(fp);
                            return 1;
                     }
       }
       fclose(fp);
       return 0;
}

 int accept_ticket_no() {
       textcolor(LIGHTGRAY);
       printf("\n\t Enter a valid ticket no : ");
       int valid;
       int ticket_no;
       do {
              valid = 1;
              scanf("%d", &ticket_no);
              if(ticket_no == 0) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Canceling input...!\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     return 0;
              }
              if(ticket_no < 0) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     printf("Error! Ticket no. should be positive");
                     getch();
                     valid = 0;
                     clear_char(11, 1, 5);
                     textcolor(LIGHTGRAY);
              }
       } while(valid == 0);
       return ticket_no;
 }

 void view_ticket(int ticket_num) {

       FILE* fp_book;
       int found;

       fp_book = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");
       if(fp_book == NULL) {

              clear_char(70, 28, 64);

              textcolor(LIGHTRED);
              gotoxy(90, 28);
              printf("No Bookings done yet");

              return;
       }

       printf("\n\n");
       textcolor(LIGHTGREEN);

       Passenger psg;
       found  = 0;
       while(fread(&psg, sizeof(Passenger),1, fp_book)) {

              if(psg.ticket_no == ticket_num) {

                     printf("\n\t NAME : %s\n\t GENDER : %c \n\t TRAIN NO. : %s \n\t CLASS : %c \n\t ADDRESS : %s \n\t AGE : %d \n\t MOBILE NO. : %s \n\t TICKET NO. : %d", psg.p_name, psg.gender, psg.train_no, psg.P_class, psg.address, psg.age, psg.mobile_no, psg.ticket_no);
                     printf("\n\n");

                     found = 1;
                     break;
              }
       }
       if(!found) {

                     textcolor(LIGHTRED);
                     printf("\t No details of the ticket no. %d found!", ticket_num);
       }
       fclose(fp_book);
 }

Passenger* get_passenger_details() {
       clrscr();
       gotoxy(50, 3);
       textcolor(CYAN);
       printf("Railway Reservation System \n");
       textcolor(LIGHTRED);
       gotoxy(85, 3);
       printf("Enter 0 to EXIT\n \n");
       textcolor(CYAN);
       for(int i = 0; i < 120; i++) {
              printf("-");
       }
       printf("\n\n\n");
       textcolor(LIGHTGRAY);
       static Passenger psg;

       printf("\t Enter passenger name : ");
       fflush(stdin);
       fgets(psg.p_name, 20, stdin);
       char* pos;
       pos = strchr(psg.p_name, '\n');
       *pos = '\0';
       if(strcmp(psg.p_name, "0") == 0) {
              textcolor(LIGHTRED);
              clear_char(70, 28, 64);
              gotoxy(90, 28);
              printf("Reservation Canceled.\n");
              getch();
              textcolor(LIGHTGRAY);
              return NULL;
       }

       int valid;
       printf("\t Enter gender(M/F) : ");
       do {
              clear_char(70, 28, 64);
              gotoxy(30, 9);
              valid = 1;
              fflush(stdin);
              scanf("%c", &psg.gender);
              if(psg.gender == '0') {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Reservation Canceled.\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     return NULL;
              }
              if(psg.gender != 'M' && psg.gender != 'F') {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     printf("Error! Gender should be M or F (in Uppercase)!\n");
                     valid = 0;
                     getch();
                     textcolor(LIGHTGRAY);
                     gotoxy(30, 9);
                     printf(" \b");
              }
       } while(valid == 0);

       printf("\t Enter train Number : ");
       do {
              clear_char(70, 28, 64);
              gotoxy(31, 10);
              valid = 1;
              fflush(stdin);
              fgets(psg.train_no, 10, stdin);
              pos = strchr(psg.train_no, '\n');
              *pos = '\0';
              if(strcmp(psg.train_no, "0") == 0) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Reservation Canceled.\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     return NULL;
              }

              //valid = check_train_no();
              if((valid = check_train_no(psg.train_no)) == 0) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     printf("Error! Invalid Train number!\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     clear_char(31, 10, 10);
              }
       } while(valid == 0);

       printf("\t Enter traveling class(First AC: F && Second AC: S) : ");
       do {
              clear_char(70, 28, 64);
              gotoxy(63, 11);
              valid = 1;
              fflush(stdin);
              scanf("%c", &psg.P_class);
              if(psg.P_class == '0') {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Reservation Canceled.\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     return NULL;
              }
              if(psg.P_class != 'F' && psg.P_class != 'S') {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     printf("Error! Traveling class should be F or S!\n");
                     valid = 0;
                     getch();
                     textcolor(LIGHTGRAY);
                     gotoxy(63, 11);
                     printf(" \b");
              }
       } while(valid == 0);

       printf("\t Enter your Address : ");
       fflush(stdin);
       fgets(psg.address, 80, stdin);
       pos = strchr(psg.address, '\n');
       *pos = '\0';
       if(strcmp(psg.address, "0") == 0) {
              textcolor(LIGHTRED);
              clear_char(70, 28, 64);
              gotoxy(90, 28);
              printf("Reservation Canceled.\n");
              getch();
              textcolor(LIGHTGRAY);
              return NULL;
       }

       printf("\t Enter age : ");
       do {
              clear_char(70, 28, 64);
              clear_char(22, 13, 5);
              valid = 1;
              fflush(stdin);
              scanf("%d", &psg.age);
              if(psg.age == 0) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Reservation Canceled.\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     return NULL;
              }
              if(psg.age < 0 || psg.age >= 125) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     printf("Error! Age should be Positive and Valid!\n");
                     valid = 0;
                     getch();
                     textcolor(LIGHTGRAY);
                     clear_char(22, 13, 5);
              }
       } while(valid == 0);

       printf("\t Enter mobile no. : ");
       do {
              clear_char(70, 28, 64);
              clear_char(29, 14, 11);
              fflush(stdin);
              fgets(psg.mobile_no, 12, stdin);
              pos = strchr(psg.mobile_no, '\n');
              if(pos != NULL) {
                     *pos = '\0';
              }
              if((valid = strcmp(psg.mobile_no, "0"))== 0) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Reservation Canceled.\n");
                     getch();
                     textcolor(LIGHTGRAY);
                     return NULL;
              }
              if(!check_mob_no(psg.mobile_no)) {
                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);
                     printf("Error! Invalid mobile no.\n");
                     valid = 0;
                     getch();
                     textcolor(LIGHTGRAY);
                     clear_char(29, 14, 11);

              }
       } while(valid == 0);

       return &psg;
}

int check_mob_no(char* mobile_no) {
       if(strlen(mobile_no) != 10) {
              return 0;
       }
       for(int i = 0; i <= 9; i++) {
              /*
              if ((int)mobile_no[i] > 57 && (int)mobile_no[i] < 48) {
                     return 0;
              }
              */
              if(!isdigit(mobile_no[i])) {
                     return 0;
              }
       }
       return 1;
}

int get_booked_ticket_count(char* train_no, char P_class) {
       FILE*  fp = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");
       if(fp == NULL) {
              return 0;
       }

       Passenger psg;
       int count;
       while(fread(&psg, sizeof(Passenger), 1, fp)) {
              if(strcmp(train_no, psg.train_no) == 0 && psg.P_class == P_class) {
                     ++count;
              }
       }
       fclose(fp);
       return count;
}

int last_ticket_no() {
       FILE* fp = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");
       if(fp == NULL) {
              return 0;
       }
       Passenger psg;
       fseek(fp, -1 * sizeof(Passenger), SEEK_END);
       fread(&psg, sizeof(Passenger), 1, fp);
       fclose(fp);
       return psg.ticket_no;
}

void clear_char(int x, int y, int number) {
       gotoxy(x, y);
       for(int i = 0; i <= number; i++) {
              printf(" ");
       }
       gotoxy(x, y);
       return;
}

void animation() {
       int i = 1;
       gotoxy(45,16);
       int counter = 0;
       textcolor(LIGHTCYAN);
       printf("Railway Reservation System");
       while(counter <= 26) {
              switch(i) {
                     case 1 : {
                            textcolor(YELLOW);
                           break;
                     }
                     case 2 : {
                            textcolor(LIGHTGREEN);
                            break;
                     }
                     case 3 : {
                            textcolor(LIGHTCYAN);
                            break;
                     }
                     case 4 : {
                            textcolor(CYAN);
                            break;
                     }
                     case 5 : {
                            textcolor(LIGHTBLUE);
                            break;
                     }
                     case 6 : {
                            textcolor(BLUE);
                            break;
                     }
                     case 7 : {
                            textcolor(LIGHTMAGENTA);
                            break;
                     }
                     case 8 : {
                            textcolor(MAGENTA);
                            break;
                     }
                     case 9 : {
                            textcolor(LIGHTRED);
                            break;
                     }
                     case 10 : {
                            textcolor(RED);
                            break;
                     }
                     case 11 : {
                            textcolor(WHITE);
                            break;
                     }
                     case 12 : {
                            textcolor(LIGHTGRAY);
                            break;
                     }
                     case 13 : {
                            textcolor(YELLOW);
                            i = 1;
                            break;
                     }
              }
              Sleep(300);
              gotoxy(50, 15);
              //settextstyle(3, 0, 5);
              printf(" INDIAN RAILWAYS ");
              i++;
              counter++;
       }
       clrscr();
}

void headline() {
       gotoxy(50, 3);
       textcolor(CYAN);
       printf("Railway Reservation System \n");
       for(int i = 0; i < 120; i++) {
              printf("-");
       }
}

void view_all_bookings() {

       FILE* fp_book;

       fp_book = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");
       if(fp_book == NULL) {
              set_message("No Bookings done yet!", 85, 28, 64);
              return ;
       }

       textcolor(LIGHTGREEN);

       Passenger psg;
       while(fread(&psg, sizeof(psg), 1, fp_book)) {

              printf("\t Name : %s\n", psg.p_name);
              printf("\t Class : %c\n", psg.P_class);
              printf("\t Ticket no. : %d\n", psg.ticket_no);
              printf("\t Train no. : %s\n", psg.train_no);
              printf("\t Name : %s\n", psg.address);
              printf("\n\n\n");
       }

       fclose(fp_book);
       getch();
       return;
}

int cancel_ticket(int ticket_no) {

       int found;

       FILE* fp_abook;
       fp_abook = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");
       if(fp_abook == NULL) {

              set_message("No Bookings yet done.", 90, 28, 64);
              return -1;
       }

       FILE* fp_temp;
       fp_temp  = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\temp.dat", "wb");

       found = 0;
       Passenger psg;
       while(fread(&psg, sizeof(psg), 1, fp_abook)) {

              if(psg.ticket_no != ticket_no) {

                     fwrite(&psg, sizeof(psg), 1, fp_temp);
              } else {

                     found = 1;
              }
       }

       char old_name[] = "d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\temp.dat";
       char new_name[] = "d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat";

       fclose(fp_abook);
       fclose(fp_temp);

       remove(new_name);
       rename(old_name, new_name);

       return found;
}

void set_message(char message[], int start, int end, int number) {

       clear_char(start , end, number);
       gotoxy(start, end);
       printf("%s", message);
       return;
}

char* accept_mob_no() {

       int valid = 1;
       char* pos;
       static char mobile_no[11];

       set_message("press 0 to cancel...", 85, 3, 32);
       textcolor(LIGHTGRAY);

       printf("\n\n\n\t Enter mobile no. : ");
       do {

       clear_char(70, 28, 64);
       clear_char(29, 6, 11);

       fflush(stdin);
       fgets(mobile_no, 12, stdin);

       pos = strchr(mobile_no, '\n');
       if(pos != NULL) {
              *pos = '\0';
       }

       if((valid = strcmp(mobile_no, "0"))== 0) {

                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);

                     printf("Reservation Canceled.\n");

                     textcolor(LIGHTGRAY);

                     return NULL;
              }
              if(!check_mob_no(mobile_no)) {

                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);

                     printf("Error! Invalid mobile no.\n");
                     valid = 0;

                     getch();

                     textcolor(LIGHTGRAY);
                     clear_char(29, 6, 20);

              }
       } while(valid == 0);

       return mobile_no;
}

int* get_ticket_no(char* mobile_no) {

       int i;
       Passenger psg;
       FILE* fp_book;

       fp_book = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");
       if(fp_book == NULL) {
              set_message("No bookings done yet!",  85, 28, 64);
              return NULL;
       }

       i = 0;
       while(fread(&psg, sizeof(psg), 1, fp_book)) {
              if(strcmp(psg.mobile_no, mobile_no) == 0) {
                     i++;
              }
       }

       if(i == 0) {
              return NULL;
       }

       rewind(fp_book);
       int* data = (int*)malloc((i + 1) * sizeof(int));

       i = 0;
       while(fread(&psg, sizeof(psg), 1, fp_book)) {
              if(strcmp(psg.mobile_no, mobile_no) == 0) {
                     *(data + i) = psg.ticket_no;
                     i++;
              }
       }

       *(data + i) = -1;
       fclose(fp_book);
       return data;
}

void view_all_tickets(char*mobile_no, int* pticket_no) {

       if(pticket_no == NULL) {
              textcolor(LIGHTRED);
              printf("\n\t Sorry! No tickets booked against the mobile no. %s.", mobile_no);

              set_message("Press any key to go back",85, 3, 32);

              return;
       }

       int i;

       textcolor(LIGHTGREEN);
       printf("\n\t Following are tickets booked for mobile no %s :",mobile_no);
       printf("\n\n\t TICKET NO\n");
       printf("\t ---------");

       for(i = 0; *(pticket_no + i) != -1; i++)
              printf("\n\t %d",*(pticket_no+i));

       textcolor(LIGHTRED);
       set_message("Press any key to go back",85, 3, 32);

       return;
       }

char* accept_train_no() {

int valid = 1;
       char* pos;
       static char train_no[10];

       set_message("press 0 to cancel...", 85, 3, 32);
       textcolor(LIGHTGRAY);

       printf("\n\n\n\t Enter train no. : ");
       do {

       clear_char(70, 28, 64);
       clear_char(28, 6, 11);

       fflush(stdin);
       fgets(train_no, 11, stdin);

       pos = strchr(train_no, '\n');
       if(pos != NULL) {
              *pos = '\0';
       }

       if((valid = strcmp(train_no, "0"))== 0) {

                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);

                     printf("Reservation Canceled.\n");

                     textcolor(LIGHTGRAY);

                     return NULL;
              }
              if(!check_train_no(train_no)) {

                     textcolor(LIGHTRED);
                     clear_char(70, 28, 64);
                     gotoxy(90, 28);

                     printf("Error! Invalid train no.\n");
                     valid = 0;

                     getch();

                     textcolor(LIGHTGRAY);
                     clear_char(29, 6, 20);

              }
       } while(valid == 0);

       return train_no;
}

void view_bookings(char* train_no) {

       int i = 0;
       Passenger psg;


       printf("\n \n");

       textcolor(LIGHTGREEN);
       printf("\t TRAIN NO\t\t CLASS\t\t NAME\t\t\t GENDER\t\t AGE\t\t MOBILE NO.\n");
       for(int i = 0; i < 120; i++) {
              printf("-");
       }
       printf("\n");

       FILE* fp = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\allbookings.dat", "rb");

       while(fread(&psg, sizeof(psg), 1, fp) == 1) {
                     if(strcmp(psg.train_no, train_no) == 0) {
                            printf("\t %s\t\t\t %c\t\t %s\t\t %c\t\t %d\t\t %s\n", psg.train_no, psg.P_class, psg.p_name, psg.gender, psg.age, psg.mobile_no);
                            i++;
                     }
       }

       if(i == 0) {
              textcolor(LIGHTRED);
              printf("\n\t Sorry! No bookings against this train no. %s.", train_no);

              set_message("Press any key to go back",85, 3, 32);

              return;
       }

       gotoxy(85, 28);
       textcolor(WHITE);
       printf("press any key to go the main screen. \n");
       getch();

       textcolor(LIGHTRED);
       set_message("Press any key to go back",85, 3, 32);
       fclose(fp);
       return;
}

int cancel_train(char* train_no) {

       int found;
       Train train;

       FILE* fp;
       fp = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\alltrains.dat", "rb");
       if(fp == NULL) {

              set_message("File not present.", 90, 28, 64);
              return -1;
       }

       FILE* fp_temp2;
       fp_temp2  = fopen("d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\temp2.dat", "wb");

       found = 0;
       while(fread(&train, sizeof(train), 1, fp)) {

              if(strcmp(train.train_no, train_no) != 0) {

                     fwrite(&train, sizeof(train), 1, fp_temp2);
              } else {

                     found = 1;
              }
       }

       char old_name[] = "d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\temp2.dat";
       char new_name[] = "d:\\CodeBlocks WorkSpcae\\Railway_Reservation_System\\alltrains.dat";

       fclose(fp);
       fclose(fp_temp2);

       remove(new_name);
       rename(old_name, new_name);

       return found;

}
