# Sandwich Shop Synchronization (C++)

This program simulates a synchronization problem inspired by the classic "Producer-Consumer" scenario using semaphores and threads in C++. 

A vendor places two of the three sandwich ingredients (bread, cheese, ham) on the table at random. Customers each have one ingredient and wait for the other two to be available to make and eat a sandwich.

## Problem Description

- The vendor randomly places two ingredients on the table.
- There are three customers, each possessing the third ingredient:
  - Customer with cheese and ham waits for bread and ham.
  - Customer with bread and ham waits for cheese and ham.
  - Customer with bread and cheese waits for bread and cheese.
- Customers take their needed ingredients, assemble a sandwich, and "eat" it.
- Synchronization is managed using POSIX semaphores (`sem_t`).

## How to Compile and Run

```bash
g++ -pthread -o sandwich-shop sandwich_shop.cpp
./sandwich-shop
```

Vendor puts bread and cheese on the table.
Customer takes bread and cheese, leaves the store, assembles and eats the sandwich.

Vendor puts cheese and ham on the table.
Customer takes cheese and ham, leaves the store, assembles and eats the sandwich.

Vendor puts bread and ham on the table.
Customer takes bread and ham, leaves the store, assembles and eats the sandwich.

...
