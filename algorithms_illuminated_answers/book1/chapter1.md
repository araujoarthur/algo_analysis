# Chapter 1 - Introduction

## Problems


### 1.2
Answer: 2

### 1.2

Answer: nlogn. The base of the logarithm doesn't really matter. One that tries to hard proof it will reach a n log_3 n, but it's just a matter of a _constant factor_ variation, given that log_3 n = log_a(n)/log_a(3).

### 1.3 

The first merged array will end with 2n elements, the second with 3n up to kn. In the end, it takes n(2+3+4+5+k). The sum of the first I integers is known as sum(k, i=1) = k(k+1)/2. We dont have the first element (1) here, so we must account for that and end with sum(k, i=1) - 1, and ultimately, (kˆ2 + 1)/2 - 1. As we are in asymptotic domain, we can safely discard lower order terms and constant factors, thus keep only kˆ2. Now we have n(kˆ2), then, nkˆ2 steps.

### 1.4

Well, _nk_ is the amount of steps per merge, since we have k/2 elements (and as discussed before, the base of the logarithm is not important for this analysis), we have logk steps. Thus, nk merges happen log(k) times, then nk * log(k).

### 1.5

a. Yes, it's possible. In a sorted array the minimum gap is between two consecutive elements, it's just a matter of sorting and within the only one pass through the sorted array compare the acquired minimum between each pair.

b. Also possible. After sorting the array the repeated integers will be adjacent, thus it's just a matter of storing the last integer and comparing against the current integer (or A\[i-1\], for example) and if they're the same, do not add to the counter.

c. Yes. As it would be done in the case above, just don't add again if the current digit matches the last added.

d. It would require a lot of work to do in C. A lot less of work in Python. In the high level algorithm it wouldn't matter so yes, we could compute a single mode or even multiple modes with one pass using a dictionary for example.

e. If we know the length and assume the indexing to start at 0, just returning the element at length/2 will do the trick.