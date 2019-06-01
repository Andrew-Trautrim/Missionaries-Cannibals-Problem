#include <stdio.h>
#include <stdlib.h>

/*
 * The Missionary Cannibal Problem
 * On one bank of a river are three missionaries and three cannibals. 
 * There is one boat available that can hold up to two people and that 
 * they would like to use to cross the river. If the cannibals ever 
 * outnumber the missionaries on either of the river’s banks, the 
 * missionaries will get eaten.
 */

// max # of possible states
#define N 100

/* Solution functions */
int depth_first_search(int start[], int goal[], int **visited);

/* Utility functions */
int double_cross(int from[], int to[], int i, int j);
int single_cross(int from[], int to[], int i);
int is_empty(int arr[]);
int is_new_state(int start[], int end[], int **visited);
int valid_state(int bank[]);

void add_state(int start[], int end[], int **visited);
void copy(int copy[], int org[]);
void print_banks(int start[], int end[]);
void reset(int org1[], int org2[], int copy1[], int copy2[]);

int main(void) {

	/* 
	 * bank1 is the initial starting state of everyone
	 * bank2 is the end goal state of everyone
	 * 3 missionaries and 3 cannibals
	 * index 0 are missionaries
	 * index 1 are cannibals
	 * index 2 is the position of the boat
	 */
	int start[] = {3, 3, 1};
	int end[] = {0, 0, 0};

	int **visited = (int**)calloc(0, sizeof(int*) * N);
	for (int i = 0; i < N; ++i)
		visited[i] = (int*)calloc(0, sizeof(int) * 6);

	// solve function
	depth_first_search(start, end, visited);

	for (int i = 0; i < N; ++i)
		free(visited[i]);
	free(visited);

	return 1;
}

/*
 * Recursive solution by depth-first search
 */
int depth_first_search(int start[], int end[], int **visited) {

	print_banks(start, end);
	add_state(start, end, visited);

	// start position is empty and solution has been found
	if (is_empty(start)) {
		return 1;
	}

	// copies values incase we need to reset
	int temp1[3];
	int temp2[3];
	copy(temp1, start);
	copy(temp2, end);

	// determines which direction to go
	int *from;
	int *to;
	if (start[2] == 1) {
		from = start;
		to = end;
	} else {
		from = end;
		to = start;
	}

	// attempts to find solution from current state
	// returns 1 on success
	// resets values otherwise
	for (int i = 0; i < 2; ++i) {
		for (int j = 0; j < 2; ++j) {
			if (double_cross(from, to, i, j) && is_new_state(start, end, visited))
				if (depth_first_search(start, end, visited)) 
					return 1;
			copy(start, temp1);
			copy(end, temp2);
		}
		if (single_cross(from, to, i) && is_new_state(start, end, visited))
			if (depth_first_search(start, end, visited))
				return 1;
		copy(start, temp1);
		copy(end, temp2);
	}

	// unsuccessful
	return 0;
}

/* 
 * two people cross the river
 * returns 1 on success, 0 otherwise
 */
int double_cross(int from[], int to[], int i, int j) {

	if (from[i] == 0 || from[j] == 0)
		return 0;

	from[i]--;
	to[i]++;
	from[j]--;
	to[j]++;

	// checks if the cross is valid
	if (!valid_state(from) || !valid_state(to)) {
		// resets values
		from[i]++;
		to[i]--;
		from[j]++;
		to[j]--;
		return 0;
	}

	// switches the side of the boat
	from[2] = 0;
	to[2] = 1;

	return 1;
}

int is_empty(int arr[]) {
	for (int i = 0, n = sizeof(arr)/sizeof(arr[0]); i < n; ++i)
		if (arr[i] != 0)
			return 0;
	return 1;
}

/* checks if current state has already been visited */
int is_new_state(int start[], int end[], int **visited) {
	for (int i = 0; i < N; ++i) {
		if (start[0] == visited[i][0] && start[1] == visited[i][1] && start[2] == visited[i][2] && 
				end[0] == visited[i][3] && end[1] == visited[i][4] && end[2] == visited[i][5])
			return 0;
		else if (is_empty(visited[i]))
			return 1;
	}
	return 1;
}

/*
 * one person crosses the river
 */
int single_cross(int from[], int to[], int i) {

	// can't have negative values
	if (from[i] == 0)
		return 0;

	from[i]--;
	to[i]++;

	// checks if the action is valid
	if (!valid_state || !valid_state) {
		from[i]++;
		to[i]--;
		return 0;
	}

	// switches the side of the boat
	from[2] = 0;
	to[2] = 1;

	return 1;
}

/* 
 * verifys if a state is valid
 * i.e. missionaries are not outnumbered by cannibals
 * 1 is valid, 0 is not
 */
int valid_state(int bank[]) {
	if ((bank[0] < bank[1] && bank[0] != 0))
		return 0;
	return 1;
}

/*
 * adds a state to the visited
 */
void add_state(int start[], int end[], int **visited) {
	for (int i = 0; i < N; ++i) {
		if (is_empty(visited[i])) {
			visited[i][0] = start[0];
			visited[i][1] = start[1];
			visited[i][2] = start[2];
			visited[i][3] = end[0];
			visited[i][4] = end[1];
			visited[i][5] = end[2];
			return;
		}
	}
}

/*
 * copies vale from one array into the other
 */
void copy(int copy[], int org[]) {
	for (int i = 0; i < 3; ++i)
		copy[i] = org[i];
	return;
}

/*
 * Testing function
 */
void print_banks(int start[], int end[]) {
 	fprintf(stdout, "Start: %d %d: %d\n", start[0], start[1], start[2]);
	fprintf(stdout, "End:   %d %d: %d\n\n", end[0], end[1], end[2]);
	return;
}
