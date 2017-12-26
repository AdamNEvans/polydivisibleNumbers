#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <gmp.h>

// ============================================================================
//                            Function declarations
// ============================================================================


int recurse(mpz_t baseValue, bool* availables, int base, int depth);
int computePolydivisibles(int base);


// ============================================================================
//                                 Functions
// ============================================================================
// Main
// ============================================================================

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		printf("Usage: %s <base>\n", argv[0]);
		return 1;
	}
	
	int base = atoi(argv[1]);
	int npolydivisibles = computePolydivisibles(base);
	printf("Found %d polydivisible numbers\n", npolydivisibles);
	
	return 0;
}

// ============================================================================
// Recursively tacks on new digits and checks for divisibility by the current
// number of digits before adding more digits.Returns the number of
// polydivisible numbers for the given base
//
// @param availables An array. availables[i] == true if that digit has been
//        used, false otherwise.
// @param base What base we are working in. Also the length of the availables
//        array
// @param depth The index of the digit being checked
// ============================================================================

int recurse(mpz_t baseValue, bool* availables, int base, int depth)
{
	if (depth == base - 1)
	{
		printf("found polydivisible number: '");
		mpz_out_str(stdout, base, baseValue);
		printf("'\n");
		return 1;
	}
	
	int total = 0;
	mpz_t mod;
	mpz_t sum;
	mpz_t newBaseValue;
	
	mpz_inits(mod, sum, newBaseValue, NULL);
	mpz_mul_ui(newBaseValue, baseValue, base);
	depth++;
	
	// loop through the digits
	for (uint64_t i = 1; i < base; i++)
	{
		if (availables[i])
		{
			continue;
		}
		
		mpz_add_ui(sum, newBaseValue, i);
		mpz_fdiv_r_ui(mod, sum, depth);
		
		// returns +1 if positive, 0 if 0, -1 if negative
		if (mpz_sgn(mod) == 0)
		{
			availables[i] = true;
			total += recurse(sum, availables, base, depth);
			availables[i] = false;
		}
	}
	
	mpz_clears(mod, sum, newBaseValue, NULL);
	
	return total;
}

// ============================================================================
// Returns the number of polydivisible numbers for the given base
// ============================================================================

int computePolydivisibles(int base)
{
	mpz_t original;
	bool* availables = (bool*)calloc(sizeof(bool), base);
	
	mpz_init(original);
	mpz_set_ui(original, 0);
	
	int nvalues = recurse(original, availables, base, 0);
	
	// be a good human being
	mpz_clear(original);
	free(availables);
	
	return nvalues;
}

// ============================================================================
