#include <stdio.h>

/*
 * The Missionary Cannibal Problem
 * On one bank of a river are three missionaries and three cannibals. 
 * There is one boat available that can hold up to two people and that 
 * they would like to use to cross the river. If the cannibals ever 
 * outnumber the missionaries on either of the river’s banks, the 
 * missionaries will get eaten.
 */

#define N 6

/* Solution functions */
int breadth_first_search(int bank1[N], int bank2[N]);
int depth_first_search(int bank1[N], int bank2[N]);
int iterative_deepening_search(int bank1[N], int bank2[N]);

/* Utility functions */
int cross(int from[N], int to[N], int i, int j);
int empty_bank(int bank[N]);
int find_empty_position(int arr[N]);
int valid_state(int bank[N]);

int main(void) {

	/* 
	 * bank1 is the initial starting state of everyone
	 * bank2 is the end goal state of everyone
	 * -1 represents a cannibal, 0 no one, and 1 a missionary
	 */
	int bank1[N] = {-1, -1, -1, 1, 1, 1};
	int bank2[N] = {0, 0, 0, 0, 0, 0};

	return 1;
}

/*
 * Recursive solution by depth-first search
 */
int depth_first_search(int bank1[], int bank2[]) {

	// base case, solution found
	if (empty_bank(bank1)) {
		return 1;
	}

	return 0;
}

/* 
 * person(s) cross the river
 * returns 1 on success, 0 otherwise
 */
int cross(int from[N], int to[N], int i, int j) {

	int index1 = find_empty_position(to);
	to[index1] = from[i];
	from[i] = 0;

	// second person is optional
	int index2;
	if (j != -1) {
		index2 = find_empty_position(to);
		to[index2] = from[j];
		from[j] = 0;
	}

	// checks state for validity
	if (valid_state(from) == 0 || valid_state(to) == 0) {
		// resets position for invalid states
		from[i] = to[index1];
		to[index1] = 0;
		if(j != -1) {
			from[j] = to[index2];
			to[index2] = 0;
		}
		return 0;
	}

	return 1;
}

/* used to check if solution is found */
int empty_bank(int bank[N]) {

	for (int i = 0; i < N; ++i)
		if (bank[i] != 0)
			return 0;
	return 1;
}

/* returns the index of the next available position, -1 otherwise */
int find_empty_position(int arr[N]) {
	for (int i = 0; i < N; ++i)
		if (arr[i] == 0)
			return i;
	return -1;
}

/* 
 * verifys if a state is valid
 * i.e. a missionary is not outnumbered by cannibals
 */
int valid_state(int bank[N]) {
	int c_count = 0;
	int m_count = 0;
	for (int i = 0; i < N; ++i) {
		if (bank[i] == -1)
			c_count++;
		else if(bank[i] == 1)
			m_count++;
	}
	// if cannibals exceed missionaries
	if (c_count > m_count)
		return 0;
	return 1;
}
