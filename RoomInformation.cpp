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

void DisplayRoomInformation(); // Declare function

int main(){
    DisplayRoomInformation(); // Call function
}

void DisplayRoomInformation(){
    Room roomInformation; // Declare Room roomInformation
    fstream fbin("room.dat",ios::binary | ios:: in); // Declare file stream variable and read the content of file
    if (fbin.is_open() == false)  //if there is an error in opening file
    {
        cout << "                                Error in opening Room File!\n"; //display error message
        exit(EXIT_FAILURE);                      //exit program
    }
    fbin.read((char*)&roomInformation, sizeof(Room)); // read the record from room file
    cout << "   =============================================================\n"; // Display "   =============================================================\n"
    cout << "                          Room Details\n"; // Display "                          Room Details\n"
    cout << "   =============================================================\n"; // Display "   =============================================================\n"
    cout << left << setw(15) << "   Room Code" << setw(12) << "Room Name" << setw(10) << "Capacity" << setw(10) << "Price" << endl; // Display "Room Code",space,"Room Name",space,"Capacity",space,"Price"
    while(!fbin.eof()){ //while havent reached end of file
        //Display details for each room
	    cout << left << setw(3) << " " << setw(12) << roomInformation.roomCode << setw(12) << roomInformation.roomName << setw(10) << roomInformation.capacity << setw(10) << roomInformation.price << endl;
	    fbin.read((char *)&roomInformation, sizeof(Room)); //read another record from room file
    }
    fbin.close();

    cout << "\nReturning back to Enquiries...\n"; // Display the returning message
    system("pause");
}

