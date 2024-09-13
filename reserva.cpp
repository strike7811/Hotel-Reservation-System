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

void confirmReservation();

int main(){
    confirmReservation();

    return 0;
}

void confirmReservation(){
    Reservation reservConfirm;
    /*struct Confirm{
        char reservationcode[9];
        char status;
    };*/

    fstream fbin("reservation.dat",ios::binary | ios::in | ios::out);
    fbin.seekg(0);

    if(!fbin){
        cout << "   Error in opening Reservation file";
        exit(EXIT_FAILURE);
    }

    else{
        char reservationcode[9];
        bool existcode = true;
        bool validateOption = true;
        int count = 0;
        int nReservation;
        char option;
        char confirmStatus;
        int number = 1;
        string room;
        do{
            cout << "   Enter the reservation code: ";
            cin >> reservationcode;
            fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
            if(strcmp(reservConfirm.reservCode, reservationcode) == 0){
                cout << "   Your reservation is found." << endl;
                do{
                    cout << "   Do you want to confirm your reservation? (Y/N): ";
                    cin >> option;
                    option = toupper(option);
                    if(option == 'Y'){
                        fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                        if(strcmp(reservConfirm.reservCode, reservationcode) == 0){
                            cout << "   You got multiple reservation. Which one you want to confirm ?" << endl;
                            cout << "                Your Reservation\n";
                            cout << "----------------------------------------------------\n";
                            cout << left << setw(8) << "Number" << setw(12) << "Room" << setw(42) << "Ëvent" << endl;
                            fbin.close();
                            while(strcmp(reservConfirm.reservCode, reservationcode) == 0){
                                switch(reservConfirm.roomCode){
                                case 'A':
                                    room = "Azure";
                                    break;
                        
                                case 'B':
                                    room = "Byzantine";
                                    break;
                                
                                case 'C':
                                    room = "Crystal";
                                    break;
                                
                                case 'D':
                                    room = "Diamond";
                                    break;
                                
                                case 'E':
                                    room = "Emerald";
                                    break;
                                
                                case 'F':
                                    room = "Florence";
                                    break;
                                
                                case 'G':
                                    room = "Genesis";
                                    break;
                                
                                case 'H':
                                    room = "Helion";
                                    break;
                                }
                                cout << left << setw(8) << ++number << setw(12) << room << setw(42) << reservConfirm.eventDescription << endl;
                            }
                            cout << "   Enter Reservation You Want to Confirm: ";
                            cin >> nReservation;
                            while (cin.fail())
                            {
                                cin.clear();
                                cin.ignore(100, '\n');
                                nReservation = 0;
                                cout << "   Error! Reservation can only be a numeric whole number!\n";
                                cout << "   Enter Your Choice: ";
                                cin >> nReservation;
                            }
                            fbin.close();

                            switch(nReservation){
                            case 1:
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                if (reservConfirm.reservStatus == 'X'){
                                    cout << "   Sorry this Reservation has been cancelled.\n";
                                }
                                else if (reservConfirm.reservStatus == 'C'){
                                    cout << "   Error. This Reservation has been confirmed.\n";
                                }else {
                                    reservConfirm.reservStatus = 'C'; //Change Status
                                    cout << "   Your reservation is confirmed.\n";
                                }
                                fbin.seekp(-sizeof(reservConfirm),ios::cur);
                                fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                                validateOption = true;
                                break;
                            case 2:
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                if (reservConfirm.reservStatus == 'X'){
                                    cout << "   Sorry this Reservation has been cancelled.\n";
                                }
                                else if (reservConfirm.reservStatus == 'C'){
                                    cout << "   Error. This Reservation has been confirmed.\n";
                                }else {
                                    reservConfirm.reservStatus = 'C'; //Change Status
                                    cout << "   Your reservation is confirmed.\n";
                                }
                                fbin.seekp(-sizeof(reservConfirm),ios::cur);
                                fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                                validateOption = true;
                                break;

                            case 3:
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                if (reservConfirm.reservStatus == 'X'){
                                    cout << "   Sorry this Reservation has been cancelled.\n";
                                }
                                else if (reservConfirm.reservStatus == 'C'){
                                    cout << "   Error. This Reservation has been confirmed.\n";
                                }
                                else {
                                    reservConfirm.reservStatus = 'C'; //Change Status
                                    cout << "   Your reservation is confirmed.\n";
                                }
                                fbin.seekp(-sizeof(reservConfirm),ios::cur);
                                fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                                validateOption = true;
                                break;

                            case 4:
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                if (reservConfirm.reservStatus == 'X'){
                                    cout << "   Sorry this Reservation has been cancelled.\n";
                                }
                                else if (reservConfirm.reservStatus == 'C'){
                                    cout << "   Error. This Reservation has been confirmed.\n";
                                }
                                else {
                                    reservConfirm.reservStatus = 'C'; //Change Status
                                    cout << "   Your reservation is confirmed.\n";
                                }
                                fbin.seekp(-sizeof(reservConfirm),ios::cur);
                                fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                                validateOption = true;
                                break;

                            case 5:
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                                if (reservConfirm.reservStatus == 'X'){
                                    cout << "   Sorry this Reservation has been cancelled.\n";
                                }
                                else if (reservConfirm.reservStatus == 'C'){
                                    cout << "   Error. This Reservation has been confirmed.\n";
                                }else {
                                    reservConfirm.reservStatus = 'C'; //Change Status
                                    cout << "   Your reservation is confirmed.\n";
                                }
                                fbin.seekp(-sizeof(reservConfirm),ios::cur);
                                fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                                validateOption = true;
                                break;
                            }
                        }

                        else {
                            fbin.read((char*)&reservConfirm,sizeof(reservConfirm));
                            if (reservConfirm.reservStatus == 'X'){
                                cout << "   Sorry this Reservation has been cancelled.\n";
                            }
                            else if (reservConfirm.reservStatus == 'C'){
                                cout << "   Error. This Reservation has been confirmed.\n";
                            }else {
                                reservConfirm.reservStatus = 'C'; //Change Status
                                cout << "   Your reservation is confirmed.\n";
                            }
                            fbin.seekp(-sizeof(reservConfirm),ios::cur);
                            fbin.write((char *)&reservConfirm, sizeof(reservConfirm));
                            validateOption = true;
                        }
                    }

                    if(option == 'N'){
                        cout << "   Please confirm your reservation before your actual date." << endl;
                        validateOption = true;
                    }

                    if(option != 'Y' && option != 'N'){
                        cout << "   Error!!!Please enter Y or N only." << endl;
                        validateOption = false;
                    }

                }while (validateOption == false);
                existcode = true;
            }

            else{
                cout << "   Your reservation is not exist. Please try it again" << endl;
                existcode = false;
                count ++;
                if (count >= 3){
                    existcode = true;
                }
            }

            fbin.close();
        }while(existcode == false);
        cout << "\n   Returning back to Enquiries...\n";
        system("pause");

    }
}