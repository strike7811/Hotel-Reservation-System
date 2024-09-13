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

void viewDetail(); // Declare function

int main(){
    viewDetail(); // Call function
}

void viewDetail(){
    Reservation viewReservation; // Declare Reservation viewReservation
    ifstream fbin("reservation.dat",ios::binary | ios::in);  // Declare file stream variable and read the file
    if(!fbin){ // if file cannot open
        cout << "Error in opening file"; // Display Error Message
    }

    // Declare variable
    string reserv_Number, room;
    char detailOption = 'N', Option;
    // Declare and Initialize validateOption = true, existcode = true, count = 0
    bool validateOption = true;
    bool existcode = true;
    bool validatelength = true;
    bool status = false;
    int count = 0;

    // Prompt and get reserv_Number
    cout << "   Enter the reservation code: ";
    cin >> reserv_Number;

    if (reserv_Number.length() != 8){ // if length of reservNumber not equal to 8
        validatelength = false; // set validatelength = false
    }

    while(validatelength == false){ // if validatelength equal to false
        cout << "   Error!!! You can enter 8 character only." << endl; // Display error message
        // Prompt and get reserv_Number
        cout << "   Enter the reservation code: ";
        cin >> reserv_Number;
        count++; //Increment count by 1

        if (reserv_Number.length() == 8){ // if length of reservNumber equal to 8
            validatelength = true; // set validatelength = true
        }
        if(count == 2){ // if count equal to 2
            validatelength = true; // set validatelength = true
        }
    }

    while(fbin.read((char*)&viewReservation,sizeof(viewReservation))){ // Read the file
        if(viewReservation.reservCode == reserv_Number){ // if reserv_Number equal to reservCode in the file
            cout << "   =============================================================\n"; // Display "   =============================================================\n"
            cout << "                       Reservation Details\n"; // Display "                       Reservation Details\n"
            cout << "   =============================================================\n"; // Display "   =============================================================\n"
            cout << "   Reservation Code     : " << viewReservation.reservCode << endl; // Display Reservation Code 
            cout << "   Reservation Date     : " << viewReservation.reservDate << endl; // Display Reservation Date
            cout << "   Reservation Name     : " << viewReservation.custName << endl; // Display Customer Name
            cout << "   Reservation Status   : " << viewReservation.reservStatus << endl; // Display Reservation Status
            cout << "   Contact Number       : " << viewReservation.contactNo << endl; // Display Contact Number
            cout << "   Total Payment        : " << viewReservation.actualPrice << endl; // Display Price
            cout << "   Number of Attendees  : " << viewReservation.noOfAttendees << endl; // Display Number of Attendees
            cout << "   Event Description    : " << viewReservation.eventDescription << endl; // Display Event Description
            cout << "   Duration Type(A/P/F) : " << viewReservation.durationType << endl; // Display Duration Type
            switch(viewReservation.roomCode){
                case 'A': // if roomCode equal to A
                    room = "Azure"; // set room = "Azure"
                    break;
                
                case 'B': // if roomCode equal to B
                    room = "Byzantine"; // set room = "Byzantine"
                    break;
                        
                case 'C': // if roomCode equal to C
                    room = "Crystal"; // set room = "Crystal"
                    break;
                        
                case 'D': // if roomCode equal to D
                    room = "Diamond"; // set room = "Diamond"
                    break;
                        
                case 'E': // if roomCode equal to E
                    room = "Emerald"; // set room = "Emerald"
                    break;
                        
                case 'F': // if roomCode equal to F
                    room = "Florence"; // set room = "Florence"
                    break;
                        
                case 'G': // if roomCode equal to G
                    room = "Genesis"; // set room = "Genesis"
                    break;
                        
                case 'H': // if roomCode equal to H
                    room = "Helion"; // set room = "Helion"
                    break;
            }
            cout << "   Room                 : " << room << endl; // Display room
            do{
                cout << "\n   Would you like to see other detail (Y/N)?: "; // Display message of ask user to check other detail
                cin >> detailOption; // Prompt and get detailOption from user
                detailOption = toupper(detailOption); // Change the detailOption to uppercase
                if(detailOption == 'Y'){ // if detailOption equal to N
                    validateOption = true; // set validateOption = true
                }

                if(detailOption == 'N'){ // if detailOption equal to N
                    validateOption = true; // set validateOption = true
                }

                if(detailOption != 'Y' && detailOption != 'N'){ // if detailOption not equal to Y and N
                    cout << "   Error!!!Please enter Y or N only."; // Display Error Message
                    validateOption = false; // set validateOption = false
                }
            }while(validateOption == false); // Do while loop when the validateOption equal to false
            existcode = true;  // set existcode = true
            status = true; // set status = true
            fbin.close(); // close the file
        }    
    }

    if(status == false){
        cout << "\n   Your reservation is not exist." << endl; // Display the message of the reservation code is not exist.
        do{
            cout << "   Do you want to exit (Y/N)?: "; // Display message of ask user to check other detail
            cin >> Option; // Prompt and get detailOption from user
            Option = toupper(Option); // Change the detailOption to uppercase
            if(Option == 'Y'){ // if detailOption equal to Y
                validateOption = true; // set validateOption = true
            }

            if(Option == 'N'){ // if detailOption equal to N
                validateOption = true; // set validateOption = true
                detailOption = 'Y'; // set detailOption = 'Y'
            }

            if(detailOption != 'Y' && detailOption != 'N'){ // if detailOption not equal to Y and N
                cout << "   Error!!!Please enter Y or N only."; // Display Error Message
                validateOption = false; // set validateOption = false
            }
        }while(validateOption == false); // Do while loop when the validateOption equal to false
    }
    

    if(detailOption == 'Y'){ // if detailOption equal to Y
        viewDetail(); // Call viewDetail function
    }

    else{
        cout << "\nReturning back to Enquiries...\n"; // Display the returning message
        system("pause");
    }
 
}