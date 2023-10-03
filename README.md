# Online Book Reader Console Program
**A Simple Online Book Reader Console Program**

## Table of Contents
- [Introduction](#introduction)
- [System Design](#system-design)
- [Program Features](#program-features)
- [Design Philosophy](#design-philosophy)

## Introduction
Welcome to the Online Book Reader Console Program! This simple console application allows users to read books and administrators to manage the book collection. While it may not have an extensive set of features, it is designed to provide a straightforward and user-friendly reading experience.

## System Design
[UML Class Diagram](https://imgur.com/a/ihh5FOU)

## Program Features
### Admin Users
- Admin users are pre-added to the system's memory (database). There is no need for admin sign-up.
- Admins have the privilege to add books to the system.
### Initial Data
- Initially, some books and customers can be added to the system.
- However, administrators have the authority to add more books and users as needed.
### Input Handling
- The program assumes users will avoid using spaces in their inputs.
- It assumes proper user behavior and does not extensively validate inputs.
### Standard Access
- Users have standard access to the program, where they can perform the following functionalities:
  - Customer Features
    - View their profile, which displays basic information.
  - Book Reading
    - Customers can view the list of available books and select one for reading.
    - Once a book is selected, a reading session is created, showing:
      1. Total pages in the book.
      2. Current page number (e.g., 1/5).
      3. Navigation options (next and previous).
      4. Option to stop reading (which remains in the sessions).
  - Navigation
    - Customers can navigate through the book pages.
    - The program keeps track of the last page visited for each session.
  - Multiple Sessions
    - Customers can have multiple open sessions for the same book.
      - For example, a user can have three sessions for the same C++ book.
    - If a customer logs out and logs back in, they can see their last sessions.
  - Admin Features
    - Admins can log in and add books to the system.
    - Multiple admins can manage the book collection.
### Seamless Experience
- If an admin logs out, and a regular user logs in, the new user will see the recently added books.

## Design Philosophy
The program focuses on simplicity and essential features.
Input validation is minimal, assuming proper user behavior.
Hard-coded lines are used sparingly, primarily in default constructors.
There are no user IDs or stored data between program sessions.
The system maintains a straightforward design for ease of use.
Please note that ***I kept things simple and focused on the design as possible***, and future updates may introduce more advanced features and data persistence. Enjoy your reading experience with the Online Book Reader Console Program!
