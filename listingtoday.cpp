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
void reservListing();
int systemYear,systemMonth, systemDay, formattedSystemDate;

void get_system_date()
{
    time_t ttime = time(0);
    tm *localTime = localtime(&ttime);
    systemYear = 1900 + localTime->tm_year;
    systemMonth = 1 + localTime->tm_mon;
    systemDay = localTime->tm_mday;
    cout << "Today's date: " << systemDay << "/" << systemMonth << "/" << systemYear << endl << endl;  
    formattedSystemDate = (systemYear - 2000) * 10000 + systemMonth * 100 + systemDay;   
}

int main(){
    get_system_date(); // Call function
    reservListing();
}

void reservListing(){
    Reservation reservlisting; // Declare Reservation reservlisting
    ifstream fbin("reservation.dat",ios::binary | ios::in); // Declare file stream variable and read the file
    if(!fbin){ // if file cannot open
        cout << "   Error in opening file"; // Display the error message
    }

    else{
        // Declare search_date
        // Declare and Initialize total_amount = 0
        int total_amount = 0;
        string room;

        while(fbin.read((char*)&reservlisting,sizeof(reservlisting))){ // Read the file
            if (reservlisting.dataEntryDate == formattedSystemDate){ // if Entry Date in the file equal to search_date
                cout << "   ========================================================================================\n"; // Display heading message
                cout << "                          New Reservations Entered Today listing\n";
                cout << "   ========================================================================================\n";
                cout << left << setw(21) << "   Name" << setw(18) << "Duration type" << setw(18) << "Reservation Date" << setw(12) << "Room Name" << setw(9) << "Status" << setw(8) << "Price" << endl;
                cout << "   ----------------------------------------------------------------------------------------\n";
                switch(reservlisting.roomCode){
                    case 'A': // if roomCode equal to A
                        room = "Azure"; // set room =  "Azure"
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
                cout << "   " << left << setw(18) << reservlisting.custName << setw(5) << " " << setw(13) << reservlisting.durationType << setw(5) << " " << setw(13) << reservlisting.reservDate << setw(12) << room << setw(2) << " " << setw(7) << reservlisting.reservStatus << setw(8) << reservlisting.actualPrice << endl; // Display "Customer Name in the file",space,"Duration Type in the file",space,"Reservation date in the file",space,"Room Name in the file",space,"Status Reservation in the file",space,"Price in the file\n"
                total_amount = 0;
                total_amount = total_amount + reservlisting.actualPrice; // total_amount = total_amount + reservlisting.actualPrice
            }
        }
        if(total_amount == 0){
            cout << "Today has not reservation come in." << endl; // Display the message of not reservation come in at that day.
        }
        else{
            cout << "\n\n   The total amount is RM" << total_amount << "." << endl; // Display the total amount
        }
        
    fbin.close(); // Close the file
    cout << "\n"; // Display a new line
    system("pause");
    }
    
}