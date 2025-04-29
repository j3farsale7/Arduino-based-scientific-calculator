# Arduino Scientific Calculator with Memory Functions 🧮

A scientific calculator built on the **Arduino Uno** platform using a **6x6 keypad**, a **16x2 LCD**, and custom input parsing logic.

Created by **Jaafar Saleh** as an educational electronics and embedded C++ learning project.  
Integrated using Proteus simulation and tested with real hardware.

---

## 🧠 Features

- ✅ Basic arithmetic: `+`, `-`, `*`, `/`, `^`  
- ✅ Trigonometric functions: `sin`, `cos`, `tan`, and their inverse/hyperbolic variants
- ✅ Logarithmic functions: `log`, `ln`, `e^x`
- ✅ Special math operations: `sqrt(x)`, `x!` (factorial)
- ✅ Memory support:
  - Press `'i'` then `'m'` or `'M'` to save value to `M1` or `M2`
  - Press `'m'` or `'M'` alone to recall saved values
- ✅ Shift (`S`) and Alpha (`A`) modes for secondary functions
- ❌ No commercial use unless explicitly permitted

---

## 🔧 Hardware Used

| Component      | Quantity | Notes |
|----------------|---------|-------|
| Arduino Uno    | 1       | Core device |
| 6x6 Keypad     | 1       | Custom layout |
| 16x2 LCD       | 1       | Display output |
| Jumper Wires   | Many    | For wiring |
| Resistors/Breadboard | As needed | Optional depending on setup |

> Simulation was originally done in **Proteus** and later implemented on physical hardware.

---

## 🛠 Library Credits

This project uses:
- [Keypad.h] by Mark Stanley and Alexander Brevig
- [LiquidCrystal.h] (https://www.arduino.cc/en/Reference/LiquidCrystal) by Arduino
- [math.h](https://en.cppreference.com/w/c/numeric/math) standard C++ library

---

## 📄 License

This project is **licensed under CC BY-NC 4.0**  
👉 [View License](https://creativecommons.org/licenses/by-nc/4.0/)

You may:
- ✅ Use, study, modify, and share this code
- ✅ Simulate it in Proteus or on breadboard
- ✅ Add features and submit pull requests

You may not:
- ❌ Sell devices based on this code
- ❌ Monetize derivatives without my **explicit permission**

📩 If you want to use this commercially, contact me at:  [j3farsale7@outlook.com]
🔮 P.S. I know it's not worth commercial usage but still it's good to clarify these boundaries.
However, if it ever happened
We can discuss:
- 💰 Profit-sharing models
- 💼 Commercial licensing
- 🤝 Collaborative development

---

## 📁 Repository Structure
├── LICENSE
├── README.md
├── calculator.ino # Main Arduino sketch
├── docs/
│ └── Project.pdf # Original project report
└── diagrams/
└── proteus_schematic.dsn # Simulation schematic
