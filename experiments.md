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

## Host 2: [NAME]

- CPU: 
- Cores: 
- Cache size (if known):
- RAM: 
- Storage (if known): 
- OS: 

### Input data

*Briefly describe how large your data set is and how you created it. Also include how long `msort` took to sort it.*

### Experiments

*Replace X, Y, Z with the number of threads used in each experiment set.*

#### X Threads

Command used to run experiment: ``

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

#### Y Threads

Command used to run experiment: ``

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

#### Z Threads

Command used to run experiment: ``

Sorting portion timings:

1. ______ seconds
2. ______ seconds
3. ______ seconds
4. ______ seconds

*repeat sections as needed*

## Observations and Conclusions

*Reflect on the experiment results and the optimal number of threads for your concurrent merge sort implementation on different hosts or platforms. Try to explain why the performance stops improving or even starts deteriorating at certain thread counts.*


