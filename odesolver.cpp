#include <iostream>
#include <string>
#include "exprtk.hpp"

using std::cout, std::cin, std::cerr, std::getline, std::endl, std::string, std::vector, std::pair;

template <typename T>
class ExpressionWrapper
{
private:
    typedef exprtk::symbol_table<T> symbol_table_type;
    typedef exprtk::expression<T>   expression_type;
    typedef exprtk::parser<T>       parser_type;

    symbol_table_type symbol_table;
    expression_type   expr;
    parser_type       parser;

    T x_, y_, z_;

public:
    ExpressionWrapper(const string& expression_string)
        : x_(T())
    {
        symbol_table.add_variable("x", x_);
        symbol_table.add_constants();

        expr.register_symbol_table(symbol_table);
        
        if (!parser.compile(expression_string, expr))
        {
            throw std::runtime_error("Failed to compile expression: " + expression_string);
        }
    }

    T operator()(T x)
    {
        x_ = x;
        return expr.value();
    }
};

double evalExpr(string userInput, double x)
{
    ExpressionWrapper<double> expression(userInput);
    return expression(x);
}

template <typename T>
class HelperFunctions
{
public:
    vector<T> linspace(T start, T end, int n)
    {
        vector<T> result(n);
        T delta = (end - start) / (n - 1);

        for (int i = 0; i < n; i++){
            result[i] = start + i * delta;
        }

        return result;
    }
};


class ODESolver
{
public:
    double EulersMethod(string expr, pair<double, double> ICs, double xTarget, int num_steps = 500)
    {
        /*
        * Euler's method to solve the ODE
        * expr: The ODE as a string
        * ICs: The initial conditions as a pair<double, double>
        * xTarget: The target value of x
        * num_steps: The number of steps to take
        * 
        * Returns: the value of y at xTarget
        */

        HelperFunctions<double> helper;
        vector<double> results(num_steps);

        // Unpack the ICs
        double x = ICs.first;
        double y = ICs.second;

        double delta = (xTarget - x) / (num_steps - 1);
        vector<double> xes = helper.linspace(x, xTarget, num_steps);

        for (int i = 0; i < num_steps; i++)
        {
            y += evalExpr(expr, xes[i]) * delta;
            results[i] = y; // Store the results
        }

        return y;
    }

    double RungeKutta2ndOrder(string expr, pair<double, double> ICs, double xTarget, int num_step = 500){
        /*
        * Runge-Kutta 2nd Order method to solve the ODE
        * expr: The ODE as a string
        * ICs: The initial conditions as a pair<double, double>
        * xTarget: The target value of x
        * num_steps: The number of steps to take
        * 
        * Returns: the value of y at xTarget
        */

        HelperFunctions<double> helper;
        vector<double> results(num_step);

        // Unpack the ICs
        double x = ICs.first;
        double y = ICs.second;
        double delta = (xTarget - x) / (num_step - 1);

        vector<double> xes = helper.linspace(x, xTarget, num_step);

        for (int i = 0; i < num_step; i++)
        {
            double f1 = evalExpr(expr, xes[i]);
            double f2 = evalExpr(expr, xes[i] + (1 / 2) * f1);
            y += delta * f2;
            results[i] = y; // Store the results
        }

        return y;
    }

    double RungeKutta4thOrder(string expr, pair<double, double> ICs, double xTarget, int num_step = 500){
        /*
        * Runge-Kutta 4th Order method to solve the ODE
        * expr: The ODE as a string
        * ICs: The initial conditions as a pair<double, double>
        * xTarget: The target value of x
        * num_steps: The number of steps to take
        * 
        * Returns: the value of y at xTarget
        */

        HelperFunctions<double> helper;
        vector<double> results(num_step);

        // Unpack the ICs
        double x = ICs.first;
        double y = ICs.second;

        double delta = (xTarget - x) / (num_step - 1);
        vector<double> xes = helper.linspace(x, xTarget, num_step);

        for (int i = 0; i < num_step; i++){
            double f1 = evalExpr(expr, xes[i]);
            double f2 = evalExpr(expr, xes[i] + (1 / 2) * f1);
            double f3 = evalExpr(expr, xes[i] + (1 / 2) * f2);
            double f4 = evalExpr(expr, xes[i] + f3);

            y += delta * (f1 + 2 * f2 + 2 * f3 + f4) / 6;
            results[i] = y; // Store the results
        }

        return y;
    }
};

int main()
{
    try
    {
        ODESolver solver;
        int num_steps = 500;
        pair<double, double> ICs;

        string expression_string;
        string initial_conditions;
        string evaluationTarget;

        // Get the ODE
        cout << "Enter the ODE as expression. F'(x) = ";
        getline(cin, expression_string);

        // Get the ICs
        cout << "\nEnter the ODE Iniitial Conditions. (x0, y0) = ";
        getline(cin, initial_conditions);

        // Get the evaluation target
        cout << "\nEnter the evaluation target. x = ";
        getline(cin, evaluationTarget);

        // Get the number of steps to do
        cout << "\nEnter the number of steps to take. Default is 500. Steps = ";
        cin >> num_steps;

        // Convert initial conditions to a pair<double, double>
        int splitIdx = initial_conditions.find(",");
        ICs.first = stod(initial_conditions.substr(0, splitIdx));
        ICs.second = stod(initial_conditions.substr(splitIdx + 1));

        cout << "\nEuler's Method (Forward): " << solver.EulersMethod(expression_string, ICs, stod(evaluationTarget), num_steps) << endl;
        cout << "Runge-Kutta 2nd Order: " << solver.RungeKutta2ndOrder(expression_string, ICs, stod(evaluationTarget), num_steps) << endl;
        cout << "Runge-Kutta 4th Order: " << solver.RungeKutta4thOrder(expression_string, ICs, stod(evaluationTarget), num_steps) << endl;
    }
    catch (const std::exception &e)
    {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}