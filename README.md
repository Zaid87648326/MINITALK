Minitalk

A simple client/server communication project using UNIX signals (SIGUSR1 and SIGUSR2).

Description:

This project is part of the 42 School curriculum.
The server receives messages from the client bit by bit using signals.

SIGUSR1 → represents bit 1
SIGUSR2 → represents bit 0

The client converts each character of the message into binary and sends it to the server.

📂 Project Structure
.
├── client.c
├── server.c
├── minitalk.h
└── makefile
⚙️ Compilation

Compile the project using:

make

This will generate:

./server
./client


Usage:
1. Start the server
./server

Example output:

WELCOME TO MINITALK
PID : 12345
2. Send a message from the client
./client 12345 "Hello World"

Replace 12345 with the PID displayed by the server.

The server will print:

Hello World
🛠 Features
Communication using UNIX signals
Binary encoding of characters
Custom ft_atoi
PID validation
Simple signal handling
How It Works

Each character is converted into 8 bits.

Example for character A:

01000001

The client sends:

SIGUSR1 for 1
SIGUSR2 for 0

The server reconstructs the character bit by bit and prints it.

📋 Notes
The server must be running before sending a message.
Invalid PID input is handled by the client.
A small usleep() delay is used to avoid signal loss.
👤 Author

msabri — student at 42 School
