#include<iostream>
using namespace std;

#include"Neuron.h"

void main()
{
	srand(time(NULL));

	NW nw;
	cout << nw.Train() << endl;
	nw.ShowTests();
}