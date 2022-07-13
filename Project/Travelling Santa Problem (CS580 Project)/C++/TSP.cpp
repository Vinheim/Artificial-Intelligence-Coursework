#include "Point.h"
#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cmath>
#include <random>
#include <ctime>
#include <algorithm>
#include <limits.h>
#include <iomanip>

using namespace std;

vector<Point> cities(0);
vector<vector<int>> population(0);
vector<int> bestEver(0);
vector<int> currentBest(0);
vector<double> fitness(150000);

int numCities = 150000;
int totalCities = 150000;
int popSize = 150000;
double recordDistance = INT_MAX;
int updated = 0;

double calcDistance(vector<Point> &points, vector<int> &order);
void calculateFitness();
void normalizeFitness();
void nextGeneration();
vector<int> pickOne(vector<vector<int>> &lists, vector<double> &prob);
int randomIndex(int finish);
int randomIndex(int start, int finish);
vector<int> crossOver(vector<int> &orderA, vector<int> &orderB);
void swap(vector<int> &a, int i, int j);
vector<int> shuffle(int num, vector<int> &order);
void mutate(vector<int> &order, double mutationRate);

default_random_engine * gptr = new default_random_engine(time(NULL));
uniform_real_distribution<double> rando(0,1);

int main() 
{	
	int id = 0;
	int x = 0;
	int y = 0;
	ifstream inFile;
	
	vector<int> orderA(0);
	
	inFile.open("santa_cities.csv");
	string currentLine;
	getline(inFile, currentLine);
	while(!inFile.eof())
	{
		getline(inFile, currentLine, ',');
        id = stoi(currentLine);
        getline(inFile, currentLine, ',');
        x = stoi(currentLine);
        getline(inFile, currentLine);
        y = stoi(currentLine);
		
		orderA.push_back(id);
		cities.push_back(*(new Point(id,x,y)));
	}
	
	cout << "****************************************\n"
		 << "* Distance of Sequential Default Order *\n" 
		 << "****************************************\n";
	cout << fixed << int(calcDistance(cities, orderA));
	vector<int> orderB = orderA;
	cout << "before shuffle\n";
	orderB = shuffle(100, orderB);
	cout << "after shuffle\n" << int(calcDistance(cities, orderB));
	
	population.push_back(orderA);
	population.push_back(orderB);
	
	cout << updated << "\n";
	
	for(int i = 0; i < 10; i++)
	{
		calculateFitness();
		normalizeFitness();
		nextGeneration();
	}

	cout << "*******************************\n"
		 << "* Distance of Best Path Found *\n" 
		 << "*******************************\n";
	cout << fixed << int(calcDistance(cities, bestEver));
	
	return 0;
}

double calcDistance(vector<Point> &points, vector<int> &order) {
	double sum = 0;
	Point cityA;
	Point cityB;
	double dist;
	for(int i = 0; i < order.size(); i++){
		int cityAIndex = order[i];
		cityA = points[cityAIndex];
		if(i == 149999){
			int cityBIndex = order[0];
			cityB = points[cityBIndex];
		} else {
			int cityBIndex = order[i + 1];
			cityB = points[cityBIndex];
		}
		double a = cityA.getHorizontalCoordinate() - cityB.getHorizontalCoordinate();
		double b = cityA.getVerticalCoordinate() - cityB.getVerticalCoordinate();
		double d = sqrt(pow(a, 2) + pow(b, 2));
		sum += d;
	}
	return sum;
}

void calculateFitness() {
	double currentRecord = INT_MAX;
	for(int i = 0; i < population.size(); i++){
		double d = calcDistance(cities, population[i]);
		if(d < recordDistance) {
			recordDistance = d;
			bestEver = population[i];
			//updated = 0;
		}else if(d < currentRecord){
			currentRecord = d;
			currentBest = population[i];
		}
		fitness[i] = 1 / (pow(d, 8) + 1);
	}
}

void normalizeFitness() {
	double sum = 0.0;
	for(int i = 0; i < fitness.size(); i++){
		sum += fitness[i];
	}
	for(int i = 0; i < fitness.size(); i++){
		fitness[i] = fitness[i] / sum;
	}
}

void nextGeneration() {
	vector<vector<int>> newPopulation(0);
	cout << "newPop created\n";
	//for(int i = 0; i < population.size(); i++){
	for(int i = 0; i < 10; i++){
		vector<int> orderA = pickOne(population, fitness);
		cout << "orderA\n";
		vector<int> orderB = pickOne(population, fitness);
		cout << "orderB\n";
		vector<int> order = crossOver(orderA, orderB);
		cout << "crossOver of A and B to order\n";
		mutate(order, 0.05);
		cout << "mutated\n";
		newPopulation.push_back(order);
	}
	population = newPopulation;
}

vector<int> pickOne(vector<vector<int>> &lists, vector<double> &prob) {
	int index = 0;
	double r = rando(*gptr);
	
	while(r > 0){
		r = r - prob[index];
		index++;
	}
	index--;
	
	return lists[index];
}

int randomInt(int finish) {
	default_random_engine gen(time(NULL));
	uniform_int_distribution<int> randInd(0, finish);
	int index = randInd(gen);
	return index;
}

int randomInt(int start, int finish) {
	default_random_engine gen(time(NULL));
	uniform_int_distribution<int> randInd(start, finish);
	int index = randInd(gen);
	return index;
}

vector<int> crossOver(vector<int> &orderA, vector<int> &orderB) {
	vector<int> newOrder(0);
	int start = randomInt(orderA.size());
	cout << "start get!\n";
	int finish = randomInt(start, orderA.size());
	cout << "finish get!\n";
	cout << "move crossOver to new order!\n";
	for(int i = start; i < finish; i++){
		newOrder.push_back(orderA[i]);
	}
	cout << "add rest of chain to new order!\n";
	
	for(int i = 0; i < orderB.size(); i++){
		cout << "i = " << i << "\n";
		if(find(newOrder.begin(), newOrder.end(), orderB[i]) != newOrder.end()) {
			cout << "Already in list!\n";
		} else {
			cout << "Not in list!\n";
			newOrder.push_back(orderB[i]);
		}
	}
	return newOrder;
}

void mutate(vector<int> &order, double mutationRate) {
	for(int i = 0; i < totalCities; i++){
		double r = rando(*gptr);
		if(r < mutationRate){
			int indexA = randomInt(order.size());
			int indexB = (indexA + 1) % totalCities;
			swap(order, indexA, indexB);
		}
	}
}

void swap(vector<int> &a, int i, int j) {
	int temp = a[i];
	a[i] = a[j];
	a[j] = temp;
}

vector<int> shuffle(int num, vector<int> &order) {
	vector<int> copy = order;
	vector<int> shuffled(0);
	vector<int>::iterator vitr;
	
	for(int i = 0; i < num; i++){
		int index = randomInt(copy.size());
		shuffled.push_back(copy[index]);
		
		vitr = copy.begin();
		for(int j = 0; j < index; j++){
			vitr++;
		}
		
		if(copy.size() == 1){
			copy.clear();
		} else {
			copy.erase(vitr);
		}
	}
	return shuffled;
}