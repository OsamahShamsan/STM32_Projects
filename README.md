# STM32 BIOS-Style Menu System  
## User Manual — Command Reference

---

### 1. Overview

This system provides a BIOS-style UART-driven text menu for controlling peripherals and retrieving system information.

- **Interface**: UART (e.g., 115200 baud, 8N1)
- **Terminal**: Any VT100-compatible serial terminal (e.g., PuTTY, TeraTerm)
- **Input**: Single-character commands
- **Case Sensitivity**: Input is **case-sensitive**
- **System**: Nucleo-G431RB running STM32Cube HAL-based firmware

---

### 2. Main Menu

| Key | Description            | Action                                      |
|-----|------------------------|---------------------------------------------|
| `1` | LED Control Submenu    | Enters submenu to control onboard LED       |
| `2` | System Info Submenu    | Shows board and firmware information        |
| `Q` | Quit                   | Exits the menu system (loops halted)        |

---

### 3. LED Control Submenu

| Key | Description     | Action                  |
|-----|-----------------|-------------------------|
| `1` | Toggle LED      | Toggles onboard LED     |
| `B` | Back            | Returns to Main Menu    |

---

### 4. System Info Submenu

| Key | Description          | Action                             |
|-----|----------------------|------------------------------------|
| `1` | Board Info           | Displays board model and part ID   |
| `2` | Firmware Version     | Displays firmware version string   |
| `B` | Back                 | Returns to Main Menu               |

---

### 5. Behavior Notes

- Menus use **VT100 terminal escape codes** to render clean screens.
- After executing a command, the system prompts:  
  `"Press any key to continue..."`  
  This lets users review output before the screen refreshes.
- **Only exact, case-matching keys are accepted**.  
  Pressing `b` (lowercase) where `B` is expected results in `"Invalid option."`

---

### 6. Example Session
========================
BIOS Style Menu v1.0
========================
1. LED Control
2. System Info
Q. Quit
Select option: 1

=== LED Control Menu ===
1. Toggle LED
B. Back
Select option: 1

[LED] Toggled

Press any key to continue...

---

### 7. Version History

| Version | Date       | Notes                |
|---------|------------|----------------------|
| 1.0     | 2025-05-13 | Initial documentation|

---

### 8. Maintainer Notes

- Add new menu options by modifying `MenuItem[]` tables.
- Ensure new commands follow single-character input logic.
- Rebuild firmware after any menu structure change.

---
