# 42_minitalk

## Overview
`minitalk` is a small data exchange program developed as part of the 42 curriculum. This project focuses on implementing a client-server communication system using UNIX signals.

## Project Description
The minitalk project consists of a server and a client that communicate with each other using only UNIX signals (SIGUSR1 and SIGUSR2). The goal is to build a reliable communication protocol that allows the client to send messages to the server.

## Features
- Server that displays received messages
- Client that can send string messages to the server
- Communication using only UNIX signals
- Acknowledgment system for reliable data transmission
- Support for all characters (including special and non-ASCII characters)

## Technical Stack
- Language: C
- Communication: UNIX signals
- Build System: Makefile

## Usage
1. First, start the server:
```bash
./server
```
The server will display its PID (Process ID) upon startup.

2. Then, in another terminal, run the client with the server's PID and the message you want to send:
```bash
./client [server_pid] [message]
```

## Example
```bash
# Terminal 1
$ ./server
Server PID: 4242

# Terminal 2
$ ./client 4242 "Hello, minitalk!"

# Terminal 1 should display
Hello, minitalk!
```

## Project Structure
- `mandatory/`: Core implementation of the client and server
- `bonus/`: Enhanced version with additional features
- `libft/`: Custom C library used in the project
- `Makefile`: Build configuration

## Bonus Features
- Support for Unicode characters
- Acknowledgment of every message received
- Real-time communication (bit by bit, no waiting)
- Improved signal handling to prevent data loss

## Implementation Details
The project implements a communication protocol where:
- Each character is sent bit by bit
- SIGUSR1 represents binary 0
- SIGUSR2 represents binary 1
- The server reconstructs characters by receiving 8 signals in sequence

## License
This project is part of the 42 curriculum.
