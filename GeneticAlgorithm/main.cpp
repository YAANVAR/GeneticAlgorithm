#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Individe{
    public:
        vector <bool> ind;
        int quality;
        bool qeye = false, geye = false;
        string gens;

        int qual() {
            if (qeye) return quality;
            int g = 0;
            for(size_t i = 0; i < ind.size(); i++) if(ind[i]) g++;
            quality = g;
            qeye = true;
            return quality;
        }

        Individe(int n) {
            for (int i = 0; i < n; i++) {
                if (rand() % 2) ind.push_back(true);
                else ind.push_back(false);
            }
            gens = str(ind);
            quality = qual();
        }

        void mutation (vector <bool> &x, int cnt, int mut){
            if(rand() % 100 < mut){
                if(x[cnt]) x[cnt] = false;
                else x[cnt] = true;
            }
        }

        string str(vector <bool> x) {
           if(geye) return gens;
            string s = "";
        	for(size_t i = 0; i < x.size(); i++){
                if(x[i]) s += '1';
				else s += '0';	
			}
			gens = s;
            geye = true;
            return gens;
        }

        size_t sz () {
            return ind.size();
        }

};

vector <Individe> make_population (int size,int capacity) {//size is length of individe. capacity refers to population
    vector <Individe> x;
    for(int i = 0; i < capacity; i++){
        Individe rec(size);
        x.push_back(rec);
    }
    return x;
}

void divis (int &del, size_t len) {
    del = rand() % len;
    del = len / 2; //equal divisor = del
}

void selection(int &x, int &y, size_t sz){
    x = rand() % sz;
    y = rand() % sz;
}

void crossover(vector <Individe> &x, unsigned int mut){//mut is mutation procent //usefull
    vector <Individe> new_x;
    for (size_t i = 0; i < x.size(); i++) {
        Individe temp(x[0].sz());
        int f, s, del; //first, second, divisor = del
        divis(del, x[0].sz());
        selection(s, f, x[i].sz());
        if (x[s].qual() > x[f].qual())  temp.ind = x[s].ind;
        else temp.ind = x[f].ind;
        selection(s, f, x[i].sz());
        if (x[s].qual() > x[f].qual())  temp.ind = x[s].ind;
        else temp.ind = x[f].ind;
        for(size_t j = temp.sz() - del; j < temp.sz(); j++){
            temp.ind[i] = x[s].ind[i];
            //mutation
            temp.mutation(temp.ind, j, mut);
            //mutation
        }
        //mutation
        for(size_t j = 0; j < temp.sz() - del; j++){
            temp.mutation(temp.ind, j, mut);
        }
        //mutation
        new_x.push_back(temp);
    }
    x = new_x;
}

double generation_quality(vector <Individe> x){
    double seq = 0;
    for(size_t i = 0; i < x.size(); i++){
        seq += x[i].quality; //quality
    }
    seq /= x.size();
    return seq;
}

void showncrossover(vector <Individe> &x, unsigned int mut){//mut is mutation procent
    cout << endl << "CURRENT GENERATION" << endl;
    cout << endl << "Middle quality of generation: " << generation_quality(x) << endl << endl;
    vector <Individe> new_x;
    for (size_t i = 0; i < x.size(); i++) {
        Individe temp(x[0].sz());
        int f, s, del; //first, second, divisor = del
        divis(del, x[0].sz());
        selection(s, f, x[i].sz());
        if (x[s].qual() > x[f].qual())  temp.ind = x[s].ind;
        else temp.ind = x[f].ind;
        selection(s, f, x[i].sz());
        if (x[s].qual() > x[f].qual())  temp.ind = x[s].ind;
        else temp.ind = x[f].ind;
        for(size_t j = temp.sz() - del; j < temp.sz(); j++){
            temp.ind[i] = x[s].ind[i];
            //mutation
            temp.mutation(temp.ind, j, mut);
            //mutation
        }
        //mutation
        for(size_t j = 0; j < temp.sz() - del; j++){
            temp.mutation(temp.ind, j, mut);
        }
        //mutation
        cout << x[i].gens << "\t" << x[i].quality <<  endl;//////////shows gens//////////////
        new_x.push_back(temp);
    }
    x = new_x;
}

void generate_generation(vector <Individe> &x, unsigned int mut){//mut is mutation procent // useless
    crossover(x, mut);
    //showncrossover(x, n);
}

void see_generation (vector <Individe> x){ //isn't useful
	cout << endl << "CURRENT GENERATION" << endl;
    for(size_t i = 0; i < x.size(); i++){
        cout << x[i].gens << "\t" << x[i].qual() << endl;//////////////////////////////////
	}
	cout << endl << "Middle quality of generation: " << generation_quality(x) << endl;
}

int best_individe(vector <Individe> x, int n) {
    int z = 0;
    for(size_t i = 0; i < x.size(); i++){
        if(x[i].qual() >= n) z++;
    }
    return z;
}

int main()
{
	srand(time(NULL));
	
    int sz, capacity, mutation, pop_quant, tests, f = 0, id;
    cout << "Size of the line: ";
    cin >> sz;
    cout << "Population capacity: ";
    cin >> capacity;
    cout << "Procent of mutation: ";
    cin >> mutation;
    cout << "Quantity of populations: ";
    cin >> pop_quant;
    cout << "Quantity of tests for one population: ";
    cin >> tests;
    cout << "How many 1 gens for ideal: ";
    cin >> id;

    vector <Individe> x;
    x = make_population (sz, capacity);

    for(int i = 0; i < pop_quant; i++){
        for(int j = 0; j < tests; j++){
            //see_generation(x);
            //generate_generation(x, mutation);
            showncrossover(x, mutation); //showncrossover is substitute see_generation and generate_generation
            cout << endl << endl << "NEXT GENERATION - " << j + 1 << endl;
            if(best_individe(x, 10) >= id){
                f++;
                j = tests;
            }
        }
    }
    cout << endl << "TRIES - " << pop_quant << endl << "IDEAL - " << f << endl;

    return 0;
}
