#include <stdio.h>

/*
 * The Missionary Cannibal Problem
 * On one bank of a river are three missionaries and three cannibals. 
 * There is one boat available that can hold up to two people and that 
 * they would like to use to cross the river. If the cannibals ever 
 * outnumber the missionaries on either of the river’s banks, the 
 * missionaries will get eaten.
 */

#define N 2

/* Solution functions */
int depth_first_search(int start[], int goal[], int visited[32][4], int path[32][4], int depth);

/* Utility functions */
int cross(int from[], int to[], int i, int j);
int is_empty(int arr[]);
int is_new_state(int start[], int end[], int visited[32][4]);
int valid_state(int bank[]);

void add_state(int start[], int end[], int visited[32][4]);
void copy(int copy[], int org[]);
void print_banks(int start[], int end[]);

int main(void) {

	/* 
	 * bank1 is the initial starting state of everyone
	 * bank2 is the end goal state of everyone
	 * 3 missionaries and 3 cannibals
	 * index 0 are missionaries
	 * index 1 are cannibals
	 */
	int start[] = {3, 3};
	int end[] = {0, 0};
	int visited[32][4];
	int path[32][4];

	depth_first_search(start, end, visited, path, 0);

	return 1;
}

/*
 * Recursive solution by depth-first search
 */
int depth_first_search(int start[], int end[], int visited[32][4], int path[32][4], int depth) {

	print_banks(start, end);
	add_state(start, end, visited);

	// start position is empty and solution has been found
	if (start[0] == 0 && start[1] == 0) {
		return 1;
	}

	// copies values incase we need to reset
	int temp1[N];
	int temp2[N];
	copy(temp1, start);
	copy(temp2, end);

	// determines which direction to go
	int *from;
	int *to;
	if (depth % 2 == 0) {
		from = start;
		to = end;
	} else {
		from = end;
		to = start;
	}

	depth++;
	// attempts to find solution from current state
	// returns 1 on success
	// resets values otherwise
	if (cross(from, to, 0, 0) && is_new_state(start, end, visited) && (depth_first_search(start, end, visited, path, depth))) { 
		return 1;
	}
	copy(start, temp1);
	copy(end, temp2);

	if (cross(from, to, 1, 1) && is_new_state(start, end, visited) && (depth_first_search(start, end, visited, path, depth)))
		return 1;
	copy(start, temp1);
	copy(end, temp2);

	if (cross(from, to, 0, 1) && is_new_state(start, end, visited) && (depth_first_search(start, end, visited, path, depth)))
		return 1;
	copy(start, temp1);
	copy(end, temp2);
	
	if (cross(from, to, 0, -1) && is_new_state(start, end, visited) && (depth_first_search(start, end, visited, path, depth)))
		return 1;
	copy(start, temp1);
	copy(end, temp2);
	
	if (cross(from, to, 1, -1) && is_new_state(start, end, visited) && (depth_first_search(start, end, visited, path, depth)))
		return 1;
	copy(start, temp1);
	copy(end, temp2);

	// unsuccessful
	return 0;
}

/* 
 * person(s) cross the river
 * returns 1 on success, 0 otherwise
 */
int cross(int from[], int to[], int i, int j) {

	from[i] -= 1;
	to[i] += 1;
	if (j != -1) {
		from[j] -= 1;
		to[j] += 1;
	}

	// checks if the cross is valid
	if (!valid_state(from) || !valid_state(to)) {
		from[i] += 1;
		to[i] -= 1;
		if(j != -1) {
			from[j] += 1;
			to[j] += 1;
		}
		return 0;
	}

	return 1;
}

int is_empty(int arr[]) {
	for (int i = 0, n = sizeof(arr)/sizeof(arr[0]); i < n; ++i)
		if (arr[i] != 0)
			return 0;
	return 1;
}

/* checks if current state has already been visited */
int is_new_state(int start[], int end[], int visited[32][4]) {
	for (int i = 0; i < 32; ++i) {
		if (start[0] == visited[i][0] && start[1] == visited[i][1] && end[0] == visited[i][2] && end[1] == visited[i][3])
			return 0;
		else if (is_empty(visited[i]))
			return 1;
	}
	return 1;
}

/* 
 * verifys if a state is valid
 * i.e. missionaries are not outnumbered by cannibals
 * 1 is valid, 0 is not
 */
int valid_state(int bank[]) {
	if (bank[0] < bank[1] && bank[0] != 0)
		return 0;
	return 1;
}

/*
 * adds a state to the visited array
 */
void add_state(int start[], int end[], int visited[32][4]) {
	for (int i = 0; i < 32; ++i) {
		if (is_empty(visited[i])) {
			visited[i][0] = start[0];
			visited[i][1] = start[1];
			visited[i][2] = end[0];
			visited[i][3] = end[1];
			return;
		}
	}
}

/*
 * copies vale from one array into the other
 */
void copy(int copy[], int org[]) {
	for (int i = 0; i < N; ++i)
		copy[i] = org[i];
	return;
}

/*
 * Testing function
 */
void print_banks(int start[], int end[]) {
 	fprintf(stdout, "Start: %d %d\n", start[0], start[1]);
	fprintf(stdout, "End:   %d %d\n\n", end[0], end[1]);
	return;
}
