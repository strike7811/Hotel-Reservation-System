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

void searchbyCustName();
void searchbyContactNo();
void cancelReservation();
void tempmenuchoice(); // No need to be included in merge file (directs to be edited : line 83,184,222,329,366,422,431,470,712) not sure might left out some, need to check afterwards
void revenuebycustomer();

int main()
{
    tempmenuchoice();
    return 0;
}

/***********/
void searchbyCustName()
{
    Reservation searchbyName; // Assign Struct Name
    ifstream fbin("reservation.dat", ios::binary | ios::in);
    if (!fbin) // If not the specific file
    {
        cout << "Error in opening file"; // Print out error message
    }
    else
    {
        int srhName = 0;
        char findname[21];
        string SBN_status, SBN_duration, SBN_RoomCode;

        // Display Message

        cout << "   =============================================================\n";
        cout << "                  Search Reservation By Customer Name\n";
        cout << "   =============================================================\n";
        cout << "               This module searches for reservation by \n";
        cout << "                       entering Customer Name.\n";
        cout << "   *Note: It will display multiple records for the same customer\n";
        cout << "                      [To Exit, Please Enter 0]\n";
        cout << "   -------------------------------------------------------------\n";

        cout << "Enter Name to search: "; // Prompt user to enter name
        cin.clear();
        cin.sync();
        cin.getline(findname, 21);
        if (findname[0] == '0') // If user press 0
        {
            cout << "Jump to process menu\n";
            srhName = 1; // Initialise srhName to 1

            tempmenuchoice();
        }

        while (fbin.read((char *)&searchbyName, sizeof(searchbyName)))
        {
            if (strcmp(searchbyName.custName, findname) == 0) // Compare input with customer's name in file
            {
                // Display Header and Reservation Code of the customer
                cout << "\n\nHere are your details: \n";
                cout << "--------------------------------------------------\n";
                cout << "Customer Name\t\t: " << searchbyName.custName << endl;    // Display Name
                cout << "Reservation Code\t: " << searchbyName.reservCode << endl; // Show Reservation Code
                // Show Reservation Date (Proper Way)
                // Seperate Day, Month and Year
                int SBN_reserv_year = searchbyName.reservDate / 10000;
                int SBN_reserv_month = (searchbyName.reservDate % 10000) / 100;
                int SBN_reserv_day = (searchbyName.reservDate % 10000) % 100;

                // Display Day, Month, Year in proper way
                cout << "Reservation Date\t: " << SBN_reserv_day << "/" << SBN_reserv_month << "/" << SBN_reserv_year << endl;

                // Convert initials stored in file to Full Form
                switch (searchbyName.durationType)
                {
                case 'A':                              // If data in file is A
                    SBN_duration = "AM (8am to 12pm)"; // Convert to proper display
                    break;
                case 'P':                             // If data in file is P
                    SBN_duration = "PM (2pm to 6pm)"; // Convert to proper display
                    break;
                case 'F':                                   // If data in file is F
                    SBN_duration = "Full Day (8am to 6pm)"; // Convert to proper display
                    break;
                    // no default needed
                }

                // Display Duration Type in proper way
                cout << "Duration Type\t\t: " << SBN_duration << endl;

                // Display Room Type in full form
                switch (searchbyName.roomCode)
                {
                case 'A': // If data in file is A
                    SBN_RoomCode = "Azure";
                    break;
                case 'B': // If data in file is B
                    SBN_RoomCode = "Byzantine";
                    break;
                case 'C': // If data in file is C
                    SBN_RoomCode = "Crystal";
                    break;
                case 'D': // If data in file is D
                    SBN_RoomCode = "Diamond";
                    break;
                case 'E': // If data in file is E
                    SBN_RoomCode = "Emerald";
                    break;
                case 'F': // If data in file is F
                    SBN_RoomCode = "Florence";
                    break;
                case 'G': // If data in file is G
                    SBN_RoomCode = "Genesis";
                    break;
                case 'H': // If data in file is H
                    SBN_RoomCode = "Helion";
                    break;
                }
                cout << "Room Type\t\t: " << SBN_RoomCode << endl; // Display Room Type in full form

                // Display Price
                cout << "Price\t\t\t: RM" << searchbyName.actualPrice << endl;

                // Display Event Description
                cout << "Event Description\t: " << searchbyName.eventDescription;

                // Convert code to word and display
                switch (searchbyName.reservStatus)
                {
                case 'R': // If data in file is R
                    SBN_status = "Reserved";
                    break;
                case 'C': // If data in file is C
                    SBN_status = "Confirmed";
                    break;
                case 'X': // If data in file is F
                    SBN_status = "Cancelled";
                    break;
                }
                cout << "\nBooking Status\t\t: " << SBN_status << endl;

                srhName = 1; // Initialise srhName to 1
            }
        }
        fbin.close();                                     // Close file
        if (srhName == 0)                                 // If variable srhName equals to 0 (means no data in file is read)
            cout << "\nCustomer Name not found in data."; // Display Error Message

        // Display message to direct user back to Enquiries Menu
        cout << "\nReturning back to Enquiries...\n";
        system("pause");

        tempmenuchoice(); // to be removed
    }
}

void searchbyContactNo()
{
    Reservation searchbyContact; // Assign struct name
    ifstream fbin("reservation.dat", ios::binary | ios::in);
    if (!fbin) // if file is not found
    {
        cout << "Error in opening file\n"; // Display Error Message
    }
    else
    {
        // Declare and initialise required variables
        int srhContact = 0;
        long long findcontact;
        string SBC_status, SBC_duration, SBC_RoomCode;

        // Display Message

        cout << "   =============================================================\n";
        cout << "                  Search Reservation By Contact Number\n";
        cout << "   =============================================================\n";
        cout << "               This module searches for reservation by \n";
        cout << "                       entering Contact Number.\n";
        cout << "   *Note: It will display multiple records for the same customer\n";
        cout << "                      [To Exit, Please Enter 0]\n";
        cout << "   -------------------------------------------------------------\n";

        // Prompt and get input for contact number
        cout << "Enter Contact Number to search: ";
        cin >> findcontact;
        if (findcontact == 0) // If user press 0
        {
            cout << "Jump to process menu\n";
            srhContact = 1;

            tempmenuchoice();
        }

        while (fbin.read((char *)&searchbyContact, sizeof(searchbyContact)))
        {
            if (searchbyContact.contactNo == findcontact) // Compare user's input with contact number in file
            {
                // Display Header and Reservation Code of the customer
                cout << "Here are your details: \n";
                cout << "--------------------------------------------------\n";
                cout << "Customer Name\t\t: " << searchbyContact.custName << endl;    // Display Name
                cout << "Reservation Code\t: " << searchbyContact.reservCode << endl; // Show Reservation Code
                // Show Reservation Date (Proper Way)
                // Seperate Day, Month and Year
                int SBC_reserv_year = searchbyContact.reservDate / 10000;
                int SBC_reserv_month = (searchbyContact.reservDate % 10000) / 100;
                int SBC_reserv_day = (searchbyContact.reservDate % 10000) % 100;

                // Display Reservation Date
                cout << "Reservation Date\t: " << SBC_reserv_day << "/" << SBC_reserv_month << "/" << SBC_reserv_year << endl;

                // Convert initials stored in file to Full Form
                switch (searchbyContact.durationType)
                {
                case 'A': // If data in file is A
                    SBC_duration = "AM (8am to 12pm)";
                    break;
                case 'P': // If data in file is P
                    SBC_duration = "PM (2pm to 6pm)";
                    break;
                case 'F': // If data in file is F
                    SBC_duration = "Full Day (8am to 6pm)";
                    break;
                    // no default needed
                }

                // Display Duration Type
                cout << "Duration Type\t\t: " << SBC_duration << endl;

                // Display Room Type in full form
                switch (searchbyContact.roomCode)
                {
                case 'A': // If data in file is A
                    SBC_RoomCode = "Azure";
                    break;
                case 'B': // If data in file is B
                    SBC_RoomCode = "Byzantine";
                    break;
                case 'C': // If data in file is C
                    SBC_RoomCode = "Crystal";
                    break;
                case 'D': // If data in file is D
                    SBC_RoomCode = "Diamond";
                    break;
                case 'E': // If data in file is E
                    SBC_RoomCode = "Emerald";
                    break;
                case 'F': // If data in file is F
                    SBC_RoomCode = "Florence";
                    break;
                case 'G': // If data in file is G
                    SBC_RoomCode = "Genesis";
                    break;
                case 'H': // If data in file is H
                    SBC_RoomCode = "Helion";
                    break;
                }

                // Display Duration Type in proper way
                cout << "Room Type\t\t: " << SBC_RoomCode << endl;

                // Display Price
                cout << "Price\t\t\t: RM" << searchbyContact.actualPrice << endl;

                // Display Event Description
                cout << "Event Description\t: " << searchbyContact.eventDescription;

                // Convert code to word and display
                switch (searchbyContact.reservStatus)
                {
                case 'R': // If data in file is R
                    SBC_status = "Reserved";
                    break;
                case 'C': // If data in file is C
                    SBC_status = "Confirmed";
                    break;
                case 'X': // If data in file is X
                    SBC_status = "Cancelled";
                    break;
                }

                // Display Booking Status
                cout << "\nBooking Status\t\t: " << SBC_status << endl;

                srhContact = 1;
            }
        }
        fbin.close();        // Close File
        if (srhContact == 0) // If variable srhContact equals to 0
        {
            cout << "\nCustomer Contact not found in data.\n"; // Display Error Message
        }

        // Display message to direct user back to Enquiries Menu
        cout << "\nReturning back to Enquiries...\n";
        system("pause");

        tempmenuchoice(); // to be removed afrer merge
    }
}

void cancelReservation()
{
    Reservation cancelReservationProcess; // Assign Struct Name
    fstream fbin("reservation.dat", ios::binary | ios::in | ios::out);
    fbin.seekg(0);
    if (!fbin)
    {
        cout << "Error in opening file"; // Display Error Message
    }
    else
    {
        // Declare required Variables
        int cancelstats = 0;
        char cancelCode[9], confirmCancel;
        int cancelLOOP = 0;
        string cancelStatus;

        // Display Message

        cout << "   =============================================================\n";
        cout << "                           Cancel Reservation\n";
        cout << "   =============================================================\n";
        cout << "               This module searches for reservation by \n";
        cout << "                       entering Reservation Code.\n";
        cout << "                        [To Exit, Please Enter 0]\n";
        cout << "   -------------------------------------------------------------\n";

        // Display Message
        cout << "\nTo exit, please press 0\n";
        cout << "Enter Reservation Code: ";
        cin >> cancelCode;
        if (cancelCode[0] == '0') // If user enter '0' as first character and press enter
        {
            cout << "Jump to process menu\n"; // Display message and direct user back to process menu
            tempmenuchoice();
        }
        else
        {
            while (fbin.read((char *)&cancelReservationProcess, sizeof(cancelReservationProcess)))
            {
                if (strcmp(cancelReservationProcess.reservCode, cancelCode) == 0) // Compare input reservation code with  reservation code in File
                {

                    switch (cancelReservationProcess.reservStatus) // If reservation code is found
                    {
                    case 'R':
                        cancelStatus = "Reserved"; // change initial to full form
                        break;
                    case 'C':
                        cancelStatus = "Confirmed"; // change initial to full form
                        break;
                    case 'X':
                        cancelStatus = "Cancelled"; // change initial to full form
                        break;
                    }

                    // Display Output Header
                    cout << "\n\nHere are your details:\n";
                    cout << "Reservation Code"
                         << "\tName\tStatus\n";
                    cout << "----------------------------------------------\n";
                    cout << cancelReservationProcess.reservCode << "\t\t" << cancelReservationProcess.custName << "\t" << cancelStatus << "\n\n";

                    // Validate if reservation code has beed confirmed or cancelled before
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
                    else // Else double confirm to cancel user's reservation
                    {

                        while (cancelLOOP == 0)

                        {
                            cancelLOOP == 1;

                            if (confirmCancel != 'Y' || confirmCancel != 'N')
                                ; // Validate if user enter any character other than Y / N
                            {
                                cout << endl
                                     << "Are you sure to cancel your reservation?\n";
                                cout << "[Y - Yes] [N - No]\nYour Choice > ";
                                cin >> confirmCancel;
                                confirmCancel = toupper(confirmCancel); // make user input to Upper Case for further validation
                                if (confirmCancel == 'N')               //
                                {
                                    // Supposed to jump Jump back to process reservation
                                    cout << "OK.\n\n";
                                    system("pause");
                                    tempmenuchoice();

                                    cancelLOOP = 0;
                                }
                                else if (confirmCancel == 'Y') // If yes, update data and change initial to 'X'
                                {
                                    cancelReservationProcess.reservStatus = 'X';
                                    cout << "\nReservation Successfully Cancelled." << endl; // Display output message.
                                    cout << "\nDirecting you back to Process Menu..." << endl;

                                    cancelLOOP = 1;
                                }
                                else
                                {
                                    cout << "Invalid Input. Please enter [Y/N] only!" << endl;

                                    cancelLOOP = 0;
                                }
                            }
                        }
                        fbin.seekp(-sizeof(cancelReservationProcess), ios::cur);
                        fbin.write((char *)&cancelReservationProcess, sizeof(cancelReservationProcess));
                    }
                    cancelstats = 1; // Update cancelstats
                }
            }
            if (cancelstats == 0)
            {
                char cancelLoop2; // Declare variable for loop

                // Display No Data Found Message
                cout << "Not Found!!!" << endl;

                do
                {
                    // Display message asking user if user wants to quit module or enter again
                    cout << endl
                         << "Do you want to enter another reservation code?" << endl;
                    cout << "[Y - Yes] [N - Direct Back to Process Menu]" << endl;
                    cout << "Your Choice > ";
                    cin >> cancelLoop2;                 // Get User Input
                    cancelLoop2 = toupper(cancelLoop2); // Make user input for furhter Validation
                    if (cancelLoop2 == 'Y')             // If user input 'Y'
                    {
                        cancelReservation(); // Loop cancel reservation module again
                    }
                    else if (cancelLoop2 == 'N') // Else if user input 'N'
                    {
                        cout << endl
                             << "Directing you back to Process Menu..." << endl;
                        system("pause");
                        tempmenuchoice(); // SUpposed to loop back to Process Menu
                    }
                    else // Else if user did not input Y or N
                    {
                        cout << "Invalid Input. Please enter [Y/N] only!" << endl;
                    }
                } while (cancelLoop2 != 'Y' || cancelLoop2 != 'N');
            }
            fbin.close(); // Close File

            system("pause");
            tempmenuchoice();
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
    case 4:
        revenuebycustomer();
    default:
        cout << "Sorry Invalid Choice (menu)";
        break;
    }
}

void revenuebycustomer()
{
    struct CustomerRevenue // Declare Structure CustomerRevenue
    {
        char RevCustSort[21]; // change array size
        int CustRevAmt;
        char CustStatus;
    };

    CustomerRevenue custArray[30]; // Declare Customer Array to store all customer names

    // Display Header
    cout << endl;
    cout << "=============================================================\n";
    cout << "                     Revenue by Customer                     \n";
    cout << "=============================================================\n";
    cout << "            This report is to identify who's the             \n";
    cout << "                   company's best customers                  \n";
    cout << "             (except for Cancelled reservations).            \n";
    cout << "        *Note: This is sorted according to alphabetical      \n";
    cout << "          order of customer with Highest Contribution        \n";
    cout << "-------------------------------------------------------------\n";

    //******************************************************//
    // Count number of data in file (get number of recCount)//
    //******************************************************//

    Reservation currentCust;
    CustomerRevenue revenueCust;

    int recCount = 0; // Initialise recCount to 0

    ifstream revenueByCust("reservation.dat", ios_base::in | ios_base::binary);
    if (!revenueByCust) // If the file entered is invalid
    {
        cout << "Error Opening File\n"; // Display error message
    }
    else
    {
        while (revenueByCust.read(reinterpret_cast<char *>(&currentCust), sizeof(currentCust))) // While reading file "reservation.dat"
        {
            // Count the total number of records
            // Check the Reservation Status of all customer.
            if (currentCust.reservStatus != 'X') // If the status is not 'X' which means cancelled
            {
                ++recCount;                                            // Increase the recCount to determine total number of customer
                strcpy(revenueCust.RevCustSort, currentCust.custName); // store customer name to Struct
                revenueCust.CustRevAmt = currentCust.actualPrice;      // store customer Price
                revenueCust.CustStatus = currentCust.reservStatus;     // store customer status

                custArray[recCount] = revenueCust; // store revenueCust into custArray with specific position
            }
        }

        revenueByCust.read(reinterpret_cast<char *>(&currentCust), sizeof(currentCust));
    }
    revenueByCust.close(); // close file

    //*****************************
    char tempCust[1];
    int tempCustRevAmt, maxCount, tempCustStatus;

    //****************************************//
    // SORTING to customer to accending order //
    //****************************************//

    for (int i = 1; i <= (recCount); i++)
    {
        for (int j = i + 1; j <= recCount; j++)
        {
            // Compare if Alphabetical Order of 1st Customer is bigger than 2nd Customer
            // strcmpi ignores the upper case or lower case of the alphabet
            if (strcmpi(custArray[i].RevCustSort, custArray[j].RevCustSort) > 0)
            {
                // Store to temp
                strcpy(tempCust, custArray[i].RevCustSort); // Store 1st Customer Name to temporary Variable
                tempCustRevAmt = custArray[i].CustRevAmt;   // Store 1st Customer's Price to temporary Variable
                tempCustStatus = custArray[i].CustStatus;   // Store 1st Customer's Status to temporary Variable

                // Replace 1st Position with 2nd Position
                strcpy(custArray[i].RevCustSort, custArray[j].RevCustSort); // Exchange 1st Customer's Name with 2nd Customer Name
                custArray[i].CustRevAmt = custArray[j].CustRevAmt;          // Exchange 1st Customer's Price with 2nd Customer's Price
                custArray[i].CustStatus = custArray[j].CustStatus;          // Exchange 1st Customer's Status with 2nd Customer's Price

                // Replace value in temporary variable (initially 1st Customer's Value)
                strcpy(custArray[j].RevCustSort, tempCust); // Store Customer's name in temporary variable to 2nd Customer's Position
                custArray[j].CustRevAmt = tempCustRevAmt;   // Store Customer's Price in temporary variable to 2nd Customer's Position
                custArray[j].CustStatus = tempCustStatus;   // Store Customer's Status in temporary variable to 2nd Customer's Position
            }
        }
    }

    // Just for checking data purpose
    /*for (int i = 1; i <= recCount; i++)
    {
        cout << custArray[i].RevCustSort << " $" << custArray[i].CustRevAmt << " " << custArray[i].CustStatus << endl;
    }

    system("pause");*/

    //**************************** fin sort

    //**********************************//
    // Removing Redundant Customer Name //
    //**********************************//

    int g = 1;           // initialize variable g to 1
    while (g < recCount) // while g less than recCount (which is total number of customer excluding cancelled status)
    {
        // Since Customer Name already sorted alphabatically, therefore if Customer Name is the same, then it will be the same person
        // While at position Customer A
        if (strcmp(custArray[g + 1].RevCustSort, custArray[g + 2].RevCustSort) == 0) // Compare Customer B and Customer C if they are the same customer
        {
            // If Customer B and C are the same customer, merge two customer and add up the Customer Price in Customer B (same customer)
            // Because they are the same customer with different records, therefore need to addup all price
            custArray[g + 1].CustRevAmt = custArray[g + 1].CustRevAmt + custArray[g + 2].CustRevAmt;

            // After adding, move all records to one position ahead
            for (int i = g + 1; i < recCount; i++)
            {
                strcpy(custArray[i + 1].RevCustSort, custArray[i + 2].RevCustSort); // Replace Customer C's Name with Customer D's Name
                custArray[i + 1].CustRevAmt = custArray[i + 2].CustRevAmt;          // Replace Customer C's Price with Customer D's Price
            }
            recCount -= 1; // Redule recCount by one value as same Customer data is merged
        }
        else
        {
            g++; // Increment g value with 1;
        }

        // If Customer A's name is not Customer B's name, loop again
    }

    // Just for Checking data Purpose
    /*
    for (int k = 1; k <= recCount; k++)
    {
        cout << custArray[k].RevCustSort << "\t" << custArray[k].CustRevAmt << endl;
    }
    system("pause");*/

    //*************************//
    // Sort Customer by Amount //
    //*************************//

    for (int i = 1; i <= (recCount); i++)
    {
        for (int j = i + 1; j <= recCount; j++)
        {

            if (custArray[i].CustRevAmt < custArray[j].CustRevAmt) // if Price Amount of Customer A is lesser than Customer B
            {
                // Store to temp
                strcpy(tempCust, custArray[i].RevCustSort); // Store Customer A's Name into temporary Variable
                tempCustRevAmt = custArray[i].CustRevAmt;   // Store Customer A's Price into temporary Variable
                tempCustStatus = custArray[i].CustStatus;   // Store Customer A's Status into temporary Variable

                // Replace 1st Position with 2nd Position
                strcpy(custArray[i].RevCustSort, custArray[j].RevCustSort); // Replace Customer A's Name with Customer B
                custArray[i].CustRevAmt = custArray[j].CustRevAmt;          // Replace Customer A's Price with Customer B
                custArray[i].CustStatus = custArray[j].CustStatus;          // Replace Customer A's Status with Customer B

                // Replace value in temporary variable (initially 1st Customer's Value)
                strcpy(custArray[j].RevCustSort, tempCust); // Store Customer's name in temporary variable to 2nd Customer's Position
                custArray[j].CustRevAmt = tempCustRevAmt;   // Store Customer's Price in temporary variable to 2nd Customer's Position
                custArray[j].CustStatus = tempCustStatus;   // Store Customer's Status in temporary variable to 2nd Customer's Position
            }
        }
    }

    //**********************************//
    //   Display sorted Customer Value  //
    //**********************************//

    cout << "\tList of Revenue of Customers" << endl;
    cout << "+----------------------------------------------+" << endl;
    cout << "|\tCustomer Name\t  Total Contribution   |" << endl;
    cout << "+----------------------------------------------+" << endl;

    // Display the Best Customer (Which is the first position of custArray)
    cout << left;
    cout << setw(5) << "|\t>> " << setw(20) << custArray[1].RevCustSort << setw(16) << custArray[1].CustRevAmt << "|" << endl;

    // Display all other Customer Data from Highest Contribution to Lowest Contribution with Alphabetical Order Sorted
    for (int i = 2; i <= recCount; i++)
    {
        cout << left;
        cout << setw(5) << "|\t" << setw(20) << custArray[i].RevCustSort << setw(16) << custArray[i].CustRevAmt << "|" << endl;
    }

    cout << "+----------------------------------------------+" << endl;

    // Analysis Message of Best Customer
    cout << endl
         << "According to Analysis, " << custArray[1].RevCustSort << " is our Best Customer!" << endl
         << endl
         << "Directing you back to Reports Menu..."
         << endl;

    system("pause");
    tempmenuchoice();
}