/*
Author	    : Myungjun Kim
Contents    : Implementation of the seating plan for the Bombardier CRJ-200 aircraft.
Instructions:
	The CRJ-200 has 50 seats and every row, except for the last one, has 4 seats. The last row consists of only 2 seats.
	Every seat is either vacant or reserved.
Requirements:
	Information to be printed to the console:
		Each seat should show its row number, position A to D within the row, and reservation status (vacant or reserved).
		Overall number of vacant seats and number of reserved seats.
		Skip row number 13 (i. e., row 12 is succeeded by row 14).
	Making reservations						:
		Initially all seats are vacant.
		Users are repeatedly prompted to reserve a seat. If vacant, its status is changed to reserved and the console output is updated.
		Users are allowed to use capital or small letters when reserving a seat (e. g., "7A" or "7a").
	Exiting the program						:
		Write the console output to a text file (e. g., flightPlan.txt) before exiting the program.
			Implement a function that writes the seat plan either to the console or to a text file.
			Use fprintf() and pass stdout (to write to the console) or the file pointer as argument.
 */

#define _CRT_SECURE_NO_DEPRECATE	// To use scanf() without warnings
#define size 50						// The number of seats in the CRJ-200 aircraft

#include <stdio.h>
#include <stdlib.h>

// Structure
typedef struct {
	int rowNumber; // Row number
	char position; // Position A to D in a row
	char status;	   // Reservation status
} seatInfo;

// Function prototypes
void reserveSeat(seatInfo *seats);
void printSeatPlan(seatInfo *seats);
void clearBuffer(void);

int main(void)
{
	seatInfo *seats;
	
	if((seats = (seatInfo*)malloc(sizeof(seatInfo) * size)) == NULL)
		exit(EXIT_FAILURE);

	for (int row = 0; row < size / 4 + 1; row++)		 // row		 == 0 ~ 12
		for (int position = 0; position < 4; position++) // position == 0 ~ 3
			if(4 * row + position < 50) // Because the last row has only two seats 
				*(seats + (4 * row) + position) = (seatInfo) { (row == 12) ? 14 : row + 1, 'A' + position, '*' };

	//printSeatPlan(seats);
	reserveSeat(seats);

	free(seats);
	getchar();
	return 0;
}

void reserveSeat(seatInfo *seats)
{
	int rowReserve = 0;
	char positionReserve = ' ';
	int scanReturn = 0;
	int bufferValue;
	
	printSeatPlan(seats); // Initially print seating plan for user to see.
	printf("\n");
	
	while(1)
	{
		printf("Reserve seat(s) (q to quit):");
		scanReturn = scanf("%d%c", &rowReserve, &positionReserve);
		if (positionReserve >= 'a' && positionReserve <= 'z') // If the user entered a lowercase letter, change to capital letter
			positionReserve -= 32;

		if (scanReturn != 2) // If the row number and position letter are not properly scanned
		{
			bufferValue = getchar();
			if (bufferValue == 'q' || bufferValue == 'Q') // User desires to exit the program
			{
				printf("Thank you for utilizing our services. Auf Wiedersehen!");
				break;
			}
			printf("Please enter a valid seat number.\n");
		}
		else if (!((rowReserve > 0 && rowReserve <= 12) || rowReserve == 14) || !(positionReserve >= 'A' && positionReserve <= 'D') || (rowReserve == 14 && !(positionReserve >= 'A' && positionReserve <= 'B')))
			printf("Please enter a valid seat number.\n");
		else if (rowReserve == 14 && (seats[(rowReserve - 2) * 4 + (positionReserve - 'A')].status == '*'))
		{
			seats[(rowReserve - 2) * 4 + (positionReserve - 'A')].status = ' ';
			printSeatPlan(seats);
		}
		else if (seats[(rowReserve - 1) * 4 + (positionReserve - 'A')].status == '*')
		{
			seats[(rowReserve - 1) * 4 + (positionReserve - 'A')].status = ' ';
			printSeatPlan(seats);
		}
		else
			printf("Unfortunately, this seat is already reserved, please choose another seat.\n");

		clearBuffer();
	}
}

void printSeatPlan(seatInfo *seats)
{
	int counter = 0;
	FILE *file = fopen("flightPlan.txt", "w");

	system("cls");

	if (file != NULL)
	{
		fprintf(stdout, " Seating plan Bombardier CRJ-200\n    /                   \\   \n   /                     \\  \n  +                       + \n");
		fprintf(file, " Seating plan Bombardier CRJ-200\n    /                   \\   \n   /                     \\  \n  +                       + \n");
		for (int row = 0; row < size / 4 + 1; row++)
		{
			fprintf(stdout, "  | ");
			fprintf(file, "  | ");
	
			for (int position = 0; position < 4; position++)
			{
				if (4 * row + position < 50)
				{
					fprintf(stdout, "%3d%c%c", seats[(4 * row) + position].rowNumber, seats[(4 * row) + position].position, seats[(4 * row) + position].status);
					fprintf(file, "%3d%c%c", seats[(4 * row) + position].rowNumber, seats[(4 * row) + position].position, seats[(4 * row) + position].status);
					if ((seats[(4 * row) + position].status == ' '))
						counter++;
				}
				else
				{
					fprintf(stdout, "          ");
					fprintf(file, "          ");
					break;
				}
			}

			fprintf(stdout, "  | \n");
			fprintf(file, "  | \n");
		}
		fprintf(stdout, "  | %2d reserved, %2d vacant*  \n", counter, size - counter);
		fprintf(file, "  | %2d reserved, %2d vacant*  \n", counter, size - counter);
	}

	fclose(file);
}

void clearBuffer(void)
{
	while (getchar() != '\n')
		continue;
}