from random import randint
from timeit import repeat

def run_sorting_algorithm(algorithm, array):
    # Set up the context and prepare the call to the specified
    # algorithm using the supplied array. Only import the
    # algorithm function if it's not the built-in `sorted()`.
    setup_code = f"from {algorithm} import {algorithm}" \
        if algorithm != "sorted" else ""

    stmt = f"{algorithm}({array})"

    # Execute the code ten different times and return the time
    # in seconds that each execution took
    times = repeat(setup=setup_code, stmt=stmt, repeat=1, number=3)

    # Finally, display the name of the algorithm and the
    # minimum time it took to run
    print(f"Algorithm: {algorithm}. Minimum execution time: {min(times)}")

ARRAY_LENGTH = 10000

if __name__ == "__main__":
    # Generate an array of `ARRAY_LENGTH` items consisting
    # of random integer values between 0 and 999
    array = [randint(0, 1000) for i in range(ARRAY_LENGTH)]

    # Call the function using the name of the sorting algorithm
    # and the array you just created
    # run_sorting_algorithm(algorithm="sorted", array=array)
    
    # Modulen insertion_sort.py ma finnes i samme katalog
    run_sorting_algorithm(algorithm="insertion_sort", array=array)
    
    # Call different sorting algorithms
    # insertion sort
    # selection sort
    # bubble sort
    # merge sort
    # quicksort
    # timsort
    # heapsort

    # Testing when list is sorted..
    # Generate a NB! sorted list of ARRAY_LENGTH items
    #array = [i for i in range(ARRAY_LENGTH)]

