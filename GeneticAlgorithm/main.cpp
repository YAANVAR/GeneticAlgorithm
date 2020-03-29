#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;

class Individe{
    public:
        vector <bool> ind;//test
        int quality = qual();
        bool qeye = false, leye = false;
        string gens = str(ind);

        int qual() {
            //if (qeye) return quality;
            int g = 0;
            for(size_t i = 0; i < ind.size(); i++) if(ind[i]) g++;
            quality = g;
            //qeye = true;
            return g;
        }

        Individe(int n) { //settings done
            for (int i = 0; i < n; i++) {
                if (rand() % 2) ind.push_back(true);
                else ind.push_back(false);
            }
        }

        void mutation (vector <bool> x){ //doesn't usefull
            for (size_t i = 0; i < x.size(); i++) {
                if (rand() % 100 <= 1) {
                    if (ind[i]) ind[i] = false;
                    else ind[i] = true;
                }
            }
        }
        void mutation2 (vector <bool> x){ //doesn't usefull
            for (size_t i = 0; i < x.size(); i++) {
                if (rand() % 100 <= 1) (ind[i]) ? ind[i] = false : ind[i] = true;
            }
        }
        
        string str(vector <bool> x) {
            //if(leye) return gens;
        	string s;
        	for(size_t i = 0; i < x.size(); i++){
                if(x[i]) s += '1';
				else s += '0';	
			}
			gens = s;
            //leye = true;
            return gens;
		}

        size_t sz () {
            return ind.size();
        }

};

double generation_quality(vector <Individe> x){
    double seq = 0;
    for(size_t i = 0; i < x.size(); i++){
        seq += x[i].qual(); //quality
	}
    seq /= x.size();
    return seq;
}

void divis (int &del, size_t len) {
    del = rand() % len;
    //del = len / 2; //equal divisor = del                       ////////////////equal//////////////
}

void selection(int &x, int &y, size_t sz){
    x = rand() % sz;
    y = rand() % sz;
}

void crossover(vector <Individe> &x, unsigned int n){//n is mutation procent
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
            if(rand() % 100 == n){
                if(x[i].ind[j]) x[i].ind[j] = false;
                else x[i].ind[j] = true;
            }
            //mutation
        }
        //mutation
        for(size_t j = 0; j < temp.sz() - del; j++){
            if(rand() % 100 == n){
                if(x[i].ind[j]) x[i].ind[j] = false;
                else x[i].ind[j] = true;
            }
        }
        //mutation
        new_x.push_back(temp);
    }
    x = new_x;
}

void generate_generation(vector <Individe> &x, unsigned int n){//n is mutation procent

    cout << endl << "CURRENT GENERATION" << endl << endl << "Middle quality of generation: " << generation_quality(x) << endl << endl;//time

    crossover(x, n);
}

vector <Individe> make_population (int size,int capacity) {//make settings
	vector <Individe> x;
    for(int i = 0; i < capacity; i++){
        Individe rec(size);
		x.push_back(rec);
	}
	return x;
}

void see_generation (vector <Individe> x){
	cout << endl << "CURRENT GENERATION" << endl;
    for(size_t i = 0; i < x.size(); i++){
        cout << x[i].str(x[i].ind) << endl;
	}
	cout << endl << "Middle quality of generation: " << generation_quality(x) << endl;
}

int best_individe(vector <Individe> x, int n) {
    int z = 0;
    for(size_t i = 0; i < x.size(); i++){
        if(x[i].qual() == n){
            z++;
        }
    }
    return z;
}

int main()
{
	srand(time(NULL));
	
    int sz, capacity, mutation;
    cout << "Size of the line: ";
    cin >> sz;
    cout << "Population capacity: ";
    cin >> capacity;
    cout << "Procent of mutation: ";
    cin >> mutation;

    vector <Individe> x;
    x = make_population (sz, capacity);

    int f = 0, r = 0, d = 0;
    for(int i = 0; i < 100; i++){
        for(int j = 0; j < 100; j++){
            see_generation(x);
            generate_generation(x, mutation);
            cout << endl << endl << "NEXT GENERATION - " << i << endl;
            if(best_individe(x, 10) >= 10){
                f++;
                d+=i;
                break;
            }
        }
        r++;
    }
    cout << endl << "TRIES - " << r << endl << "IDEAL - " << f << endl << "MIDDLE - " << d / 100 << endl;

    return 0;
}
