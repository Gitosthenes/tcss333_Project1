#include <stdio.h>
#include <stdbool.h>

bool isInRange (int, bool);
int decToBin (int);

int main (void) {

    START:
    printf("\nWhat type of conversion would you like to do? [1: IP address & Subnet, 2: Network prefix & Host ID]: ");

    int choice;
    LOOP1:
    scanf("%d", &choice);
    while (choice != 1 && choice != 2) {
        printf("Not a valid option, please re-enter... ");
        goto LOOP1;
    }

    if (choice == 1) {
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
    } else {
        printf("2 pressed.\n");
    }

    char selection;

    END:
    printf("Please make a selection [r: Repeat program, q: Quit program]: ");
    scanf(" %c", &selection);

    if (selection == 'r') {
        goto START;
    } else if (selection == 'q') {

    } else {
        printf("Invalid selection...\n ");
        goto END;
    }

    return 0;
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
