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

struct MonthlyRevenue
{
    char Month[4];
    int RevenueAmt;
};

int systemYear, systemMonth, systemDay, formattedSystemDate;
const int MAX_ROOMS = 8;
void welcomeScreen();
void endingScreen();
//**************Get System Date ***********************
void get_system_date();
//*************************Menus************************
// Main Menu
void mainMenu();

// Sub Menus
void reserveProcessMenu();
void enquiriesMenu();
void reportsMenu();

//********************Process Reservation**************
void createReservation();
void roomPriceMaintenance();
// void confirmReservation();
void cancelReservation();

//********************Enquiries************************
void checkAvailability();
void ReservForDate();
void searchbyCustName();
void searchbyContactNo();
void DisplayRoomInformation(); // Declare function
void viewDetail(); // Declare function

//********************Reports**************************
void monthlyRevenueGivenYear();
void SortMonthsByDescRev(struct mthRev[]);
void revForMonthAndYear();
void revenuebycustomer();

//*******************Validations***********************

bool check_illegal_char_string(string Input);

bool check_illegal_char_cn(string Input);

bool check_string_length(string Input, int InputLength);

bool check_contactno_length(long long Input, int *Length);

bool check_contactno_front(long Input);

string validateCustName(string custName, int custNameLength);

long long validateContactNum(long long ContactNum);

char validateDurationType(char duration_type);

int validateRDate(int RDate);

int validateRDate_enquiry(int ResDate);

bool check_RDate_length(int RDate, int *Length);

int validateNumAttendees(int num_attendees);

int main()
{
    welcomeScreen();
    mainMenu();
    return 0;
}

void welcomeScreen()
{
    cout << "\n\n  -------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                             ___   ___   _    ____\n";
    cout << "                                            / _ \\ /  _\\ /_\\  | ___|\n";
    cout << "                                           / /_\\/// /_)//_\\\\ |___ \\\n";
    cout << "                                          / /_ \\/ ___//  _  \\ ___) |\n";
    cout << "                                          \\____/\\/    \\_/ \\_/|____/\n";

    cout << "            ___                                  _    _                   ___              _       \n";
    cout << "           / __\\ ___   _ __ ___   __ ___  _ __  | |_ (_)  ___   _ __     / __\\ ___  _ __  | |_  _ __  ___\n";
    cout << "          / /   / _ \\ | '_ \\\\  \\ / // _ \\| '_ \\ | __|| | / _ \\ | '_ \\   / /   / _ \\| '_ \\ | __|| '__|/ _ \\\n";
    cout << "         / /___| (_) || | | |\\  V /|  __/| | | || |_ | || (_) || | | | / /___|  __/| | | || |_ | |  |  __/\n";
    cout << "         \\____/ \\___/ |_| |_| \\__/  \\___||_| |_| \\__||_| \\___/ |_| |_| \\____/ \\___||_| |_| \\__||_|   \\___| \n";
    cout << "\n\n  -------------------------------------------------------------------------------------------------------------------\n";
    cout << "\n                                    WELCOME TO GPA5 CONVENTION CENTRE SYSTEM!!!\n";
    get_system_date();
    system("pause");
}

void endingScreen()
{
    system("CLS");
    cout << "\n\n------------------------------------------------------------------------------------------------------------------\n";
    cout << "                                       ___   ___   _    ____\n";
    cout << "                                      / _ \\ /  _\\ /_\\  | ___|\n";
    cout << "                                     / /_\\/// /_)//_\\\\ |___ \\\n";
    cout << "                                    / /_ \\/ ___//  _  \\ ___) |\n";
    cout << "                                    \\____/\\/    \\_/ \\_/|____/\n";

    cout << "      ___                                  _    _                   ___              _       \n";
    cout << "     / __\\ ___   _ __ ___   __ ___  _ __  | |_ (_)  ___   _ __     / __\\ ___  _ __  | |_  _ __  ___\n";
    cout << "    / /   / _ \\ | '_ \\\\  \\ / // _ \\| '_ \\ | __|| | / _ \\ | '_ \\   / /   / _ \\| '_ \\ | __|| '__|/ _ \\\n";
    cout << "   / /___| (_) || | | |\\  V /|  __/| | | || |_ | || (_) || | | | / /___|  __/| | | || |_ | |  |  __/\n";
    cout << "   \\____/ \\___/ |_| |_| \\__/  \\___||_| |_| \\__||_| \\___/ |_| |_| \\____/ \\___||_| |_| \\__||_|   \\___| \n";
    cout << "\n\n------------------------------------------------------------------------------------------------------------------\n";
    cout << "\n                               THANK YOU FOR USING GPA5 CONVENTION CENTRE SYSTEM!!!\n";
    system("pause");
}

void get_system_date()
{
    time_t ttime = time(0);
    tm *localTime = localtime(&ttime);
    systemYear = 1900 + localTime->tm_year;
    systemMonth = 1 + localTime->tm_mon;
    systemDay = localTime->tm_mday;
    cout << "      Today's date: " << systemDay << "/" << systemMonth << "/" << systemYear << endl
         << endl;
    formattedSystemDate = (systemYear - 2000) * 10000 + systemMonth * 100 + systemDay;
}

//**********Validations used for Creating Reservation************
int validateNumAttendees(int num_attendees)
{
    bool notANum = true;
    bool isNegativeZero = true;
    bool excessDigits = true;
    int count;
    int num;
    do
    {
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            num_attendees = 0;
            cout << "             Error! Number of Attendees can only be a numeric whole number!\n";
            cout << "             Enter the Number of Attendees (Max 3 digits): ";
            cin >> num_attendees;
        }
        cin.ignore(100, '\n');
        notANum = false;

        if (num_attendees <= 0)
        {
            cout << "             Error! Number of attendees cannot be negative or 0!\n";
            isNegativeZero = true;
        }
        else
            isNegativeZero = false;

        num = num_attendees;
        count = 0;
        do
        {
            num /= 10;
            count++;
        } while (num != 0);

        if (count > 3)
        {
            cout << "             Error! Number of attendees can only be 3 digits long!\n";
            excessDigits = true;
        }
        else
            excessDigits = false;

        if (excessDigits == true || isNegativeZero == true)
        {
            cout << "             Enter the Number of Attendees (Max 3 digits): ";
            cin >> num_attendees;
        }

    } while (excessDigits == true || isNegativeZero == true);
    return num_attendees;
}

char validateDurationType(char duration_type)
{
    bool validDurationType = false;
    do
    {
        switch (duration_type)
        {
        case 'A':
        case 'P':
        case 'F':
            validDurationType = true;
            break;
        default:
            validDurationType = false;
        }

        if (validDurationType == false)
        {
            cout << "             Error! Duration type can be either A, a, P, p, F or f!\n";
            cout << "             Enter Duration Type (A/P/F): ";
            cin.get(duration_type);
            duration_type = toupper(duration_type);
            cin.ignore(100, '\n');
        }
    } while (validDurationType == false);
    return duration_type;
}

int validateRDate(int RDate)
{
    bool InvalidRDateData = true;
    do
    {
        int length = 0;
        int firstDigit;
        int secondDigit;
        int thirdDigit;
        int fourthDigit;
        int fifthDigit;
        int sixthDigit;
        bool IllegalRDate = true;
        int Q1, Q2, Q3, Q4, Q5, Q6, R1, R2, R3, R4, R5, R6, YY, MM, DD, fullYear = 2000, ttlDays;
        bool YearValid = false, MonthValid = false, DayValid = false, leapYear = true;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            RDate = 0;
            cout << "             Error! Date can only be a numeric whole number!\n";
            cout << "             Enter Reservation Date (Format: YYMMDD): ";
            cin >> RDate;
        }
        cin.ignore(100, '\n');
        IllegalRDate = false;

        bool LengthyRDate = check_RDate_length(RDate, &length);

        if (LengthyRDate == false)
        {
            Q1 = RDate / 10;
            R1 = RDate % 10;
            sixthDigit = R1;
            Q2 = Q1 / 10;
            R2 = Q1 % 10;
            fifthDigit = R2;
            Q3 = Q2 / 10;
            R3 = Q2 % 10;
            fourthDigit = R3;
            Q4 = Q3 / 10;
            R4 = Q3 % 10;
            thirdDigit = R4;
            Q5 = Q4 / 10;
            R5 = Q4 % 10;
            secondDigit = R5;
            Q6 = Q5 / 10;
            R6 = Q5 % 10;
            firstDigit = R6;

            YY = firstDigit * 10 + secondDigit;
            MM = thirdDigit * 10 + fourthDigit;
            DD = fifthDigit * 10 + sixthDigit;

            if (YY >= (systemYear - 2000))
            {
                YearValid = true;
                fullYear += YY;
                if (fullYear % 4 == 0)
                {
                    if (fullYear % 100 == 0)
                    {
                        if (fullYear % 400 == 0)
                        {
                            leapYear = true;
                        }
                        else
                        {
                            leapYear = false;
                        }
                    }
                    else
                    {
                        leapYear = true;
                    }
                }
                else
                {
                    leapYear = false;
                }
            }
            else
            {
                cout << "             Error! Year of Reservation Date must not be before Year of Entry Date!\n";
                YearValid = false;
            }

            if (MM >= 1 && MM <= 12)
                MonthValid = true;
            if (DD >= 1 && DD <= 31)
            {
                if (MM == 2)
                {
                    if (DD <= 29 && leapYear == true)
                    {
                        DayValid = true;
                    }
                    else if (DD <= 28 && leapYear == false)
                    {
                        DayValid = true;
                    }
                    else
                        DayValid = false;
                }
                else
                {
                    switch (MM)
                    {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        ttlDays = 31;
                        break;
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        ttlDays = 30;
                        break;
                    }
                    if (DD <= ttlDays)
                        DayValid = true;
                    else
                        DayValid = false;
                }
            }
        }
        if (DayValid == true && MonthValid == true && YearValid == true)
        {
            if (fullYear > systemYear)
                InvalidRDateData = false;
            else if (fullYear == systemYear)
            {
                if (MM > systemMonth)
                {
                    InvalidRDateData = false;
                }
                else if (MM == systemMonth)
                {
                    if (DD > systemDay)
                        InvalidRDateData = false;
                    else
                    {
                        InvalidRDateData = true;
                        cout << "             Error! Day of Reservation Date must be at least 1 day after Day of Entry Date!\n";
                        cout << "             Enter Reservation Date (Format: YYMMDD): ";
                        cin >> RDate;
                    }
                }
                else
                {
                    InvalidRDateData = true;
                    cout << "             Error! Month of Reservation Date must not be before Month of Entry Date!\n";
                    cout << "             Enter Reservation Date (Format: YYMMDD): ";
                    cin >> RDate;
                }
            }
        }
        else
        {
            cout << "             Error! Reservation Date must be 6 digits long with the format YYMMDD!\n";
            cout << "             Enter Reservation Date (Format: YYMMDD): ";
            cin >> RDate;
        }
    } while (InvalidRDateData == true);
    return RDate;
}

int validateRDate_enquiry(int ResDate)
{
    bool InvalidRDateData = true;
    do
    {
        int length = 0;
        int firstDigit;
        int secondDigit;
        int thirdDigit;
        int fourthDigit;
        int fifthDigit;
        int sixthDigit;
        bool IllegalRDate = true;
        int Q1, Q2, Q3, Q4, Q5, Q6, R1, R2, R3, R4, R5, R6, YY, MM, DD, fullYear = 2000, ttlDays;
        bool YearValid = false, MonthValid = false, DayValid = false, leapYear = true;

        while (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            ResDate = 0;
            cout << "                      Error! Date can only be a numeric whole number!\n";
            cout << "                      Enter Reservation Date (Format: YYMMDD): ";
            cin >> ResDate;
        }
        cin.ignore(100, '\n');
        IllegalRDate = false;

        bool LengthyRDate = check_RDate_length(ResDate, &length);

        if (LengthyRDate == false)
        {
            Q1 = ResDate / 10;
            R1 = ResDate % 10;
            sixthDigit = R1;
            Q2 = Q1 / 10;
            R2 = Q1 % 10;
            fifthDigit = R2;
            Q3 = Q2 / 10;
            R3 = Q2 % 10;
            fourthDigit = R3;
            Q4 = Q3 / 10;
            R4 = Q3 % 10;
            thirdDigit = R4;
            Q5 = Q4 / 10;
            R5 = Q4 % 10;
            secondDigit = R5;
            Q6 = Q5 / 10;
            R6 = Q5 % 10;
            firstDigit = R6;

            YY = firstDigit * 10 + secondDigit;
            MM = thirdDigit * 10 + fourthDigit;
            DD = fifthDigit * 10 + sixthDigit;

            if (YY >= 0)
            {
                YearValid = true;
                fullYear += YY;
                if (fullYear % 4 == 0)
                {
                    if (fullYear % 100 == 0)
                    {
                        if (fullYear % 400 == 0)
                        {
                            leapYear = true;
                        }
                        else
                        {
                            leapYear = false;
                        }
                    }
                    else
                    {
                        leapYear = true;
                    }
                }
                else
                {
                    leapYear = false;
                }
            }
            else
            {
                cout << "                      Error! Year of Reservation Date must not be a negative number!\n";
                YearValid = false;
            }

            if (MM >= 1 && MM <= 12)
                MonthValid = true;
            if (DD >= 1 && DD <= 31)
            {
                if (MM == 2)
                {
                    if (DD <= 29 && leapYear == true)
                    {
                        DayValid = true;
                    }
                    else if (DD <= 28 && leapYear == false)
                    {
                        DayValid = true;
                    }
                    else
                        DayValid = false;
                }
                else
                {
                    switch (MM)
                    {
                    case 1:
                    case 3:
                    case 5:
                    case 7:
                    case 8:
                    case 10:
                    case 12:
                        ttlDays = 31;
                        break;
                    case 4:
                    case 6:
                    case 9:
                    case 11:
                        ttlDays = 30;
                        break;
                    }
                    if (DD <= ttlDays)
                        DayValid = true;
                    else
                        DayValid = false;
                }
            }
        }
        if (DayValid == true && MonthValid == true && YearValid == true)
        {
            InvalidRDateData = false;
        }
        else
        {
            cout << "                      Error! Reservation Date must be 6 digits long with the format YYMMDD!\n";
            cout << "                      Enter Reservation Date (Format: YYMMDD): ";
            cin >> ResDate;
        }
    } while (InvalidRDateData == true);
    return ResDate;
}

bool check_RDate_length(int RDate, int *Length)
{
    int num = RDate;
    int count = 0;

    do
    {
        num /= 10;
        count++;
    } while (num != 0);

    *Length = count;

    if (count == 6)
        return false;
    else
        return true;
}

long long validateContactNum(long long contactNum)
{
    int length = 0;
    int firstDigit;
    int secondDigit;
    bool IllegalContactNum = true;

    while (cin.fail())
    {
        cin.clear();
        cin.ignore(100, '\n');
        contactNum = 0;
        cout << "             Error! Contact Number can only be a numeric whole number!\n";
        cout << "             Enter customer's contact number (Max:11 or 12 characters): ";
        cin >> contactNum;
    }

    cin.ignore(100, '\n');

    IllegalContactNum = false;

    bool LengthyContactNum = check_contactno_length(contactNum, &length);
    bool frontPartInvalid = true;
    if (length == 11)
    {
        firstDigit = contactNum / 10000000000;
        secondDigit = (contactNum % 10000000000) / 1000000000;
    }
    else if (length == 12)
    {
        firstDigit = contactNum / 100000000000;
        secondDigit = (contactNum % 100000000000) / 10000000000;
    }
    else
    {
        long long firstDivision = 10;
        long long secondDivision = 10;

        for (int i = 1; i < length - 1; i++)
        {
            firstDivision *= 10;
        }

        for (int j = 1; j < length - 2; j++)
        {
            secondDivision *= 10;
        }

        firstDigit = contactNum / firstDivision;
        secondDigit = (contactNum % firstDivision) / secondDivision;
    }

    if ((firstDigit == 6 && secondDigit == 0))
        frontPartInvalid = false;
    else
        frontPartInvalid = true;

    while (LengthyContactNum == true || frontPartInvalid == true)
    {
        if (LengthyContactNum == true)
            cout << "             Error! Contact Number must be 11 or 12 digits long!\n";
        if (frontPartInvalid == true)
            cout << "             Error! Contact Number must begin with 60!\n";
        cout << "             Enter customer's contact number (Max:11 or 12 characters): ";
        cin >> contactNum;
        IllegalContactNum = true;
        while (cin.fail())
        {
            cin.clear();
            cin.ignore(100, '\n');
            contactNum = 0;
            cout << "             Error! Contact Number can only be a numeric whole number!\n";
            cout << "             Enter customer's contact number (Max:11 or 12 characters): ";
            cin >> contactNum;
        }

        cin.ignore(100, '\n');
        IllegalContactNum = false;

        LengthyContactNum = check_contactno_length(contactNum, &length);
        if (length == 11)
        {
            firstDigit = contactNum / 10000000000;
            secondDigit = (contactNum % 10000000000) / 1000000000;
        }
        else if (length == 12)
        {
            firstDigit = contactNum / 100000000000;
            secondDigit = (contactNum % 100000000000) / 10000000000;
        }
        else
        {
            long long firstDivision = 10;
            long long secondDivision = 10;

            for (int i = 1; i < length - 1; i++)
            {
                firstDivision *= 10;
            }

            for (int j = 1; j < length - 2; j++)
            {
                secondDivision *= 10;
            }

            firstDigit = contactNum / firstDivision;
            secondDigit = (contactNum % firstDivision) / secondDivision;
        }

        if ((firstDigit == 6 && secondDigit == 0))
            frontPartInvalid = false;
        else
            frontPartInvalid = true;
    }
    return contactNum;
}

string validateCustName(string custName, int custNameLength)
{
    bool LengthyName = check_string_length(custName, custNameLength);
    bool IllegalName = check_illegal_char_string(custName);

    while (LengthyName == true || IllegalName == true)
    {
        cout << "             Error! Name must not exceed 20 characters and must not contain illegal characters!\n";
        cout << "             Enter customer's name (Max:20 characters): ";
        cin >> custName;

        LengthyName = check_string_length(custName, custNameLength);
        IllegalName = check_illegal_char_string(custName);
    }
    return custName;
}
bool check_contactno_length(long long Input, int *Length)
{
    long long num = Input;
    int count = 0;
    do
    {
        num /= 10;
        count++;
    } while (num != 0);

    *Length = count;

    if (count == 11 || count == 12)
        return false;
    else
        return true;
}

bool check_string_length(string Input, int InputLength)
{
    if (Input.length() > InputLength)
        return true;
    else
        return false;
}

bool check_illegal_char_string(string Input)
{
    bool result;
    char illegalChars[42] = {'1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '`', '~', '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_', '+', '=', '[', '{', ']', '}', '|', '\\', ':', ';', '\'', '/', '?', '.', '>', '<', ',', '\"'};
    for (int i = 0; i < Input.length(); i++)
    {
        for (int j = 0; j < 42; j++)
        {
            if (Input.at(i) == illegalChars[j])
            {
                result = true;
                break;
            }
            else if ((Input.at(i) != illegalChars[j]) && (j == 41))
                result = false;
        }
        if (result == true)
            break;
    }
    return result;
}
//*************end of validations****************

//***********************MENUS*********************************
// Main Menu
void mainMenu()
{
    system("CLS"); // Clears screen
    cout << endl;
    int choice;
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    cout << "             |                                      MAIN MENU                                            |\n";
    cout << "             ---------------------------------------------------------------------------------------------\n";
    cout << "             |                             1. Process Reservation                                        |\n";
    cout << "             |                             2. Enquiries                                                  |\n";
    cout << "             |                             3. Reports                                                    |\n";
    cout << "             |                             4. Exit                                                       |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    do
    {
        cout << "                                Enter your choice: -> "; // Get user's choice for menu option
        cin >> choice;
        cin.ignore(100, '\n');
        if (cin.fail()) // If user doesnt enter an integer
        {
            cin.clear();           // clear failed state
            cin.ignore(100, '\n'); // ignore next 100 chars or until it encounters newline
            choice = 0;
            cout << "                                Error! Please enter number only.\n"; // display error message
        }
        else if (choice != 1 && choice != 2 && choice != 3 && choice != 4)                                 // if choice is not from menu
            cout << "                                Error! Please enter a number from the menu above.\n"; // display error message
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4);                                    // prompt as long as choice is invalid

    // If user's choice is valid, call the respective function
    switch (choice)
    {
    case 1:
        cout << "\n\n";
        reserveProcessMenu(); // Go Process Reservation
        break;
    case 2:
        cout << "\n\n";
        enquiriesMenu(); // Go to Enquiries
        break;
    case 3:
        cout << "\n\n";
        reportsMenu(); // Go to Reports
        break;
    case 4:
        cout << "\n\n";
        endingScreen(); // Go to Ending Screen
        break;
    }
}

// Process Reservation Menu
void reserveProcessMenu()
{
    system("CLS");
    cout << endl;
    int choice;
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    cout << "             |                                      PROCESS RESERVATION                                  |\n";
    cout << "             ---------------------------------------------------------------------------------------------\n";
    cout << "             |                             1. Create Reservation                                         |\n";
    cout << "             |                             2. Confirm Reservation                                        |\n";
    cout << "             |                             3. Cancel Reservation                                         |\n";
    cout << "             |                             4. Room Price Maintenance                                     |\n";
    cout << "             |                             5. Return to Main Menu                                        |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    do
    {
        cout << "                                Enter your choice: -> "; // Get user's choice for menu option
        cin >> choice;
        cin.ignore(100, '\n');
        if (cin.fail()) // If user doesnt enter an integer
        {
            cin.clear();           // clear input failed state
            cin.ignore(100, '\n'); // ignore next 100 chars or until it encounters newline
            choice = 0;
            cout << "                                Error! Please enter number only.\n"; // display error message
        }
        else if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5) // if choice is not from menu
            cout << "                                Error! Please enter a number from the menu above.\n";
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5); // prompts as long as choice is invalid

    // If user's choice is valid, call the respective function
    switch (choice)
    {
    case 1:
        cout << "\n\n";
        createReservation();
        break;
    case 2:
        cout << "\n\n";
        mainMenu();
        break;
    case 3:
        cout << "\n\n";
        cancelReservation();
        break;
    case 4:
        cout << "\n\n";
        roomPriceMaintenance();
        break;
    case 5:
        cout << "\n\n";
        mainMenu();
        break;
    }
}

// Enquiries Menu
void enquiriesMenu()
{
    system("CLS");
    cout << endl;
    int choice;
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    cout << "             |                                        ENQUIRIES                                          |\n";
    cout << "             ---------------------------------------------------------------------------------------------\n";
    cout << "             |                        1. Check Room Availability                                         |\n";
    cout << "             |                        2. View Reservation Details                                        |\n";
    cout << "             |                        3. Display Rooms Information                                       |\n";
    cout << "             |                        4. Reservations for Given Date                                     |\n";
    cout << "             |                        5. Find Reservations by Customer Name                              |\n";
    cout << "             |                        6. Find Reservations by Contact Number                             |\n";
    cout << "             |                        7. Return to Main Menu                                             |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    do
    {
        cout << "                                Enter your choice: -> "; // Get user's choice for menu option
        cin >> choice;
        cin.ignore(100, '\n');
        if (cin.fail()) // If user doesnt enter an integer
        {
            cin.clear();           // clear failed state
            cin.ignore(100, '\n'); // ignore next 100 chars or until it encounters newline
            choice = 0;
            cout << "                                Error! Please enter number only.\n"; // display error message
        }
        else if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7) // if choice is not from menu
            cout << "                                Error! Please enter a number from the menu above.\n";              // display error message
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5 && choice != 6 && choice != 7);    // prompt as long as choice is invalid
    // if user's choice is valid, call the respective function
    switch (choice)
    {
    case 1:
        cout << "\n\n";
        checkAvailability(); // Go to Check Room Availability
        break;
    case 2:
        cout << "\n\n";
        viewDetail();
        break;
    case 3:
        cout << "\n\n";
        DisplayRoomInformation(); // Call function
        break;
    case 4:
        cout << "\n\n";
        ReservForDate(); // Go to Reservations for Given Date
        break;
    case 5:
        cout << "\n\n";
        searchbyCustName();
        break;
    case 6:
        cout << "\n\n";
        searchbyContactNo();
        break;
    case 7:
        cout << "\n\n";
        mainMenu();
        break;
    }
}

// Reports Menu
void reportsMenu()
{
    system("CLS");
    cout << endl;
    int choice;
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    cout << "             |                                         REPORTS                                           |\n";
    cout << "             ---------------------------------------------------------------------------------------------\n";
    cout << "             |                          1. New Reservations Entered Today                                |\n";
    cout << "             |                          2. Revenue by Customer                                           |\n";
    cout << "             |                          3. Monthly Revenue for given Year - Summary                      |\n";
    cout << "             |                          4. Revenue for given Month and Year - Detailed                   |\n";
    cout << "             |                          5. Return to Main Menu                                           |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    do
    {
        cout << "                                Enter your choice: -> "; // Get user's choice for menu option
        cin >> choice;
        cin.ignore(100, '\n');
        if (cin.fail()) // If user doesnt enter an integer
        {
            cin.clear();           // clear failed state
            cin.ignore(100, '\n'); // ignore next 100 chars or until it encounters newline
            choice = 0;
            cout << "                                Error! Please enter number only.\n"; // display error message
        }
        else if (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5)                  // if choice is not from menu
            cout << "                                Error! Please enter a number from the menu above.\n"; // display error message
    } while (choice != 1 && choice != 2 && choice != 3 && choice != 4 && choice != 5);                     // prompt as long as choice is invalid

    // If user's choice is valid, call the respective function
    switch (choice)
    {
    case 1:
        cout << "\n\n";
        mainMenu();
        break;
    case 2:
        cout << "\n\n";
        revenuebycustomer();
        break;
    case 3:
        cout << "\n\n";
        monthlyRevenueGivenYear();
        break;
    case 4:
        cout << "\n\n";
        revForMonthAndYear();
        break;
    case 5:
        cout << "\n\n";
        mainMenu();
        break;
    }
}

//**********************END OF MENUS**************************
//*****************PROCESS RESERVATION************************

void roomPriceMaintenance()
{
    system("CLS");
    cout << endl;
    bool changeMorePrice = true; // Predetermines that user wants to change room price
    char contChangeMorePrice;    // Get user's choice whether to continue changing room price
    long recNo;                  // Later used for the user to select record to edit
    cout << "             o===========================================================================================o\n";
    cout << "             |                                     Room Price Maintenance                                |\n";
    cout << "             =============================================================================================\n";
    cout << "             |                       This module allows room prices to be updated.                       |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    while (changeMorePrice) // while user wants to change room prices
    {
        Room roomRec;       // struct for reading each record from room file
        long recNumber = 0; // Record Number displayed will start from 1

        // Open Room File in binary mode for both input and output
        fstream roomFil("room.dat", ios::in | ios::out | ios::binary);

        if (roomFil.is_open() == false) // if there is an error in opening file
        {
            cout << "                                Error in opening Room File!\n"; // display error message
            exit(EXIT_FAILURE);                                                      // exit program
        }

        roomFil.read((char *)&roomRec, sizeof(Room)); // read a record from room file
        cout << endl;                                 // Display headers for table displaying room info
        cout << "                                Record No. Room Code Room Name Capacity Price FD (RM)\n";
        cout << "                                ---------- --------- --------- -------- -------------\n";
        while (!roomFil.eof()) // while havent reached end of file
        {
            recNumber++; // Increment recNumber by 1
            // Display details for each room
            cout << "                                " << setw(5) << recNumber << setw(11) << roomRec.roomCode << left << "     " << setw(10) << roomRec.roomName << right << setw(5) << roomRec.capacity << setw(10) << roomRec.price << endl;
            roomFil.read((char *)&roomRec, sizeof(Room)); // read another record from room file
        }

        cout << endl;
        // Get the roomRec number of the desired roomRec.
        do
        {
            cout << "                                Please select the Record Number for the room that you want to update price: ";
            cin >> recNo; // Get desired record number
            cin.ignore(100, '\n');
            if (cin.fail()) // If input is not an integer
            {
                cin.clear();           // clear input failed state
                cin.ignore(100, '\n'); // ignore the next 100 chars or until it encounters newline
                recNo = -1;
                cout << "                                Error! Record Number must be a numeric whole number!\n"; // Display error message
            }
            else if (recNo < 0 || recNo > recNumber)                                                                            // if record number is not within acceptable range
                cout << "                                Error! Record Number must be in the range 1 to " << recNumber << endl; // Display error message
        } while (recNo < 0 || recNo > recNumber);                                                                               // prompts as long as input is invalid

        roomFil.clear();             // Clear eof flag
        roomFil.seekg(0L, ios::beg); // Move read file pointer to the beginning of file

        // Move read file pointer to the beginning of the selected record and read it.
        roomFil.seekg((recNo - 1) * sizeof(roomRec), ios_base::beg);
        roomFil.read((char *)&roomRec, sizeof(Room));

        // Displays the selected Room info
        cout << endl;
        cout << "                                Details about the Room\n";
        cout << "                                ----------------------\n";
        cout << "                                1) Room Code: ";
        cout << roomRec.roomCode << endl;
        cout << "                                2) Room Name: ";
        cout << roomRec.roomName << endl;
        cout << "                                3) Capacity: ";
        cout << roomRec.capacity << endl;
        cout << "                                4) Price (Full Day): RM";
        cout << roomRec.price << endl;

        cout << endl;
        do
        {
            cout << "                                Please enter the new Price: RM ";
            cin >> roomRec.price; // Prompt user for the New Price
            cin.ignore(100, '\n');
            if (cin.fail()) // if input is not an integer
            {
                cin.clear();           // clear input failed state
                cin.ignore(100, '\n'); // ignore the next 100 chars or until it encounters newline
                roomRec.price = -1;
                cout << "                                Error! Price must be a numeric whole number!\n"; // Display error message
            }
            else if (roomRec.price <= 0)                                                    // If price is 0 or negative
                cout << "                                Error! Price must be positive!\n"; // Display error message
        } while (roomRec.price <= 0);                                                       // prompts as long as price is invalid

        // Move write file pointer back to the beginning of this roomRec's position.
        roomFil.seekp((recNo - 1) * sizeof(roomRec), ios::beg);

        // Write the new roomRec over the current roomRec.
        roomFil.write(reinterpret_cast<char *>(&roomRec), sizeof(Room));

        if (!roomFil)                                                                   // if there is an error in writing to file
            cout << "                                Error in writing to Room File!\n"; // display error message
        else                                                                            // else display success message
            cout << "                                **Successfully updated the Room Price!**\n";

        // Move read file pointer to the beginning of the selected record.
        roomFil.seekg(0L, ios_base::beg);

        recNumber = 0; // reset value of recNumber

        roomFil.read((char *)&roomRec, sizeof(Room)); // Read a record from room file
        // Display headers for table displaying updated room info
        cout << endl
             << "                                Updated Room Records\n";
        cout << "                                Record No. Room Code Room Name Capacity Price FD (RM)\n";
        cout << "                                ---------- --------- --------- -------- -------------\n";
        while (!roomFil.eof()) // while havent reached end of line
        {
            recNumber++; // Increment recNumber by 1
            // Display details for each room
            cout << "                                " << setw(5) << recNumber << setw(11) << roomRec.roomCode << left << "     " << setw(10) << roomRec.roomName << right << setw(5) << roomRec.capacity << setw(10) << roomRec.price << endl;
            roomFil.read((char *)&roomRec, sizeof(Room)); // Read another record from room file
        }

        roomFil.clear();             // clear eof flag
        roomFil.seekg(0L, ios::beg); // move read file pointer to beginning of file

        roomFil.close(); // close file

        do
        {
            cout << endl;
            cout << "                                Would you like to change the price of another room (Y/N)?: ";
            cin >> contChangeMorePrice; // Get user's choice whether to change more room prices
            cin.ignore(100, '\n');
            if (contChangeMorePrice != 'Y' && contChangeMorePrice != 'y' && contChangeMorePrice != 'N' && contChangeMorePrice != 'n')   // if user's choice is invalid
                cout << "                                Error! You can only enter Y, y, N or n! Please try again!\n";                  // display error message
        } while (contChangeMorePrice != 'Y' && contChangeMorePrice != 'y' && contChangeMorePrice != 'N' && contChangeMorePrice != 'n'); // prompts as long as input is invalid

        Room resetRoomRec;      // declare a variable of struct type
        roomRec = resetRoomRec; // reset the values of the struct above with resetRoomRec
        // if user's choice is valid
        switch (contChangeMorePrice)
        {
        case 'Y': // if user wants to change another room's price
        case 'y':
            changeMorePrice = true;
            cout << endl;
            break;
        case 'N': // if user doesnt want to change another room's price
        case 'n':
            changeMorePrice = false;
            break;
        }
    }
    cout << "                      ";
    system("pause");
    cout << endl;
    reserveProcessMenu(); // Go back to Process Reservation Menu
}

void createReservation()
{
    system("CLS");
    cout << endl;
    string CustName;               // To store customer name temporarily
    long long ContactNumber;       // To store contact number temporarily
    int ReservationDate;           // To store desired reservation date temporarily
    char DurationType;             // To store desired duration type temporarily
    int NumAttendees;              // To store number of attendees temporarily
    char EventDesc[41];            // To store event description temporarily
    char RoomCode;                 // To store desired room code temporarily
    int OrigPrice;                 // To store initial price to be paid for room
    bool createReservation = true; // Predetermines that user wants to create reservation for customer
    int num_reserv_created = 0;    // Keeps track of number of reservations created
    char contCreateReserv;         // whether user wants to continue creating reservation

    cout << "             o===========================================================================================o\n";
    cout << "             |                                    Create Reservation                                     |\n";
    cout << "             =============================================================================================\n";
    cout << "             |           To create a reservation, the customer must provide the following details:       |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    while (createReservation) // While creating reservation
    {
        bool invalidRoomCode = true; // By default, indicate that room code entered is invalid

        if (contCreateReserv != 'Y' && contCreateReserv != 'y') // if user is not creating reservation for the first time
        {
            cout << "             Enter customer's name (Max:20 characters): ";
            getline(cin, CustName);                    // Get Customer Name
            CustName = validateCustName(CustName, 20); // Validate Customer Name
            cout << endl;

            cout << "             Enter customer's contact number (Max:11 or 12 characters): ";
            cin >> ContactNumber;                              // Get contact numner
            ContactNumber = validateContactNum(ContactNumber); // Validate Contact Number
            cout << endl;
        }

        cout << "             Enter the Number of Attendees (Max 3 digits): ";
        cin >> NumAttendees;                               // Get number of attendees
        NumAttendees = validateNumAttendees(NumAttendees); // Validate Number of Attendees
        cout << endl;

        cout << "             Enter Event Description: ";
        cin.getline(EventDesc, 41); // Get event description
        cout << endl;

        cout << "             Enter Reservation Date (Format: YYMMDD): ";
        cin >> ReservationDate;                           // Get Reservation Date
        ReservationDate = validateRDate(ReservationDate); // Validate reservation date
        cout << endl;

        cout << "             Enter Duration Type (A=AM  P=PM  F=Full Day): ";
        cin.get(DurationType);                // Get duration type
        DurationType = toupper(DurationType); // Capitalise duration type
        cin.ignore(100, '\n');
        DurationType = validateDurationType(DurationType); // Validate duration type
        cout << endl;

        // will be used to create an array of struct to store room details that initially are suitable for customer
        struct ReqDateRooms
        {
            char roomCode;
            char roomName[11];
            int capacity;
            int price;
            char AM;
            char PM;
            char FD;
        };
        // will be used to create an array of struct to store rooms that are available and suitable for customer
        struct AvailRoom
        {
            char roomCode;
            char roomName[11];
            int capacity;
            int price;
        };

        // Open Room File in binary mode for input
        ifstream fin("room.dat", ios_base::in | ios_base::binary);
        Room room;                            // Declare room variable of struct type
        ReqDateRooms suitableRoom[MAX_ROOMS]; // Declare suitableRoom as an array of struct
        if (fin.is_open() == false)           // if error in opening file
        {
            cout << "             Error in opening Room File!\n"; // display error message
            exit(EXIT_FAILURE);                                   // exit program
        }

        int noInserted = 0;                                      // to keep track of the number of records read from file and placed in array of struct
        fin.read(reinterpret_cast<char *>(&room), sizeof(Room)); // Read a record from room file

        while (!fin.eof()) // while havent reached end of line
        {
            if (NumAttendees <= room.capacity) // if number of attendees is less than or equal to room capacity
            {
                // Store record in suitableRoom array of struct
                suitableRoom[noInserted].roomCode = room.roomCode;
                strcpy(suitableRoom[noInserted].roomName, room.roomName);
                suitableRoom[noInserted].capacity = room.capacity;
                suitableRoom[noInserted].price = room.price;
                // By default, set available for all 3 duration types
                suitableRoom[noInserted].AM = 'A';
                suitableRoom[noInserted].PM = 'A';
                suitableRoom[noInserted].FD = 'A';
                noInserted++; // Increment  number of records inserted by 1
            }
            fin.read(reinterpret_cast<char *>(&room), sizeof(Room)); // Read another record from room file
        }

        fin.close(); // Close fin
        // Open Reservation File in binary mode for input
        ifstream reserv("reservation.dat", ios_base::in | ios_base::binary);
        Reservation curReserv;
        if (reserv.is_open() == false) // if error in opening file
        {
            cout << "             Error in opening Reservation File!\n"; // Display error message
            exit(EXIT_FAILURE);                                          // Exit the program
        }
        //
        int NumRecRead = 0;                                                     // keep track of the number of records read
        reserv.read(reinterpret_cast<char *>(&curReserv), sizeof(Reservation)); // read record from reservation file

        while (!reserv.eof()) // while havent reached end of file
        {
            if (curReserv.reservDate == ReservationDate) // if desired reservation date matches reservation date in reservation file
            {
                if (curReserv.reservStatus != 'X') // if the reservation status of the reservation in file is not cancelled
                {
                    for (int k = 0; k < noInserted; k++) // this will update the availability of room type for particular duration types
                    {
                        if (curReserv.roomCode == suitableRoom[k].roomCode) // if the room code of reservation in file matches room code in array of struct
                        {
                            if (curReserv.durationType == 'A') // if the duration type of reservation in file is equal to A
                            {
                                suitableRoom[k].AM = 'U'; // Set the room as unavailable for AM & FUll day sessions
                                suitableRoom[k].FD = 'U';
                            }
                            else if (curReserv.durationType == 'P') // else if the duration type of reservation in file is equal to P
                            {
                                suitableRoom[k].FD = 'U'; // Set the room as unavailable for Full day & PM sessions
                                suitableRoom[k].PM = 'U';
                            }
                            else // else if duration type is F
                            {    // Set the room as unavaiable for all 3 duration types
                                suitableRoom[k].FD = 'U';
                                suitableRoom[k].AM = 'U';
                                suitableRoom[k].PM = 'U';
                            }
                        }
                    }
                }
            }
            NumRecRead++;                                                           // Increment number of records read by 1
            reserv.read(reinterpret_cast<char *>(&curReserv), sizeof(Reservation)); // Read record from reservation file
        }
        reserv.close(); // Close reservation file

        cout << endl;

        AvailRoom AvailableRooms[MAX_ROOMS]; // Declare an array of struct to hold available rooms

        int noAvailableRooms = 0; // To keep track of number of available rooms

        for (int l = 0; l < noInserted; l++)
        {
            if (DurationType == 'F') // if duration is full day
            {
                if (suitableRoom[l].FD == 'A') // if full day is available
                {                              // Store the room details in AvailableRooms array of struct
                    strcpy(AvailableRooms[noAvailableRooms].roomName, suitableRoom[l].roomName);
                    AvailableRooms[noAvailableRooms].roomCode = suitableRoom[l].roomCode;
                    AvailableRooms[noAvailableRooms].capacity = suitableRoom[l].capacity;
                    AvailableRooms[noAvailableRooms].price = suitableRoom[l].price;
                    noAvailableRooms++; // Increment the number of available rooms by 1
                }
            }
            else if (DurationType == 'A') // if duration is AM
            {
                if (suitableRoom[l].AM == 'A') // if a session is available
                {                              // Store the room details in AvailableRooms array of struct
                    strcpy(AvailableRooms[noAvailableRooms].roomName, suitableRoom[l].roomName);
                    AvailableRooms[noAvailableRooms].roomCode = suitableRoom[l].roomCode;
                    AvailableRooms[noAvailableRooms].capacity = suitableRoom[l].capacity;
                    AvailableRooms[noAvailableRooms].price = suitableRoom[l].price / 2;
                    noAvailableRooms++;
                }
            }
            else // if duration is PM
            {    // Store the room details in AvailableRooms array of struct
                if (suitableRoom[l].PM == 'A')
                {
                    strcpy(AvailableRooms[noAvailableRooms].roomName, suitableRoom[l].roomName);
                    AvailableRooms[noAvailableRooms].roomCode = suitableRoom[l].roomCode;
                    AvailableRooms[noAvailableRooms].capacity = suitableRoom[l].capacity;
                    AvailableRooms[noAvailableRooms].price = suitableRoom[l].price / 2;
                    noAvailableRooms++;
                }
            }
        }

        // if number of available rooms is greater than 0
        if (noAvailableRooms > 0)
        {
            cout << endl;
            // Display table headers for available rooms
            cout << "                            Available Rooms:\n";
            cout << "                 ---------  ---------    -----   --------\n";
            cout << "                 Room Code  Room Name    Price   Capacity\n";
            cout << "                 ---------  ---------    -----   --------\n";

            for (int j = 0; j < noAvailableRooms; j++)
            { // Display the records in AvailableRooms array of struct
                cout << left;
                cout << "                 " << setw(11) << AvailableRooms[j].roomCode << setw(13) << AvailableRooms[j].roomName << setw(9) << AvailableRooms[j].price << right << setw(4) << AvailableRooms[j].capacity << endl;
            }
            cout << endl;
        }

        while (invalidRoomCode == true && noAvailableRooms != 0) // While there are available rooms but user enters wrong room code
        {
            cout << "             Enter Room Code of selected room: ";
            cin >> RoomCode; // Get room code
            cin.ignore(100, '\n');
            RoomCode = toupper(RoomCode); // Capitalize room code
            for (int m = 0; m < noAvailableRooms; m++)
            {
                if (RoomCode == AvailableRooms[m].roomCode) // if the room code entered by customer is one of the room codes in the array of struct
                {
                    invalidRoomCode = false;             // indicate that the room code is valid
                    OrigPrice = AvailableRooms[m].price; // store the original price of the room before dividing by 2 if necessary
                    break;
                }
            }
            if (invalidRoomCode) // otherwise, display error message
                cout << "             Error! The Room Code entered is invalid! Please try again!\n";
        }

        if (noAvailableRooms > 0) // if number of available rooms is more than 0, it means that we can append the reservation to the reservation file
        {                         // Open reservation file in binary mode for appending
            cout << "             ** Reservation Request is Accepted! **\n";

            ofstream appendReserv("reservation.dat", ios_base::app | ios_base::binary);

            Reservation newReserv; // struct to hold the reservation details

            string ReservDate = to_string(ReservationDate); // convert reservation date from integer to string

            char reservDate_arr[6]; // to hold the reservation date using char data type

            char reservationCode_arr[8]; // to hold the reservation code using char data tyoe

            strcpy(reservDate_arr, ReservDate.c_str()); // convert the reservation date from string to char and copy it to the char array

            strcpy(reservationCode_arr, reservDate_arr); // copy the reservation date char array into the reservation code array

            char DR[3] = {DurationType, RoomCode}; // merge duration type and room code

            strcat(reservationCode_arr, DR); // append DR into reservation code

            strcpy(newReserv.reservCode, reservationCode_arr); // store the char array of reservation code into the struct

            newReserv.reservDate = ReservationDate; // store the reservation date into the struct

            newReserv.durationType = DurationType; // store the duration type into the struct

            newReserv.roomCode = RoomCode; // store the room code into the struct

            newReserv.noOfAttendees = NumAttendees; // store the number of attendees into the struct

            newReserv.actualPrice = OrigPrice; // store the original price into the struct

            char custname_array[21]; // to hold the customer name using char array

            strcpy(custname_array, CustName.c_str()); // convert customer name from string to char and store into the custname_array

            for (int i = 0; i < 21; i++)
            {
                custname_array[i] = toupper(custname_array[i]); // capitalise each character in the customer name
            }

            strcpy(newReserv.custName, custname_array); // store the customer name into the struct

            newReserv.contactNo = ContactNumber; // store the contact number into the struct

            strcpy(newReserv.eventDescription, EventDesc); // store the event description in the struct

            newReserv.reservStatus = 'R'; // store the 'R' reservation status into the struct

            newReserv.dataEntryDate = formattedSystemDate; // store the data entry date into the struct

            appendReserv.write((char *)&newReserv, sizeof(Reservation));        // write the reservation record into the reservation file
            if (!appendReserv)                                                  // if error in writing to reservation file
                cout << "             Error in writing to Reservation File!\n"; // display error message
            else
            {
                cout << "             ** Successfully created Reservation for the customer! **\n"; // otherwise, display success messaga
                num_reserv_created++;                                                              // increment the number of created reservations by 1
            }
            appendReserv.close();
        }
        else // else if there are no available rooms, inform the user
        {
            cout << "             ** Reservation request is Rejected! No rooms available for the date and duration type specified! **\n";
        }

        do
        {
            cout << "             Would you like to create another reservation for the SAME customer (Y/N)?: ";
            cin >> contCreateReserv;                                                                                        // Get user's choice whether to create another reservation for the same customer
            cin.ignore(100, '\n');                                                                                          // Ignore the next 100 chars or until it encounters a newline
            if (contCreateReserv != 'Y' && contCreateReserv != 'y' && contCreateReserv != 'N' && contCreateReserv != 'n')   // if choice is invalid
                cout << "             Error! You can only enter Y, y, N or n! Please try again!\n";                         // display error message
        } while (contCreateReserv != 'Y' && contCreateReserv != 'y' && contCreateReserv != 'N' && contCreateReserv != 'n'); // prompts as long as choice is invalid
        // reset the values in the suitableRoom array of struct
        for (int x = 0; x < noInserted; x++)
        {
            suitableRoom[x].roomCode = ' ';
            for (int x1 = 0; x1 < 11; x1++)
            {
                suitableRoom[x].roomName[x1] = ' ';
            }
            suitableRoom[x].capacity = 0;
            suitableRoom[x].price = 0;
            suitableRoom[x].AM = ' ';
            suitableRoom[x].PM = ' ';
            suitableRoom[x].FD = ' ';
        }
        // reset the values in the AvailableRooms array of struct
        for (int y = 0; y < noAvailableRooms; y++)
        {
            AvailableRooms[y].roomCode = ' ';
            for (int y1 = 0; y1 < 11; y1++)
            {
                AvailableRooms[y].roomName[y1] = ' ';
            }
            AvailableRooms[y].capacity = 0;
            AvailableRooms[y].price = 0;
        }

        switch (contCreateReserv)
        {
        case 'Y': // if user wants to create another reservation
        case 'y':
            createReservation = true; // while loop will reiterate
            cout << endl;
            break;
        case 'N': // else if user doesnt want to create another reservation
        case 'n':
            createReservation = false; // while loop will not reiterate
            break;
        }
    }
    if (num_reserv_created > 0) // if user managed to create any reservation(s) successfully, prompt user to remind customer to confirm reservation
        cout << "             Please remind the customer to confirm the reservation(s) at least 1 day before the event.\n";
    cout << "\n\n";
    cout << "                      ";
    system("pause");
    cout << endl;
    reserveProcessMenu(); // go to Process Reservation Menu
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
        system("CLS");
        cout << "             o===========================================================================================o\n";
        cout << "             |                                    Cancel Reservation                                     |\n";
        cout << "             =============================================================================================\n";
        cout << "             |              This module searches for reservation by entering Reservation Code.           |\n";
        cout << "             |              [To Exit, Please Enter 0]                                                    |\n";
        cout << "             o-------------------------------------------------------------------------------------------o\n";

        // Display Message
        cout << "                                To exit, please press 0\n";
        cout << "                                Enter Reservation Code: ";
        cin >> cancelCode;
        if (cancelCode[0] == '0') // If user enter '0' as first character and press enter
        {
            cout << "                                Jump to Process Reservation Menu\n"; // Display message and direct user back to process menu
            cout << "                      ";
            system("pause");
            reserveProcessMenu();
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
                    cout << "\n\n                                Here are the details:\n";
                    cout << "                                Reservation Code"
                         << "\tName\tStatus\n";
                    cout << "                                ----------------------------------------------\n";
                    cout << "                                " << cancelReservationProcess.reservCode << "\t\t" << cancelReservationProcess.custName << "\t" << cancelStatus << "\n\n";

                    // Validate if reservation code has beed confirmed or cancelled before
                    if (cancelReservationProcess.reservStatus == 'C')
                    {
                        cout << "                                This Reservation has been confirmed. Unable to cancel this reservation.\n";
                        cout << "                      ";
                        system("pause");
                        cancelReservation();
                    }
                    else if (cancelReservationProcess.reservStatus == 'X')
                    {
                        cout << "                                This Reservation Has Been Cancelled. Please enter again.\n";
                        cout << "                      ";
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
                                     << "                                Are you sure to cancel your reservation?\n";
                                cout << "                                [Y - Yes] [N - No]\n                                Your Choice > ";
                                cin >> confirmCancel;
                                confirmCancel = toupper(confirmCancel); // make user input to Upper Case for further validation
                                if (confirmCancel == 'N')               //
                                {
                                    // Supposed to jump Jump back to process reservation
                                    cout << "                                OK.\n\n";
                                    cout << "                      ";
                                    system("pause");
                                    reserveProcessMenu();

                                    cancelLOOP = 0;
                                }
                                else if (confirmCancel == 'Y') // If yes, update data and change initial to 'X'
                                {
                                    cancelReservationProcess.reservStatus = 'X';
                                    cout << "\n                                Reservation Successfully Cancelled." << endl; // Display output message.
                                    cout << "\n                                Directing you back to Process Menu..." << endl;

                                    cancelLOOP = 1;
                                }
                                else
                                {
                                    cout << "                                Invalid Input. Please enter [Y/N] only!" << endl;

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
                cout << "                                Not Found!!!" << endl;

                do
                {
                    // Display message asking user if user wants to quit module or enter again
                    cout << endl
                         << "                                Do you want to enter another reservation code?" << endl;
                    cout << "                                [Y - Yes] [N - Direct Back to Process Menu]" << endl;
                    cout << "                                Your Choice > ";
                    cin >> cancelLoop2;                 // Get User Input
                    cancelLoop2 = toupper(cancelLoop2); // Make user input for furhter Validation
                    if (cancelLoop2 == 'Y')             // If user input 'Y'
                    {
                        cancelReservation(); // Loop cancel reservation module again
                    }
                    else if (cancelLoop2 == 'N') // Else if user input 'N'
                    {
                        cout << endl
                             << "                                Directing you back to Process Reservation Menu..." << endl;
                        cout << "                      ";
                        system("pause");
                        reserveProcessMenu(); // SUpposed to loop back to Process Menu
                    }
                    else // Else if user did not input Y or N
                    {
                        cout << "                                Invalid Input. Please enter [Y/N] only!" << endl;
                    }
                } while (cancelLoop2 != 'Y' || cancelLoop2 != 'N');
            }
            fbin.close(); // Close File
            cout << "                      ";
            system("pause");
            reserveProcessMenu();
        }
    }
}

//******************END OF PROCESS RESERVATION****************

//*****************ENQUIRIES**********************************

void ReservForDate()
{
    system("CLS");
    cout << endl;
    int reservDate;             // To hold the requested reservation date
    bool findMoreReserv = true; // predetermines that the user wants to find reservation(s)
    char contFindMoreReserv;    // to hold user's choice whether to continue finding more reservations

    cout << "             o===========================================================================================o\n";
    cout << "             |                                  Reservations for Given Date                              |\n";
    cout << "             =============================================================================================\n";
    cout << "             |                    This module displays reservations for a specific date.                 |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    Reservation reservForDate[20]; // an array of struct used to store reservation records that match the requested reservation date

    Reservation eachRecord; // a struct used to read each record from reservation file

    while (findMoreReserv) // while user wants to find reservation(s)
    {
        cout << "                      Enter Reservation Date (Format: YYMMDD): ";
        cin >> reservDate;                              // get reservation date
        reservDate = validateRDate_enquiry(reservDate); // validate reservation date
        // open reservation file in binary mode for input
        ifstream readReserv("reservation.dat", ios_base::in | ios_base::binary);

        if (readReserv.is_open() == false) // if there is an error in opening file
        {
            cout << "                      Error in opening Reservation File!\n"; // display error message
            exit(EXIT_FAILURE);                                                   // exit program
        }

        int noInserted = 0;                                                          // to keep track of the number of records inserted into the array of struct
        readReserv.read(reinterpret_cast<char *>(&eachRecord), sizeof(Reservation)); // read each record from reservation file into struct

        while (!readReserv.eof()) // while havent reached end of file
        {
            if (eachRecord.reservDate == reservDate) // if reservation date of record in file matches requested reservation date
            {
                reservForDate[noInserted] = eachRecord; // store the record in array of struct
                noInserted++;                           // increment the number of inserted records
            }
            readReserv.read(reinterpret_cast<char *>(&eachRecord), sizeof(Reservation)); // read another record from the reservation file into struct
        }

        readReserv.close(); // close reservation file

        int i, minCodeIndex;

        Reservation varTemp; // this struct will be used for swapping the elements in the array of struct
        // The following is a selection sort that sorts the reservations alphabetically by room code
        for (i = 0; i < (noInserted - 1); i++)
        {
            minCodeIndex = i;
            for (int j = i; j < noInserted; j++)
            {
                if (reservForDate[j].roomCode < reservForDate[minCodeIndex].roomCode)
                    minCodeIndex = j;
            }
            if (minCodeIndex != i)
            {
                varTemp = reservForDate[minCodeIndex];
                reservForDate[minCodeIndex] = reservForDate[i];
                reservForDate[i] = varTemp;
            }
        }
        // if reservations were found for the given date
        if (noInserted > 0)
        {
            cout << endl;
            // display table headers
            cout << "        --------- --------- -------------- -------------------- ------------- ------------- ---------------- ------\n";
            cout << "        Room Code Price(RM) Contact Number Customer Name        Duration Type No. Attendees Reservation Code Status \n";
            cout << "        --------- --------- -------------- -------------------- ------------- ------------- ---------------- ------\n";
            for (int k = 0; k < noInserted; k++) // displays all of the sorted reservations
            {
                char mod_duration_type[3];
                if (reservForDate[k].durationType == 'A')
                    strcpy(mod_duration_type, "AM");
                else if (reservForDate[k].durationType == 'P')
                    strcpy(mod_duration_type, "PM");
                else
                    strcpy(mod_duration_type, "FD");
                cout << "            " << right << reservForDate[k].roomCode << setw(11) << reservForDate[k].actualPrice << "    " << left << setw(15) << reservForDate[k].contactNo << setw(26) << reservForDate[k].custName << mod_duration_type << right << setw(16) << reservForDate[k].noOfAttendees << setw(16) << reservForDate[k].reservCode << "         " << reservForDate[k].reservStatus << endl;
                cout << "                                                 (Event: " << reservForDate[k].eventDescription << ")" << endl
                     << endl;
            }
            cout << endl;
        }
        else // else if there were no reservations found, display a message
            cout << "\n\n                      No reservations found for the specified date!\n\n";

        do
        {
            cout << "                      Would you like to enquire on another date (Y/N)?: ";
            cin >> contFindMoreReserv;                                                                                              // get user's choice whether to do another enquiry
            cin.ignore(100, '\n');                                                                                                  // ignore the next 100 charc or until it encounters a newline
            if (contFindMoreReserv != 'Y' && contFindMoreReserv != 'y' && contFindMoreReserv != 'N' && contFindMoreReserv != 'n')   // if choice is invalid
                cout << "                      Error! You can only enter Y, y, N or n! Please try again!\n";                        // display error message
        } while (contFindMoreReserv != 'Y' && contFindMoreReserv != 'y' && contFindMoreReserv != 'N' && contFindMoreReserv != 'n'); // prompts as long as choice is invalid
        // the following for loop resets the values in the reservForDate array of struct
        for (int m = 0; m < noInserted; m++)
        {
            reservForDate[m].roomCode = ' ';
            reservForDate[m].contactNo = 0;
            reservForDate[m].actualPrice = 0;
            reservForDate[m].dataEntryDate = 0;
            reservForDate[m].reservDate = 0;
            reservForDate[m].durationType = ' ';
            reservForDate[m].reservStatus = ' ';
            reservForDate[m].noOfAttendees = ' ';
            for (int m1 = 0; m1 < 21; m1++)
            {
                reservForDate[m].custName[m1] = ' ';
            }

            for (int m2 = 0; m2 < 9; m2++)
            {
                reservForDate[m].reservCode[m2] = ' ';
            }
            for (int m3 = 0; m3 < 41; m3++)
            {
                reservForDate[m].eventDescription[m3] = ' ';
            }
        }
        switch (contFindMoreReserv)
        {
        case 'Y': // if user wants to do another enquiry
        case 'y':
            findMoreReserv = true; // iterate the while loop again
            cout << endl;
            break;
        case 'N': // else if user doesnt want to do another enquiry
        case 'n':
            findMoreReserv = false; // dont iterate the while loop again
            break;
        }
    }
    cout << "                      ";
    system("pause"); // prompt user to press any key to continue
    cout << endl;
    enquiriesMenu(); // go to Enquiries Menu
}

void checkAvailability()
{
    system("CLS");
    cout << endl;
    int requested_date;             // to store reservation date
    char duration_type;             // to store duration type
    int num_attendees;              // to store number of attendees
    bool check_availability = true; // to determine whether to continue checking availability
    char contCheckAvailability;     // to store user's choice

    cout << "             o===========================================================================================o\n";
    cout << "             |                                   Check Availability                                      |\n";
    cout << "             =============================================================================================\n";
    cout << "             |           This module searches for available rooms based on the date, duration type       |\n";
    cout << "             |           and room capacity requested by the customer.                                    |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    ;

    struct ReqDateAvailability // Later it will be used as an array of struct
    {
        char room_code;
        char room_name[11];
        int capacity;
        int price;
        char AM;
        char PM;
        char FD;
    };

    struct RoomAvail
    {
        char room_code;
        char room_name[11];
        int capacity;
        int price;
    };

    while (check_availability) // while continue to check availability
    {
        cout << "                      Enter Reservation Date (Format: YYMMDD): ";
        cin >> requested_date;                                  // get reservation date
        requested_date = validateRDate_enquiry(requested_date); // validate reservation date
        cout << endl;

        cout << "                      Enter Duration Type (A/P/F): ";
        cin.get(duration_type);                              // get duration type
        duration_type = toupper(duration_type);              // capitalise duration type
        cin.ignore(100, '\n');                               // ignore the next 100 chars or until it encounters a newline
        duration_type = validateDurationType(duration_type); // validate duration type
        cout << endl;

        cout << "                      Enter Expected Number of Attendees: ";
        cin >> num_attendees;                                // get number of attendees
        num_attendees = validateNumAttendees(num_attendees); // validate number of attendees

        Room room; // a struct used to read each record from the room file

        ifstream inRoom("room.dat", ios_base::in | ios_base::binary); // open the room file in binary mode for input

        ReqDateAvailability suggestedRoom[MAX_ROOMS]; // an array of struct to store details of rooms that initially meet customer's requests

        if (inRoom.is_open() == false) // if error in opening room file
        {
            cout << "                      Error in opening Room File!\n"; // display error message
            exit(EXIT_FAILURE);                                            // exit program
        }

        int num_inserted = 0;                                       // to keep track of the number of records inserted into the array of struct
        inRoom.read(reinterpret_cast<char *>(&room), sizeof(Room)); // read a record from room file

        while (!inRoom.eof()) // while havent reached end of file
        {
            if (num_attendees <= room.capacity) // if requested capacity is less than or equal to the room's max capacity
            {                                   // insert the details from the struct into the array of struct
                suggestedRoom[num_inserted].room_code = room.roomCode;
                strcpy(suggestedRoom[num_inserted].room_name, room.roomName);
                suggestedRoom[num_inserted].capacity = room.capacity;
                suggestedRoom[num_inserted].price = room.price;
                // by default, set the room as available for all duration types
                suggestedRoom[num_inserted].AM = 'A';
                suggestedRoom[num_inserted].PM = 'A';
                suggestedRoom[num_inserted].FD = 'A';
                num_inserted++; // increment the number of inserted records by 1
            }
            inRoom.read(reinterpret_cast<char *>(&room), sizeof(Room)); // read another record from the room file
        }

        inRoom.close(); // close room file
        // open reservation file in binary mode for input
        ifstream inReserv("reservation.dat", ios_base::in | ios_base::binary);

        Reservation currentReserv;       // this struct will be used to temporarily store each record read from reservation file
        if (inReserv.is_open() == false) // if error in opening file
        {
            cout << "                      Error in opening Reservation File!\n"; // display error message
            exit(EXIT_FAILURE);                                                   // exit program
        }

        int num_reserv_read = 0;                                                      // to keep track of the number of records read from reservation file
        inReserv.read(reinterpret_cast<char *>(&currentReserv), sizeof(Reservation)); // read a record from reservation file

        while (!inReserv.eof()) // while havent reached end of file
        {
            if (currentReserv.reservDate == requested_date) // if reservation date from file record matches the requested reservation date
            {
                if (currentReserv.reservStatus != 'X') // if the reservation's status is not cancelled
                {
                    for (int j = 0; j < num_inserted; j++)
                    {
                        if (currentReserv.roomCode == suggestedRoom[j].room_code) // if room code from file record matches the room code in the suggestedRoom array of struct
                        {
                            if (currentReserv.durationType == 'A') // if the duration type of file record is A
                            {                                      // Set the AM and FD durations as unavailable
                                suggestedRoom[j].AM = 'U';
                                suggestedRoom[j].FD = 'U';
                            }
                            else if (currentReserv.durationType == 'P') // else if the duration type of file record is P
                            {                                           // Set the PM and FD durations as unavailable
                                suggestedRoom[j].PM = 'U';
                                suggestedRoom[j].FD = 'U';
                            }
                            else // else if the duration type of file record is F
                            {    // Set the AM, PM and FD as unavailable
                                suggestedRoom[j].AM = 'U';
                                suggestedRoom[j].PM = 'U';
                                suggestedRoom[j].FD = 'U';
                            }
                        }
                    }
                }
            }
            num_reserv_read++;                                                            // increment the number of records read from file by 1
            inReserv.read(reinterpret_cast<char *>(&currentReserv), sizeof(Reservation)); // read another record from file
        }

        inReserv.close(); // close reservation file

        cout << endl;

        RoomAvail AvailableRooms[MAX_ROOMS]; // an array of struct used to store details of rooms that meet customer's requirements

        int num_available_room = 0; // to keep track of the number of rooms that are actually available

        for (int k = 0; k < num_inserted; k++)
        {
            if (duration_type == 'F') // if the requested duration type is F
            {
                if (suggestedRoom[k].FD == 'A') // if the room is available for the full day
                {                               // copy the room details into AvailableRooms array of struct
                    strcpy(AvailableRooms[num_available_room].room_name, suggestedRoom[k].room_name);
                    AvailableRooms[num_available_room].room_code = suggestedRoom[k].room_code;
                    AvailableRooms[num_available_room].capacity = suggestedRoom[k].capacity;
                    AvailableRooms[num_available_room].price = suggestedRoom[k].price;
                    num_available_room++; // increment the number of available rooms by 1
                }
            }
            else if (duration_type == 'A') // else if the requested duration type is A
            {
                if (suggestedRoom[k].AM == 'A') // if the room is available for AM session
                {                               // copy the room details into AvailableRooms array of struct
                    strcpy(AvailableRooms[num_available_room].room_name, suggestedRoom[k].room_name);
                    AvailableRooms[num_available_room].room_code = suggestedRoom[k].room_code;
                    AvailableRooms[num_available_room].capacity = suggestedRoom[k].capacity;
                    AvailableRooms[num_available_room].price = suggestedRoom[k].price / 2;
                    num_available_room++; // increment the number of available rooms by 1
                }
            }
            else // else if the requested duration type is P
            {
                if (suggestedRoom[k].PM == 'A') // if the room is available for PM session
                {                               // copy the room details into AvailableRooms array of struct
                    strcpy(AvailableRooms[num_available_room].room_name, suggestedRoom[k].room_name);
                    AvailableRooms[num_available_room].room_code = suggestedRoom[k].room_code;
                    AvailableRooms[num_available_room].capacity = suggestedRoom[k].capacity;
                    AvailableRooms[num_available_room].price = suggestedRoom[k].price / 2;
                    num_available_room++; // increment the number of available rooms by 1
                }
            }
        }

        if (num_available_room > 0) // if the number of available rooms is more than 0
        {                           // display headers for table
            cout << "                                                    Available Rooms:\n";
            cout << "                                       ---------  ---------   --------  ---------\n";
            cout << "                                       Room Code  Room Name   Capacity  Price(RM)\n";
            cout << "                                       ---------  ---------   --------  ---------\n";
            for (int l = 0; l < num_available_room; l++)
            {
                cout << left; // displays the details of available rooms
                cout << "                                           " << setw(7) << AvailableRooms[l].room_code << setw(12) << AvailableRooms[l].room_name << right << setw(5) << AvailableRooms[l].capacity << setw(11) << AvailableRooms[l].price << endl;
            }
        }
        else // else, display a message
        {
            cout << "                      Sorry! There are no available rooms!";
        }

        cout << endl;

        do
        {
            cout << "                      Would the customer like to enquire on another date (Y/N)?: ";
            cin >> contCheckAvailability;                                                                                                     // get user's choice whether to continue enquiring on another date
            cin.ignore(100, '\n');                                                                                                            // ignore the next 100 chars or until it encounters newline
            if (contCheckAvailability != 'Y' && contCheckAvailability != 'y' && contCheckAvailability != 'N' && contCheckAvailability != 'n') // if user's choice is invalid
                cout << "                      Error! You can only enter Y, y, N or n! Please try again!\n";
        } while (contCheckAvailability != 'Y' && contCheckAvailability != 'y' && contCheckAvailability != 'N' && contCheckAvailability != 'n'); // if user's choice is invalid
        // Reset the values in the arrays of struct
        for (int m = 0; m < num_inserted; m++)
        {
            suggestedRoom[m].room_code = ' ';
            for (int m1 = 0; m1 < 11; m1++)
            {
                suggestedRoom[m].room_name[m1] = ' ';
            }
            suggestedRoom[m].capacity = 0;
            suggestedRoom[m].price = 0;
            suggestedRoom[m].AM = ' ';
            suggestedRoom[m].PM = ' ';
            suggestedRoom[m].FD = ' ';
        }
        for (int n = 0; n < num_inserted; n++)
        {
            AvailableRooms[n].room_code = ' ';
            for (int n1 = 0; n1 < 11; n1++)
            {
                AvailableRooms[n].room_name[n1] = ' ';
            }
            AvailableRooms[n].capacity = 0;
            AvailableRooms[n].price = 0;
        }

        switch (contCheckAvailability)
        {
        case 'Y': // if user wants to continue doing enquiry
        case 'y':
            check_availability = true; // reiterate the while loop
            cout << endl;
            break;
        case 'N': // else if user doesnt want to continue doing enquiry
        case 'n':
            check_availability = false; // dont reiterate the whole loop
            break;
        }
    }
    cout << "                      ";
    system("pause"); // prompt user to press any key to continue
    cout << endl;
    enquiriesMenu(); // go back to Enquiries Menu
}

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
        system("CLS");
        // Display Message

        cout << "             o===========================================================================================o\n";
        cout << "             |                           Search Reservation By Customer Name                             |\n";
        cout << "             |-------------------------------------------------------------------------------------------|\n";
        cout << "             |           This module searches for reservation by entering Customer Name.                 |\n";
        cout << "             |           *Note: It will display multiple records for the same customer                   |\n";
        cout << "             |           [To Exit, Please Enter 0]                                                       |\n";
        cout << "             o-------------------------------------------------------------------------------------------o\n";

        cout << "                      Enter Name to search: "; // Prompt user to enter name
        cin.clear();
        cin.sync();
        cin.getline(findname, 21);
        for (int i = 0; i < 21; i++)
        {
            findname[i] = toupper(findname[i]);
        }

        if (findname[0] == '0') // If user press 0
        {
            cout << "                      Jump to Enquiries menu\n";
            srhName = 1; // Initialise srhName to 1

            enquiriesMenu();
        }

        while (fbin.read((char *)&searchbyName, sizeof(searchbyName)))
        {
            if (strcmp(searchbyName.custName, findname) == 0) // Compare input with customer's name in file
            {
                // Display Header and Reservation Code of the customer
                cout << "\n\n                      Here are the details: \n";
                cout << "                      --------------------------------------------------\n";
                cout << "                      Customer Name\t\t: " << searchbyName.custName << endl;      // Display Name
                cout << "                      Reservation Code\t\t: " << searchbyName.reservCode << endl; // Show Reservation Code
                // Show Reservation Date (Proper Way)
                // Seperate Day, Month and Year
                int SBN_reserv_year = searchbyName.reservDate / 10000;
                int SBN_reserv_month = (searchbyName.reservDate % 10000) / 100;
                int SBN_reserv_day = (searchbyName.reservDate % 10000) % 100;

                // Display Day, Month, Year in proper way
                cout << "                      Reservation Date\t\t: " << SBN_reserv_day << "/" << SBN_reserv_month << "/" << SBN_reserv_year << endl;

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
                cout << "                      Duration Type\t\t: " << SBN_duration << endl;

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
                cout << "                      Room Type\t\t\t: " << SBN_RoomCode << endl; // Display Room Type in full form

                // Display Price
                cout << "                      Price\t\t\t: RM" << searchbyName.actualPrice << endl;

                // Display Event Description
                cout << "                      Event Description\t\t: " << searchbyName.eventDescription;

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
                cout << "\n                      Booking Status\t\t: " << SBN_status << endl;

                srhName = 1; // Initialise srhName to 1
            }
        }
        fbin.close();                                                           // Close file
        if (srhName == 0)                                                       // If variable srhName equals to 0 (means no data in file is read)
            cout << "\n                      Customer Name not found in data."; // Display Error Message

        // Display message to direct user back to Enquiries Menu
        cout << "\n                      Returning back to Enquiries...\n";
        cout << "                      ";
        system("pause");

        enquiriesMenu(); // to be removed
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
        system("CLS");
        // Display Message

        cout << "             o===========================================================================================o\n";
        cout << "             |                           Search Reservation By Contact Number                            |\n";
        cout << "             |===========================================================================================|\n";
        cout << "             |             This module searches for reservation by entering Contact Number.              |\n";
        cout << "             |             *Note: It will display multiple records for the same customer                 |\n";
        cout << "             |             [To Exit, Please Enter 0]                                                     |\n";
        cout << "             o-------------------------------------------------------------------------------------------o\n";

        // Prompt and get input for contact number
        cout << "                      Enter Contact Number to search: ";
        cin >> findcontact;
        if (findcontact == 0) // If user press 0
        {
            cout << "                      Jump to Enquiries menu\n";
            srhContact = 1;

            enquiriesMenu();
        }

        while (fbin.read((char *)&searchbyContact, sizeof(searchbyContact)))
        {
            if (searchbyContact.contactNo == findcontact) // Compare user's input with contact number in file
            {
                // Display Header and Reservation Code of the customer
                cout << "                      Here are your details: \n";
                cout << "                      --------------------------------------------------\n";
                cout << "                      Customer Name\t\t: " << searchbyContact.custName << endl;      // Display Name
                cout << "                      Reservation Code\t\t: " << searchbyContact.reservCode << endl; // Show Reservation Code
                // Show Reservation Date (Proper Way)
                // Seperate Day, Month and Year
                int SBC_reserv_year = searchbyContact.reservDate / 10000;
                int SBC_reserv_month = (searchbyContact.reservDate % 10000) / 100;
                int SBC_reserv_day = (searchbyContact.reservDate % 10000) % 100;

                // Display Reservation Date
                cout << "                      Reservation Date\t\t: " << SBC_reserv_day << "/" << SBC_reserv_month << "/" << SBC_reserv_year << endl;

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
                cout << "                      Duration Type\t\t: " << SBC_duration << endl;

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
                cout << "                      Room Type\t\t\t: " << SBC_RoomCode << endl;

                // Display Price
                cout << "                      Price\t\t\t: RM" << searchbyContact.actualPrice << endl;

                // Display Event Description
                cout << "                      Event Description\t\t: " << searchbyContact.eventDescription;

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
                cout << "\n                      Booking Status\t\t: " << SBC_status << endl;

                srhContact = 1;
            }
        }
        fbin.close();        // Close File
        if (srhContact == 0) // If variable srhContact equals to 0
        {
            cout << "\n                      Customer Contact not found in data.\n"; // Display Error Message
        }

        // Display message to direct user back to Enquiries Menu
        cout << "\n                      Returning back to Enquiries...\n";
        cout << "                      ";
        system("pause");

        enquiriesMenu(); // to be removed afrer merge
    }
}

void DisplayRoomInformation(){
    Room roomInformation; // Declare Room roomInformation
    fstream fbin("room.dat",ios::binary | ios:: in); // Declare file stream variable and read the content of file
    if (fbin.is_open() == false)  //if there is an error in opening file
    {
        cout << "                      Error in opening Room File!\n"; //display error message
        exit(EXIT_FAILURE);                      //exit program
    }
    fbin.read((char*)&roomInformation, sizeof(Room)); // read the record from room file
    system("CLS");
    cout << "             o===========================================================================================o\n";
    cout << "             |                                       Room Details                                        |\n"; // Display "                          
    cout << "             |===========================================================================================|\n"; 
    cout << "             |                  This module displays the details for all Room Types.                     |\n";
    cout << "             |                  *Note: Prices shown are for Full day reservations. If reservations       |\n";
    cout << "             |                  If reservations are for AM or PM sessions, room prices will be halved    |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    cout << left << setw(15) << "                                        Room Code" << setw(12) << " Room Name" << setw(10) << "Capacity" << setw(10) << "Price(RM)" << endl; // Display "Room Code",space,"Room Name",space,"Capacity",space,"Price"
    cout << left << setw(15) << "                                        ---------" << setw(12) << " ---------" << setw(10) << "--------" << setw(10) << "---------" << endl;
    while(!fbin.eof()){ //while havent reached end of file
        //Display details for each room
	    cout << left << setw(40) << " " << setw(10) << roomInformation.roomCode << setw(12) << roomInformation.roomName << setw(12) << right << setw(4) << roomInformation.capacity << setw(10) << roomInformation.price << endl;
	    fbin.read((char *)&roomInformation, sizeof(Room)); //read another record from room file
    }
    fbin.close();

    cout << "\n                      Returning back to Enquiries...\n"; // Display the returning message
    cout << "                      ";
    system("pause");
    enquiriesMenu();
}

void viewDetail(){
    Reservation viewReservation; // Declare Reservation viewReservation
    ifstream fbin("reservation.dat",ios::binary | ios::in);  // Declare file stream variable and read the file
    if(!fbin){ // if file cannot open
        cout << "                      Error in opening file"; // Display Error Message
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
    system("CLS");
    cout << "             o===========================================================================================o\n";
    cout << "             |                                  View Reservation Details                                 |\n";
    cout << "             |===========================================================================================|\n";
    cout << "             |        This allows the user to check the reservation details for a particular customer    |\n";
    cout << "             |        before proceeding to confirm reservation for customer.                             |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    // Prompt and get the reservation code
    cout << "                      Enter the reservation code: ";
    cin >> reserv_Number;

    if (reserv_Number.length() != 8){
        validatelength = false;
    }

    while(validatelength == false){
        cout << "   Error!!! You can enter 8 characters only." << endl;
        cout << "   Enter the reservation code: ";
        cin >> reserv_Number;
        count++;

        if (reserv_Number.length() == 8){
            validatelength = true;
        }
        if(count == 2){
            validatelength = true;
        }
    }

    while(fbin.read((char*)&viewReservation,sizeof(viewReservation))){ // Read the file
        if(viewReservation.reservCode == reserv_Number){ // if reserv_Number equal to reservCode in the file
            int year_reserv = viewReservation.reservDate / 10000;
            int month_reserv = (viewReservation.reservDate % 10000) / 100;
            int day_reserv = (viewReservation.reservDate % 10000) % 100;
            cout << "                      =============================================================\n"; // Display "   =============================================================\n"
            cout << "                                           Reservation Details\n"; // Display "                       Reservation Details\n"
            cout << "                      =============================================================\n"; // Display "   =============================================================\n"
            cout << "                      Reservation Code     : " << viewReservation.reservCode << endl; // Display Reservation Code 
            cout << "                      Reservation Date     : " << day_reserv << '/' << month_reserv << '/' << year_reserv << endl; // Display Reservation Date
            cout << "                      Reservation Name     : " << viewReservation.custName << endl; // Display Customer Name
            cout << "                      Reservation Status   : " << viewReservation.reservStatus << endl; // Display Reservation Status
            cout << "                      Contact Number       : " << viewReservation.contactNo << endl; // Display Contact Number
            cout << "                      Total Payment        : " << viewReservation.actualPrice << endl; // Display Price
            cout << "                      Number of Attendees  : " << viewReservation.noOfAttendees << endl; // Display Number of Attendees
            cout << "                      Event Description    : " << viewReservation.eventDescription << endl; // Display Event Description
            cout << "                      Duration Type(A/P/F) : " << viewReservation.durationType << endl; // Display Duration Type
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
            cout << "                      Room Name            : " << room << endl; // Display room
            cout << "                      Room Code            : " << viewReservation.roomCode << endl;
            do{
                cout << "\n                      Would you like to see the details of another reservation (Y/N)?: "; // Display message of ask user to check other detail
                cin >> detailOption; // Prompt and get detailOption from user
                detailOption = toupper(detailOption); // Change the detailOption to uppercase
                if(detailOption == 'Y'){ // if detailOption equal to N
                    validateOption = true; // set validateOption = true
                }

                if(detailOption == 'N'){ // if detailOption equal to N
                    validateOption = true; // set validateOption = true
                }

                if(detailOption != 'Y' && detailOption != 'N'){ // if detailOption not equal to Y and N
                    cout << "                      Error!!!Please enter Y or N only."; // Display Error Message
                    validateOption = false; // set validateOption = false
                }
            }while(validateOption == false); // Do while loop when the validateOption equal to false
            existcode = true;  // set existcode = true
            status = true; // status = true
            fbin.close();
        }    
    }

    if(status == false){
        cout << "\n                      The reservation does not exist." << endl; // Display the message of the reservation code is not exist.
        do{
            cout << "                      Do you want to exit (Y/N)?: "; // Display message of ask user to check other detail
            cin >> Option; // Prompt and get detailOption from user
            Option = toupper(Option); // Change the detailOption to uppercase
            if(Option == 'Y'){ // if detailOption equal to N
                validateOption = true; // set validateOption = true
            }

            if(Option == 'N'){ // if detailOption equal to N
                validateOption = true; // set validateOption = true
                detailOption = 'Y';
            }

            if(detailOption != 'Y' && detailOption != 'N'){ // if detailOption not equal to Y and N
                cout << "                      Error!!!Please enter Y or N only."; // Display Error Message
                validateOption = false; // set validateOption = false
            }
        }while(validateOption == false); // Do while loop when the validateOption equal to false
    }
    

    if(detailOption == 'Y'){
        viewDetail();
    }

    else{
        cout << "\n                      Returning back to Enquiries...\n"; // Display the returning message
        cout << "                      ";
        system("pause");
        enquiriesMenu();
    }
 
}

//*****************END OF ENQUIRIES**************************

//*****************REPORTS************************************
void SortMonthsByDescRev(MonthlyRevenue mthRev[])
{ // Uses selection sort to sort the monthly revenues in descending order
    const int NUM_MTHS = 12;
    int i, maxIndex;
    MonthlyRevenue tempVar;

    for (i = 0; i < (NUM_MTHS - 1); i++)
    {
        maxIndex = i;
        for (int j = i; j < NUM_MTHS; j++)
        {
            if (mthRev[j].RevenueAmt > mthRev[maxIndex].RevenueAmt)
                maxIndex = j;
        }
        if (maxIndex != i)
        {
            tempVar = mthRev[maxIndex];
            mthRev[maxIndex] = mthRev[i];
            mthRev[i] = tempVar;
        }
    }
}

void monthlyRevenueGivenYear()
{
    system("CLS"); // clears screen
    cout << endl;
    int requestedYear;     // used to store the last 2 digits of requested year
    int fullRequestedYr;   // used to store all 4 digits of requested year
    int Revenue[12] = {0}; // initialize revenues for all 12 months to be 0
    // used to store the abbreviations for all 12 months
    char MthNum[12][4] = {{"JAN"}, {"FEB"}, {"MAR"}, {"APR"}, {"MAY"}, {"JUN"}, {"JUL"}, {"AUG"}, {"SEP"}, {"OCT"}, {"NOV"}, {"DEC"}};
    bool generateMonthlyRevenue = true; // predetermines that the user wants to generate monthly revenue reports
    char contGenerateMthRevenue;        // stores user's choice whether to continue generating reports
    int reservYear;                     // stores the 2 digit year of reservation
    int reservMonth;                    // stores the 2 digit month of reservation

    cout << "             o===========================================================================================o\n";
    cout << "             |                        Monthly Revenue for given Year - Summary                           |\n";
    cout << "             =============================================================================================\n";
    cout << "             |              It generates a report, showing Revenue by Month for                          |\n";
    cout << "             |              a given year. Its purpose is to discover which                               |\n";
    cout << "             |              months are peak and non-peak.                                                |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";
    while (generateMonthlyRevenue) // while generate reports
    {
        MonthlyRevenue RevenueTable[12]; // an array of struct used to store the abbreviations of months and their respective revenues
        Reservation currentReserv;       // used to temporarily store each record from reservation file

        for (int x = 0; x < 12; x++)
        {
            char mthChar[4] = {}; // declare an empty char array used for inserting month abbreviation into RevenueTable array of struct later on
            for (int y = 0; y < 3; y++)
            {
                mthChar[y] = MthNum[x][y]; // copy month abbreviation from MthNum array into mthChar array
            }
            strcpy(RevenueTable[x].Month, mthChar); // copy month abbreviation into the RevenueTable array of struct
            RevenueTable[x].RevenueAmt = 0;         // by default, set Revenue for each mont to be 0
        }

        do
        {
            cout << "                      Enter Year: ";
            cin >> fullRequestedYr; // Get the 4 digits year
            if (cin.fail())         // if year is not an integer
            {
                cin.clear();                                                                   // clear input failed state
                cin.ignore(100, '\n');                                                         // ignore the next 100 chars or until encounter newline
                fullRequestedYr = 0;                                                           // set the year to 0
                cout << "                      Error! Year must be a numeric whole number!\n"; // display error message
            }
            else if (fullRequestedYr < 2000)                                                          // else if year entered isnt from 21st century
                cout << "                      Error! Year must be greater than or equal to 2000!\n"; // display error message
        } while (fullRequestedYr < 2000);                                                             // prompts as long as year entered isnt from 21st century

        requestedYear = fullRequestedYr - 2000; // get the last 2 digits of year
        cout << endl;
        // open the reservation file in binary mode for input
        ifstream calcRevenue("reservation.dat", ios_base::in | ios_base::binary);

        if (calcRevenue.is_open() == false) // if error in opening file
        {
            cout << "                      Error in opening Room File!\n"; // display error message
            exit(EXIT_FAILURE);                                            // exit program
        }

        int no_rec_read = 0; // to keep track of the number of records read from reservation file

        calcRevenue.read(reinterpret_cast<char *>(&currentReserv), sizeof(Reservation)); // read a record from reservatio file

        while (!calcRevenue.eof()) // while havent reached end of file
        {
            reservYear = currentReserv.reservDate / 10000;          // to extract the 2 digit year from record's reservation date
            reservMonth = (currentReserv.reservDate % 10000) / 100; // to extract the 2 digit month from record's reservation date
            if (reservYear == requestedYear)                        // if the 2 digit year from reservation is the same as the 2 digit requested year
            {
                if (currentReserv.reservStatus != 'X') // if the reservation status of the record is not cancelled
                {
                    switch (reservMonth)
                    { // accumulate total revenue by month
                    case 1:
                        Revenue[0] += currentReserv.actualPrice;
                        break;
                    case 2:
                        Revenue[1] += currentReserv.actualPrice;
                        break;
                    case 3:
                        Revenue[2] += currentReserv.actualPrice;
                        break;
                    case 4:
                        Revenue[3] += currentReserv.actualPrice;
                        break;
                    case 5:
                        Revenue[4] += currentReserv.actualPrice;
                        break;
                    case 6:
                        Revenue[5] += currentReserv.actualPrice;
                        break;
                    case 7:
                        Revenue[6] += currentReserv.actualPrice;
                        break;
                    case 8:
                        Revenue[7] += currentReserv.actualPrice;
                        break;
                    case 9:
                        Revenue[8] += currentReserv.actualPrice;
                        break;
                    case 10:
                        Revenue[9] += currentReserv.actualPrice;
                        break;
                    case 11:
                        Revenue[10] += currentReserv.actualPrice;
                        break;
                    case 12:
                        Revenue[11] += currentReserv.actualPrice;
                        break;
                    }
                }
            }
            no_rec_read++;                                                                   // increment the number of records read by 1
            calcRevenue.read(reinterpret_cast<char *>(&currentReserv), sizeof(Reservation)); // read another record from reservation file
        }
        // display headers for 1st report
        cout << "                          Monthly Revenues Chronologically Sorted By Month" << endl;
        cout << "                          ================================================" << endl;
        cout << "                                        Month   Revenue(RM)" << endl;
        cout << "                                        -----   -----------" << endl;
        for (int i = 0; i < 12; i++) // displays each month and its respective total revenue
        {
            RevenueTable[i].RevenueAmt = Revenue[i];
            cout << "                                        " << RevenueTable[i].Month << setw(12) << right << RevenueTable[i].RevenueAmt << endl;
        }
        cout << endl;
        SortMonthsByDescRev(RevenueTable); // sorts array of struct by descending revenue order

        cout << endl; // display headers for 2nd report
        cout << "                          Monthly Revenues Sorted in Descending Order" << endl;
        cout << "                          ===========================================" << endl;
        cout << "                                        Month   Revenue(RM)" << endl;
        cout << "                                        -----   -----------" << endl;
        for (int z = 0; z < 12; z++) // display each month and its respective revenue
        {
            cout << "                                        " << RevenueTable[z].Month << setw(12) << right << RevenueTable[z].RevenueAmt << endl;
        }
        cout << endl;

        do
        {
            cout << "                      Would you like to generate another set of reports for another year (Y/N)?: ";
            cin >> contGenerateMthRevenue; // get user's choice to continue generating reports
            cin.ignore(100, '\n');
            // if user's choice is invalid
            if (contGenerateMthRevenue != 'Y' && contGenerateMthRevenue != 'y' && contGenerateMthRevenue != 'N' && contGenerateMthRevenue != 'n')
                cout << "                      Error! You can only enter Y, y, N or n! Please try again!\n"; // display error message
            // prompts as long as user's choice is invalid
        } while (contGenerateMthRevenue != 'Y' && contGenerateMthRevenue != 'y' && contGenerateMthRevenue != 'N' && contGenerateMthRevenue != 'n');

        // Resets the values in the RevenueTable array of struct
        for (int y = 0; y < 12; y++)
        {
            Revenue[y] = 0;
            RevenueTable[y].RevenueAmt = 0;
            for (int y1 = 0; y1 < 4; y1++)
            {
                RevenueTable[y].Month[y1] = ' ';
            }
        }

        switch (contGenerateMthRevenue)
        {
        case 'Y': // if user wants to generate another set of reports
        case 'y':
            cout << endl;
            generateMonthlyRevenue = true; // reiterate the while loop
            break;

        case 'N': // else if user doesnt want to generate another set of reports
        case 'n':
            generateMonthlyRevenue = false; // dont reiterate the while loop
            break;
        }
    }
    system("pause"); // prompt user to press any key to continue
    cout << endl;
    reportsMenu(); // go to Reports Menu
}

void revForMonthAndYear()
{
    system("CLS"); // clear screen
    cout << endl;
    int requested_year, requested_month; // to store the 2 digit year and month
    int requested_full_yr;               // to store the 4 digits year
    bool generateDetailedReport = true;  // predetermines that the user wants to generate a report
    char contGenerateDetailedRpt;        // store user's choice whether to continue generating report
    int reserv_year, reserv_month;       // store the 2 digit year and month of reservation
    int reserv_day;                      // store the day of reservation
    const int SIZE = 400;                // assume that a max of 300 reservations is created for the given month & year
    string month_word;                   // store the full name of month

    cout << "             o===========================================================================================o\n";
    cout << "             |                          Revenue for given Month and Year - Detailed                      |\n";
    cout << "             =============================================================================================\n";
    cout << "             |                  It generates a report, displaying all the reservations                   |\n";
    cout << "             |                  (except for Cancelled reservations).                                     |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    while (generateDetailedReport) // while generate report
    {
        Reservation reserv_rec;         // struct used to temporarily store each record from reservation file
        Reservation filtered_rec[SIZE]; // an array of struct used to store the desired reservation records

        long TTLRevenue = 0; // set total revenue to 0
        do
        {
            cout << "                      Enter customer's Requested Year: ";
            cin >> requested_full_yr; // get 4 digit requested year
            if (cin.fail())           // if year is not an integer
            {
                cin.clear();                                                                       // clear input failed state
                cin.ignore(100, '\n');                                                             // ignore the next 100 chars or until it encounters newline
                requested_full_yr = 0;                                                             // reset the year to 0
                cout << "                      Error! Year can only be a numeric whole number!\n"; // display error message
            }
            else if (requested_full_yr < 2000)                                                 // else if year is less than 2000
                cout << "                      Year must be greater than or equal to 2000!\n"; // display error message
        } while (requested_full_yr < 2000);                                                    // prompts as long as year is less than 2000
        cout << endl;
        do
        {
            cout << "                      Enter customer's Requested Month (1-12): ";
            cin >> requested_month; // get month
            if (cin.fail())         // if month is not an integer
            {
                cin.clear();                                                                        // clear input failed state
                cin.ignore(100, '\n');                                                              // ignore the next 100 chars or until it encounters newline
                requested_month = 0;                                                                // reset month to 0
                cout << "                      Error! Month can only be a numeric whole number!\n"; // display error message
            }
            else if (requested_month < 1 || requested_month > 12)                         // else if month is invalid
                cout << "                      Month can only be in the range 1 - 12!\n"; // display error message
        } while (requested_month < 1 || requested_month > 12);                            // prompts as long as month is less than 1 or more than 12

        requested_year = requested_full_yr - 2000; // get the last 2 digits of year

        // open reservation file in binary mode for input
        ifstream readRec("reservation.dat", ios_base::in | ios_base::binary);

        // if error in opening file
        if (readRec.is_open() == false)
        {
            cout << "                      Error in opening Reservation File!\n"; // display error message
            exit(EXIT_FAILURE);                                                   // exit program
        }

        int num_read_reserv = 0;                                                  // keep track of the number of reservation records read from reservation file
        readRec.read(reinterpret_cast<char *>(&reserv_rec), sizeof(Reservation)); // read record from reservation

        while (!readRec.eof()) // while havent reached end of file
        {
            reserv_year = reserv_rec.reservDate / 10000;          // extract the 2 digit year from file record's reservation date
            reserv_month = (reserv_rec.reservDate % 10000) / 100; // extract month from file record's reservation date
            if (reserv_year == requested_year)                    // if year of record's reservation date is equal to requested year
            {
                if (reserv_month == requested_month) // if month of record's reservation date is equal to requested month
                {
                    if (reserv_rec.reservStatus != 'X') // if reservation status is not cancelled
                    {
                        filtered_rec[num_read_reserv] = reserv_rec;                          // copy reservation details from struct to array of struct
                        TTLRevenue = TTLRevenue + filtered_rec[num_read_reserv].actualPrice; // increment the total revenue
                        num_read_reserv++;                                                   // increment the number of reservation records read
                    }
                }
            }
            readRec.read(reinterpret_cast<char *>(&reserv_rec), sizeof(Reservation)); // read another record from reservation file
        }

        readRec.close();         // close reservation file
        if (num_read_reserv > 0) // if number of reservations read is more than 0
        {                        // determines the month to be displayed based on month number
            switch (requested_month)
            {
            case 1:
                month_word = "JAN";
                break;
            case 2:
                month_word = "FEB";
                break;
            case 3:
                month_word = "MAR";
                break;
            case 4:
                month_word = "APR";
                break;
            case 5:
                month_word = "MAY";
                break;
            case 6:
                month_word = "JUN";
                break;
            case 7:
                month_word = "JUL";
                break;
            case 8:
                month_word = "AUG";
                break;
            case 9:
                month_word = "SEP";
                break;
            case 10:
                month_word = "OCT";
                break;
            case 11:
                month_word = "NOV";
                break;
            case 12:
                month_word = "DEC";
                break;
            }

            cout << endl;
            // uses selection sort to sort reservations by reservation date
            Reservation tempVar;

            int i, minIndex;

            for (i = 0; i < (num_read_reserv - 1); i++)
            {
                minIndex = i;
                for (int j = i; j < num_read_reserv; j++)
                {
                    if (filtered_rec[j].reservDate < filtered_rec[minIndex].reservDate)
                        minIndex = j;
                }
                if (minIndex != i)
                {
                    tempVar = filtered_rec[minIndex];
                    filtered_rec[minIndex] = filtered_rec[i];
                    filtered_rec[i] = tempVar;
                }
            }
            // display headers for report
            cout << "                                                                                         Total Revenue for " << month_word << " " << requested_full_yr << " : RM " << TTLRevenue << endl;
            cout << setw(17) << "---------------- " << setw(16) << "---------------- " << setw(14) << "------------- " << setw(9) << "--------- "
                 << "---------------- "
                 << "-------------------- "
                 << "-------------- "
                 << "------ "
                 << "-----------\n";
            cout << setw(17) << "Reservation Code " << setw(16) << "Reservation Date " << setw(14) << "Duration Type " << setw(9) << "Room Code "
                 << "No. of Attendees "
                 << "Customer Name        "
                 << "Contact Number "
                 << "Status "
                 << "Revenue(RM)\n";
            cout << setw(17) << "---------------- " << setw(16) << "---------------- " << setw(14) << "------------- " << setw(9) << "--------- "
                 << "---------------- "
                 << "-------------------- "
                 << "-------------- "
                 << "------ "
                 << "-----------\n";
            for (int k = 0; k < num_read_reserv; k++)
            {
                reserv_year = filtered_rec[k].reservDate / 10000;          // get the 2 digit year from record's reservation date
                reserv_month = (filtered_rec[k].reservDate % 10000) / 100; // get the month from record's reservation date
                reserv_day = (filtered_rec[k].reservDate % 10000) % 100;   // get the day from record's reservation date
                char mod_duration_type[3];                                 // to store the full form of duration type
                if (filtered_rec[k].durationType == 'A')                   // if duration type is "A"
                    strcpy(mod_duration_type, "AM");                       // copy "AM" into mod_duration_type for display later
                else if (filtered_rec[k].durationType == 'P')              // else if duration type is "P"
                    strcpy(mod_duration_type, "PM");                       // copy "PM" into mod_duration_type for display later
                else                                                       // else if duration type is "F"
                    strcpy(mod_duration_type, "FD");                       // copy "FD" into mod_duration_type for display later
                // displays each of filtered reservation record
                cout << right << setw(12) << filtered_rec[k].reservCode << setw(11) << reserv_day << "/" << reserv_month << "/" << reserv_year << setw(11) << mod_duration_type << setw(13) << filtered_rec[k].roomCode << setw(14) << filtered_rec[k].noOfAttendees << "         " << left << setw(21) << filtered_rec[k].custName << setw(17) << filtered_rec[k].contactNo << setw(5) << filtered_rec[k].reservStatus << setw(7) << right << filtered_rec[k].actualPrice << endl;
            }
        }
        else // else if no reservations found, display a message
            cout << "\n                      ** No reservations found for the specified month and year! **\n";
        do
        {
            cin.ignore(100, '\n');
            cout << "\n                      Would you like to generate another report for another month and year (Y/N)?: ";
            cin >> contGenerateDetailedRpt; // get user's choice whether to generate another report
            // if choice is invalid
            if (contGenerateDetailedRpt != 'Y' && contGenerateDetailedRpt != 'y' && contGenerateDetailedRpt != 'N' && contGenerateDetailedRpt != 'n')
                cout << "                      Error! You can only enter Y, y, N or n! Please try again!\n"; // display error message
            // prompts as long as choice is invalid
        } while (contGenerateDetailedRpt != 'Y' && contGenerateDetailedRpt != 'y' && contGenerateDetailedRpt != 'N' && contGenerateDetailedRpt != 'n');
        // resets the values of the array of struct
        for (int m = 0; m < num_read_reserv; m++)
        {
            filtered_rec[m].roomCode = ' ';
            for (int m1 = 0; m1 < 9; m1++)
            {
                filtered_rec[m].reservCode[m1] = ' ';
            }
            filtered_rec[m].durationType = ' ';
            filtered_rec[m].actualPrice = 0;
            filtered_rec[m].contactNo = 0;
            filtered_rec[m].noOfAttendees = 0;
            filtered_rec[m].reservDate = 0;
            filtered_rec[m].dataEntryDate = 0;
            filtered_rec[m].reservStatus = ' ';
            for (int m2 = 0; m2 < 21; m2++)
            {
                filtered_rec[m].custName[m2] = ' ';
            }
            for (int m3 = 0; m3 < 41; m3++)
            {
                filtered_rec[m].eventDescription[m3] = ' ';
            }
        }
        // reset the value of the struct
        reserv_rec.actualPrice = 0;
        reserv_rec.contactNo = 0;
        reserv_rec.dataEntryDate = 0;
        reserv_rec.reservDate = 0;
        reserv_rec.noOfAttendees = 0;
        reserv_rec.reservStatus = ' ';
        reserv_rec.roomCode = ' ';
        for (int n1 = 0; n1 < 21; n1++)
        {
            reserv_rec.custName[n1] = ' ';
        }
        for (int n2 = 0; n2 < 41; n2++)
        {
            reserv_rec.eventDescription[n2] = ' ';
        }
        for (int n3 = 0; n3 < 9; n3++)
        {
            reserv_rec.reservCode[n3] = ' ';
        }

        switch (contGenerateDetailedRpt)
        {
        case 'Y': // if user wants to continue generating report
        case 'y':
            generateDetailedReport = true; // iterate the while loop again
            cout << endl;
            break;
        case 'N': // else if user doesnt want to continue generating report
        case 'n':
            generateDetailedReport = false; // dont iterate the while loop
            break;
        }
    }
    system("pause"); // prompt user to press any key to continue
    cout << endl;
    reportsMenu(); // go to Reports Menu
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

    system("CLS"); // clear screen
    // Display Header
    cout << endl;
    cout << "             o===========================================================================================o\n";
    cout << "             |                                   Revenue by Customer                                     |\n";
    cout << "             |===========================================================================================|\n";
    cout << "             |               This report is to identify who's the company's best customers               |\n";
    cout << "             |                            (except for Cancelled reservations).                           |\n";
    cout << "             |                      *Note: This is sorted according to alphabetical                      |\n";
    cout << "             |                        order of customer with Highest Contribution                        |\n";
    cout << "             o-------------------------------------------------------------------------------------------o\n";

    //******************************************************//
    // Count number of data in file (get number of recCount)//
    //******************************************************//

    Reservation currentCust;
    CustomerRevenue revenueCust;

    int recCount = 0; // Initialise recCount to 0

    ifstream revenueByCust("reservation.dat", ios_base::in | ios_base::binary);
    if (!revenueByCust) // If the file entered is invalid
    {
        cout << "                      Error Opening File\n"; // Display error message
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

    int g = 0;           // initialize variable g to 1
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

    /*for (int k = 1; k <= recCount; k++)
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

    cout << "             |                                                                                           |" << endl;
    cout << "             |                               List of Revenue of Customers                                |" << endl;
    cout << "             +-------------------------------------------------------------------------------------------+" << endl;
    cout << "             |                    Customer Name                    Total Contribution                    |" << endl;
    cout << "             |                  -----------------                ----------------------                  |" << endl;

    // Display the Best Customer (Which is the first position of custArray)
    cout << right;
    cout << setw(14) << "|" << setw(20) << setfill(' ') << ">> ";
    cout << left;
    cout << setw(40) <<custArray[1].RevCustSort << setw(31) << custArray[1].CustRevAmt << "|" << endl;

    // Display all other Customer Data from Highest Contribution to Lowest Contribution with Alphabetical Order Sorted
    for (int i = 2; i <= recCount; i++)
    {
        cout << right;
        cout << setw(14) << "|" << setw(20) << setfill(' ') << "    ";
        cout << left;
        cout << setw(40) << custArray[i].RevCustSort << setw(31) << custArray[i].CustRevAmt << "|" << endl;
    }

    cout << "             o-------------------------------------------------------------------------------------------o" << endl;

    // Analysis Message of Best Customer
    cout << endl
         << "                           According to Analysis, " << custArray[1].RevCustSort << " is our Best Customer!" << endl
         << endl
         << "                           Directing you back to Reports Menu..."
         << endl;

    system("pause");
    reportsMenu();
}