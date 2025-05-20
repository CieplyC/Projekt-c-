#include "kalkulator.hpp"
#include <iostream>
#include <algorithm>

namespace my_calculator
{

    static std::vector<Operation> history;

    double add(double a, double b)
    {
        return a + b;
    }

    double subtract(double a, double b)
    {
        return a - b;
    }

    double multiply(double a, double b)
    {
        return a * b;
    }

    double divide(double a, double b)
    {
        if (b == 0)
        {
            std::cout << "Error: Division by zero!\n";
            return 0;
        }
        return a / b;
    }

    void saveOperation(const Operation &op)
    {
        if (history.size() < MAX_OPERATIONS)
        {
            history.push_back(op);
        }
    }

    void showHistory()
    {
        std::cout << "\n== Operation History ==\n";
        for (const auto &op : history)
        {
            std::cout << op.name << " " << op.operatorChar << " " << op.result << "\n";
        }
    }

    void sortHistory()
    {
        std::sort(history.begin(), history.end(), [](const Operation &a, const Operation &b)
                  { return a.result < b.result; });
        std::cout << "History sorted by result.\n";
    }
}
