Richfield Library and Student Management Systems
This repository contains a series of C++ programs developed as part of a Programming 622 assignment at Richfield College. The programs are designed to address real-world management needs for an academic library, course scheduling, and student club memberships. Each section demonstrates advanced object-oriented programming principles and makes use of efficient C++ Standard Library (STL) features.

Table of Contents
Project Overview
Technologies Used
Solutions Overview
Library Catalog System
Course Scheduling System
Student Club Management - ClubHub
Setup and Installation
Acknowledgments
Project Overview
The assignment required the design and implementation of three systems to address common needs within an academic environment:

A Library Catalog System for efficient resource management.
A Course Scheduling System to handle room assignments and course registrations.
A Student Club Management System (ClubHub) to organize and track student memberships.
Each program is a standalone solution that demonstrates best practices in object-oriented design, data structure optimization, and modular programming.

Technologies Used
Language: C++ (with OOP principles)
Standard Library: C++ STL (Vectors, Queues, Algorithms)
Data Structures: Adjacency list for graphs, Priority Queue, File I/O
Solutions Overview
Library Catalog System
The Library Catalog System provides a streamlined way to manage academic resources, such as books, journals, and digital resources.

Features:
Resource Class Design: Uses inheritance to create a flexible Resource class that supports different resource types (books, journals, digital media).
Catalog Management: A Catalog class uses STL containers to store and manage resources efficiently.
Core Functionalities:
Add new resources to the system.
Remove outdated or damaged resources.
Search resources by title, author, ISBN, or type.
Generate categorized reports by resource type.
Course Scheduling System
The Course Scheduling System is designed to optimize room allocations, manage course enrollments, and generate student schedules.

Features:
Core Classes:
Course class stores information on course code, required room type, capacity, and schedules.
Student class includes attributes like ID, major, enrolled courses, and academic year.
Room class manages room details including type, capacity, and special equipment.
Priority Queue for Registrations: A priority queue sorts registrations based on student year, course relevance, and request timing.
Scheduling Optimization:
Processes course registration requests.
Assigns appropriate rooms based on course needs.
Balances class sizes and resolves scheduling conflicts.
Generates optimized individual schedules for students.
Student Club Management - ClubHub
ClubHub is a student club management system that organizes memberships and fosters connections between students.

Features:
Graph-Based Structure: Utilizes a graph with an adjacency list to represent students as nodes and shared club memberships as edges.
Core Functionalities:
Add new students and clubs to the system.
Manage club memberships, including automatic creation of connections based on shared memberships.
Search for all clubs a student belongs to or all students in a specific club.
Alphabetically sort students by last name using a basic sorting algorithm.
Save and load system data to/from a text file for persistent storage.
