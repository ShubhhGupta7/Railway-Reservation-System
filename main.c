#include <stdio.h>
#include <stdlib.h>
#include "rlyres.h"
#include "conio2.h"

int main()
{
       int choice;
       int ticket_no;
       Passenger* p;
       char* mobile_no;
       int* p_ticket_no;
       char* train_no;

       animation();
       add_trains();

       while(1) {

              clrscr();
              headline();
              choice = enterchoice();

              switch(choice) {

                     case 9 : {
                            exit(0);
                            break;
                     }

                     case 1 : {
                            view_trains();
                            break;
                     }

                     case 2 : {

                            clrscr();

                            p = get_passenger_details();
                            if(p != NULL) {

                                   ticket_no = book_ticket(*p);
                                   if(ticket_no == -1) {

                                          textcolor(LIGHTGRAY);
                                          clear_char(70, 28, 64);
                                          gotoxy(90, 28);
                                          printf("Booking Failed!");

                                          getch();
                                   } else {

                                          textcolor(LIGHTGREEN);
                                          printf("\n\t Ticket Successfully Booked \n\t Your ticket no is %d", ticket_no);
                                   }

                                   textcolor(LIGHTRED);
                                   gotoxy(80, 3);
                                   printf("Press any key to go back");

                                   getch();
                                   clrscr();
                            }
                            break;
                     }

                     case 3 : {

                            clrscr();
                            headline();

                            int ticket_no = accept_ticket_no();
                            if(ticket_no != 0) {

                                   view_ticket(ticket_no);
                            }

                            textcolor(LIGHTRED);
                            gotoxy(80, 3);
                            printf("Press any key to go back");

                            getch();
                            clrscr();
                            break;
                     }

                     case 4 : {

                            clrscr();
                            headline();
                            printf("\n\n\n\n");

                            textcolor(LIGHTGRAY);

                            mobile_no = accept_mob_no();
                            if(mobile_no != NULL) {

                                   p_ticket_no = get_ticket_no(mobile_no);
                                   view_all_tickets(mobile_no, p_ticket_no);
                            }

                            getch();
                            break;
                     }

                     case 5 : {

                            clrscr();

                            textcolor(LIGHTRED);
                            set_message("Press 0 to go back", 85, 3, 32);
                            headline();
                            printf("\n\n\n");

                            view_all_bookings();

                            getch();
                            break;
                     }

                     case 6 : {

                            clrscr();
                            headline();
                            printf("\n\n");

                            textcolor(LIGHTGRAY);

                            train_no = accept_train_no();
                            if(train_no != NULL) {

                                   view_bookings(train_no);
                            }

                            getch();
                            break;
                     }

                     case 7 : {

                            clrscr();
                            textcolor(LIGHTRED);
                            set_message("Press 0 to go back", 85, 3, 32);
                            headline();
                            printf("\n\n\n");

                            ticket_no = accept_ticket_no();
                            textcolor(LIGHTRED);

                            if(!cancel_ticket(ticket_no)) {

                                   set_message("No such booking is done yet!", 80, 28, 64);
                            } else {

                                   textcolor(LIGHTGREEN);
                                   set_message("Successfully canceled your booking.", 80, 28, 64);
                            }

                            getch();
                            break;
                     }

                     case 8 : {

                            clrscr();
                            headline();
                            printf("\n\n");

                            textcolor(LIGHTGRAY);

                            train_no = accept_train_no();
                            if(train_no != NULL) {

                                   cancel_train(train_no);
                                   textcolor(LIGHTGREEN);
                                   set_message("Successfully canceled the Train.", 80, 28, 64);

                            }

                            getch();
                            break;
                     }

                     default : {

                            textcolor(LIGHTRED);
                            printf("\t Wrong Choice! Try Again");

                            getch();
                            clrscr();
                     }
              }
       }
}
