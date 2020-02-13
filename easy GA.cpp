#include<iostream>
#include<bitset>
#include<cmath>
#include<vector>
#include<stdlib.h>
#include<time.h> 
using namespace std;
class Individual{
	public:
		Individual(int start, int end, int digit){
			number = pow(2, digit);
			value = new double[number];
			for(int i=0; i<number; i++){
				value[i] = start + i*(end-start)*1.0/(number-1);
			}
			for(int i=0; i<number; i++){
				cout<<value[i]<<" ";
			}
			cout<<endl;
		}
		double getIndividual(int a){
			return value[a];
		}
		double Fitness(double d){
			fitness = -pow(d, 4)-5*pow(d,3)-4*pow(d,2)+4*d-1;
			return fitness;
		}
		void RandomPopulation(int r, double arr[]){
			p = new double[r];
			srand((unsigned)time(NULL));
			for(int i=0; i<r; i++){
				p[i] = rand()%16;
				for(int j=0; j<i; j++){
					if(p[j] == p[i]){
						while(p[j]==p[i]){
							p[i] = rand()%16;
						}
					}
				}
				arr[i] = p[i];
			}
		}
		
	private:
		double* value;
		double* p;
		double* c;
		int number;
		double fitness;
};

int main(){
	double parent[4];
	double fitness[4];
	double middle[4];
	double probabily[4];
	Individual individual(-4,-1,4);
	individual.RandomPopulation(4, parent);
	double children[4];
	int generation = 0;
	srand((unsigned)time(NULL));
	while(generation<=50){
		for(int i=0; i<4; i++){
			fitness[i] =10 + individual.Fitness(individual.getIndividual(parent[i]));
			cout<<fitness[i]<<"f  ";
		}
		cout<<endl;
		for(int i=0; i<4; i++){
			cout<<parent[i]<<"p"<<endl;
		}
		for(int i=0; i<4; i++){
			probabily[i] = fitness[i]/(fitness[0]+fitness[1]+fitness[2]+fitness[3]);
			cout<<probabily[i]<<" !";
		}
		cout<<endl;
		//产生中间的父代 
		
		for(int i=0; i<4; i++){
			int k=0;
			double d = (rand()%10)*1.0/11;
			cout<<d<<endl;
			double F = probabily[0];
			while(F<d){
				k = k+1;
				F = F+probabily[k];				
			}
			middle[i] = k;
			if(i%2!=0){
				while(middle[i]==middle[i-1]){
					int k=0;
					double d = (rand()%10)*1.0/11;
					double F = probabily[0];
					while(F<d){
						k = k+1;
						F = F+probabily[k];
					}
					middle[i] = k;
				}
				
			}
		}
		for(int i=0; i<4; i++){
			cout<<middle[i]<<" ";
		}
		for(int i=0; i<4; i=i+2){ 
			bitset<4> b(0);
			int m1 = middle[i];
			bitset<4> b1(parent[m1]);
			cout<<"b1"<<" "<<b1<<" ";
			int j = i+1;
			int m2 = middle[j];
			bitset<4> b2(parent[m2]);
			cout<<"b2"<<" "<<b2<<" ";
			int crossPoint = rand()%4;
			cout<<crossPoint<<" ";
			for(int e=0; e<=crossPoint; e++){
				b[e] = b1[e];
				b1[e] = b2[e];
				b2[e] = b[e];
			}
			cout<<endl;
			cout<<"b1"<<" "<<b1<<" b2"<<" "<<b2;
			children[i] = b1.to_ulong();
			children[j] = b2.to_ulong();
		}
		for(int i=0; i<4; i++){
			parent[i] = children[i];
			cout<<children[i]<<"c ";
		}
		cout<<endl;
		cout<<"第"<<generation<<"代："; 
		for(int i=0; i<4; i++){
			cout<<individual.getIndividual(parent[i])<<"  ";
		}
		generation++;
	}
}

















