/*
 * Alex Bledsoe - Assignment 1
 * tcss333 - Winter 2018
 */

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
            printf("\nPlease make a selection [r: Repeat program, q: Quit program]: ");
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

//  Get information from user.
    int first, second, third, fourth, subnet;
    printf("Enter the IP address, followed by the Subnet (ex. 192.192.192.192/24): ");
    scanf ("%d.%d.%d.%d/%d", &first, &second, &third, &fourth, &subnet);
    while (!isInRange(first, false) || !isInRange(second, false) || !isInRange(third, false) || !isInRange(fourth, false) || !isInRange(subnet, true)) {
        printf("Invalid IP or Subnet. Please re-enter...\n");
        scanf ("%d.%d.%d.%d/%d", &first, &second, &third, &fourth, &subnet);
    }

//  Print IP address information.
    printf("\nThe binary representation of the IP address is: ");
    printf("%08d %08d %08d %08d\n", decToBin(first), decToBin(second), decToBin(third), decToBin(fourth));
    printf("The hexidecimal representation of the IP address is: ");
    printf("%02X%02X%02X%02X\n", first, second, third, fourth);


//  Print subnet mask information.
    unsigned char subnetFirst = 255;
    unsigned char subnetSecond = 255;
    unsigned char subnetThird = 255;
    unsigned char subnetFourth = 255;

    if (subnet <= 8) {
        subnetFourth = 0;
        subnetThird = 0;
        subnetSecond = 0;
        subnetFirst <<= 8 - subnet;
    } else if (subnet <= 16) {
        subnetFourth = 0;
        subnetThird = 0;
        subnetSecond <<= 8 - (subnet - 8);
    } else if (subnet <= 24) {
        subnetFourth = 0;
        subnetThird <<= 8 - (subnet - 16);
    } else {
        subnetFourth <<= 8 - (subnet - 24);
    }

    printf("\nThe Subnet mask in dot-decimal is: ");
    printf("%d.%d.%d.%d\n", subnetFirst, subnetSecond, subnetThird, subnetFourth);
    printf("The hexidecimal representation of the Subnet mask is: ");
    printf("%02X%02X%02X%02X\n", subnetFirst, subnetSecond, subnetThird, subnetFourth);
    printf("The binary representation of the Subnet mask is: ");
    printf("%08d %08d %08d %08d\n",decToBin(subnetFirst), decToBin(subnetSecond), decToBin(subnetThird), decToBin(subnetFourth));

//  Print Host-ID information.
    unsigned char npFirst = (unsigned char) (first & subnetFirst);
    unsigned char npSecond = (unsigned char) (second & subnetSecond);
    unsigned char npThird = (unsigned char) third & subnetThird;
    unsigned char npFourth = (unsigned char) fourth & subnetFourth;

    printf("\nThe Host-ID in dot-decimal is: ");
    printf("%d.%d.%d.%d\n", npFirst, npSecond, npThird, npFourth);
    printf("The hexidecimal representation of the Host-ID is: ");
    printf("%02X%02X%02X%02X\n", npFirst, npSecond, npThird, npFourth);
    printf("The binary representation of the Host-ID is: ");
    printf("%08d %08d %08d %08d\n", decToBin(npFirst), decToBin(npSecond), decToBin(npThird), decToBin(npFourth));

//  Print Network prefix information.
    unsigned char flippedSubnetFirst = ~subnetFirst;
    unsigned char flippedSubnetSecond = ~subnetSecond;
    unsigned char flippedSubnetThird = ~subnetThird;
    unsigned char flippedSubnetFourth = ~subnetFourth;

    printf("\nThe Network Prefix in dot-decimal is: ");
    printf("%d.%d.%d.%d\n", flippedSubnetFirst, flippedSubnetSecond, flippedSubnetThird, flippedSubnetFourth);
    printf("The hexidecimal representation of the Network Prefix is: ");
    printf("%02X%02X%02X%02X\n", flippedSubnetFirst, flippedSubnetSecond, flippedSubnetThird, flippedSubnetFourth);
    printf("The binary representation of the Network Prefix is: ");
    printf("%08d %08d %08d %08d\n",decToBin(flippedSubnetFirst), decToBin(flippedSubnetSecond), decToBin(flippedSubnetThird), decToBin(flippedSubnetFourth));

/*
        printf("TEST OUTPUT: %d %d %d %d %d\n", first, second, third, fourth, subnet);
*/

}

void option2 () {

    //  Get information from user.
    int hostFirst, hostSecond, hostThird, hostFourth, npFirst, npSecond, npThird, npFourth;
    printf("Enter the Host-ID (ex. 0.0.0.130): ");
    scanf ("%d.%d.%d.%d", &hostFirst, &hostSecond, &hostThird, &hostFourth);
    while (!isInRange(hostFirst, false) || !isInRange(hostSecond, false) || !isInRange(hostThird, false) || !isInRange(hostFourth, false)) {
        printf("Invalid Host-ID. Please re-enter...\n");
        scanf ("%d.%d.%d.%d", &hostFirst, &hostSecond, &hostThird, &hostFourth);
    }
    printf("\nEnter the Network Prefix: ");
    scanf ("%d.%d.%d.%d", &npFirst, &npSecond, &npThird, &npFourth);
    while (!isInRange(hostFirst, false) || !isInRange(hostSecond, false) || !isInRange(hostThird, false) || !isInRange(hostFourth, false)) {
        printf("Invalid Host-ID. Please re-enter...\n");
        scanf ("%d.%d.%d.%d", &npFirst, &npSecond, &npThird, &npFourth);
    }

    hostFirst = (unsigned char) hostFirst;
    hostSecond = (unsigned char) hostSecond;
    hostThird = (unsigned char) hostThird;
    hostFourth = (unsigned char) hostFourth;
    npFirst = (unsigned char) npFirst;
    npSecond = (unsigned char) npSecond;
    npThird = (unsigned char) npThird;
    npFourth = (unsigned char) npFourth;

//  Find the IP address.
    unsigned char ipFirst, ipSecond, ipThird, ipFourth;
    ipFirst = (unsigned char) (hostFirst | npFirst);
    ipSecond = (unsigned char) (hostSecond | npSecond);
    ipThird = (unsigned char) (hostThird | npThird);
    ipFourth = (unsigned char) (hostFourth | npFourth);

//  Find the Subnet Mask.
    int subnet = 32;
    bool flag = true;
    if (decToBin(npFourth) != 0) {
        int binary = decToBin(npFourth);
        while (flag) {
            if (binary % 10 != 0) {
                flag = false;
            } else {
                binary /= 10;
                subnet--;
            }
        }
    } else if (decToBin(npThird) != 0) {
        subnet -= 8;
        int binary = decToBin(npThird);
        while (flag) {
            if (binary % 10 != 0) {
                flag = false;
            } else {
                binary /= 10;
                subnet--;
            }
        }
    } else if (decToBin(npSecond) != 0) {
        subnet -= 16;
        int binary = decToBin(npSecond);
        while (flag) {
            if (binary % 10 != 0) {
                flag = false;
            } else {
                binary /= 10;
                subnet--;
            }
        }
    } else if (decToBin(npFirst) != 0) {
        subnet -= 24;
        int binary = decToBin(npFirst);
        while (flag) {
            if (binary % 10 != 0) {
                flag = false;
            } else {
                binary /= 10;
                subnet--;
            }
        }
    } else {
        subnet = 0;
    }
    printf("%d.%d.%d.%d/%d\n", ipFirst, ipSecond, ipThird, ipFourth, subnet);
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