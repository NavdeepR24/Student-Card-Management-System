#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<conio.h>
#include<vector>
#include<algorithm>

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

    void deleteStudent() {
        system("cls");
        std::cout << "\t\t***** Delete Student *****\t\t" << std::endl << std::endl;
        
        int rollToDelete;
        std::cout << "Enter roll number of student to delete: ";
        std::cin >> rollToDelete;
        
        std::fstream file, tempFile;
        std::string line;
        bool found = false;
        std::vector<std::string> allRecords;
        
        // Open original file for reading
        file.open("StudentRecord.txt", std::ios::in);
        if (!file.is_open()) {
            std::cout << "\nError: Unable to open file or no records found!" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            return;
        }
        
        // Read all records
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            allRecords.push_back(line);
        }
        file.close();
        
        // Find and display the record to delete
        std::string recordToDelete;
        for (const std::string& record : allRecords) {
            int currentRoll = extractRollNumber(record);
            if (currentRoll == rollToDelete) {
                found = true;
                recordToDelete = record;
                
                std::cout << "\nStudent found:" << std::endl;
                displaySingleRecord(record);
                break;
            }
        }
        
        if (!found) {
            std::cout << "\nStudent with roll number " << rollToDelete << " not found!" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            return;
        }
        
        char confirm;
        std::cout << "\nAre you sure you want to delete this record? (y/n): ";
        std::cin >> confirm;
        
        if (confirm == 'y' || confirm == 'Y') {
            // Write all records except the one to delete
            tempFile.open("temp.txt", std::ios::out);
            for (const std::string& record : allRecords) {
                if (record != recordToDelete) {
                    tempFile << record << std::endl;
                }
            }
            tempFile.close();
            
            remove("StudentRecord.txt");
            rename("temp.txt", "StudentRecord.txt");
            
            std::cout << "\nStudent record deleted successfully!" << std::endl;
        } else {
            std::cout << "\nDeletion cancelled." << std::endl;
        }
        
        std::cout << "Press Enter to continue...";
        std::cin.ignore();
        std::cin.get();
    }

    void searchStudent() {
        system("cls");
        std::cout << "\t\t***** Search Student *****\t\t" << std::endl << std::endl;
        
        int searchType;
        std::cout << "Search by:" << std::endl;
        std::cout << "1. Roll Number" << std::endl;
        std::cout << "2. Name" << std::endl;
        std::cout << "3. Course" << std::endl;
        std::cout << "Enter choice (1-3): ";
        std::cin >> searchType;
        std::cin.ignore();
        
        if (searchType < 1 || searchType > 3) {
            std::cout << "Invalid choice!" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.get();
            return;
        }
        
        std::string searchTerm;
        int rollNo;
        
        if (searchType == 1) {
            std::cout << "Enter roll number: ";
            std::cin >> rollNo;
            searchTerm = std::to_string(rollNo);
        } else if (searchType == 2) {
            std::cout << "Enter student name: ";
            std::getline(std::cin, searchTerm);
        } else {
            std::cout << "Enter course name: ";
            std::getline(std::cin, searchTerm);
        }
        
        std::fstream file;
        std::string line;
        std::vector<std::string> matchedRecords;
        int recordCount = 0;
        
        file.open("StudentRecord.txt", std::ios::in);
        if (!file.is_open()) {
            std::cout << "\nError: Unable to open file or no records found!" << std::endl;
            std::cout << "Press Enter to continue...";
            std::cin.ignore();
            std::cin.get();
            return;
        }
        
        // Search for matching records
        while (std::getline(file, line)) {
            if (line.empty()) continue;
            
            bool isMatch = false;
            if (searchType == 1) {
                // Search by roll number
                int currentRoll = extractRollNumber(line);
                if (currentRoll == rollNo) {
                    isMatch = true;
                }
            } else if (searchType == 2) {
                // Search by name (case-insensitive)
                std::string recordName = extractName(line);
                std::string lowerRecordName = recordName;
                std::string lowerSearchTerm = searchTerm;
                std::transform(lowerRecordName.begin(), lowerRecordName.end(), lowerRecordName.begin(), ::tolower);
                std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);
                
                if (lowerRecordName.find(lowerSearchTerm) != std::string::npos) {
                    isMatch = true;
                }
            } else {
                // Search by course (case-insensitive)
                std::string recordCourse = extractCourse(line);
                std::string lowerRecordCourse = recordCourse;
                std::string lowerSearchTerm = searchTerm;
                std::transform(lowerRecordCourse.begin(), lowerRecordCourse.end(), lowerRecordCourse.begin(), ::tolower);
                std::transform(lowerSearchTerm.begin(), lowerSearchTerm.end(), lowerSearchTerm.begin(), ::tolower);
                
                if (lowerRecordCourse.find(lowerSearchTerm) != std::string::npos) {
                    isMatch = true;
                }
            }
            
            if (isMatch) {
                matchedRecords.push_back(line);
                recordCount++;
            }
        }
        file.close();
        
        if (matchedRecords.empty()) {
            std::cout << "\nNo matching records found!" << std::endl;
        } else {
            std::cout << "\n" << recordCount << " matching record(s) found:" << std::endl;
            std::cout << std::string(60, '=') << std::endl;
            
            int displayCount = 0;
            for (const std::string& record : matchedRecords) {
                std::cout << "  Record " << ++displayCount << ":" << std::endl;
                displaySingleRecord(record);
                std::cout << std::string(50, '-') << std::endl;
            }
        }
        
        std::cout << "\nPress Enter to continue...";
        std::cin.ignore();
        std::cin.get();
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

    // Helper functions
    int extractRollNumber(const std::string& line) {
        std::istringstream iss(line);
        std::string token;
        int rollNo = -1;
        
        // Skip name (enclosed in quotes)
        if (line[0] == '"') {
            size_t pos = line.find('"', 1);  // Find closing quote
            if (pos != std::string::npos) {
                std::string remaining = line.substr(pos + 2); // Skip quote and space
                std::istringstream remainingStream(remaining);
                remainingStream >> rollNo;
            }
        }
        return rollNo;
    }

    std::string extractName(const std::string& line) {
        if (line[0] == '"') {
            size_t pos = line.find('"', 1);
            if (pos != std::string::npos) {
                return line.substr(1, pos - 1);
            }
        }
        return "";
    }

    std::string extractCourse(const std::string& line) {
        std::istringstream iss(line);
        std::string token, course;
        
        // Skip name
        if (std::getline(iss, token, '"') && std::getline(iss, token, '"')) {
            int rollNo;
            iss >> rollNo;
            
            // Read course
            if (std::getline(iss, token, '"') && std::getline(iss, course, '"')) {
                return course;
            }
        }
        return "";
    }

    void displaySingleRecord(const std::string& line) {
        std::istringstream iss(line);
        std::string token, tempName, tempCourse, tempMailId, tempContactNo, tempAddress;
        int tempRollNo;
        float tempCGPA;
        
        // Parse the record
        if(std::getline(iss, token, '"') && std::getline(iss, tempName, '"')) {
            iss >> tempRollNo;
            
            if(std::getline(iss, token, '"') && std::getline(iss, tempCourse, '"')) {
                iss >> tempCGPA;
                
                if(std::getline(iss, token, '"') && std::getline(iss, tempMailId, '"')) {
                    if(std::getline(iss, token, '"') && std::getline(iss, tempContactNo, '"')) {
                        if(std::getline(iss, token, '"') && std::getline(iss, tempAddress, '"')) {
                            
                            std::cout << "\t Student name       : " << tempName << std::endl;
                            std::cout << "\t Student Roll No    : " << tempRollNo << std::endl;
                            std::cout << "\t Student Course     : " << tempCourse << std::endl;
                            std::cout << "\t Student CGPA       : " << tempCGPA << std::endl;
                            std::cout << "\t Student Mail Id    : " << tempMailId << std::endl;
                            std::cout << "\t Student Contact No : " << tempContactNo << std::endl;
                            std::cout << "\t Student address    : " << tempAddress << std::endl;
                        }
                    }
                }
            }
        }
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
                deleteStudent();
                break;

            case 3:
                searchStudent();
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