// H2-1
// Description: Given an integer array A of length n, sort the array.

// Input
// The first line contains a positive integer n.
// The second line contains n positive integers: a1, a2, ..., an.
// Size of data: 1 <= n <= 10,000,000; 0 <= ai <= 10^9.

// Output
// n integres in order from smallest to largest

// Sample input 1:
/*6
  6 1 6 4 1 9*/

// Sample output 1:
// 1 1 4 6 6 9

// Algorithm idea: starting from a plain quick sorting algorithm,
// the pivot is selected randomly each time, (or adopting a three-value compromise approach, with risk of timeout)
// and the elements in the array with the same value as the pivot are clustered around the pivot after partitioning.

// Experimentally, the algorithm is shown to be close to the function std::sort().

#include <cstdio>

#include <ctime>

#include <cstdlib>

#include <iostream>

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

int Random_Partition(int*& A, int p, int r) {
    int q = p + rand() % (r - p + 1);
    swap(A[q], A[r]);
    int x = A[r];
    int i = p - 1;
    for (int j = p; j < r; j++) {
        if (A[j] <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
} // Random_Partition

/*Gathering elements that are the same as pivot together*/
std::pair<int, int> Gather_Pivot(int*& A, int p, int r, int pivot) {
    /*the search range*/
    int left = pivot - 1;
    int right = pivot + 1;
    
    int guide_left = pivot - 1;
    int guide_right = pivot + 1;
    for (int i = left; i >= p; --i) { // search in the left subarray
        if (A[i] == A[pivot]) {
            if (i != guide_left) {
                swap(A[i], A[guide_left]);
                guide_left--;
            }
            else {
                guide_left--;
            }
        }
    }
    for (int i = right; i <= r; ++i) { // search in the right subarray
        if (A[i] == A[pivot]) {
            if (i != guide_right) {
                swap(A[i], A[guide_right]);
                guide_right++;
            }
            else {
                guide_right++;
            }
        }
    }
    return std::make_pair(guide_left, guide_right);
} // Gather_Pivot

void Quick_Sort(int*& A, int p, int r) {
    if (p < r) {
        int q = Random_Partition(A, p, r);
        std::pair<int, int> temp = Gather_Pivot(A, p, r, q);
        Quick_Sort(A, p, temp.first);
        Quick_Sort(A, temp.second, r);
    }
} // Quick_Sort

int main() {
    srand((unsigned)time(NULL));
    int len = 0; // the length of the array
    scanf("%d", &len);
    int* nums = new int[len];
    for (int i = 0; i < len; i++) scanf("%d", nums + i);
    Quick_Sort(nums, 0, len - 1);
    for (int i = 0; i < len; i++) printf("%d ", nums[i]);
    return 0;
}
