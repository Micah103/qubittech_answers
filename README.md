
---

# C++ Interview Implementation

This project consists of five C++ libraries and applications created as part of interview preparation. Each solution is implemented in C++ using **Microsoft Visual Studio Community 2022** as the primary IDE. The README provides setup instructions, dependencies, and implementation details for each question.

## Table of Contents
1. [Environment Setup](#environment-setup)
2. [Question 1: Message Fragmentation Library](#question-1-message-fragmentation-library)
3. [Question 2: SQL Builder Library](#question-2-sql-builder-library)
4. [Question 3: TCP Proxy Server](#question-3-tcp-proxy-server)
5. [Question 4: Header-only JSON Library](#question-4-header-only-json-library)
6. [Question 5: Log File Processor](#question-5-log-file-processor)

---

## Environment Setup

**IDE**: Microsoft Visual Studio Community 2022 (recommended)  
**Alternative IDE**: Visual Studio Code (with C++ and CMake extensions)

### Visual Studio Workloads
For the best experience, ensure you have the following workloads installed in Visual Studio:
1. **Desktop Development with C++**
2. **Game Development with C++**
3. **Data Storage and Processing**
4. **Linux and Embedded Development with C++**

These workloads include the necessary libraries, compilers, and tools for handling networking, JSON parsing, SQLite integration, and other project requirements.

### Project Setup
1. Clone the repository from GitHub.
2. Open the `.sln` solution file in Visual Studio.
3. Check that all dependencies are configured, and build each project individually.

For Visual Studio Code, ensure that the **C++** extensions, **CMake**, and **SQLite** dependencies are installed and configured.

---

## Question 1: Message Fragmentation Library

### Description
This library provides functionality to:
- Fragment long messages into smaller, manageable chunks.
- Reassemble fragmented chunks even if they arrive out of order.
- Utilize callbacks to detect and handle missing chunks.
- Report corrupted data if not received within a specified timeout.

### Implementation Notes
1. **Classes**: `Fragmenter` and `MessageAssembler`.
2. **Testing**: A set of tests is included to validate fragmentation, reassembly, and error handling.
3. **Multithreading**: Used to handle asynchronous message reception and reassembly.

### Dependencies
- **Standard C++ Libraries**: No external libraries are required.

---

## Question 2: SQL Builder Library

### Description
The SQL Builder Library enables easy creation and management of SQL queries through:
- A **SQL Builder Module** for query construction.
- **Chain method syntax** to simplify complex query building.
- A lightweight **ORM (Object-Relational Mapping)** for seamless mapping between database rows and C++ objects.

### Implementation Notes
1. **SQLite Integration**: For testing purposes, SQLite is included(In the `logdata` sqlite file).
2. **File Structure**: The SQLite include directory is referenced relatively for portability.
3. **Classes**: Core classes include `SQLBuilder`, `Query`, and the ORM implementation.

### Dependencies
- **SQLite**: Ensure SQLite is available in the project path. Adjust `Additional Include Directories` if necessary.
- **C++ Standard Library**.

---

## Question 3: TCP Proxy Server

### Description
A multithreaded TCP Proxy Server capable of:
- Handling 1000 simultaneous connections.
- Distributing connections across a 5-thread pool.
- Logging incoming requests and outgoing responses to a file and console.

### Implementation Notes
1. **Thread Pool**: A custom thread pool is implemented to manage connection handling.
2. **Logger**: Logs are written to `server_log.txt` and also printed to the console.
3. **Testing**: Can be tested with utilities like **Postman** or a custom script but make sure to allow Network permissions.
4. **Bench Test**: The 1000 Connections bench test was conducted using the connections_1000.py script.

### Dependencies
- **Windows Sockets (Winsock)**: Required for TCP socket programming on Windows.
- **C++ Standard Library**: for threading and file handling.

---

## Question 4: Header-only JSON Library

### Description
A minimalistic header-only JSON library that can:
- Parse JSON strings into C++ objects (arrays, objects, values).
- Manipulate JSON objects by indexing and updating values.
- Create JSON strings from C++ objects.

### Implementation Notes
1. **Single-header Library**: Entire functionality is provided in a single header file (`json.hpp`).
2. **Parser**: Implements parsing for basic JSON types and structures.
3. **Testing**: Various tests are included to verify JSON parsing and generation.

### Dependencies
- **Standard C++ Libraries**: This library is standalone and does not rely on external libraries.

---

## Question 5: Log File Processor

### Description
This utility reads large log files, processes each line, and stores results in a database. It includes:
- Multithreading for efficient processing of large files.
- Database storage to retain processed log data.
  
### Implementation Notes
1. **Multithreading**: Optimizes performance for large file handling.
2. **Database Storage**: SQLite integration for storing processed data(In the `logdata` sqlite file).
3. **File Handling**: Reads and processes lines sequentially but uses threads for database insertions.
4. **Logger**: Logs are written to `logfile.txt`.

### Dependencies
- **SQLite**: Used as the database for storing log data.
- **C++ Standard Library**.

---

## Important Notes
For all solutions, ensure that:
1. **SQLite** is configured properly if required, especially for the SQL Builder Library and Log File Processor.
2. **Thread Pool Library** is set up and compatible with your environment for projects requiring threading.

**Comments** are provided within each source file for detailed understanding of individual modules and functions.

---
