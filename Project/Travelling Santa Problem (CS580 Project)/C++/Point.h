#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED

#include <iostream>
#include <fstream>

class Point
{
private:
	int horizontalCoordinate;
	int verticalCoordinate;
	int identify;
public:
	Point();
	Point(int id, int hc, int vc);
	Point(const Point& src);

	int getHorizontalCoordinate() const;
	int getVerticalCoordinate() const;
	int getIdentify() const;
	void setidentify(int id);
	void setHorizontalCoordinate(int hc);
	void setVerticalCoordinate(int vc);

	void display(std::ostream& outs) const;
};

inline
int Point::getHorizontalCoordinate() const
{
	return horizontalCoordinate;
}
inline
int Point::getIdentify() const
{
	return identify;
}

inline
int Point::getVerticalCoordinate() const
{
	return verticalCoordinate;
}

inline
void Point::setHorizontalCoordinate(int hc)
{
	horizontalCoordinate = hc;
}

inline
void Point::setVerticalCoordinate(int vc)
{
	verticalCoordinate = vc;
}
inline
void Point::setidentify(int id)
{
	identify = id;
}
inline
std::ostream& operator<<(std::ostream& outs, const Point& prt)
{
	prt.display(outs);
	return outs;
}

#endif
/*
void calculateFitness(int cities[]) {
  int currentRecord ;
  for (int i = 0; i < population.length; i++) {
    int d = calcDistance(cities, population[i]);
    if (d < recordDistance) {
      recordDistance = d;
      bestEver = population[i];
	  stopLoop = 0;
    }
    if (d < currentRecord) {
      currentRecord = d;
      currentBest = population[i];
    }

    // This fitness void has been edited from the original video
    // to improve performance, as discussed in The Nature of Code 9.6 video,
    // available here: https://www.youtube.com/watch?v=HzaLIO9dLbA
    fitness[i] = 1 / (pow(d, 8) + 1);
  }
}

void normalizeFitness() {
  int sum = 0;
  for (int i = 0; i < fitness.length; i++) {
    sum += fitness[i];
  }
  for (int i = 0; i < fitness.length; i++) {
    fitness[i] = fitness[i] / sum;;
  }
}

void nextGeneration() {
  int newPopulation = [];
  for (int i = 0; i < population.length; i++) {
    int orderA = pickOne(population, fitness);
    int orderB = pickOne(population, fitness);
    int order = crossOver(orderA, orderB);
    mutate(order, 0.01);
    newPopulation[i] = order;
  }
  population = newPopulation;

}

int pickOne(int list,int prob) {
  int index = 0;
  int r = random(1);

  while (r > 0) {
    r = r - prob[index];
    index++;
  }
  index--;
  return list[index].slice();
}

int crossOver(int orderA,int orderB) {
  int start = floor(random(orderA.length));
  int end = floor(random(start + 1, orderA.length));
  int neworder = orderA.slice(start, end);
  // int left = totalCities - neworder.length;
  for (int i = 0; i < orderB.length; i++) {
    int city = orderB[i];
    if (!neworder.includes(city)) {
      neworder.push(city);
    }
  }
  return neworder;
}

void mutate(int order,int mutationRate) {
  for (int i = 0; i < totalCities; i++) {
    if (random(1) < mutationRate) {
      int indexA = floor(random(order.length));
      int indexB = (indexA + 1) % totalCities;
      swap(order, indexA, indexB);
    }
  }
}
*/
