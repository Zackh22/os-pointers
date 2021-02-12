// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments;
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);
//Will be used to keep track of toal # assignments for other functions.
int assignment_num = 0;

int main(int argc, char **argv)
{
    Student student;
    double average;
    std::string doubleMessage = new char[127];
    student.f_name = new char[127];
    student.l_name = new char[127];

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 1, 999999999);
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;
    student.n_assignments = promptInt("Please enter how many assigments were graded: ", 1, 134217728);
    std::cout << "\n";
    student.grades = new double[student.n_assignments];
    for(assignment_num = 0; assignment_num < student.n_assignments; assignment_num++){
        doubleMessage = ""; //Clears the message after each loop.
        doubleMessage += "Please enter grade for assingment "; // The basic message
        doubleMessage += std::to_string(assignment_num); // This adds the number.
        doubleMessage += ": ";
        student.grades[assignment_num] = promptDouble(doubleMessage, 0, 1000.0);
    }
    std::cout << "\nStudent: " << student.f_name << " " << student.l_name << " [" << student.id << "]" << std::endl;
    // Call `CalculateStudentAverage(???, ???)`
    calculateStudentAverage(student.grades, &average);
   
    // Output `average`
    std::cout << "  Average grade: " << average << std::endl;

    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    // Code to prompt user for an int
    std::string input;
    
    bool isInt = false;
    int in;
    while(!isInt){
        isInt = true;
        std::cout << message;
        std::cin >> input;
        // Error Checking for the input value
        if(input.find_first_not_of("0123456789") != std::string::npos){
            isInt = false;
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
        }
        else if(std::stoi(input) < min || std::stoi(input) > max){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            isInt = false;
        }
        else
        {
            in = std::stoi(input);
        }
    }
    return in;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)
{
    // Code to prompt user for a double
    int decimalPointCounter;
    int isDub = 0;
    int gradeSize =0;
    double grade;
    std::string inGrade;
    /*
    std::cout << message;
    std::cin >> inGrade;
    */
    while(isDub != 1){
        isDub = 0;
        decimalPointCounter = 0;
        std::cout << message;
        std::cin >> inGrade;
        // This if statement catches if the input is only a "."
        if(inGrade.size() == 1 && inGrade.find_first_of(".") != std::string::npos){
            std::cout << "Sorry, I cannot understand your answer" << std::endl;
            isDub = 0;
        }
        else{
            if(inGrade.find_first_not_of("0123456789.") != std::string::npos){
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
                isDub = 0;
            } else if(std::stod(inGrade) > max || std::stod(inGrade) < min){
                isDub = 0;
                std::cout << "Sorry, I cannot understand your answer" << std::endl;
            }else{
                // This while loop looks to see if there are multiple decimal points
                while(gradeSize < inGrade.size()){
                    // If it is a '.' increase counter
                    if(inGrade[gradeSize] == '.'){
                        decimalPointCounter++;
                    }
                    gradeSize++;
                }
                if(decimalPointCounter > 1){
                    std::cout << "Sorry, I cannot understand your answer" << std::endl;
                    isDub = 0;
                }else{
                    grade = std::stod(inGrade);
                    isDub = 1;
                }
            }
        }
    }
    /*
    while(grade > max || grade < min){
        std::cout << "Sorry, I cannot understand your answer" << std::endl;
        std::cout << message;
        std::cin >> grade;
    }
    */
    return grade;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // Code to calculate and store average grade
    double total = 0;
    int j = 0;

    for (j = 0; j< assignment_num; j++){
        total = total + ((double*)object)[j]; //casts to a double pointer
    }
    //dividing by number of assignemnts
    total = total/(int)(j);

    // Rounding
    total += 0.05;
    total *= 10;
    int temp = (int) total;
    total = (double) temp/10;
    // assigning *avg to total
    *avg = total;
}
