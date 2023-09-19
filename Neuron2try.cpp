#include<iostream>
using namespace std;

#include"Neuron.h"

void main()
{
	NW nw;
	cout << nw.Train() << endl;
	
	nw.ShowTests();
}