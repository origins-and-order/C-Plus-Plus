
class Expression{
private:

    struct Token{
    public:
        string _operator = " ";
        double _operand;
        Token * left = NULL;
        Token * right = NULL;
    };

    vector<string> string_tokens;
    stack<string> _operators;
    stack<Token*> tree;

    bool read_expression(string expression)
    {
        unsigned int _operators = 0;
        unsigned int _operands = 0;
        unsigned int _closed_parenthesis = 0;
        unsigned int _opened_parenthesis = 0;

        for (unsigned int i = 0; i < expression.size(); i++) /* space tokens out */
        {
            if (expression[i]=='(')
            {
                _opened_parenthesis++;
                expression.insert(i+1, " ");
                i++;
            }
            else if(expression[i]==')')
            {
                _closed_parenthesis++;
                expression.insert(i, " ");
                i++;
            }
        }

        istringstream iss(expression);
        vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}}; /* split tokens into vector */
        set<string> __operators({"*","/","+","-"});
        
        for (auto &token: tokens)
        {
            if (__operators.find(token) != __operators.end())
                _operators++;
            else if(token != " " && token != "(" && token != ")")
                _operands++;
        }

        string_tokens = tokens;
        return _operands == _operators + 1 && _opened_parenthesis == _closed_parenthesis; /* correct syntax */
    }

    void build_tree()
    {
        set<string> __operators({"*","/","+","-","(",")"});

        for (auto &token: string_tokens)
        {

            bool is_number = __operators.find(token) == __operators.end();

            if (is_number) /* numeric */
            {
                Token * t = new Token;
                t->_operand = atof(token.c_str());
                tree.push(t);
            }
            else if(!is_number)/* operator*/
            {
                if(token == ")")
                {
                    while (_operators.top() != "(")
                    {
                        Token * t = new Token;
                        t->_operator = _operators.top();
                        _operators.pop();
                        t->right = tree.top();
                        tree.pop();
                        t->left = tree.top();
                        tree.pop();
                        tree.push(t);
                    }
                    _operators.pop();
                }
                else
                {
                    if (_operators.size() > 0 && (_operators.top() == "*" || _operators.top() == "/")) //precedence if higher on top of stack
                    {
                        Token * t = new Token;
                        t->_operator = _operators.top();
                        _operators.pop();
                        t->right = tree.top();
                        tree.pop();
                        t->left = tree.top();
                        tree.pop();
                        tree.push(t);
                        _operators.push(token);
                    }
                    else
                    {
                        _operators.push(token);
                    }
                }
            }
        }

        while (!_operators.empty())  /* pop remaining operators */
        {
            Token * t = new Token;
            t->_operator = _operators.top();
            _operators.pop();
            t->right = tree.top();
            tree.pop();
            t->left = tree.top();
            tree.pop();
            tree.push(t);
        }
    }

    double evaluate_tree(Token * t)
    {
        if(t->_operator == "*")
            return evaluate_tree(t->left) * evaluate_tree(t->right);
        else if (t->_operator == "/")
            return evaluate_tree(t->left) / evaluate_tree(t->right);
        else if (t->_operator == "+")
            return evaluate_tree(t->left) + evaluate_tree(t->right);
        else if (t->_operator == "-")
            return evaluate_tree(t->left) - evaluate_tree(t->right);
        else
            return t->_operand;
    }

    void print_prefix(Token * t)
    {
        if (t != NULL)
        {
            if (t->_operator != " ")
                cout << t->_operator << " ";
            else
                cout << t->_operand << " ";

            print_prefix(t->left);
            print_prefix(t->right);
        }
    }

    void print_infix(Token * t)
    {
        if (t != NULL)
        {
            print_infix(t->left);
            
            if (t->_operator != " ")
                cout << t->_operator << " ";
            else
                cout << t->_operand << " ";
            
            print_infix(t->right);
        }
    }
    
    void print_postfix(Token * t)
    {
        if (t != NULL)
        {
            print_postfix(t->left);
            

            if (t->_operator != " ")
                cout << t->_operator << " ";
            else
                cout << t->_operand << " ";
            
            print_postfix(t->right);
        }
    }

public:

    Expression(string exp)
    {
        if(read_expression(exp))
        {
            build_tree();
            cout << "Value is: " << evaluate_tree(tree.top()) << ".\n";
            
            cout << "Prefix: ";
            print_prefix(tree.top());
            cout << endl;

            cout << "Postfix: ";
            print_postfix(tree.top());
            cout << endl;
        }
        else
        {
            cout << "Syntax error.\n";
        }
    }
};
