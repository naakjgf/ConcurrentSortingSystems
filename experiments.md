# Threaded Merge Sort Experiments


## Host 1: Ubuntu VM

- CPU: QEMU Virtual Processor, Model virt-7.2, 5 Cores, 2000 MHz Max Speed, 1 Thread per Core
- Cores: 5
- Cache size (if known):
- RAM: 8192 MB
- Storage (if known): 15.11 GB Available 
- OS: Ubuntu 22.04

### Input data

100 million randomly generated numbers, I used "shuf -i1-100000000 > hundred-million.txt" as was in the example to create a randomly generated file with 100 million numbers unordered, for the default msort it took 20.002258 seconds, which is more than the recommended 10 seconds. 

### Experiments

*Replace X, Y, Z with the number of threads used in each experiment set.*

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 8.839257 seconds
2. 8.837980 seconds
3. 8.836806 seconds
4. 8.862133 seconds

#### 5 Threads

Command used to run experiment: 'MSORT_THREADS=5 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 4.416931 seconds
2. 4.346295 seconds
3. 4.377550 seconds
4. 4.359940 seconds

#### 10 Threads

Command used to run experiment: `MSORT_THREADS=10 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 4.314750 seconds
2. 4.275673 seconds
3. 4.356747 seconds
4. 4.353963 seconds

## Host 2: MacOS Host Machine

- CPU: Apple M1 Max
- Cores: 10
- Cache size (if known):
- RAM: 32 GB
- Storage (if known): 1.7 TB 
- OS: MacOS Monterey Version 12.6

### Input data

Same as before -- 100 million randomly generated numbers, though I brew installed similiar library and I used "gshuf -i1-100000000 > hundred-million.txt" as was in the
example to create a randomly generated file with 100 million numbers unordered, for the default msort it took 17.504015 seconds, which is yet again a bit more than
the recommended 10 seconds.

### Experiments

*Replace X, Y, Z with the number of threads used in each experiment set.*

#### 2 Threads

Command used to run experiment: `MSORT_THREADS=2 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 9.422514 seconds
2. 9.417725 seconds
3. 9.410817 seconds
4. 9.410579 seconds

#### 5 Threads

Command used to run experiment: `MSORT_THREADS=5 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 4.445159 seconds
2. 4.465497 seconds
3. 4.473328 seconds
4. 4.462042 seconds

#### 10 Threads

Command used to run experiment: `MSORT_THREADS=10 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 3.113935 seconds
2. 3.157699 seconds
3. 3.174569 seconds
4. 3.157227 seconds

#### 20 Threads

Command used to run experiment: `MSORT_THREADS=20 ./tmsort 100000000 < hundred-million.txt > /dev/null`

Sorting portion timings:

1. 3.084598 seconds
2. 3.115128 seconds
3. 3.130812 seconds
4. 3.118340 seconds

## Observations and Conclusions

*Reflect on the experiment results and the optimal number of threads for your concurrent merge sort implementation on different hosts or platforms. Try to explain why the performance stops improving or even starts deteriorating at certain thread counts.*

There appears to be a highest return from my experience around 5 threads, possibly would be either 6 or 4. The reason it seems is there is diminishing return, merge sort
is a logarithmic algorithm so I would bet that could be a reason attributed to why the more threads given it can only get so fast, the gains you get depreciate, each of
those additinal threads are working on a smaller set of numbers and as such they would be less efficient just due to the fact they are working less than previous threads.
I would say this applies for when the threads go beyond the number of cores, like double has essentially the same amount of preformance and this can probably be attribute to cores only being able to spawn one instance of a thread, each core is a complete CPU capable of executing on a thread though that is only 1 single thread, hence our
CPU core count limits the amount of threads we can even make and use. I believe those two things account for most of the lowering efficiency, there may be other
variables I am unaware of, and may be intersted in learning about in a moment when I have more time on my hands.
