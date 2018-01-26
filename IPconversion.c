#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

void option1 ();
void option2 ();
bool isInRange (int, bool);
int decToBin (int);

int main (void) {

    bool running = true;

    do {
        printf("\nWhat type of conversion would you like to do? [1: IP address & Subnet, 2: Network prefix & Host ID]: ");

        int choice;
        scanf("%d", &choice);
        while (choice != 1 && choice != 2) {
            printf("Not a valid option, please re-enter... ");
            scanf("%d", &choice);
        }

        if (choice == 1) {
            option1();
        } else {
            option2();
        }

        char selection;
        do {
            printf("Please make a selection [r: Repeat program, q: Quit program]: ");
            scanf(" %c", &selection);

            if (selection == 'r') {
                continue;
            } else if (selection == 'q') {
                running = false;
            } else {
                printf("Invalid selection...\n ");
            }
        } while (selection != 'r' && selection != 'q');

    } while (running);

    return 0;
}

void option1 () {

    int first, second, third, fourth, subnet;
    LOOP2:
    printf("Enter the IP address, followed by the Subnet (ex. 192.192.192.192/24): ");
    scanf ("%d.%d.%d.%d/%d", &first, &second, &third, &fourth, &subnet);
    while (!isInRange(first, false) || !isInRange(second, false) || !isInRange(third, false) || !isInRange(fourth, false) || !isInRange(subnet, true)) {
        printf("Invalid IP or Subnet. Please re-enter...\n");
        goto LOOP2;
    }

    printf("\nThe binary representation of the IP address is: ");
    printf("%08d %08d %08d %08d\n", decToBin(first), decToBin(second), decToBin(third), decToBin(fourth));

    printf("The binary representation of the Subnet mask is: ");
    printf("%08d\n\n", decToBin(subnet));
/*
        printf("TEST OUTPUT: %d %d %d %d %d\n", first, second, third, fourth, subnet);
*/

}

void option2 () {
    printf("2 pressed.\n");
}

bool isInRange (int input, bool isSubnet) {

    bool result;
    if (!isSubnet) {
        result = (input >=0 && input <= 255);
    } else {
        result = (input >= 0 && input <= 32);
    }

    return result;
}

int decToBin (int decimal) {

    int result;

    if (decimal == 0) {
        result = 0;
    } else {
        result = (decimal % 2 + 10 * decToBin(decimal / 2));
    }

    return result;
}