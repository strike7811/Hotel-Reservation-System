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

int main(){
    confirmReservation(); // Call function

    return 0;
}

void confirmReservation(){
    Reservation reservConfirm; // // Declare Reservation reservConfirm
    fstream fbin("reservation.dat",ios::binary | ios::in | ios::out);  // Declare file stream variable and read the file
    fbin.seekg(0); // Allow to find the position in the file
    long long ccount = 0;

    if(!fbin){ // if file cannot be opened
        cout << "   Error in opening Reservation file"; // Display error message
        exit(EXIT_FAILURE); // Exit the program
    }

    else{
        // Declare variable
        string reservationcode;
        bool existcode = true;
        bool validateOption = true;
        bool status = false;
        int count = 0;
        bool validatePaymentOption = true;
        char option,payment_option;
        char confirmStatus;

        fbin.read((char*)&reservConfirm,sizeof(Reservation));
        while(!fbin.eof()){
            ccount++;
            fbin.read((char*)&reservConfirm,sizeof(Reservation));
        }

        fbin.clear(); //Clear eof flag
        fbin.seekg(0L, ios::beg); //Move read file pointer to the beginning of file

        cout << "   ======================================================================\n"; // Display "   ======================================================================\n"
        cout << "                          Confirm Reservation \n"; // Display "                          Confirm Reservation \n"
        cout << "   ======================================================================\n"; // Display "   ======================================================================\n"
        do{
            // Prompt and get the reservation code
            cout << "   Enter the reservation code: ";
            cin >> reservationcode;
            while (reservationcode.length() != 8){ // while reservationcode.lenth)() not equal to 8
                cout << "   Error!!! You can enter 8 character only." << endl; // Display error message
                // Prompt and get reservation code
                cout << "   Enter the reservation code: ";
                cin >> reservationcode;
            }

            while(fbin.read((char*)&reservConfirm,sizeof(reservConfirm))) // Read the file
            {
                if(reservConfirm.reservCode == reservationcode){ // if reservCode in the file is equal to reservationcode
                    cout << "   Your reservation is found." << endl; // Display success message
                    cout << "\n   Please ensure that the customer has paid RM" << reservConfirm.actualPrice << " to the cashier before confirming this reservation." << endl; // Display payment message
                    // Check the payment status from the customer
                    cout << "   If payment has been made, enter Y to confirm reservation. Enter N if customer has not paid." << endl;
                    do{
                        // Prompt and get the payment_option from the user
                        cout << "\n   Enter Y or N: ";
                        cin >> payment_option;
                        payment_option = toupper(payment_option); // Change the payment_option to uppercase
                        if(payment_option == 'Y'){ // if payment_option equal to Y
                            do{
                                // Prompt and get the option from the user
                                cout << "\n   Do you want to confirm your reservation? (Y/N): ";
                                cin >> option;
                                option = toupper(option); // Change the option to uppercase
                                if(option == 'Y'){ // if option equal to Y
                                    if (reservConfirm.reservStatus == 'X'){ // if reservConfirm.reservStatus equal to 'X'
                                            cout << "   Sorry this Reservation has been cancelled.\n"; // Display the message of reservation has been cancelled
                                    }

                                    else if (reservConfirm.reservStatus == 'C'){ // if reservConfirm.reservStatus equal to 'C'
                                        cout << "   Error!!!This Reservation has been confirmed.\n"; // Display the error message
                                    }

                                    else {
                                        reservConfirm.reservStatus = 'C';
                                        // Move write file pointer back to the beginning of this reservConfirm's position.
                                        fbin.seekp((ccount - 1) * sizeof(reservConfirm), ios::beg);

                                        // Write the new reservStatus over the current reservConfirm.
                                        fbin.write(reinterpret_cast<char *>(&reservConfirm), sizeof(Reservation));

                                        if (!fbin){ //if there is an error in writing to file
                                            cout << "                                Error in writing to Room File!\n"; //display error message
                                        }
                                        else{ //else display success message
                                            cout << "   Your reservation is confirmed. Enjoy your holiday.\n"; // Display the success confirm message
                                        }
                                    }

                                    validateOption = true; // validateOption = true
                                }

                                if(option == 'N'){ // if option equal to N
                                    cout << "\n   Please confirm your reservation before your actual date." << endl; // Display the message of request to confirm
                                    validateOption = true; // validateOption = true
                                }

                                if(option != 'Y' && option != 'N'){ // if option not equal to 'Y' and the option not equal to N
                                    cout << "   Error!!!Please enter Y or N only." << endl; // Display error message
                                    validateOption = false; // validateOption = false
                                }

                            }while (validateOption == false); // Do while loop if the validateOption equal to false
                            validatePaymentOption = true; // validatePaymentOption = true
                        }

                        if(payment_option == 'N'){ // if payment_option equal to 'N'
                            cout << "\n   Please complete your payment before your actual date." << endl; // Display the message of request to confirm
                            validatePaymentOption = true; // validatePaymentOpyion = true
                        }

                        if(payment_option != 'Y' && payment_option != 'N'){ // if payment_option not equal to 'Y' and not equal to 'N'
                            cout << "   Error!!!Please enter Y or N only." << endl; // Display error message
                            validatePaymentOption = false; // validatePaymentOption = false
                        }
                    }while(validatePaymentOption == false);// Do while loop if the validatePaymentOption equal to false
                    existcode = true; // existcode = true
                    status = true; // status = true
                }
            }
            fbin.close(); // Close the file

            if(status == false){ // if status equal to false
                cout << "   Your reservation is not exist. Please try it again" << endl; // Display the message of code not exist
                existcode = false; // set existcode = false
                count ++; //Increment count by 1
                if(count >= 3){ // if count greater than or equal to 3
                    existcode = true; // set existcode = true
                    status = true; // status = true
                }
            }
        }while(existcode == false); // do while loop if the existcode = false
        
        cout << "\nReturning back to Enquiries...\n"; // Display the returning message
        system("pause");

    }
}