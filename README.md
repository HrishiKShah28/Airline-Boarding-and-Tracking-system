# ✈️ Airline Boarding and Tracking System  

This is a **C++ OOP project** that simulates a real-world **airline passenger boarding system**.  
It demonstrates concepts such as **inheritance (single, multilevel, and multiple)**, **polymorphism**, **constructors/destructors**, **virtual functions**, and **friend functions** — all implemented **without STL or databases**.  

Everything is done using **manual arrays** and **dynamic memory allocation** to manage passengers efficiently.  

---

## 🎯 Core Features  

### 🧍 Passenger Management  
- Stores passenger details like **name**, **passport number**, **seat number**, **status**, and **class type**.  
- Supports **Business**, **Economy**, **First Class**, and **Staff** passenger categories.  
- Maintains status updates — *Checked-in*, *Boarded (Business)*, *Boarded (Economy)*.  

---

### 🛫 Flight Management  
- Each **Flight** object stores flight details:  
  - Flight Number ✈️  
  - Source & Destination 🌍  
  - Gate Number 🛗  
- Manages passengers using **manual dynamic arrays (no STL)**.  
- Supports **auto-resizing** when passenger capacity is exceeded.  

---

### 💼 Business Class (Single Inheritance)  
- Derived from `Passenger` class.  
- Includes:  
  - Lounge Access ✔️  
  - Priority Boarding ✔️  
  - Higher Baggage Allowance (40 kg) ✔️  
- Base fare: **₹1500**  
- Overrides `boardFlight()` with **priority boarding** message.  
- Uses **friend function** `showBusinessDetails()` to display private data.  

---

### 🪑 Economy Class (Single Inheritance)  
- Derived from `Passenger` class.  
- Includes:  
  - Standard Baggage (20 kg)  
  - Optional Meal (default: No)  
- Base fare: **₹500**  
- Regular boarding after Business class passengers.  

---

### 👑 First Class Passenger (Multilevel Inheritance)  
- Derived from **BusinessPassenger → Passenger** (multilevel).  
- Adds a **private suite** feature.  
- Overrides `boardFlight()` for *ultra-priority boarding*.  
- Demonstrates **method overriding and reusability**.  

---

### 👷 Staff Passenger (Multiple Inheritance)  
- Inherits from both **EconomyPassenger** and **AirlineStaff**.  
- Represents **airline employees traveling on duty**.  
- Displays both **passenger** and **staff details** (via multiple inheritance).  
- Demonstrates **diamond ambiguity resolution** and **explicit constructor chaining**.  

---

## 🧠 Object-Oriented Concepts Demonstrated  

| Concept | Implementation Example |
|----------|------------------------|
| **Encapsulation** | Private data members (name, passport, status) |
| **Inheritance** | Business, Economy, FirstClass, Staff classes |
| **Multilevel Inheritance** | FirstClass → Business → Passenger |
| **Multiple Inheritance** | StaffPassenger → (EconomyPassenger, AirlineStaff) |
| **Polymorphism** | Virtual `boardFlight()` and `show()` functions |
| **Friend Function** | `showBusinessDetails()` accesses private data |
| **Constructors & Destructors** | Show lifecycle of objects dynamically |
| **Dynamic Memory Allocation** | Manual passenger array resizing in `Flight` class |

---

## 🧾 Boarding Flow Simulation  

1. Add passengers of any type (Business, Economy, First Class, or Staff).  
2. Start boarding sequence:  
   - **Business & First Class** board first (priority).  
   - **Economy & Staff** board next.  
3. View updated passenger statuses live.  

---

## 🖥️ Menu Options (Main Program)  

| Option | Description |
|---------|-------------|
| 1 | Add Business Class Passenger |
| 2 | Add Economy Class Passenger |
| 3 | Start Boarding |
| 4 | Show Passenger Status |
| 5 | Add Passenger (via Overloaded Function) |
| 6 | Add First Class Passenger (Multilevel Inheritance) |
| 7 | Add Staff Passenger (Multiple Inheritance) |
| 0 | Exit the Program |

---

## ⚙️ Technologies Used  
- **Language:** C++  
- **Concepts:** OOP (Encapsulation, Inheritance, Polymorphism, Friend Function)  
- **Memory:** Manual Dynamic Allocation (No STL containers)  
- **Input/Output:** Standard Console (No file handling, no database)
