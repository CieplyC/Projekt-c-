#define _USE_MATH_DEFINES
#include "kalkulator.hpp"
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <locale.h>
#include <cmath>

using namespace std;

int outputPrecision = 2;

void enterSettings()
{
    cout << "\n== Settings Menu ==\n";
    cout << "General output precision (out): " << outputPrecision << "\n";
    cout << "Enter option to change (out): ";

    string choice;
    cin >> choice;

    if (choice == "out")
    {
        int newOut;
        cout << "Enter new output precision (0 - 100): ";
        cin >> newOut;
        if (cin.fail() || newOut < 0 || newOut > 100)
        {
            cout << "Invalid input. Output precision remains: " << outputPrecision << "\n";
        }
        else
        {
            outputPrecision = newOut;
            cout << "Output precision set to: " << outputPrecision << "\n";
        }
    }
    else
    {
        cout << "Unknown setting option.\n";
    }

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "Polish");
    cout << "== Flapz Calculator ==\n";
    cout << "Calculator created by Błażej Ciepiel\n";
    cout << "Enter a math operation, or type exit, history, sort, settings\n";
    cout << defaultfloat << setprecision(outputPrecision);

    if (argc > 1)
    {
        for (int i = 1; i < argc; ++i)
        {
            cout << "Arg " << i << ": " << argv[i] << "\n";
        }
    }

    string input;

    while (true)
    {
        cout << "> ";
        getline(cin, input);

        if (input == "exit")
            break;
        else if (input == "history")
        {
            my_calculator::showHistory();
            continue;
        }
        else if (input == "sort")
        {
            my_calculator::sortHistory();
            continue;
        }
        else if (input == "settings")
        {
            enterSettings();
            cout << fixed << setprecision(outputPrecision);
            continue;
        }

        stringstream spaced;
        for (char c : input)
        {
            if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                spaced << ' ' << c << ' ';
            }
            else
            {
                spaced << c;
            }
        }

        vector<string> tokens;
        string token;
        while (spaced >> token)
        {
            if (token == "pi")
            {
                tokens.push_back(to_string(M_PI));
            }
            else
            {
                tokens.push_back(token);
            }
        }

        if (tokens.size() < 3 || tokens.size() % 2 == 0)
        {
            cout << "Invalid expression format.\n";
            continue;
        }

        double result;
        try
        {
            result = stod(tokens[0]);
        }
        catch (...)
        {
            cout << "Invalid number: " << tokens[0] << "\n";
            continue;
        }

        bool error = false;

        for (size_t i = 1; i < tokens.size(); i += 2)
        {
            char op = tokens[i][0];
            double next;

            try
            {
                next = stod(tokens[i + 1]);
            }
            catch (...)
            {
                cout << "Invalid number: " << tokens[i + 1] << "\n";
                error = true;
                break;
            }

            switch (op)
            {
            case '+':
                result = my_calculator::add(result, next);
                break;
            case '-':
                result = my_calculator::subtract(result, next);
                break;
            case '*':
                result = my_calculator::multiply(result, next);
                break;
            case '/':
                result = my_calculator::divide(result, next);
                break;
            default:
                cout << "Unknown operator: " << op << "\n";
                error = true;
                break;
            }
        }

        if (!error)
        {
            cout << "Result: " << result << "\n";
            my_calculator::saveOperation({input, result, '='});
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
