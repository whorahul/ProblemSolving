import math
import os
import random
import re
import sys

#
# hackerrank.com/whorahul
#

def gamingArray(arr):
    counter = -1
    cmax = 0

    for i in range(len(arr)):
        if cmax < arr[i]:
            cmax = arr[i]
            counter += 1

    if counter%2 == 0:
        return 'BOB'
    else:
        return "ANDY"

if __name__ == '__main__':
    fptr = open(os.environ['OUTPUT_PATH'], 'w')

    g = int(input().strip())

    for g_itr in range(g):
        arr_count = int(input().strip())

        arr = list(map(int, input().rstrip().split()))

        result = gamingArray(arr)

        fptr.write(result + '\n')

    fptr.close()
