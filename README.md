# Pipe Lab Experiments

This repository contains C programs demonstrating inter-process communication (IPC) using pipes:
- Half Duplex communication
- Full Duplex communication
- Non-blocking send & blocking receive
- Order preserving (FIFO)
- Bounded and unbounded buffer behavior
- Data persistence characteristics

---

## 🧪 Verification and Observations

This section describes how each pipe-based IPC experiment was tested and verified practically on **Linux (Kali)** using tools like `ps`, `lsof`, and observation of program output.

| **Program File** | **Concept Demonstrated** | **Verification / Observation Method** |
|------------------|--------------------------|--------------------------------------|
| **`half_duplex_pipe.c`** | One-way (half-duplex) communication | Run the program and enter a number limit. Observe that the parent writes a sequence of numbers, while the child reads and prints only the odd numbers. Use `ps` to confirm both processes are running simultaneously. |
| **`full_duplex_pipe.c`** | Two-way (full-duplex) communication using two pipes | Observe that both parent and child exchange data. Each process both writes and reads — demonstrating bidirectional data transfer. |
| **`fifo_order_preserving_pipe.c`** | Order preserving (FIFO) behavior | Input a sequence of numbers (e.g., 1–6). Confirm that the child receives them in the **same order** they were written. This verifies that pipes preserve FIFO order. |
| **`non_blocking_send.c`** | Non-blocking send and blocking receive | The parent uses `fcntl(p[1], F_SETFL, O_NONBLOCK)` to make the write end non-blocking. When the pipe buffer is full, it prints “Pipe full! Retrying...”, while the child continues reading normally — showing blocking receive and non-blocking send. |
| **`blocking_send_nonblocking_receive.c`** | Blocking send and non-blocking receive | The child uses `fcntl(p[0], F_SETFL, O_NONBLOCK)` on the read end. When no data is available, it prints “No data available, waiting...”, while the parent continues writing — showing non-blocking read and blocking write behavior. |
| **`bounded_unbounded_buffer.c`** | Pipe buffer capacity (bounded vs unbounded) | Reduce the write/read buffer size and observe if the parent’s `write()` blocks once the pipe is full. The pipe acts as a **bounded buffer** — it pauses writing until the child reads data. |
| **`data_persistence_after_read.c`** | Data persistence after reading | The child performs **two consecutive reads**. During the first read, data is received normally. The second read prints nothing, proving that pipe data is **not preserved** once read. |
| **`data_persistence_after_lifetime.c`** | Pipe lifetime after process termination | The program prints parent and child **PIDs** using `getpid()`. While the program runs, execute the command below in another terminal:  |
| | | ```bash<br>lsof -p <PID><br>``` |
| | | The output will show a pipe entry under the “TYPE” column. After both processes terminate, running `lsof` again shows no pipe entry — proving that pipes are destroyed after process termination. |

---

## 🧠 Key Conclusions

- Pipes operate in **FIFO (First In, First Out)** order — they are **order-preserving**.
- Pipes are **bounded buffers**; writing blocks when full.
- **Data is not persistent** after it has been read from the pipe.
- **Pipes do not persist** after both communicating processes terminate.
- They support **local IPC only** — cannot be used between different machines.
- Non-blocking and blocking behaviors can be controlled using the **`fcntl()`** system call.

---

## ⚙️ Practical Commands Used

| Purpose | Command |
|----------|----------|
| Check process IDs | `ps -ef` |
| Check open file descriptors for a process | `lsof -p <PID>` |
| Compile program | `gcc filename.c -o output` |
| Run program | `./output` |

---

> 🧾 *All experiments were conducted on Kali Linux using the GCC compiler, with parent–child synchronization achieved through `wait(NULL)`.*


