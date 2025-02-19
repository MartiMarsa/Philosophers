Dining Philosophers Problem in C

Introduction

The Dining Philosophers Problem is a classic synchronization problem in computer science and concurrent programming. It was originally formulated by Edsger W. Dijkstra in 1965 and highlights challenges related to resource sharing, deadlock, starvation, and concurrency control.

Problem Statement

Five philosophers sit around a circular table, each alternating between two activities: thinking and eating. In front of each philosopher is a plate of food, and between each pair of adjacent philosophers, there is a single fork. To eat, a philosopher must pick up both the left and right forks. However, since there are only five forks, not all philosophers can eat simultaneously. The challenge is to design a synchronization mechanism that allows the philosophers to eat without leading to deadlock or starvation.

Theoretical Concepts

To develop a robust solution in C, one must understand the following theoretical concepts:

1. Mutual Exclusion

Philosophers must acquire forks in a way that prevents multiple philosophers from using the same fork at the same time.

2. Deadlock

A deadlock situation occurs if each philosopher picks up one fork and waits indefinitely for the second fork, preventing any of them from eating.

3. Starvation

A philosopher might starve if an unfair scheduling mechanism prevents them from ever acquiring both forks.

4. Concurrency and Synchronization

Using mutexes (mutual exclusion locks) and semaphores to manage concurrent access to shared resources.

5. Thread Management

In C, the problem is typically solved using POSIX threads (pthreads), where each philosopher is represented as an independent thread.

6. Resource Allocation Strategies

Different strategies can be applied to prevent deadlocks and starvation, including:

Ordered Fork Picking: Always picking up the lower-numbered fork first.

Asymmetric Philosophers: Some philosophers pick up the left fork first, while others pick up the right.

Arbitrator Solution: A central entity grants permission to eat, ensuring that not all philosophers attempt to pick up forks simultaneously.
