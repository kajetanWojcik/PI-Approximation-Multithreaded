#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <ctime>
#include <thread>
#include <mutex>
#include <float.h>
#include <string>

#define MAX_THREADS 100

using namespace std;

mutex locker;

int pointsInsideSquare;
int pointsInsideCircle = 0;
int threadsNumber;


void piApproximation(int inputPoints, double startOrigin, double endOrigin, double start, double end) {
	mt19937 generator{random_device{}() };
	uniform_real_distribution<double> randomX{startOrigin, endOrigin};
	uniform_real_distribution<double> randomY{start, end};

	double x, y;
	for (int i = 0; i < inputPoints; i++)
	{
		x = randomX(generator);
		y = randomY(generator);

		if (x*x + y*y <= 1)
		{
			locker.lock();
			++pointsInsideCircle;
			locker.unlock();
		}
	}
}


void piApproximationMultithreaded(double start, double end) {
	vector<thread> thVector;
	unsigned int thSquareSpread = pointsInsideSquare / threadsNumber;

	double startOrigin = start;
	double endOrigin = end;

	double thSpread = end / (double) threadsNumber;
	double newEnd = start + thSpread - DBL_MIN;

	for (int j = 0; j < threadsNumber; j++) {
		thVector.emplace_back(piApproximation, thSquareSpread, startOrigin, endOrigin, start, newEnd);
		start += thSpread;
		newEnd += thSpread;
	}

	for (auto& k : thVector) {
		k.join();
	}
}


void initialization() {
	bool validSamplesInput = false;
	bool validThreadsInput = false;

	cout << "Multithreaded PI value approximation using Monte Carlo method.\n";

	int samplesInput;
	int threadsInput;

	do {
		cout << "\nSpecify number of samples: ";

		if (!(cin >> samplesInput)) {
			cout << "Wrong Input Type. \nPlease input a number greater than 0 and less or equal " << INT32_MAX << ".\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			if (samplesInput <= 0) {
				cout << "Wrong number. \nPlease input a number greater than 0 and less or equal " << INT32_MAX << ".\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else {
				pointsInsideSquare = samplesInput;
				validSamplesInput = true;
			}
		}
	} while (validSamplesInput != true);


	do {
		cout << "\nSpecify desired number of threads: ";

		if (!(cin >> threadsInput)) {
			cout << "Wrong Input Type. \nPlease input a number greater than 0 and less or equal " << MAX_THREADS << ".\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else {
			if (threadsInput <= 0 || threadsInput > MAX_THREADS) {
				cout << "Wrong number. \nPlease input a number greater than 0 and less or equal " << MAX_THREADS << ".\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			else {
				threadsNumber = threadsInput;
				validThreadsInput = true;
			}
		}
	} while (validThreadsInput != true);

	cout << "\n - - - - - - - - - - Approximation in process - - - - - - - - - - " << endl;
}


void printResults(double PI, int startTime, int endTime){
	cout << "\nResults after testing " << pointsInsideSquare << " samples using " << threadsNumber << " threads:" << endl;
	cout << "\n\tApproximated PI value = " << PI << endl;
	cout << "\tPoints inside the circle = " << pointsInsideCircle << " of " << pointsInsideSquare << endl;
	cout << "\tExecution time = " << (endTime - startTime) / double(CLOCKS_PER_SEC) << " s\n" << endl;
}


int main(){

	double squareStartPoint = 0.;
	double squareEndPoint = 1.;

	initialization();

	int startTime = clock();
	piApproximationMultithreaded(squareStartPoint, squareEndPoint);
	int endTime = clock();

	double PI = 4. * pointsInsideCircle / pointsInsideSquare;
	printResults(PI, startTime, endTime);
	
	system("pause");

	return 0;
}