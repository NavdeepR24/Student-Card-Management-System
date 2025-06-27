#include<iostream>
#include<string>
#include<conio.h>



class Student {
    int roll;
    std::string name;
    float English_marks;
    float Hindi_marks;
    float Chemistry_marks;
    float Maths_marks;
    float Science_marks;
public:
    void setmarks() {
        std::cout << "Enter roll number: ";
        std::cin >> roll;
        std::cout << "The length of the name must be less then 20 characters\nEnter the name of the student: ";
        std::getline(std::cin, name);
        std::cout << "Enter English marks: ";
        std::cin >> English_marks;
        std::cout << "Enter Hindi marks: ";
        std::cin >> Hindi_marks;
        std::cout << "Enter Chemistry marks: ";
        std::cin >> Chemistry_marks;
        std::cout << "Enter Maths marks: ";
        std::cin >> Maths_marks;
        std::cout << "Enter Science marks: ";
        std::cin >> Science_marks;

    }

    int persentage() {
        float total_marks = English_marks + Hindi_marks + Chemistry_marks + Maths_marks + Science_marks;
        return (total_marks / 500) * 100; 
    }

    char grade() {
        int percent = persentage();
        if (percent >= 90) return 'A';
        else if (percent >= 80) return 'B';
        else if (percent >= 70) return 'C';
        else if (percent >= 60) return 'D';
        else if (percent >= 50) return 'E';
        else return 'F';
    }

    void display() {
        std::cout << "Roll Number: " << roll << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << name << " has secured " << persentage() << "% and is graded " << grade() << std::endl;
    }
    
};

int main(){
    int enterRollNo;

    system("cls");

    Student s1;

    // s1.setmarks();

    while(true){

        system("cls");

        int choice;

        std::cout<<"\t\t***** WECLOME TO THE SYSTEM *****\t\t"<<std::endl<<std::endl;
        std::cout<<"\t What can I do for you"<<std::endl;
        std::cout<<"1\tPress one for adding a new student in the system"<<std::endl;
        std::cout<<"2\tPress two for deleting a student form the system"<<std::endl;
        std::cout<<"3\tPress three for searching a student in the system"<<std::endl;
        std::cout<<"4\tPress four for getting the list of all the names and roll numbers of all the students"<<std::endl;
        std::cout<<"5\tPress five for exiting the system"<<std::endl;

        std::cin>>choice;

        switch (choice)
        {
        case 1 :
            /* code */
            break;

        case 2 :
            /* code */
            break;

        case 3 :
            /* code */
            break;

        case 4 :
            /* code */
            break;

        case 5 :
            
            std::cout<<"Thanks for Visiting!..."<<std::endl;

            exit(0);
            break;
        
        default:

            std::cout<<"Invlaid user input!"<<std::endl;
            std::cout<<"Press Enter and try again..."<<std::endl;

            getch();

            break;
        }


    }

    return 0;
}