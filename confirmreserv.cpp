#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <ctime>
#include <filesystem>
#include <array>
using namespace std;

struct Reservation {
    char reservCode[9];
    int reservDate;
    char durationType;
    char roomCode;
    int noOfAttendees;
    int actualPrice;
    char custName[21];
    long long contactNo;
    char eventDescription[41];
    char reservStatus;
    int dataEntryDate;    
};

struct Room
{
    char roomCode;
    char roomName[11];
    int capacity;
    int price;    
};

void confirmReservation(); // Declare function
void confirmReservation(){
    Reservation reservConfirm; // // Declare Reservation reservConfirm
    fstream fbin("reservation.dat",ios::binary | ios::in | ios::out);  // Declare file stream variable and read the file
    fbin.seekg(0); // Allow to find the position in the file
    
    if(!fbin){ // if file cannot be opened
        cout << "   Error in opening Reservation file"; // Display error message
        exit(EXIT_FAILURE); // Exit the program
    }

    

    else{
        // Declare confirmCode[9], option, moreoption, confirmStatus
        // Declare and Initialize existcode = true, validateoption = true
        bool existcode = true;
        char confirmCode[9], option, moreoption, payment_option;
        bool validateoption = true;
        string confirmStatus;

        // Display Heading message
        system("CLS");
        cout << "             o===========================================================================================o\n";
        cout << "             |                                    Confirm Reservation                                     |\n";
        cout << "             =============================================================================================\n";
        cout << "             |              This module searches for reservation by entering Reservation Code.           |\n";
        cout << "             |              [To Exit, Please Enter 0]                                                    |\n";
        cout << "             o-------------------------------------------------------------------------------------------o\n";
        // Prompt and get the confirmCode
        cout << "                                Enter Reservation Code: ";
        cin >> confirmCode;
        if (confirmCode[0] == '0') // If user enter '0' as first character
        {
            cout << "                                Returning back to Enquiries...\n"; // Display message return back to process menu
            cout << "                      ";
            system("pause");
            reserveProcessMenu();
        }
        else
        {
            while (fbin.read((char *)&reservConfirm, sizeof(reservConfirm))) // Read the file
            {
                if (strcmp(reservConfirm.reservCode, confirmCode) == 0) // Compare input reservation code with reservation code in File
                {

                    switch (reservConfirm.reservStatus) // If reservation code is found
                    {
                    case 'R':
                        confirmStatus = "Reserved"; // change confirmStatus = "Reserved"
                        break;
                    case 'C':
                        confirmStatus = "Confirmed"; // change confirmStatus = "Confirmed"
                        break;
                    case 'X':
                        confirmStatus = "Cancelled"; // change confirmStatus = "Cancelled"
                        break;
                    }
                    // Display the output header
                    cout << "                                Reservation Code   " << left << setw(22) << "Name" << setw(7) << "Status\n";
                    cout << "                                ------------------------------------------------------\n";
                    cout << "                                " << reservConfirm.reservCode << "\t   " << left << setw(22) << reservConfirm.custName << setw(7) << confirmStatus << "\n\n";
                    cout << "\n                                Please ensure that the customer has paid RM" << reservConfirm.actualPrice << " to the cashier before confirming this reservation." << endl; // Display payment message
                    // Prompt and get the payment_option from the user
                        cout << "\n   Enter Y or N: ";
                        cin >> payment_option;
                        payment_option = toupper(payment_option); // Change the payment_option to uppercase
                    if (reservConfirm.reservStatus == 'C') // if reservConfirm.reservStatus equal to 'C'
                    {
                        cout << "                                This reservation has been confirmed.\n"; // Display the message of already confirmed
                        cout << "                      ";
                        system("pause");
                        confirmReservation();
                    }
                    else if (reservConfirm.reservStatus == 'X') // if reservConfirm.reservStatus equal to 'X'
                    {
                        cout << "                                This reservation has been cancelled. You are unable to confirm it.\n"; // Display the message of already canceled
                        cout << "                      ";
                        system("pause");
                        confirmReservation();
                    }
                    else{
                        while (validateoption == true) // while validateoption equal to true

                        {
                            if(payment_option == 'Y'){
                                // Prompt and get option
                                cout << endl
                                    << "                                Do you want to confirm your reservation? (Y/N):";
                                cin >> option;
                                option = toupper(option); // change option to uppercase
                            }

                            if(payment_option == 'N'){
                                cout << "                                Please complete your payment before your actual date.\n\n";
                                cout << "\n                                Returning back to Enquiries Menu..." << endl;
                                cout << "                      ";
                                system("pause");
                                reserveProcessMenu();
                                validateoption = false;
                            }
                            if (option == 'N')               // if option equal to 'N'
                            {
                                // Display message ask for confirm as fast as possible
                                cout << "                                Please confirm your reservation before your actual date.\n\n";
                                cout << "\n                                Returning back to Enquiries Menu..." << endl;
                                cout << "                      ";
                                system("pause");
                                reserveProcessMenu();
                                validateoption = true;
                            }
                            else if (option == 'Y') // else if option equal to 'Y'
                            {
                                reservConfirm.reservStatus = 'C'; // set reservConfirm.reservStatus = 'C'
                                cout << "\n                                Your reservation is confirmed. Enjoy your holiday." << endl; // Display successful confirmed message
                                cout << "\n                                Returning back to Enquiries Menu..." << endl;
                                validateoption = false;
                            }
                            else
                            {
                                cout << "                                Invalid Input. Please enter Y or N only!" << endl; // Display error message

                                validateoption = true;
                            }
                            
                        }
                        fbin.seekp(-sizeof(reservConfirm), ios::cur);
                        fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                    }
                    existcode = false; // set existcode = false
                }
            }
            if (existcode == true) // if existcode equal to true
            {
                // Display No Data Found Message
                cout << "                                Your reservation code is not exist!!!" << endl;

                do
                {
                    // Display message asking user for more action
                    cout << endl
                         << "                                Do you want to confirm more reservation? (Y/N):";
                    cin >> moreoption;                 // Prompt and get moreoption
                    moreoption = toupper(moreoption); // Change moreoption to uppercase
                    if (moreoption == 'Y')             // If moreoption euqal to 'Y'
                    {
                        confirmReservation(); // Call confirmReservation function
                    }
                    else if (moreoption == 'N') // Else if moreoption euqal to 'N'
                    {
                        cout << endl
                             << "                                Returning back to Enquiries Menu..." << endl;
                        cout << "                      ";
                        system("pause");
                        reserveProcessMenu(); // Call reserveProcessMenu function
                    }
                    else // Else moreoption not equal to Y or N
                    {
                        // Display erro message
                        cout << "                                Invalid Input. Please enter Y or N only!" << endl;
                    }
                } while (moreoption != 'Y' || moreoption != 'N');
            }
            fbin.close(); // Close File
            cout << "                      ";
            system("pause");
            reserveProcessMenu();
        }
    }
}