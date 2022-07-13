#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<math.h>
#include<time.h>

using namespace std;

const int POPULATION_SIZE = 100;
int fitnessP1, fitnessP2;
ofstream out("Assign-2_Genetic-Algotithm-nQueen_Results.txt");

//Stores pieces on 'board' and the fitness of that board
class Queen{
    public:
        double fitness;
        vector<int> places;
        Queen();
        Queen(int);
        void print();
        void printToFile();
};

//Stores population of boards
class Population{
    public:
        Queen *population[POPULATION_SIZE];
        Population();
        Population(int);
};

//Column check (is it in vector yet)
bool CheckColumns(vector<int> a, int spot, int value){
	for(int i = 0; i < spot; i++){
		if(a[i] == value)
			return true;
	}
	return false;
}

//Calculates number of Queens attacking each other
int numAttackingQueen(vector<int> a, int number)
{
	int attackCount = 0;
	bool upAttacks = false, downAttacks = false;
	for(int i = 0; i < number; i++){
		for(int j = i+1; j < number; j++){
			if(j < number){
				int dx = i - j;
				int dy = a[i] - a[j];
				if(abs(dx) == abs(dy) && (!upAttacks || !downAttacks)){
					if(dy > 0)
						upAttacks = true;
					else
						downAttacks = true;
					attackCount++;
				}
			}
		}
		upAttacks = false;
		downAttacks = false;
	}
	return attackCount;
}

//Board
void Queen::print(){
	cout<<endl;
	for(int i = 0; i < places.size(); i++){
		cout<<places[i]<<" ";
	}
	cout<<endl;
}

//Outputs the Board to file
void Queen::printToFile() {
	for(int i = 0; i < places.size(); i++){
		out << places[i] << " ";
	}
}

Queen::Queen(){
	/*for(int i = 0; i < 10; i++)
	{
		places.push_back(i);
	}*/
}

Queen::Queen(int num){
	//Initiates positions
	int r;
	//int attackCount = 0;
	for(int i = 0; i < num; i++){
		do{ r = rand()%num + 1;}
		while(CheckColumns(places,i,r));

		places.push_back(r);
	}
	//Gets fitness of the board
	int attackCount = numAttackingQueen(places,num);
	fitness = 1 / (attackCount + 0.01);
}

Population::Population(){
	for(int i = 0; i < 10; i++){
		population[i] = new Queen(8);
		population[i]->print();
	}
}

Population::Population(int size){
	for(int i = 0; i < POPULATION_SIZE; i++){
		population[i] = new Queen(size);
	}
}

//Find the most fit in population
Queen* mostFit(Population *pop, int size){
	Queen *a = pop->population[0];
	for(int i = 0; i < size; i++){
		if(a != NULL && pop->population[i] != NULL && a->fitness < pop->population[i]->fitness){
			a = pop->population[i];
			fitnessP1 = i;
		}
	}
	return a;
}

Queen* mostFit(vector<Queen*> pop, int size){
	Queen *a = pop[0];
	for(int i = 0; i < size; i++){
		if(a != NULL && pop[i] != NULL && a->fitness < pop[i]->fitness){
			a = pop[i];
			fitnessP2 = i;
		}
	}
	return a;
}

//Returns position that most fits
int mostFitPos(Population *pop, int size){
	int pos = 0;
	for(int i = 0; i < size; i ++){
		if(pop->population[pos] < pop->population[i])
			pos = i;
	}
	return pos;
}

int mostFitPos(vector<Queen*> pop, int size){
	int pos = 0;
	for(int i = 0; i < size; i ++){
		if(pop[pos] < pop[i])
			pos = i;
	}
	return pos;
}

//Method for selecting parents, with substitution
bool getMate(vector<Queen*> *a, Population h){
	int r1, r2, r3;
	int current_member = 1;
	Queen *b;
	while(current_member <= 40){
		//Select random members
		r1 = rand()%POPULATION_SIZE;
		do{r2 = rand()%POPULATION_SIZE;}while(r2 == r1);
		do{r3 = rand()%POPULATION_SIZE;}while(r3 == r1 || r3 == r2);
		//Find most fit among population
		if(h.population[r1]->fitness > h.population[r2]->fitness &&
           h.population[r1]->fitness > h.population[r3]->fitness)
            b=h.population[r1];
		else if(h.population[r2]->fitness > h.population[r1]->fitness &&
                h.population[r2]->fitness > h.population[r3]->fitness)
            b=h.population[r2];
		else
            b=h.population[r3];
		//Add ideal to mating pool and increase counter
		a->push_back(b);
		current_member++;
	}
	return true;
}

int main()
{
	int n;
	cout<<"Welcome to the N-Queen solver. How much do you want N to be?  ";
	cin>>n;
	bool found = false; //is solution is found
	int generations = 0; //How many generations til solution

	out<<"Solution"<<"      "<<"# of Tries"<<"	"<<"Solution"<<endl;

	//Initialize population
	srand (time(NULL));
	system("CLS");

	for(int times = 0; times < 3; times++){
		Population group(n); //Population which algorithm is applied to
		while(!found){
			//Parent Selection
			vector<Queen*> mategroup; //Mating group
			getMate(&mategroup,group);

			//Copies half of one parent to one child, then copies rest of parent
			vector<Queen*> children;
			for(int i = 0; i < 20; i++){
				//Select parents
				Queen *p1 = mategroup[i], *p2 = mategroup[i+1];
				//Initialize Children
				Queen *c1 = new Queen, *c2 = new Queen;
				//Add half of one parent to one child
				for(int j = 0; j < n/2; j++){
					c1->places.push_back(p1->places[j]);
					c2->places.push_back(p2->places[j]);
				}
				//Add rest of positions
				int cnt1 = n/2, cnt2 = cnt1;
				for(int k = 0; k < n; k++){
					if(!CheckColumns(c1->places,cnt1,p2->places[k])){
						c1->places.push_back(p2->places[k]);
						cnt1++;
					}
					if(!CheckColumns(c2->places,cnt2,p1->places[k])){
						c2->places.push_back(p1->places[k]);
						cnt2++;
					}
				}
				//Random number [0, 3] If num = 1 -> no mutation occurs
				//else two spots at random are selected and switched
				int mut = rand()%4;
				if(mut != 1){
					int pos1 = rand()%n, pos2;
					do{pos2 = rand()%n;}while(pos1 == pos2);

					int val1 = c1->places[pos1], val2 = c1->places[pos2];

					c1->places[pos1] = val2;
					c1->places[pos2] = val1;
				}
				mut = rand()%4;
				if(mut != 1){
					int pos1 = rand()%n;
					int pos2;
					do{pos2 = rand()%n;}while(pos1 == pos2);

					int val1 = c2->places[pos1];
					int val2 = c2->places[pos2];

					c2->places[pos1] = val2;
					c2->places[pos2] = val1;
				}
				//Calculate fitness of children
				int col1 = numAttackingQueen(c1->places,n);
				int col2 = numAttackingQueen(c2->places,n);
				c1->fitness = 1/(col1 + 0.01);
				c2->fitness = 1/(col2 + 0.01);

				if(c1->fitness == 100 || c2->fitness == 100)
					found = true;

				children.push_back(c1);
				children.push_back(c2);
			}
			generations++; system("CLS");

			//The 200 ideal fit individuals are stored in the dummy variable
			//ideal.  They are then copied to group.

			Population ideal(n); //Temporarily stores ideal individuals
			Queen *fitOne, *fitTwo; //To store ideal in population and children, respectively
			int v_cnt = 0, h_cnt = 0;
			for(int i = 0; i < POPULATION_SIZE; i++){
				fitOne = mostFit(&group,POPULATION_SIZE - i);
				fitTwo = mostFit(children,40);

				//Find which is most fit
				if(fitTwo == NULL || fitOne->fitness > fitTwo->fitness){
					ideal.population[i] = fitOne;
					cout<<"Selected fitOne\n";

					group.population[fitnessP1] = group.population[POPULATION_SIZE - 1 - h_cnt];
					group.population[POPULATION_SIZE - 1 - h_cnt] = NULL;
					h_cnt++;
				}
				else{
					ideal.population[i] = fitTwo;
					cout<<"Selected fitTwo\n";
					children[fitnessP2] = children[39 - v_cnt];
					children[39 - v_cnt] = NULL;
					v_cnt++;
				}
				system("CLS");
			}
			group = ideal;
			cout<<"Finished cycle\n";
			system("CLS");
		}//end while loop
		out<<times+1<<"		"<<generations<<"		"; group.population[0]->printToFile();
		out<<endl;

		system("CLS");
		found = false;
		generations = 0;
	}//end for loop
	out.close();
	system("pause");
	return 0;
}
