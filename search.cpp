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

// Declare function
void searchbyCustName();
void searchbyContactNo();

int main(){
    char search_choice; // Declare search_choice
    // Prompt and get the search_choice
    cout << "1. Search by Customer Name (Enquiry Module)\n";
    cout << "2. Search by Contact Number (Enquiry Module)\n";
    cout << "Enter your choice: ";

    cin >> search_choice;
    if (search_choice == '1') // if search_choice equal to 1
    {
        searchbyCustName(); // call searchbyCustName function
    }else if (search_choice == '2') // if search_choice equal to 2
    {
        searchbyContactNo(); // call searchbyContactNo function
    }
}

void searchbyCustName(){
    Reservation searchbyName ; // Declare Reservation searchbyName
    ifstream fbin("reservation.dat",ios::binary | ios::in); // Declare fbin file stream variable and write the content of file
    if(!fbin){ // if file cannot open
        cout << "Error in opening file"; // Display error message
    }
    else{
        // Declare findname,SBN_status
        // Declare and Initialize srhName = 0
        int srhName = 0 ;
        char findname[21];
        string SBN_status;
        // Prompt and get findname
        cout << "Enter Name to search: ";
        cin >> findname;
        while(fbin.read((char *)&searchbyName, sizeof(searchbyName))){ // Read the file
            if(strcmp(searchbyName.custName, findname) == 0){ // if customer name in the file is equal to findname
                cout << "\n\nHello " << searchbyName.custName << endl; // Display heading message
                cout << "Here are your details: \n";
                cout << "--------------------------------------------------\n";
                cout << "Reservation Code\t: " << searchbyName.reservCode << endl; // Display reservation code in the file
                cout << "Contact Number\t\t: " << searchbyName.contactNo << endl; // Display contact number in the file
                cout << "Event Description\t: " << searchbyName.eventDescription << endl; // Display event description in the file
                if (searchbyName.reservStatus == 'R') // if status in the file euqal to R
                {
                    SBN_status = "Reserved"; // set SBN_status = "Reserved"
                }else if (searchbyName.reservStatus == 'C') // if status in the file euqal to C 
                {
                    SBN_status = "Confirmed"; // set SBN_status = "Confirmed"
                }else if (searchbyName.reservStatus == 'X')  // if status in the file euqal to X
                {
                    SBN_status = "Cancelled"; // set SBN_status = "Cancelled"
                }
                cout << "Booking Status\t\t: " << SBN_status; // Display SBN_status

                srhName = 1; // set srhName = 1
            }
        }
        fbin.close(); // Close the file
        if(srhName == 0) // if srhName equal to 0
            cout << "Customer Name not found in data."; // Display the name is not exist
    }
}

void searchbyContactNo(){
    Reservation searchbyContact ; // Declare Reservation searchbyContact
    ifstream fbin("reservation.dat",ios::binary | ios::in); // Declare fbin file stream variable and write the content of file
    if(!fbin){ // if file cannot open
        cout << "Error in opening file"; // Display error message
    }
    else{
        // Declare findcontact,SBC_status
        // Declare and Initialize srhContact = 0
        int srhContact = 0 ;
        long long findcontact;
        string SBC_status;
        // Prompt and get findcontact
        cout << "Enter Contact Number to search: ";
        cin >> findcontact;
        while(fbin.read((char *)&searchbyContact, sizeof(searchbyContact))){ // Read the file
            if(searchbyContact.contactNo == findcontact){ // if contact number in the file is equal to findcontact
                cout << "\n\nHello " << searchbyContact.custName << endl; // Display heading message
                cout << "Here are your details: \n";
                cout << "--------------------------------------------------\n";
                cout << "Reservation Code\t: " << searchbyContact.reservCode << endl; // Display reservation code in the file
                cout << "Reservation Name\t: " << searchbyContact.custName << endl; // Display customer name in the file
                cout << "Contact Number\t\t: " << searchbyContact.contactNo << endl; // Display contact number in the file
                cout << "Event Description\t: " << searchbyContact.eventDescription << endl; // Display event description in the file

                if (searchbyContact.reservStatus == 'R') // if status in the file euqal to R
                {
                    SBC_status = "Reserved"; // set SBC_status = "Reserved"
                }else if (searchbyContact.reservStatus == 'C') // if status in the file euqal to C
                {
                    SBC_status = "Confirmed"; // set SBC_status = "Confirmed"
                }else if (searchbyContact.reservStatus == 'X') // if status in the file euqal to X
                {
                    SBC_status = "Cancelled"; // set SBC_status = "Cancelled"
                }
                cout << "Booking Status\t\t: " << SBC_status; // Display SBC_status

                srhContact = 1; // set srhContact = 1
            }
        }
        fbin.close(); // Close the file
        if(srhContact == 0) // if srhContact equal to 0
            cout << "Customer Name not found in data."; // Display the name is not exist
    }
}