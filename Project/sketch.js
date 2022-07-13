/**
 * With this assignment we try to assist Santa on his yearly mission of delivering presents to myriads of people all around the world.
 * With an elegant amd efficient implementation of our program, these people will be able to awake Christmas morn to a very pleasant surprise!
 * In order to help Santa, we are tasked with finding a short path between a large collection of cities that he and Rudolph must visit overnight.
 */

/**
 * Create variables to aid in keeping track of our cities in the implementation of a genetic algorithm.
 */
var cities = [];

/**
 * Motivation: Creating even a single path of approximately (11^5) edges would take far too long and is taxing for the program.
 * Therefore, declare a variable to store the size of individual sections of the total graph of cities.
 * Upon division of the city graph into sections of size numCities, we develop populations for each collection and try to find the shortest path or best population in each collection.
 * Upon completion of this, we simply combine the terminal point of each section to the initial point of the following section, until we are left with just one contiguous path through every city.
 */
var numCities = 100;
var totalCities = 30;

// Create an array to store the generated population of unique paths, or "orders", for a particular collection of cities of size numCities.
var popSize = 100;
var population = [];
 
// Store within an array parallel to population the fitness values for each order in the population.
var fitness = [];

/**
 * Upon determination of the fitness values and distances of each path in the array of populations, set the new recordDistance and bestDistanceEver, if necessary.
 * recordDistance is used to keep track of the numerical value of the shortest distance path we have found.
 * bestEver is used to keep track of which order in the population yielded that new recordDistance.
 * currentBest is used to keep track of the best distance in any particular population.  
 */
var recordDistance = Infinity;
var bestEver;
var currentBest;
var table;
var stopLoop = 0;
/*
function preload() {
	console.log("Entering Preload");
	table = loadTable("http://localhost:8080/santa_cities.csv", "csv", "header");
}*/

function setup()
{
  /*
  print(table.getRowCount() + ' total rows in table');
  print(table.getColumnCount() + ' total columns in table');
  print(table.getColumn('id'));
  /*
  for (var r = 0; r < table.getRowCount(); r++){
    for (var c = 0; c < table.getColumnCount(); c++) {
      print(table.getString(r, c));
    }
  }*/
	
  createCanvas(1000, 1000);
  // Declare and initialize in loop the contents of our default order collection, which keeps track of what order in which we are visiting the cities. order = {0, 1, 2, ..., (totalCities-1)}
  var order = [];
  
  for(var i = 0; i < totalCities; i++)
  {
  	// Until we have create totalCities amount of cities, create cities as vectors to be randomly allocated on a 2D plane.
  	var v = createVector(random(width), random(height / 2));
  	cities[i] = v;
  	order[i] = i;
  }/*
  //for(var i = 0; i < table.getRowCount(); i++){
  for(var i = 0; i < 100; i++){
	  /*for(var j = 0; j < table.getColumnCount(); j++){
		  
	  }
	  
	  var x = table.getNum(i, 1);
	  var y = table.getNum(i, 2);
	  
	  x = x / 4;
	  y = y / 4;
	  
	  var v = createVector(x, y);
	  cities[i] = v;
	  order[i] = i;
	  
	  console.log(cities[i].toString());
  }*/

  for(var i = 0; i < popSize; i++)
  {
  	population[i] = shuffle(order);
  }

  console.log(calcDistance())
  statusP = createP('').style('font-size', '32pt');
  
  //console.log(population);
}

function draw()
{
	background(50, 50, 50);

	// Genetic Algorithm Component
	calculateFitness(cities);
	normalizeFitness();
	nextGeneration();

	var initialCity = color(100, 250, 250);
	var terminalCity = color(250, 25, 25);
	stroke(255);
	strokeWeight(4);
	beginShape();
	for (var i = 0; i < bestEver.length; i++) {
	var n = bestEver[i];
		vertex(cities[n].x, cities[n].y);
		ellipse(cities[n].x, cities[n].y, 16, 16);
	}
	vertex(cities[0].x, cities[0].y);
	endShape();

	translate(0, height / 2);
	stroke(255)
	strokeWeight(4);
	noFill();  
	
	beginShape();
	for (var i = 0; i < currentBest.length; i++) {
		var n = currentBest[i];
		vertex(cities[n].x, cities[n].y);
		ellipse(cities[n].x, cities[n].y, 16, 16);
	}
	endShape();
	stopLoop++;
	console.log(stopLoop);
		
	if(stopLoop == 5000){
		noLoop();
	}
}

// function shuffle(a, num) {
//   for (var i = 0; i < num; i++) {
//     var indexA = floor(random(a.length));
//     var indexB = floor(random(a.length));
//     swap(a, indexA, indexB);
//   }
// }


function swap(a, i, j) {
  var temp = a[i];
  a[i] = a[j];
  a[j] = temp;
}


function calcDistance(points, order) {
  var sum = 0;
  var cityA;
  for (var i = 0; i < order.length - 1; i++) {
    var cityAIndex = order[i];
    var cityA = points[cityAIndex];
    var cityBIndex = order[i + 1];
    var cityB = points[cityBIndex];
    var d = cityA.dist(cityB);
    sum += d;
  }
  return sum;
}
