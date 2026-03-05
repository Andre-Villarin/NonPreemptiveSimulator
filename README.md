
# Table of Contents
- [Overview](#overview)
- [Project Files](#project-files)
- [Contributions](#contributions)
- [Running the Simulator](#running-the-simulator)
- [Example](#example)

# Overview
A CPU scheduler simulator demonstrating First-Come-First-Served (FCFS) and Shortest Job First (SJF) algorithms. Written in C++.

Made for partial fulfillment of CSCI 51.01 (Introduction to OS - Lecture), this C++ program simulates 2 algorithms
in CPU process scheduling: FCFS and SJF. It takes an input file (.txt) containing the processes to be
simulated, and outputs a Gantt chart in text form.

# Project Files
    NonPreemptiveSimulator/
    |
    ├── InputFile1.txt                 # contains 8 test cases
    ├── InputFile2.txt                 # contains 8 test cases
    ├── NonPreemptiveCPUScheduler.cpp  # takes an input file (.txt) and outputs simulation results to console
    ├── README.md                      # this file

# Contributions
The source code in this repository was written by me. The original project was developed as part of a group project, but this repository only contains the components I implemented.

My contributions include:
- FCFS scheduling algorithm
- SJF scheduling algorithm

# Running the Simulator

Requirements: C++

1. Clone this repo and 'cd' to the directory containing the source files

2. Compile NonPreemptiveCPUScheduler.cpp
    ```
      g++ NonPreemptiveCPUScheduler.cpp -o simulate
    ```

3. Run ./simulate using either InputFile1.txt or InputFile2.txt

    eg.
     ```
     ./simulate < InputFile1.txt
     ```
4. Simulation results will be outputed to the terminal. For how to interpret the results, refer to [this document](https://docs.google.com/document/d/1S_PEOaSddTODd2oxNNreiPuIp5A8u9puorTZCAZYMsI/edit?usp=sharing).

# Example

Input:
  ```
    ./simulate < InputFile1.txt
  ```

Output:
  ```
1 FCFS
0 1 50X 
50 3 3X 
53 2 2X 
Total time elapsed: 55ns
Total CPU burst time: 55ns
CPU Utilization: 100%
Throughput: 0.0545455 processes/ns
Waiting times: 14.3333ns
 Process 1: 0ns 
 Process 2: 13ns 
 Process 3: 30ns 
Turnaround times: 32.6667ns
 Process 1: 50ns 
 Process 2: 15ns 
 Process 3: 33ns 
Response times: 14.3333ns
 Process 1: 0ns 
 Process 2: 13ns 
 Process 3: 30ns 
2 FCFS
10 2 70X 
100 1 10X 
Total time elapsed: 110ns
Total CPU burst time: 80ns
CPU Utilization: 72.7273%
Throughput: 0.0181818 processes/ns
Waiting times: 0ns
 Process 1: 0ns 
 Process 2: 0ns 
Turnaround times: 40ns
 Process 1: 10ns 
 Process 2: 70ns 
Response times: 0ns
 Process 1: 0ns 
 Process 2: 0ns 
3 FCFS
0 2 100X 
100 3 10X 
110 1 10X 
Total time elapsed: 120ns
Total CPU burst time: 120ns
CPU Utilization: 100%
Throughput: 0.025 processes/ns
Waiting times: 26.6667ns
 Process 1: 30ns 
 Process 2: 0ns 
 Process 3: 50ns 
Turnaround times: 66.6667ns
 Process 1: 40ns 
 Process 2: 100ns 
 Process 3: 60ns 
Response times: 26.6667ns
 Process 1: 30ns 
 Process 2: 0ns 
 Process 3: 50ns 
4 SJF
0 1 100X 
100 4 10X 
110 2 20X 
130 3 30X 
Total time elapsed: 160ns
Total CPU burst time: 160ns
CPU Utilization: 100%
Throughput: 0.025 processes/ns
Waiting times: 70ns
 Process 1: 0ns 
 Process 2: 90ns 
 Process 3: 110ns 
 Process 4: 80ns 
Turnaround times: 110ns
 Process 1: 100ns 
 Process 2: 110ns 
 Process 3: 140ns 
 Process 4: 90ns 
Response times: 70ns
 Process 1: 0ns 
 Process 2: 90ns 
 Process 3: 110ns 
 Process 4: 80ns 
5 SJF
0 1 65X 
65 5 5X 
70 4 10X 
80 2 20X 
100 3 15X 
Total time elapsed: 115ns
Total CPU burst time: 115ns
CPU Utilization: 100%
Throughput: 0.0434783 processes/ns
Waiting times: 23ns
 Process 1: 0ns 
 Process 2: 40ns 
 Process 3: 10ns 
 Process 4: 50ns 
 Process 5: 15ns 
Turnaround times: 46ns
 Process 1: 65ns 
 Process 2: 60ns 
 Process 3: 25ns 
 Process 4: 60ns 
 Process 5: 20ns 
Response times: 23ns
 Process 1: 0ns 
 Process 2: 40ns 
 Process 3: 10ns 
 Process 4: 50ns 
 Process 5: 15ns 
6 FCFS
0 5 20X 
20 4 20X 
40 3 20X 
60 2 20X 
80 1 20X 
Total time elapsed: 100ns
Total CPU burst time: 100ns
CPU Utilization: 100%
Throughput: 0.05 processes/ns
Waiting times: 20ns
 Process 1: 40ns 
 Process 2: 30ns 
 Process 3: 20ns 
 Process 4: 10ns 
 Process 5: 0ns 
Turnaround times: 40ns
 Process 1: 60ns 
 Process 2: 50ns 
 Process 3: 40ns 
 Process 4: 30ns 
 Process 5: 20ns 
Response times: 20ns
 Process 1: 40ns 
 Process 2: 30ns 
 Process 3: 20ns 
 Process 4: 10ns 
 Process 5: 0ns 
7 SJF
0 1 100X 
100 3 10X 
110 8 10X 
120 6 20X 
140 2 30X 
170 7 30X 
200 4 40X 
240 5 80X 
Total time elapsed: 320ns
Total CPU burst time: 320ns
CPU Utilization: 100%
Throughput: 0.025 processes/ns
Waiting times: 103.125ns
 Process 1: 0ns 
 Process 2: 130ns 
 Process 3: 80ns 
 Process 4: 185ns 
 Process 5: 185ns 
 Process 6: 60ns 
 Process 7: 100ns 
 Process 8: 85ns 
Turnaround times: 143.125ns
 Process 1: 100ns 
 Process 2: 160ns 
 Process 3: 90ns 
 Process 4: 225ns 
 Process 5: 265ns 
 Process 6: 80ns 
 Process 7: 130ns 
 Process 8: 95ns 
Response times: 103.125ns
 Process 1: 0ns 
 Process 2: 130ns 
 Process 3: 80ns 
 Process 4: 185ns 
 Process 5: 185ns 
 Process 6: 60ns 
 Process 7: 100ns 
 Process 8: 85ns 
8 SJF
0 1 50X 
50 2 2X 
52 3 3X 
Total time elapsed: 55ns
Total CPU burst time: 55ns
CPU Utilization: 100%
Throughput: 0.0545455 processes/ns
Waiting times: 14ns
 Process 1: 0ns 
 Process 2: 10ns 
 Process 3: 32ns 
Turnaround times: 32.3333ns
 Process 1: 50ns 
 Process 2: 12ns 
 Process 3: 35ns 
Response times: 14ns
 Process 1: 0ns 
 Process 2: 10ns 
 Process 3: 32ns
```
