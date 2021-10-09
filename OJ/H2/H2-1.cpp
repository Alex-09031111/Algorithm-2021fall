// H2-1

// Description: 
// At a party, the organizer prepared a raffle for the audience, and the rules of the raffle were as follows.
// The host will randomly generate a number k on the big screen, 
// and then the audience will enter a number between 0 and 10000 (including 0 and 10000) in the raffle system through their cell phones, 
// at this time the winning audience will be the one who enters the kth smallest among all the audience,
// please output the number chosen by the winning audience.

// Input:
// There are two rows of input data.
// The first line has two numbers, the first number n represents the total number of people and the second number k , 
// the input k will ensure that the kth smaller number exists.
// The second line has n digits, each representing the number ai of digits entered by audience.
// Data size: 0 < k <= n <= 10^7; 0 <= ai <= 10,000.

// Output:
// The output contains one line containing a number indicating the number entered by the winning audience.

// Sample Input 1:
// 6 4
// 6 1 6 4 1 9

// Sample Output 1:
// 6

#include <iostream>

#include <cstdio>

void Insertion_Sort(int*& A, int p, int q) {
	int key = 0;
	for (int j = p + 1; j <= q; j++) {
		key = A[j];
		int i = j - 1;
		while (i >= p && A[i] > key) {
			A[i + 1] = A[i];
			i--;
		}
		A[i + 1] = key;
	}
} // Insertion_Sort

/*Get the median of array A*/
int Median(int*& A, int p, int q) {
	Insertion_Sort(A, p, q);
	return A[p + (q - p) / 2];
} // Median

/*Partite the array A[p..q] according to the pivot*/
int Pivot_Partition(int*& A, int p, int r, int pivot) {
	for (int i = p; i <= r; i++) {
		if (A[i] == pivot) {
			std::swap(A[i], A[r]); // exchange pivot and the tail A[r]
			break;
		}
	}
	/*partite the array*/
	int x = A[r];
	int i = p - 1;
	for (int j = p; j < r; j++) {
		if (A[j] <= x) {
			i++;
			std::swap(A[i], A[j]);
		}
	}
	std::swap(A[i + 1], A[r]);
	return i + 1;
} // Pivot_Partition

int Worst_Linear_Select(int*& A, int p, int r, int k) {
	if (p == r) return A[p];
	int len = r - p + 1;
	int medians_num = 1;
	if (len > 5) medians_num = (len % 5 == 0) ? len / 5 : len / 5 + 1;
	int* medians = new int[medians_num]; // Storage medians
	int count = p;
	for (int i = 0; i < medians_num - 1; i++) {
		medians[i] = Median(A, count, count + 4);
		// solve for the median of subarray A[count..count + 4] with length 5
		count += 5;
	}
	medians[medians_num - 1] = Median(A, count, r);
	/*solve for the median of the array medians[..] recursively*/
	int pivot = Worst_Linear_Select(medians, 0, medians_num - 1, (medians_num + 1) / 2);
	/*Partite the array with the above pivot*/
	int pos = Pivot_Partition(A, p, r, pivot);
	int len1 = pos - p + 1; // length of the left subarray A[p..pos]
	if (len1 == k) return pivot; // the key position is just the pivot
	else if (len1 > k) return Worst_Linear_Select(A, p, pos - 1, k); // the key position is in the left subarray
	else return Worst_Linear_Select(A, pos + 1, r, k - len1); // the key position is in the right subarray
} // Worst_Linear_Select

int main() {
	int len = 0; // total number of people
	int k = 0;
	scanf("%d%d", &len, &k);
	int* nums = new int[len];
	for (int i = 0; i < len; i++) scanf("%d", nums + i);
	printf("%d", Worst_Linear_Select(nums, 0, len - 1, k));
	return 0;
} // main
