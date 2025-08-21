# 🍝 Philosophers

**Philosophers** (a.k.a. *Dining Philosophers Problem*) is a project from the **1337 School curriculum**.  
It is a classic concurrency problem that explores the concepts of **multithreading, synchronization, and process management**.  

---

## 📖 Project Overview

The goal of the project is to implement a simulation of philosophers sitting at a table, eating, thinking, and sleeping.  
Philosophers must not starve and proper synchronization must be ensured to avoid **data races** and **deadlocks**.  

---

## 🚀 Mandatory Part

- Implemented using **threads** and **mutexes**.  
- Each philosopher is a thread.  
- Forks are represented by **mutexes**.  
- Actions:
  - **Eating**
  - **Sleeping**
  - **Thinking**
- Prevent race conditions with proper mutex handling.  
- Detect if a philosopher **dies** (doesn’t eat within `time_to_die`).  

### Program arguments


- `number_of_philosophers` → Number of philosophers and forks.  
- `time_to_die` (ms) → Time a philosopher can live without eating.  
- `time_to_eat` (ms) → Time taken to eat.  
- `time_to_sleep` (ms) → Time taken to sleep.  
- `number_of_times_each_philosopher_must_eat` (optional) → If all philosophers eat this many times, simulation ends.  

---

## 🌟 Bonus Part

- Implemented using **processes** and **semaphores**.  
- Each philosopher is a separate process.  
- Forks are controlled with semaphores.  
- Same rules as mandatory part, but with **different synchronization mechanisms**.  

---

## 🛠️ Requirements

- **C language** (C99 standard)  
- Use of:
  - `pthread` (mandatory)  
  - `semaphore.h` (bonus)  
- Strict Norm compliance.  
- **Makefile** with rules: `all`, `clean`, `fclean`, `re`.  

---

## ⚙️ Installation

Clone the repository:

```bash
git clone https://github.com/ylamkhan/philo.git
cd philosophers
make
