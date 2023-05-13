import time
import random
import hashlib
from typing import List
import os

R = [random.randint(0, 2**32-1) for _ in range(256)]


def hash_crc(key: bytearray) -> int:
    h = 0xffffffff

    for ki in key:
        h = h ^ ki  # Исправлено: ki уже является int, его не нужно преобразовывать
        for _ in range(8):
            if h & 0x00000001:
                h = (h >> 1) ^ 0xedb88320
            else:
                h >>= 1
    return h ^ 0xffffffff


def hash_pjw(key: bytes) -> int:
    h = 0

    for ki in key:
        h = (h << 4) + ki
        g = h & 0xf0000000
        if g != 0:
            h = h ^ (g >> 24)
            h = h ^ g

    return h


def hash_buz(key: str) -> int:
    h = 0
    for ki in key:
        highorder = h & 0x80000000
        h = h << 1
        h = h ^ (highorder >> 31)
        h = h ^ R[ki]

    return h


def find_duplicates(files: List[str], hash_function: callable) -> List[str]:
    unique_files = {}
    duplicates = []
    directory = 'out'
    for filename in os.listdir(directory):
        file_path = os.path.join(directory, filename)
        with open(file_path, 'rb') as f:
            contents = f.read()
            hash_value = hash_function(contents)
            if hash_value in unique_files:
                duplicates.append(f)
            else:
                unique_files[hash_value] = f

    return duplicates

t0 = time.time()
duplicates_crc = find_duplicates(os.listdir('out'), hash_crc)
t1 = time.time()
print("Function Name:\t\thash_crc")
print("Duplicates:\t\t", len(duplicates_crc))
print("Execution time:\t\t", t1-t0, "sec")

t0 = time.time()
duplicates_pjw = find_duplicates(os.listdir('out'), hash_pjw)
t1 = time.time()
print("Function Name:\t\thash_pjw")
print("Duplicates:\t\t", len(duplicates_pjw))
print("Execution time:\t\t", t1-t0, "sec")

t0 = time.time()
duplicates_buz = find_duplicates(os.listdir('out'), hash_buz)
t1 = time.time()
print("Function Name:\t\thash_buz")
print("Duplicates:\t\t", len(duplicates_buz))
print("Execution time:\t\t", t1-t0, "sec")

t0 = time.time()
duplicates_default = find_duplicates(os.listdir('out'), hashlib.sha1)
t1 = time.time()
print("Function Name:\t\thash_default")
print("Duplicates:\t\t", len(duplicates_default))
print("Execution time:\t\t", t1-t0, "sec")
