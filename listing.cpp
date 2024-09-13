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
int validateLDate(int LDate);
bool check_LDate_length(int LDate, int *Length);

int main(){
    reservListing(); // Call function
}

int validateLDate(int LDate)
{
    // Declare variavle
    int Year, Month, Day, Date;
    bool InvalidLDateData = true;

    do { 
        // Declare firstDigit, secondDigit, thirdDigit, fourthDigit, fifthDigit, sixthDigit, Q1, Q2, Q3, Q4, Q5, Q6, R1, R2, R3, R4, R5, R6, YY, MM, DD, ttlDays
        // Decalare and initialize IllegalLDate = true, YearValid = false, MonthValid = false, DayValid = false, leapYear = true, fullYear = 2000
        int length = 0;
        int firstDigit;
        int secondDigit;
        int thirdDigit;
        int fourthDigit;
        int fifthDigit;
        int sixthDigit;
        bool IllegalLDate = true;        
        int Q1,Q2,Q3,Q4,Q5,Q6,R1,R2,R3,R4,R5,R6, YY, MM, DD, fullYear = 2000, ttlDays;
        bool YearValid = false, MonthValid = false, DayValid = false, leapYear = true;

        while (cin.fail()) // if data get from the user is different type
        {
            cin.clear(); // Clear the input
            cin.ignore(100, '\n'); //Ignore the next 100 characters or until it encounters newline
            LDate = 0; // set LDate = 0
            cout << "   Error! Date can only be a numeric whole number!\n"; // Display error message
            // Prompt and get the LDate
            cout << "   Enter Reservation Date (Format: YYMMDD): ";
            cin >> LDate;

        }
        cin.ignore(100, '\n'); // Ignore the next 100 characters or until it encounters newline
        IllegalLDate = false; // set IllegalLdate = false

        bool LengthyLDate = check_LDate_length(LDate, &length); // Call function
        

        if (LengthyLDate == false) // if LenghtyLDate equal to false
        {
            Q1 = LDate / 10; // Q1 = LDate / 10
            R1 = LDate % 10; // R1 = LDate % 10;
            sixthDigit = R1;  // set the sixthDigit = R1
            Q2 = Q1 / 10; // Q2 = Q1 / 10
            R2 = Q1 % 10; // R2 = Q1 % 10
            fifthDigit = R2; // set the fifthDigit = R2
            Q3 = Q2 / 10; // Q3 = Q2 / 10
            R3 = Q2 % 10; // R3 = Q2 % 10
            fourthDigit = R3; // set the fourthDigit = R3
            Q4 = Q3 / 10; // Q4 = Q3 / 10
            R4 = Q3 % 10; // R4 = Q3 % 10
            thirdDigit = R4; // set the thirdDigit = R4
            Q5 = Q4 / 10; // Q5 = Q4 / 10
            R5 = Q4 % 10; // R5 = Q4 % 10
            secondDigit = R5; // set the secondDigit = R5
            Q6 = Q5 / 10; // Q6 = Q5 / 10
            R6 = Q5 % 10; // R6 = Q5 % 10
            firstDigit = R6; // set the firstDigit = R6

            YY = firstDigit * 10 + secondDigit; // YY = firstDigit * 10 + secondDigit
            MM = thirdDigit * 10 + fourthDigit; // MM = thirdDigit * 10 + fourthDigit
            DD = fifthDigit * 10 + sixthDigit; // DD = fifthDigit * 10 + sixthDigit



            if (YY >= (Year - 2000)) // if YY greater than or equal to (Year - 2000)
            {
                YearValid = true; // set YearValid = true
                fullYear += YY; // fullYear += YY
                if (fullYear % 4 == 0) // if the remainder of fullYear divided by 4 is equal to 0
                {
                    if (fullYear % 100 == 0) // if the remainder of fullYear divided by 100 is equal to 0
                    {
                        if (fullYear % 400 == 0) // if the remainder of fullYear divided by 400 is equal to 0
                        {   
                            leapYear = true; // set leapYear = true
                        }
                        else
                        {
                            leapYear = false; // set leapYear = false
                        }
                    }
                    else
                    {
                        leapYear = true; // set leapYear = true
                    }
                }
                else
                {
                    leapYear = false; // set leapYear = false
                }
                
            }
            else
            {
                cout << "   Error! Year of Reservation Date must not be before Year of Entry Date!\n"; // Display error message
                YearValid = false; // set YearValid = false
            }

            if (MM >= 1 && MM <= 12) // if MM greater than or equal to 1 and MM less than or equal to 12
                MonthValid = true; // set MonthValid = true
            if (DD >= 1 && DD <= 31) // if DD greater than or equal to 1 and DD less than or equal to 31
            {
                if (MM == 2) // if MM equal to 2
                {
                    if (DD <= 29 && leapYear == true) // if DD less than or equal to 29 and leapYear equal to true
                    {
                        DayValid = true; // set DayValid = true
                    }
                    else if (DD <= 28 && leapYear == false) // if DD less than or equal to 28 and leapYear equal to false
                    {
                        DayValid = true; // set DayValid = true
                    }
                    else
                        DayValid = false; // set DayValid = false
                }
                else
                {
                    switch (MM)
                    {
                        //if MM equal to 1,3,5,7,8,10 or 12
                        case 1:
                        case 3:
                        case 5:
                        case 7:
                        case 8:
                        case 10:
                        case 12:
                                ttlDays = 31; // set ttlDays = 31
                                break;

                        //if MM equal to 4,6,9 or 11
                        case 4:
                        case 6:
                        case 9:
                        case 11:
                                ttlDays = 30; // set ttlDays = 30
                                break;                              
                    }
                    if (DD <= ttlDays) // if DD less than or equal to ttlDays
                        DayValid = true; // set DayValid = true
                    else
                        DayValid = false; // set DayValid = false
                }
            }
        }
        if (DayValid == true && MonthValid == true && YearValid == true) // if DayValid equal to true and MonthValid equal to true and YearValid equal to true
        {
            if (fullYear > Year) // if fullYear greater than Year
                InvalidLDateData = false; // set InvalidLDateDate = false
            else if (fullYear == Year) // else if fullYear equal to Year
            {
                if (MM > Month) // if MM greater than Month
                {
                    InvalidLDateData = false; // set InvalidLDateDate = false
                }
                else if (MM == Month) // if MM equal to Month
                {
                    if (DD > Day) // if DD greater than Day
                        InvalidLDateData = false; // set InvalidLDateDate = false
                    else
                    {
                        InvalidLDateData = true;  // set InvalidLDateDate = true
                        cout << "   Error! Day of Reservation Date must be at least 1 day after Day of Entry Date!\n"; // Display error message
                        // Prompt and get LDate
                        cout << "   Enter Reservation Date (Format: YYMMDD): ";
                        cin >> LDate;
                    }                   
                }
                else
                {
                    InvalidLDateData = true; // set InvalidLDateData = true
                    cout << "   Error! Month of Reservation Date must not be before Month of Entry Date!\n"; // Display error message
                    // Prompt and get LDate
                    cout << "   Enter Reservation Date (Format: YYMMDD): ";
                    cin >> LDate;
                }
            }
            
        }
        else
        {
            cout << "   Error! Reservation Date must be 6 digits long with the format YYMMDD!\n"; // Display error message
            // Prompt and get LDate
            cout << "   Enter Reservation Date (Format: YYMMDD): ";
            cin >> LDate;
        }
    } while (InvalidLDateData == true); // do while loop if InvalidLDateData equal to true
    return LDate; // Return the value LDate
}

bool check_LDate_length(int LDate, int *Length)
{
    // Declare num and set num to the LDate
    int num = LDate;
    // Declare and Initialize count = 0
    int count = 0;

    do
    {
        num /= 10; // num /= 10
        count++; //Increment count by 1
    } while (num != 0); // do while loop if num not equal to 0

    *Length = count;
    
    if (count == 6) // if count equal to 6
        return false; // return false value
    else
        return true; // return true value
}

void reservListing(){
    Reservation reservlisting; // Declare Reservation reservlisting
    ifstream fbin("reservation.dat",ios::binary | ios::out); // Declare file stream variable and read the file
    if(!fbin){ // if file cannot open
        cout << "   Error in opening file"; // Display the error message
    }

    else{
        // Declare search_date
        // Declare and Initialize total_amount = 0, existreserv = true
        int search_date,total_amount = 0;
        bool existreserv = true;
        string room;
        // Prompt and get the search_date from the user
        cout << "   Enter Reservation Date (Format: YYMMDD): ";
        cin >> search_date;
         
        search_date = validateLDate(search_date); // Call function to validate the date
        

        while(fbin.read((char*)&reservlisting,sizeof(reservlisting))){ // Read the file
            if (reservlisting.dataEntryDate == search_date){ // if Entry Date in the file is equal to search_date
                existreserv = true; // set the existreserv = true
                cout << "   ========================================================================================\n"; // Display "   ========================================================================================\n"
                cout << "                          New Reservations Entered Today listing\n"; // Display "                          New Reservations Entered Today listing\n"
                cout << "   ========================================================================================\n"; // Display "   ========================================================================================\n"
                cout << left << setw(21) << "   Name" << setw(18) << "Duration type" << setw(18) << "Reservation Date" << setw(12) << "Room Name" << setw(9) << "Status" << setw(8) << "Price" << endl;
                cout << "   ----------------------------------------------------------------------------------------\n"; // Display "   ----------------------------------------------------------------------------------------\n"
            }

            else{
                existreserv = false; // set the existreserv = false
                cout << "   Today has not reservation come in." << endl; // Display the message of not reservation come in at that day.
            }
            fbin.close(); // Close the file
        }
        
        fbin.open("reservation.dat",ios::out); // Open the file
        while(fbin.read((char*)&reservlisting,sizeof(reservlisting))){ // Read the file
            if (reservlisting.dataEntryDate == search_date){ // if Entry Date in the file equal to search_date
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
                total_amount = total_amount + reservlisting.actualPrice; // total_amount = total_amount + reservlisting.actualPrice
            }
        }
        cout << "\n\n   The total amount is RM" << total_amount << "." << endl; // Display the total amount
        cout << "\n"; // Display a new line
        system("pause");
        
    fbin.close(); // Close the file
    }
    
}