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
        // Assuming each subject is out of 100
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

    return 0;
}