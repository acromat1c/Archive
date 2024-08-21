from random import randint
from timeit import repeat

def run_sorting_algorithm(algorithm, array):
    try:
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
    except Exception as error:
        print(f"Algorithm: {algorithm}. Minimum execution time: faild, {error}")


ARRAY_LENGTH = 10000

if __name__ == "__main__":
    array = [randint(0, 1000) for i in range(ARRAY_LENGTH)]
    print("random array:")
    run_sorting_algorithm(algorithm="insertion_sort", array=array)
    run_sorting_algorithm(algorithm="selection_sort", array=array)
    run_sorting_algorithm(algorithm="bubble_sort", array=array)
    run_sorting_algorithm(algorithm="merge_sort", array=array)
    run_sorting_algorithm(algorithm="quick_sort", array=array)
    run_sorting_algorithm(algorithm="tim_sort", array=array)
    run_sorting_algorithm(algorithm="heap_sort", array=array)
    print()
    array = [i for i in range(ARRAY_LENGTH)]
    print("sorted array:")
    run_sorting_algorithm(algorithm="insertion_sort", array=array)
    run_sorting_algorithm(algorithm="selection_sort", array=array)
    run_sorting_algorithm(algorithm="bubble_sort", array=array)
    run_sorting_algorithm(algorithm="merge_sort", array=array)
    run_sorting_algorithm(algorithm="quick_sort", array=array)
    run_sorting_algorithm(algorithm="tim_sort", array=array)
    run_sorting_algorithm(algorithm="heap_sort", array=array)
    print()
    for _ in range(int(ARRAY_LENGTH/10)):
        i = randint(0,len(array)-1)
        j = randint(0,len(array)-1)
        array[i], array[j] = array[j], array[i]
    print()
    print("sorted array:")
    run_sorting_algorithm(algorithm="insertion_sort", array=array)
    run_sorting_algorithm(algorithm="selection_sort", array=array)
    run_sorting_algorithm(algorithm="bubble_sort", array=array)
    run_sorting_algorithm(algorithm="merge_sort", array=array)
    run_sorting_algorithm(algorithm="quick_sort", array=array)
    run_sorting_algorithm(algorithm="tim_sort", array=array)
    run_sorting_algorithm(algorithm="heap_sort", array=array)
    

#conclusion: some algorythems are faster, some are more complex and some are just downright better.