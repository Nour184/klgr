# klgr

## ⚠️ Legal Disclaimer
**This project is created strictly for educational purposes and academic research.** K-klgr is a proof-of-concept tool designed to study the Linux input subsystem, character device mapping, and user-space hardware interactions. It is not intended for malicious use. The author assumes no liability and is not responsible for any misuse or damage caused by this program. By using this software, you agree to the terms of the MIT License.

## Technical Overview
K-klgr is a user-space keystroke monitor written in C for Linux environments. It operates by bypassing higher-level display servers (like X11 or Wayland) and directly reading raw hardware event streams from the kernel's input subsystem.

## Prerequisites
To compile and execute this research tool, your environment must meet the following requirements:
* A Linux-based operating system (Tested on Ubuntu)
* GNU Compiler Collection (`gcc`)
* Root (`sudo`) privileges (required to read from `/dev/input/`)

## Compilation and Execution
*(Note: These commands will be updated as the project structure evolves.)*

1. Clone the repository to your local machine.
2. Compile the C source code using `gcc`:
   ```bash
   gcc main.c -o K-klgr
