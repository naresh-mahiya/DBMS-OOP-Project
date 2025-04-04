# Database Management System

A C++ implementation of a simple database management system that supports basic database operations using OOPs principles.

## Features

- **Database Management**
  - Create and manage multiple databases
  - Save and load databases from files
  - Display database contents

- **Table Operations**
  - Create tables with custom fields
  - Add, update, and delete records
  - Display table contents
  - Query records based on criteria
  - Support for unique constraints on fields

- **Record Management**
  - Store records with multiple fields
  - Update individual fields
  - Display record contents

## Project Structure

- `main.cpp`: Contains the main implementation of the database system
- `data/`: Directory for storing database files
- `main.exe`: Compiled executable

## Classes

1. **Record**
   - Base class for storing individual records
   - Manages a collection of fields
   - Supports field updates and display

2. **Table**
   - Manages a collection of records
   - Supports unique constraints
   - Handles file I/O operations
   - Provides query functionality

3. **Database**
   - Manages multiple tables
   - Handles database-level operations
   - Supports saving and loading from files

4. **Databases**
   - Top-level class managing multiple databases
   - Provides database creation and management interface

## Usage

1. Compile the project using a C++ compiler
2. Run the executable
3. Follow the interactive menu to:
   - Create new databases
   - Manage existing databases
   - Create and modify tables
   - Add, update, or delete records
   - Query data based on criteria

## Requirements

- C++ compiler with support for C++11 or later
- Standard C++ libraries

## File Format

Data is stored in CSV format with:
- First line containing field names
- Subsequent lines containing record data
- Fields separated by commas

## Note

This is a simple database management system implementation for educational purposes, demonstrating object-oriented programming concepts and basic database operations.
