#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<conio.h>

class Student {
    int roll_No;
    std::string name, mailId, Contact_No, address, course;
    float CGPA;

public:
    void addstudent() {
        system("cls");
        std::fstream file;
        std::cout << "\t\t***** Add Student *****\t\t" << std::endl << std::endl;
        
        std::cout << "Enter roll number: ";
        std::cin >> roll_No;
        std::cin.ignore(); // Clear the input buffer
        
        std::cout << "Enter the name of the student: ";
        std::getline(std::cin, name);
        
        std::cout << "Enter the Course of the student: ";
        std::getline(std::cin, course);
        
        std::cout << "Enter student's CGPA: ";
        std::cin >> CGPA;
        std::cin.ignore(); // Clear the input buffer
        
        std::cout << "Enter student's mailId: ";
        std::getline(std::cin, mailId);
        
        std::cout << "Enter student's Contact No: ";
        std::getline(std::cin, Contact_No);
        
        std::cout << "Enter the address of the student: ";
        std::getline(std::cin, address);

        file.open("StudentRecord.txt", std::ios::app | std::ios::out);
        if(file.is_open()) {
            // Write data with quotes to handle spaces in names/addresses
            file << "\"" << name << "\" " << roll_No << " \"" << course << "\" " << CGPA << " \""
                 << mailId << "\" \"" << Contact_No << "\" \"" << address << "\"" << std::endl;
            file.close();
            std::cout << "\nStudent record added successfully!" << std::endl;
        } else {
            std::cout << "\nError: Unable to open file!" << std::endl;
        }
    }

    void display() {
        std::fstream file;
        int SNO = 0;
        system("cls");
        std::cout << "\t\t***** Student List *****\t\t" << std::endl << std::endl;
        
        file.open("StudentRecord.txt", std::ios::in);
        if(!file.is_open()) {
            std::cout << "\t\tNo data is present or file cannot be opened...\n";
        }
        else {
            std::string line;
            // Read line by line and parse manually
            while(std::getline(file, line)) {
                if(line.empty()) continue; // Skip empty lines
                
                // Parse the quoted strings and numbers
                std::istringstream iss(line);
                std::string token;
                
                // Read name (quoted)
                if(std::getline(iss, token, '"') && std::getline(iss, name, '"')) {
                    iss >> roll_No;
                    
                    // Read course (quoted)
                    if(std::getline(iss, token, '"') && std::getline(iss, course, '"')) {
                        iss >> CGPA;
                        
                        // Read email (quoted)
                        if(std::getline(iss, token, '"') && std::getline(iss, mailId, '"')) {
                            
                            // Read contact (quoted)
                            if(std::getline(iss, token, '"') && std::getline(iss, Contact_No, '"')) {
                                
                                // Read address (quoted)
                                if(std::getline(iss, token, '"') && std::getline(iss, address, '"')) {
                                    
                                    std::cout << "  S.No. " << ++SNO << std::endl;
                                    std::cout << "\t Student name       : " << name << std::endl;
                                    std::cout << "\t Student Roll No    : " << roll_No << std::endl;
                                    std::cout << "\t Student Course     : " << course << std::endl;
                                    std::cout << "\t Student CGPA       : " << CGPA << std::endl;
                                    std::cout << "\t Student Mail Id    : " << mailId << std::endl;
                                    std::cout << "\t Student Contact No : " << Contact_No << std::endl;
                                    std::cout << "\t Student address    : " << address << std::endl;
                                    std::cout << "\t" << std::string(50, '-') << std::endl;
                                }
                            }
                        }
                    }
                }
            }
            
            if(SNO == 0) {
                std::cout << "\t\tNo data is present..." << std::endl;
            }
        }
        file.close();
        
        // Add pause so user can read the data
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    void menu() {
        while(true) {
            system("cls");
            int choice;
            char x;

            std::cout << "\t\t***** WELCOME TO THE SYSTEM *****\t\t" << std::endl << std::endl;
            std::cout << "\t    What can I do for you" << std::endl;
            std::cout << "\t1 Press one for adding a new student in the system" << std::endl;
            std::cout << "\t2 Press two for deleting a student from the system" << std::endl;
            std::cout << "\t3 Press three for searching a student in the system" << std::endl;
            std::cout << "\t4 Press four for getting the list of the students" << std::endl;
            std::cout << "\t5 Press five for exiting the system" << std::endl;
            std::cout << "  \t ";

            std::cin >> choice;

            switch (choice) {
            case 1:
                do {
                    addstudent();
                    std::cout << "Want to add another student? Press (Y) if yes, (N) if no: ";
                    std::cin >> x;
                } while(x == 'y' || x == 'Y');
                break;

            case 2:
                std::cout << "Delete functionality not implemented yet." << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;

            case 3:
                std::cout << "Search functionality not implemented yet." << std::endl;
                std::cout << "Press Enter to continue...";
                std::cin.ignore();
                std::cin.get();
                break;

            case 4:
                display();
                break;

            case 5:
                std::cout << "Thanks for Visiting!..." << std::endl;
                exit(0);
                break;

            default:
                std::cout << "Invalid user input!" << std::endl;
                std::cout << "Press Enter and try again..." << std::endl;
                getch();
                break;
            }
        }
    }
};

int main() {
    Student s1;
    s1.menu();
    return 0;
}