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

struct Reservation
{
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

struct CustomerRevenue
{
    char RevCustSort[21]; // change array size
    int CustRevAmt;
    char CustStatus;
};

struct tempCustomerRevenue
{
    char RevCustSort[21]; // change array size
    int CustRevAmt;
};
tempCustomerRevenue tempCustArray[30];
CustomerRevenue custArray[30];
CustomerRevenue sortedArray[100];

void searchbyCustName();
void searchbyContactNo();
void cancelReservation();
void tempmenuchoice();
void revenuebycustomer();
void SBC_lookupRoomcode();
void doSortCust(int *);

int main()
{
    tempmenuchoice();
    return 0;
}

/***********/
void searchbyCustName()
{
    Reservation searchbyName;
    ifstream fbin("reservation.dat", ios::binary | ios::in);
    if (!fbin)
    {
        cout << "Error in opening file";
    }
    else
    {
        int srhName = 0;
        char findname[21];
        string SBN_status, SBN_duration, SBN_RoomCode;

        cout << "Enter Name to search: ";
        cin >> findname;
        while (fbin.read((char *)&searchbyName, sizeof(searchbyName)))
        {
            if (strcmp(searchbyName.custName, findname) == 0)
            {
                // Display Header and Reservation Code of the customer
                cout << "\n\nHere are your details: \n";
                cout << "--------------------------------------------------\n";
                cout << "Customer Name\t\t: " << searchbyName.custName << endl;    // Display Name
                cout << "Reservation Code\t: " << searchbyName.reservCode << endl; // Show Reservation Code
                // Show Reservation Date (Proper Way)
                int SBN_reserv_year = searchbyName.reservDate / 10000;
                int SBN_reserv_month = (searchbyName.reservDate % 10000) / 100;
                int SBN_reserv_day = (searchbyName.reservDate % 10000) % 100;

                cout << "Reservation Date\t: " << SBN_reserv_day << "/" << SBN_reserv_month << "/" << SBN_reserv_year << endl;

                switch (searchbyName.durationType)
                {
                case 'A':
                    SBN_duration = "AM (8am to 12pm)";
                    break;
                case 'P':
                    SBN_duration = "PM (2pm to 6pm)";
                    break;
                case 'F':
                    SBN_duration = "Full Day (8am to 6pm)";
                    break;
                    // no default needed
                }
                cout << "Duration Type\t\t: " << SBN_duration << endl;

                // Display Room Type in full form
                switch (searchbyName.roomCode)
                {
                case 'A':
                    SBN_RoomCode = "Azure";
                    break;
                case 'B':
                    SBN_RoomCode = "Byzantine";
                    break;
                case 'C':
                    SBN_RoomCode = "Crystal";
                    break;
                case 'D':
                    SBN_RoomCode = "Diamond";
                    break;
                case 'E':
                    SBN_RoomCode = "Emerald";
                    break;
                case 'F':
                    SBN_RoomCode = "Florence";
                    break;
                case 'G':
                    SBN_RoomCode = "Genesis";
                    break;
                case 'H':
                    SBN_RoomCode = "Helion";
                    break;
                }
                cout << "Room Type\t\t: " << SBN_RoomCode << endl;

                // Display Price
                cout << "Price\t\t\t: RM" << searchbyName.actualPrice << endl;

                cout << "Event Description\t: " << searchbyName.eventDescription;
                // Convert code to word and display
                switch (searchbyName.reservStatus)
                {
                case 'R':
                    SBN_status = "Reserved";
                    break;
                case 'C':
                    SBN_status = "Confirmed";
                    break;
                case 'X':
                    SBN_status = "Cancelled";
                    break;
                }
                cout << "\nBooking Status\t\t: " << SBN_status << endl;

                srhName = 1;
            }
        }
        fbin.close();
        if (srhName == 0)
            cout << "Customer Name not found in data.";

        cout << "\nReturning back to Enquiries...\n";
        system("pause");
        tempmenuchoice();
    }
}

void searchbyContactNo()
{
    Reservation searchbyContact;
    ifstream fbin("reservation.dat", ios::binary | ios::in);
    if (!fbin)
    {
        cout << "Error in opening file\n";
    }
    else
    {
        int srhContact = 0;
        long long findcontact;
        string SBC_status, SBC_duration, SBC_RoomCode;
        cout << "Enter Contact Number to search: ";
        cin >> findcontact;
        while (fbin.read((char *)&searchbyContact, sizeof(searchbyContact)))
        {
            if (searchbyContact.contactNo == findcontact)
            {
                // Display Header and Reservation Code of the customer
                cout << "Here are your details: \n";
                cout << "--------------------------------------------------\n";
                cout << "Customer Name\t\t: " << searchbyContact.custName << endl;    // Display Name
                cout << "Reservation Code\t: " << searchbyContact.reservCode << endl; // Show Reservation Code
                // Show Reservation Date (Proper Way)
                int SBC_reserv_year = searchbyContact.reservDate / 10000;
                int SBC_reserv_month = (searchbyContact.reservDate % 10000) / 100;
                int SBC_reserv_day = (searchbyContact.reservDate % 10000) % 100;

                cout << "Reservation Date\t: " << SBC_reserv_day << "/" << SBC_reserv_month << "/" << SBC_reserv_year << endl;

                switch (searchbyContact.durationType)
                {
                case 'A':
                    SBC_duration = "AM (8am to 12pm)";
                    break;
                case 'P':
                    SBC_duration = "PM (2pm to 6pm)";
                    break;
                case 'F':
                    SBC_duration = "Full Day (8am to 6pm)";
                    break;
                    // no default needed
                }
                cout << "Duration Type\t\t: " << SBC_duration << endl;

                // Display Room Type in full form
                switch (searchbyContact.roomCode)
                {
                case 'A':
                    SBC_RoomCode = "Azure";
                    break;
                case 'B':
                    SBC_RoomCode = "Byzantine";
                    break;
                case 'C':
                    SBC_RoomCode = "Crystal";
                    break;
                case 'D':
                    SBC_RoomCode = "Diamond";
                    break;
                case 'E':
                    SBC_RoomCode = "Emerald";
                    break;
                case 'F':
                    SBC_RoomCode = "Florence";
                    break;
                case 'G':
                    SBC_RoomCode = "Genesis";
                    break;
                case 'H':
                    SBC_RoomCode = "Helion";
                    break;
                }
                // SBC_lookupRoomcode(searchbyContact.reservCode);
                cout << "Room Type\t\t: " << SBC_RoomCode << endl;

                // Display Price
                cout << "Price\t\t\t: RM" << searchbyContact.actualPrice << endl;

                cout << "Event Description\t: " << searchbyContact.eventDescription;
                // Convert code to word and display
                switch (searchbyContact.reservStatus)
                {
                case 'R':
                    SBC_status = "Reserved";
                    break;
                case 'C':
                    SBC_status = "Confirmed";
                    break;
                case 'X':
                    SBC_status = "Cancelled";
                    break;
                }
                cout << "\nBooking Status\t\t: " << SBC_status << endl;

                srhContact = 1;
            }
        }
        fbin.close();
        if (srhContact == 0)
        {
            cout << "\nCustomer Contact not found in data.\n";
        }
        cout << "\nReturning back to Enquiries...\n";
        system("pause");
        tempmenuchoice();
    }
}

void cancelReservation()
{
    Reservation cancelReservationProcess;
    fstream fbin("reservation.dat", ios::binary | ios::in | ios::out);
    fbin.seekg(0);
    if (!fbin)
    {
        cout << "Error in opening file";
    }
    else
    {
        int cancelstats = 0;
        char cancelCode[9], confirmCancel;
        string cancelStatus;
        cout << "\nTo exit, please press 0\n";
        cout << "Enter Reservation Code: ";
        cin >> cancelCode;
        if (cancelCode[0] == '0')
        {
            cout << "Jump to process menu\n";
            tempmenuchoice();
        }
        else
        {
            while (fbin.read((char *)&cancelReservationProcess, sizeof(cancelReservationProcess)))
            {
                if (strcmp(cancelReservationProcess.reservCode, cancelCode) == 0)
                {

                    // cancel_ValidateCode(&cancelReservationProcess.reservCode);

                    switch (cancelReservationProcess.reservStatus)
                    {
                    case 'R':
                        cancelStatus = "Reserved";
                        break;
                    case 'C':
                        cancelStatus = "Confirmed";
                        break;
                    case 'X':
                        cancelStatus = "Cancelled";
                        break;
                    }
                    cout << "\n\nHere are your details:\n";
                    cout << "Reservation Code"
                         << "\tName\tStatus\n";
                    cout << "----------------------------------------------\n";
                    cout << cancelReservationProcess.reservCode << "\t\t" << cancelReservationProcess.custName << "\t" << cancelStatus << "\n\n";

                    if (cancelReservationProcess.reservStatus == 'C')
                    {
                        cout << "This Reservation has been confirmed. Unable to cancel this reservation.\n";
                        system("pause");
                        cancelReservation();
                    }
                    else if (cancelReservationProcess.reservStatus == 'X')
                    {
                        cout << "This Reservation Has Been Cancelled. Please enter again.\n";
                        system("pause");
                        cancelReservation();
                    }
                    else
                    {
                        cout << "Are you sure to cancel your reservation? ";
                        cin >> confirmCancel;
                        confirmCancel = toupper(confirmCancel);
                        if (confirmCancel == 'N')
                        {
                            // Jump back to process reservation
                            cout << "OK.\n\n";
                            tempmenuchoice();
                        }
                        else if (confirmCancel == 'Y')
                        {
                            cancelReservationProcess.reservStatus = 'X';
                            cout << "Reservation Successfully Cancelled.";
                        }
                        fbin.seekp(-sizeof(cancelReservationProcess), ios::cur);
                        fbin.write((char *)&cancelReservationProcess, sizeof(cancelReservationProcess));
                    }
                    cancelstats = 1;
                }
            }
            fbin.close();
            if (cancelstats == 0)
            {
                cout << "Not Found!!!";
                cancelReservation();
            }
        }
    }
}

void tempmenuchoice()
{
    int search_choice;
    cout << endl;
    cout << "1. Search by Customer Name (Enquiry Module)\n";
    cout << "2. Search by Contact Number (Enquiry Module)\n";
    cout << "3. Cancel Reservation (Process Reservation)\n";
    cout << "4. Revenue by Customer (Reports)\n";
    cout << "Enter your choice: ";
    cin >> search_choice;

    switch (search_choice)
    {
    case 1:
        searchbyCustName();
        break;
    case 2:
        searchbyContactNo();
        break;
    case 3:
        cancelReservation();
        break;
    //case 4:
    //    revenuebycustomer();
    default:
        cout << "Sorry Invalid Choice";
        break;
    }
}

