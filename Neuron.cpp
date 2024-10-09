#include"Neuron.h"
#include<time.h>
#include<iostream>

double rand(double left, double right)
{
	return left + (right - left) * double(rand()) / double(RAND_MAX);
}


neuron::neuron(int size)
{
	in = vector<double>(size, 0);
	w = vector<double>(size, 0);
	for (int i = 0; i < size; i++)
	{
		w[i] = rand(-1, 1);
	}
	fi = rand(-1, 1);
}


NW::NW()
{
	_betta = 0.1;
	for (int i = 0; i < _size; i++)
	{
		first[i] = neuron(3);
	}
	second = neuron(_size);
	CreateTests();
}


void NW::CreateTests()
{
	test = { {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
	{1,0,0}, {1,0,1}, {1,1,0}, {1,1,1} };
	answers = { 0,1,1,0,1,0,0,1 };
}


void NW::ProcessNeuron(neuron& n, vector<double>& in)
{
	n.in = in;
	double res = 0;
	for (int i = 0; i < in.size(); i++)
	{
		res+= n.w[i] * in[i];
	}
	res -= n.fi;
	n.out = f(res);
}
double NW::Calc(vector<double>& in)
{
	vector<double>tin(_size, 0);
	for (int i = 0; i < _size; i++)
	{
		ProcessNeuron(first[i], in);
		tin[i] = first[i].out;
	}

	ProcessNeuron(second, tin);
	return second.out;
}

double NW::f(double x)
{
	return 1. / (1. + exp(- 2 * x));
}
double NW::df(double x)
{
	return x * (1 - x);
}


int NW::Train()
{
	int ctr = 0;

	bool TestRes[8] = { 0,0,0,0,0,0,0,0 };

	do
	{
		for (int i = 0; i < 8; i++)
		{
			double res = Calc(test[i]);
			res -= answers[i];
			res *= res;
			if (res < 1e-6)
			{
				TestRes[i] = true;
				continue;
			}
			else TestRes[i] = false;


			double tDelta = -2 * second.out * (1 - second.out) * (answers[i] - second.out);
			double fDelta[_size];
			for (int j = 0; j < _size; j++)
			{
				fDelta[j] = 2 * first[j].out * (1 - first[j].out) * tDelta * second.w[j];
			}


			for (int j = 0; j < _size; j++)
			{
				second.w[j] -= 0.1 * tDelta * second.in[j];
			}
			second.fi += 0.1 * tDelta;


			for (int j = 0; j < _size; j++)
			{
				for (int k = 0; k < 3; k++)
				{
					first[j].w[k] -= 0.1 * fDelta[j] * first[j].in[k];
				}
				first[j].fi += 0.1 * fDelta[j];
			}
		}

		ctr++;


		if (ctr > 10000000)break;
	} while (isTestsUnsucceed(TestRes));
	return ctr;
}

bool NW::isTestsUnsucceed(bool* test)
{
	for (int i = 0; i < 8; i++)
	{
		if (!test[i])return true;
	}
	return false;
}


void NW::ShowTests()
{
	cout << "\n\nTest showcase:\n\n";
	for (int i = 0; i < test.size(); i++)
	{
		double calc = Calc(test[i]);
		double mist = calc - answers[i];
		mist *= mist;
		string str = "ok";
		if (mist > 1e-2) str = "WA";
		printf("{ %d, %d, %d }\t%.3f\tans: %d\t%s\n", (int)test[i][0], (int)test[i][1], (int)test[i][2], calc, (int)answers[i], str.c_str());

	}
	cout << "\n\n";
}
