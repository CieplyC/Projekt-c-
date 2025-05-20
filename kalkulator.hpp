#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <vector>

#define MAX_OPERATIONS 100

typedef std::string Text;

namespace my_calculator
{
    struct Operation
    {
        Text name;
        double result;
        char operatorChar;
    };

    double add(double a, double b);
    double subtract(double a, double b);
    double multiply(double a, double b);
    double divide(double a, double b);

    void saveOperation(const Operation& op);
    void showHistory();
    void sortHistory();
    void saveHistoryToFile();
}

#endif