# Pipe Lab Experiments

This repository contains C programs demonstrating inter-process communication (IPC) using pipes:
- Half Duplex communication
- Full Duplex communication
- Non-blocking send & blocking receive
- Order preserving (FIFO)
- Bounded and unbounded buffer behavior
- Data persistence characteristics

All programs were tested on Kali Linux using GCC.
 ## 📂 Programs Included

| File Name | Description |
 `half_duplex_pipe.c` | Basic half-duplex communication between parent and child using a single pipe. |
 `full_duplex_pipe.c` | Implementation of full-duplex communication using two half-duplex pipes. |
 `non_blocking_send.c` | Demonstrates non-blocking send and blocking receive behavior using pipes. |
 `fifo_order_preserving_pipe.c` | Verifies the FIFO (First In, First Out) nature of pipe communication. |
 `data_persistence_after_read.c` | Tests whether data remains in the pipe after it has been read (shows that it doesn’t). |

