#ifndef RLYRES_H_INCLUDED
#define RLYRES_H_INCLUDED

struct Train {
       char train_no[10];
       char from[10];
       char to[10];
       int fac_fare;
       int sac_fare;
};

struct Passenger {
       char p_name[20];
       char gender;
       char train_no[10];
       char P_class;
       char address[80];
       int age;
       int ticket_no;
       char mobile_no[11];
};

typedef struct Train Train;
typedef struct Passenger Passenger;

// Methods of main Function.
int enterchoice();
void add_trains();
void view_trains();
int book_ticket(Passenger);
int* get_ticket_no(char*);
void view_ticket(int);
void view_all_bookings();
void view_bookings(char*);
int cancel_ticket(int);
int cancel_train(char*);
int accept_ticket_no();

// For Booking a Ticket.
Passenger* get_passenger_details();
int check_train_no(char*);
int get_booked_ticket_count(char*, char);
int last_ticket_no();
int book_ticket(Passenger);

//Get Ticket number,
int check_mob_no(char*);
char* accept_mob_no();
int* get_train_no(char*);;
void view_all_tickets();

//get train bookingss.
char* accept_train_no();

// Self Defined.
void clear_char(int, int, int);
void set_message(char[], int , int, int);
void animation();
void headline();

#endif // RLYRES_H_INCLUDED
