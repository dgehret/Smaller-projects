#include <iostream>
#include <cstdlib>
#include <cmath>
#include <random>
#include <gmpxx.h>
#include <iomanip>
#include <boost/multiprecision/gmp.hpp>
using namespace std;

/* Bernoulli Trials Simulator */

const bool DEBUG = false;

#define MAX_LUCK 10
#define TRIALS 100
#define FLIPS 40
#define PERCENT_PER_STAR 1

bool coin_flip(mpz_class bias, gmp_randclass &RNG) {
	mpz_class roll = RNG.get_z_range(MAX_LUCK); //Generates a number from 0 to 9
	if (roll < bias) return true;
	return false;
}

uint64_t choose(int n, int k) { 
	if (k > n / 2) 
		k = n - k; 
	uint64_t answer = 1; 
	for (int i = 1; i <= k; i++) { 
		answer *= (n - k + i); 
		answer /= i; 
	} 
	if constexpr (DEBUG) cout << n << " choose " << k << " = " << answer << endl;
	return answer; 
} 

double binomialProbability(int n, int k, double p) {
	double result = choose(n, k) * pow(p, k) * pow(1 - p, n - k); 
	if constexpr (DEBUG) cout << "Binomial Probability: %" << result*100 << endl;
	return result*100;
}

void printHist(int *bins, double luck) {
	for (int i = 0; i < FLIPS+1; i++) {
		int percentActual = bins[i];
		int percentExpected = binomialProbability(FLIPS,i,luck/10);
		cout << "Bin " << setw(2) << setfill('0') << i << ": " << setw(2) << setfill('0') << percentExpected << "% vs " << setw(2) << setfill('0') << percentActual << "%: ";
		for (int j = 0; j < bins[i]; j++) cout << "*";
		cout << endl;
	}
}

void trial(int *bins, double luck, gmp_randclass &RNG) {
	for (int i = 0; i < TRIALS; i++) {
		int counter = 0;
		int counter2 = 0;
		for (int j = 0; j < FLIPS; j++) {
			bool success = coin_flip(luck, RNG); //The higher your luck, the higher the chance of success
			if (success) counter++;
		}
		bins[counter] += 1;
	}
}

int main() {
	cout << "Please input a random seed: ";
	mpz_class my_seed;
	cin >> my_seed;
	gmp_randclass RNG(gmp_randinit_mt);
	RNG.seed(my_seed);

	//Your luck score controls how likely you are to get a heads on a flip
	//At 0, you have a 0% chance, at 10 you have a 100% chance.
	//By default, it should be 5 for a 50/50 chance.
	//(This is called a "bias" on a coin flip)
	cout << "Please enter your luck score (from 0 to " << MAX_LUCK << "): ";
	double luck;
	cin >> luck;
	if (luck < 0 || luck > MAX_LUCK) {
		cout << "Bad input.\n";
		exit(1);
	}
	int bins[FLIPS + 1] = {}; //Holds how many times we get each result, initialized to zero
	trial(bins, luck, RNG);

	printHist(bins, luck);
	//Explanation:
	// The bin number is how many heads came up, which will range from 0 to FLIPS
	// The expected percent is the expected probability, given by (n choose k) * p^k * (1-p)^(n-k)
	// The actual percent is how many actually got rolled (which will rarely match the expected number)
	//
	return 0;
}
