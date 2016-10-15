//
//  main.cpp
//  homework 4
//
//  Created by Dustin Ramsey on 8/3/15.
//  Copyright (c) 2015 Dustin Ramsey. All rights reserved.
//
//

#include "imports.h"


int main()
{
    
	AdjListGraph g;

	string start;

	string end;

	unsigned int const number_of_times = 10;

	for (unsigned int i = 0; i < number_of_times; i++)
	{
		cout << "0: Enter two words: \n";

		cin >> start;

		cin >> end;

		clock_t start1 = clock();    

        g.path(start, end);

		cout << "1: Time to compute: " << (clock() - start1) / (double) CLOCKS_PER_SEC << endl << endl;
	}
    
	return 0;
}
