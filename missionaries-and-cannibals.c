#include <stdio.h>

/*
 * The Missionary Canibal Problem
 * On one bank of a river are three missionaries and three cannibals. 
 * There is one boat available that can hold up to two people and that 
 * they would like to use to cross the river. If the cannibals ever 
 * outnumber the missionaries on either of the river’s banks, the 
 * missionaries will get eaten.
 */

#define N 6

/* solutions */
int breadth_first_search(int bank1[N], int bank2[N]);
int depth_first_search(int bank1[N], int bank2[N]);

/* Utility functions */
int empty_bank(int bank[N]);
int find_empty_position(int arr[N]);
int valid_state(int bank[N]);

void cross(int from[N], int to[N], int index1, int index2);

int main(void) {

	/* bank1 is the starting initial state of everyone
	 * bank2 is the end state of everyone
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


	return 0;
}

/* used to check if solution is found */
int empty_bank(int bank[]) {

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
 * i.e. a missionary is not outnumbered by canibals
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
	// if canibals exceed missionaries
	if (c_count > m_count)
		return 0;
	return 1;
}

/* person(s) cross the river */
void cross(int from[N], int to[N], int i, int j) {

	to[find_empty_position(to)] = from[i];
	from[i] = 0;

	// second person is optional
	if (j != NULL) {
		to[find_empty_position(to)] = from[j];
		from[j] = 0;
	}

	return;
}
