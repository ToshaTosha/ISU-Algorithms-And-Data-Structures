import time
import sys
import random

def dict_test(n):
    start_time = time.perf_counter_ns()
    result = {}
    n_elements = n
    for i in range(1, n_elements+1):
        key = random.randint(0, 100000)
        value = random.randint(0, 100000)
        result[key] = value
    end_time = time.perf_counter_ns()
    time_diff = (end_time - start_time)
    memory = sys.getsizeof(result)
    print(f"Время: {time_diff} ms, память: {memory} b")
    return time_diff, memory

for i in range(6):
    n = 10 ** i
    elapsed, memory = dict_test(n)
    with open('out-py.txt', 'a', encoding='UTF-8') as file:
        file.write(str(memory) + ' ' + str(elapsed) + '\n')
