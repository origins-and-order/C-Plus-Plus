//
//  final_ladder.h
//  homework 4
//
//  Created by Dustin Ramsey on 8/16/15.
//  Copyright (c) 2015 Dustin Ramsey. All rights reserved.
//

class AdjListGraph{
private:
    
    unordered_set<string> dict;
    
    unordered_map<string, set<string> > graph;
    
    set<string> adjacent_words(const string &word)
    {
        set<string> tmp_set;
        
        for (unsigned int i = 0; i < word.size(); i++)
        {
            string tmp = word;
                        
            for (char j = 'a'; j <= 'z'; j++)
            {
                tmp[i] = j;
                
                bool found = dict.find(tmp) != dict.end();
                
                if (found && tmp != word)
                {
                    tmp_set.insert(tmp);
                }
            }
        }
        
        return tmp_set;
    }
    /* 
        read in dictionary,
        create graph
    */
    void build_graph()
    {
        ifstream ifs("dictionary.txt");
        
        while (ifs.good())
        {
            string word;
            ifs >> word;
            dict.insert(word);
            if (ifs.eof())
                break;
        }
        
        ifs.close();
        
        for (auto &word: dict)
        {
            graph[word] = adjacent_words(word);
        }
    }
    
    stack<string> breadth_first_search(const string &start, const string &end)
    {
        queue<string> unvisited;
        
        unvisited.push(start);
        
        unordered_map<string, string> visited;
        
        stack<string> path;
        
        bool found = false;
        
        while (!found)
        {
            string vertex = unvisited.front();
            unvisited.pop();
            
            for(auto &edge: graph[vertex])
            {
                if (visited.find(edge) == visited.end())
                {
                    visited[edge] = vertex;
                    unvisited.push(edge);
                }
            }
            /* if end is in visited */
            if (visited.find(end) != visited.end())
            {   
                path.push(end);
                
                while (true)
                {
                    if (path.top() == start)
                    {
                        found = true;
                        break;
                    }
                    
                    else
                        path.push(visited[path.top()]);
                }
            }
        }
        
        return path;
    }
    
public:
    
    AdjListGraph()
    {
        cout << "0: Building Adjacency List Graph.\n";
        
        clock_t start = clock();
        
        build_graph();
        
        cout << "1: Adjacency List Graph built.\n";
        
        cout << "2: Time to create graph: " << (clock() - start) / (double) CLOCKS_PER_SEC << " seconds.\n";
    }
    
    void path(const string &start, const string &end)
    {
        auto path = breadth_first_search(start, end);
        
        if (path.size() == 0)
        {
            cout << "No ladder can be constructed.\n";
        }
        
        else
        {
            cout << "Size of ladder: " << path.size() << ".\n";
            
            while (!path.empty())
            {
                cout << path.top() << endl;
                path.pop();
            }
        }
    }
};
