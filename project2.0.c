 #include<stdio.h>
 #include <windows.h>
 #include <stdlib.h>
 #include <string.h>
 void show_current_movies(void);
 void reserve(void);
 //
#include <stdbool.h>

// Constants for seats
#define ROWS_VIP 2         // Number of rows for VIP seats
#define ROWS_NORMAL 5      // Number of rows for Normal seats
#define SEATS_PER_ROW 10   // Number of seats per row

// Structure for reservations
typedef struct Reservation {
    char name[50];            // User's name
    char fname[50];           // User's first name
    int movie_id;             // Movie ID (1, 2, or 3)
    char seat_type[10];       // Seat type (VIP or Normal)
    int row;                  // Row number
    int seat;                 // Seat number
    struct Reservation* next; // Pointer to the next reservation
} Reservation;

Reservation* head = NULL; // Linked list of reservations

// Arrays for seat availability (0 = free, 1 = reserved)
int vip_seats[ROWS_VIP][SEATS_PER_ROW] = {0};
int normal_seats[ROWS_NORMAL][SEATS_PER_ROW] = {0};

// Display seat availability
void display_seats(int movie_id) {
    printf("\n\n*************** Seat Plan (Movie %d) ***************\n", movie_id);

    // Display VIP seats
    printf("\nVIP Seats:\n");
    for (int i = 0; i < ROWS_VIP; i++) {
        printf("VIP Row %d: ", i + 1);
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            if (vip_seats[i][j] == 0)
                printf("* "); // Free
            else
                printf("# "); // Reserved
        }
        printf("\n");
    }

    // Display Normal seats
    printf("\nNormal Seats:\n");
    for (int i = 0; i < ROWS_NORMAL; i++) {
        printf("Normal Row %d: ", i + 1);
        for (int j = 0; j < SEATS_PER_ROW; j++) {
            if (normal_seats[i][j] == 0)
                printf("* "); // Free
            else
                printf("# "); // Reserved
        }
        printf("\n");
    }
    printf("\n*: Free, #: Reserved\n");
}
void reserve_seat(int movie_id) {
    int choice, row, seat;
    char seat_type[10];
    char name[50], fname[50];

    // Show available seats
    display_seats(movie_id);

    // Choose seat type (VIP or Normal)
    do {
        printf("Choose seat type:\n1. VIP\n2. Normal\nYour choice: ");
        scanf("%d", &choice);
    } while (choice < 1 || choice > 2);

    if (choice == 1) {
        strcpy(seat_type, "VIP");
    } else {
        strcpy(seat_type, "Normal");
    }

    // Input row and seat number
    do {
        printf("Enter the row number: ");
        scanf("%d", &row);
        printf("Enter the seat number: ");
        scanf("%d", &seat);

        if (choice == 1) { // Check VIP seats
            if (row < 1 || row > ROWS_VIP || seat < 1 || seat > SEATS_PER_ROW || vip_seats[row - 1][seat - 1] == 1) {
                printf("This seat is already reserved or invalid. Please try again.\n");
            } else {
                break; // Valid seat
            }
        } else { // Check Normal seats
            if (row < 1 || row > ROWS_NORMAL || seat < 1 || seat > SEATS_PER_ROW || normal_seats[row - 1][seat - 1] == 1) {
                printf("This seat is already reserved or invalid. Please try again.\n");
            } else {
                break; // Valid seat
            }
        }
    } while (1);

    // Mark the seat as reserved
    if (choice == 1) {
        vip_seats[row - 1][seat - 1] = 1;
    } else {
        normal_seats[row - 1][seat - 1] = 1;
    }

    // Get user information
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your first name: ");
    scanf("%s", fname);

    // Add reservation to the linked list
    Reservation* newReservation = (Reservation*)malloc(sizeof(Reservation));
    strcpy(newReservation->name, name);
    strcpy(newReservation->fname, fname);
    newReservation->movie_id = movie_id;
    strcpy(newReservation->seat_type, seat_type);
    newReservation->row = row;
    newReservation->seat = seat;
    newReservation->next = head;
    head = newReservation;

    // Confirmation
    printf("Your reservation is confirmed: %s %s, Movie %d, Seat %s, Row %d, Seat %d.\n",
           name, fname, movie_id, seat_type, row, seat);
}

//
 void gotoxy(int x, int y)
 {
	COORD c;
	c.X = x;
	c.Y = y;

	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
 void main()
 {
    int choice;
	gotoxy(25, 3);
    printf("************WELCOME it's movie time !************\n");
	gotoxy(33, 5);
    printf("**********************************");
    gotoxy(36, 8);
    printf("   1....check our latest films\n");
	gotoxy(36, 10);
	printf("   2....save a place");
	gotoxy(36, 12);
	printf("   3....cancel a reservation");
	printf("\n\nENTER YOUR CHOICE..");
	scanf("%d", &choice);
	switch (choice) {
	case 1:
		system("cls");
		show_current_movies();
		break;

	case 2:
		system("cls");
		reserve();
		break;

	case 3:
		system("cls");
		cancel();
		break;
	}
    getchar();

 }
//
//creation_of_show_current_movies
 void show_current_movies(){
	int r;
	FILE *fichier = fopen("movies.txt", "r"); 
    if (fichier == NULL) {
        printf("Erreur  .\n");
        return;
    }

    char line[200];
    char movies[3][50]; 
    char begin[3][6];  
    char end[3][6];  
    int i;

    // read-file
    while (fgets(line, sizeof(line), fichier)) {
        if (strstr(line, "movies")) {
            sscanf(line, "movies	%s	%s	%s", movies[0], movies[1], movies[2]);
        } else if (strstr(line, "beginning")) {
            sscanf(line, "beginning	%s	%s	%s", begin[0], begin[1], begin[2]);
        } else if (strstr(line, "ending")) {
            sscanf(line, "ending	%s	%s	%s", end[0], end[1], end[2]);
        }
    }

    fclose(fichier);
	gotoxy(25, 3);
    printf("****Movies available with their start, end and duration time :****\n\n");

    for (i = 0; i < 3; i++) {
        
        int begin_h, begin_m, end_h, end_m, duration_h, duration_m;
        sscanf(begin[i], "%d:%d", &begin_h, &begin_m);
        sscanf(end[i], "%d:%d", &end_h, &end_m);

        int begin_min = begin_h * 60 + begin_m; 
        int end_min = end_h * 60 + end_m;       
		// calculate-time-in-minutes
        int duration_min = end_min - begin_min; 
        duration_h = duration_min / 60;               
        duration_m = duration_min % 60;               
		printf("****It's movie number**** : %d\n",i+1);
        printf("Movie : %s\n", movies[i]);
        printf("   Beginning : %s\n", begin[i]);
        printf("   Ending   : %s\n", end[i]);
        printf("   Duration : %d hour(s) et %d minute(s)\n\n", duration_h, duration_m);
    }
	do{
		printf("press '1' to go back to menue ");
		scanf("%d", &r);
	}while(r!=1);
	system("cls");
	main();
	getchar();
	
 }

void reserve() {
    int movie_id;

    // Choose the movie
    do {
        printf("Please enter the number (1~3) of the movie you want to reserve a seat for: ");
        scanf("%d", &movie_id);
    } while (movie_id < 1 || movie_id > 3);

    // Reserve a seat
    reserve_seat(movie_id);

    // Display all current reservations (optional)
    Reservation* temp = head;
    printf("\n=== Current Reservations ===\n");
    while (temp != NULL) {
        printf("Name: %s, First Name: %s, Movie: %d, Seat Type: %s, Row: %d, Seat: %d\n",
               temp->name, temp->fname, temp->movie_id, temp->seat_type, temp->row, temp->seat);
        temp = temp->next;
    }

    printf("\nPress any key to return to the main menu...\n");
    getchar();
    getchar();
    system("cls");
    main();
}
void cancel() {
    char name[50], fname[50];
    int movie_id, row, seat;
    char seat_type[10];
    bool found = false;

    // Get user details
    printf("Enter your name: ");
    scanf("%s", name);
    printf("Enter your first name: ");
    scanf("%s", fname);
    printf("Enter the movie number (1~3): ");
    scanf("%d", &movie_id);

    // Choose seat type (VIP or Normal)
    do {
        printf("Enter the seat type (VIP/Normal): ");
        scanf("%s", seat_type);
        if (strcmp(seat_type, "VIP") != 0 && strcmp(seat_type, "Normal") != 0) {
            printf("Invalid seat type. Please enter 'VIP' or 'Normal'.\n");
        }
    } while (strcmp(seat_type, "VIP") != 0 && strcmp(seat_type, "Normal") != 0);

    // Get seat details
    printf("Enter the row number: ");
    scanf("%d", &row);
    printf("Enter the seat number: ");
    scanf("%d", &seat);

    // Validate seat type and mark it as free
    if (strcmp(seat_type, "VIP") == 0) {
        if (row < 1 || row > ROWS_VIP || seat < 1 || seat > SEATS_PER_ROW || vip_seats[row - 1][seat - 1] == 0) {
            printf("Invalid or unreserved seat. Cannot cancel.\n");
            return;
        }
        vip_seats[row - 1][seat - 1] = 0; // Free the seat
    } else {
        if (row < 1 || row > ROWS_NORMAL || seat < 1 || seat > SEATS_PER_ROW || normal_seats[row - 1][seat - 1] == 0) {
            printf("Invalid or unreserved seat. Cannot cancel.\n");
            return;
        }
        normal_seats[row - 1][seat - 1] = 0; // Free the seat
    }

    // Search for the reservation in the linked list
    Reservation *current = head, *previous = NULL;

    while (current != NULL) {
        if (strcmp(current->name, name) == 0 && strcmp(current->fname, fname) == 0 &&
            current->movie_id == movie_id && strcmp(current->seat_type, seat_type) == 0 &&
            current->row == row && current->seat == seat) {
            
            found = true;

            // Remove from the linked list
            if (previous == NULL) {
                head = current->next; // Removing the first node
            } else {
                previous->next = current->next; // Removing a middle or last node
            }

            free(current); // Free the memory of the removed node
            printf("Reservation successfully canceled.\n");
            break;
        }
        previous = current;
        current = current->next;
    }

    if (!found) {
        printf("No reservation found matching the provided details.\n");
    }

    // Return to main menu
    printf("\nPress any key to return to the main menu...\n");
    getchar();
    getchar();
    system("cls");
    main();
}

