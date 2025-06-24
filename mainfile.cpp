#include<iostream>

class Student {
    int roll;
    std::string name;
    float English_marks;
    float Hindi_marks;
    float Chemistry_marks;
    float Maths_marks;
    float Science_marks;
public:
    void input() {
        std::cout << "Enter roll number: ";
        std::cin >> roll;
        std::cout << "Enter name: ";
        std::cin >> name;
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
    void display() {
        std::cout << "Roll Number: " << roll << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Total Marks: " << (English_marks + Hindi_marks + Chemistry_marks + Maths_marks + Science_marks) << std::endl;
    }
    
};

int main(){

    return 0;
}