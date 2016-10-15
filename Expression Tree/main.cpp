#include "imports.h"

int main()
{
    
    ifstream f("homework1.txt");
    vector<string> string_expressions;
    string expression;
    
    while (f.good())
    {
        getline(f, expression);
        string_expressions.push_back(expression);
        
        if (f.eof())
        {
            f.close();
            break;
        }
    }
    
    for(auto &expression: string_expressions)
    {
        Expression e(expression);
        cout << endl;
    }
    
    return 0;
}