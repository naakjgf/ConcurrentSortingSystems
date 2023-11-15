/** 
 * Threaded Merge Sort
 *
 * Modify this file to implement your multi-threaded version of merge sort. 
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>

#include <unistd.h>

#include <assert.h>

#define tty_printf(...) (isatty(1) && isatty(0) ? printf(__VA_ARGS__) : 0)

#ifndef SHUSH
#define log(...) (fprintf(stderr, __VA_ARGS__))
#else 
#define log(...)
#endif

typedef struct {
	long* nums;
	long* target;
	int from;
	int to;
} sortArgs;

/** The number of threads to be used for sorting. Default: 1 */
int thread_count = 1;

/**
 * Compute the delta between the given timevals in seconds.
 */
double time_in_secs(const struct timeval *begin, const struct timeval *end) {
	long s = end->tv_sec - begin->tv_sec;
	long ms = end->tv_usec - begin->tv_usec;
	return s + ms * 1e-6;
}

/**
 * Print the given array of longs, an element per line.
 */
void print_long_array(const long *array, int count) {
	for (int i = 0; i < count; ++i) {
		printf("%ld\n", array[i]);
	}
}

/**
 * Merge two slices of nums into the corresponding portion of target.
 */
void merge(long nums[], int from, int mid, int to, long target[]) {
	int left = from;
	int right = mid;

	int i = from;
	for (; i < to && left < mid && right < to; i++) {
		if (nums[left] <= nums[right]) {
			target[i] = nums[left];
			left++;
		}
		else {
			target[i] = nums[right];
			right++;
		}
	}
	if (left < mid) {
		memmove(&target[i], &nums[left], (mid - left) * sizeof(long));
	}
	else if (right < to) {
		memmove(&target[i], &nums[right], (to - right) * sizeof(long));
	}

}


/**
 * Sort the given slice of nums into target.
 *
 * Warning: nums gets overwritten.
 */
void merge_sort_aux(long nums[], int from, int to, long target[]) {
	if (to - from <= 1) {
		return;
	}

	int mid = (from + to) / 2;
	merge_sort_aux(target, from, mid, nums);
	merge_sort_aux(target, mid, to, nums);
	merge(nums, from, mid, to, target);
}

/**
 * Thread function for sorting it's portion of the array.
 * 
 * This function kind of acts as the starting point for each thread created in the multi-threaded
 * merge sort process. It casts the argument back to the the sortArgs struct made at the top,
 * which contains the segment of the array to be sorted and the corresponding target array to later be
 * combined with.
 * 
 * @param arg A void pointer/generic pointer that needs to be cast back to sortArgs to access
 *            all it's data fields. It contains the information about the part of the array
 *            to be sorted.
 * @return NULL since we don't need to return anything from the thread.
 */
void* thread_sort(void* arg) {
	sortArgs* sort_args = (sortArgs*)arg;
	merge_sort_aux(sort_args->nums, sort_args->from, sort_args->to, sort_args->target);
	return NULL;
}

/**
 * This Function performs the final merge of the subarrays sorted by each thread.
 * 
 * Then it merges the sorted subarrays produced by each thread into a single
 * sorted array. The merging is done sequentially and ensures that the final array
 * is completely sorted. If there aren't enough threads left, then just merges the result
 * a single one was working on.
 * 
 * @param nums Pointer to the original array.
 * @param target Pointer to the array where sorted segments are stored.
 * @param count Total number of elements in the array.
 * @param chunk_size Size of the segments that were sorted individually by each thread.
 */
void final_merge(long* nums, long* target, int count, int chunk_size) {
	for (int i = 0; i < thread_count - 1; i++) {
		merge(target, i * chunk_size, (i + 1) * chunk_size, (i + 2) * chunk_size > count ? count : (i + 2) * chunk_size, nums);
	}
}

/**
 * The main function that preforms/is the root of the multi-threaded merge sort.
 * 
 * It allocates memory for the result array and divides the sorting task
 * among multiple threads. Each thread sorts a portion of the array, and then
 * final_merge is called to merge these sorted portions.
 * 
 * @param nums Array of numbers to be sorted.
 * @param count The total number of elements in the array.
 * @return Pointer to the sorted array.
 */
long *merge_sort(long nums[], int count) {
	long *result = calloc(count, sizeof(long));
	assert(result != NULL);

	memmove(result, nums, count * sizeof(long));

	// Create an array of threads
	pthread_t threads[thread_count];
	sortArgs args[thread_count];

	// Calculate the size of each subarray
	int chunk_size = count / thread_count;

	for (int i = 0; i < thread_count; ++i) {
		// all the setup arguments for each thread
		args[i].nums = nums;
		args[i].target = result;
		args[i].from = i * chunk_size;
		args[i].to = (i == thread_count - 1) ? count : (i + 1) * chunk_size;

		// Creating threads
		pthread_create(&threads[i], NULL, thread_sort, &args[i]);
	}

	//wating for the threads to finish
	for (int i = 0; i < thread_count; ++i) {
		pthread_join(threads[i], NULL);
	}

	final_merge(nums, result, count, chunk_size);

	return result;
}

/**
 * Based on command line arguments, allocate and populate an input and a 
 * helper array.
 *
 * Returns the number of elements in the array.
 */
int allocate_load_array(int argc, char **argv, long **array) {
	assert(argc > 1);
	int count = atoi(argv[1]);

	*array = calloc(count, sizeof(long));
	assert(*array != NULL);

	long element;
	tty_printf("Enter %d elements, separated by whitespace\n", count);
	int i = 0;
	while (i < count && scanf("%ld", &element) != EOF)  {
		(*array)[i++] = element;
	}

	return count;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <n>\n", argv[0]);
		return 1;
	}

	struct timeval begin, end;

	// get the number of threads from the environment variable SORT_THREADS
	if (getenv("MSORT_THREADS") != NULL)
		thread_count = atoi(getenv("MSORT_THREADS"));

	log("Running with %d thread(s). Reading input.\n", thread_count);

	// Read the input
	gettimeofday(&begin, 0);
	long *array = NULL;
	int count = allocate_load_array(argc, argv, &array);
	gettimeofday(&end, 0);

	log("Array read in %f seconds, beginning sort.\n", 
			time_in_secs(&begin, &end));

	// Sort the array
	gettimeofday(&begin, 0);
	long *result = merge_sort(array, count);
	gettimeofday(&end, 0);

	log("Sorting completed in %f seconds.\n", time_in_secs(&begin, &end));

	// Print the result
	gettimeofday(&begin, 0);
	print_long_array(result, count);
	gettimeofday(&end, 0);

	log("Array printed in %f seconds.\n", time_in_secs(&begin, &end));

	free(array);
	free(result);

	return 0;
}
