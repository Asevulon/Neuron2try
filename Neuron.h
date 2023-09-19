#pragma once
#include<vector>
using namespace std;


struct neuron
{
	vector<double> in;
	double out = 0;
	
	vector<double> w;
	double fi = 0;

	neuron() {}
	neuron(int size);
};


class NW
{
private:
	static const int _size = 4;
	neuron first[_size];
	neuron second;

	double _betta;

	vector<vector<double>>test;
	vector<double> answers;

protected:
	void CreateTests();
	void ProcessNeuron(neuron& n, vector<double>& in);
	inline double f(double x);
	inline double df(double x);
	inline bool isTestsUnsucceed(bool* test);
public:
	NW();

	double Calc(vector<double>& in);
	int Train();

	void ShowTests();
};