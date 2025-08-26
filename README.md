# ESP32 IoT Control System
## Project Overview
This project aims to build a versatile, industrial-grade IoT Network Server device using the ESP32 platform. The system is designed for modularity, scalability, and maintainability, with a modern embedded architecture suitable for an IoT Web Service for controlling and monitoring devices on its network.
### Hardware Platform
**MCU:**
- ESP32 C3 supermini
**Displays:**
- 128 x 64 [address 0x3C]
- 128 x 64 [address 0x3D]
**Inputs:**
- 4 x Push Buttons (B1 [pin 10], B2 [pin 20], B3 [pin 21], B2 [pin 0])
- 6 x Dip Switches (Pins 1 - 6)
**Sensors:**
- BMS280 Temperature, Humidity, Pressure Sensor (address 0x76)
**Connectivity:**
- WiFi (AP)
- i2c (SDA [pin 8], SCL [pin 9])
**Outputs:**
- WS2812 RGB LED STRIP (pin 7)
## Key Objectives
- **Architecture:** Clean separation of concerns (HAL, services, applications)
- **Memory Management:** Custom allocators, object pools, stack optimization
- **Performance:** Multi-core utilization, efficient task scheduling, profiling
- **Maintainability:** Dependency injection, testing, logging
- **Scalability:** Plugin architecture, modular design, configuration management
- **Quality:** Static analysis, automated testing, performance monitoring
- **User Experience:** Responsive UI, smooth animations, consistent theming
- **Development:** Modern build tools, CI/CD, documentation
---
## Development Phases
### Phase 1: Project Foundation & Architecture
- **Modern Project Structure:** Organize code into clear modules (HAL, services, apps)
- **Hardware Abstraction Layer (HAL):** Abstract hardware access for portability and testability
### Phase 2: Core System Implementation
- **Real-Time Task Scheduler:** Efficient multi-core task management
- **Memory Management:** Custom allocators, resource pools
- **Hardware Abstraction Interfaces:** Standardized interfaces for all hardware components
### Phase 3: UI Framework Implementation
- **Modern UI Framework:** Retained mode rendering, widget system
- **Immediate Mode Elements:** For dynamic UI components
- **Screen Management:** State persistence across screens
- **Optimized Drawing:** Dirty rectangle tracking, double buffering, and event batching for high performance
- **Async UI Updates:** Non-blocking UI refresh and input handling
### Phase 4: Application Architecture
- **Application Base Class:** Common lifecycle and event handling
- **Smart Clock App:** Timekeeping, alarms, scheduling
- **Timer App:** State machine for countdowns and intervals
### Phase 5: Service Layer & Data Management
- **Service Architecture:** Dependency injection for modular services
- **Data Service:** Persistent storage for settings and logs
- **Network Service:** Modern patterns for WiFi and IoT communication
### Phase 6: Advanced Features & Optimization
- **Performance Monitoring:** Profiling, resource usage tracking
- **Power Management:** Sleep modes, dynamic frequency scaling
- **OTA Updates:** Secure firmware updates over WiFi
### Phase 7: Testing & Quality Assurance
- **Unit Testing Framework:** Automated tests for all modules
- **Hardware-in-the-Loop Testing:** Real hardware validation
### Phase 8: Deployment & Maintenance
- **Configuration Management:** Centralized settings, versioning
- **Logging & Diagnostics:** Error tracking, system health monitoring
---
## Architecture Overview
### 1. Hardware Abstraction Layer (HAL)
- Encapsulates all hardware-specific code
- Provides interfaces for sensors, displays, inputs, outputs
- Enables portability and easier testing
### 2. Service Layer
- Manages data, network, and system services
- Uses dependency injection for flexibility
- Handles persistence, communication, and background tasks
### 3. Application Layer
- Contains user-facing applications (clock, timer, etc.)
- Built on a common base class for lifecycle management
- Interacts with services and HAL
### 4. UI Framework
- Retained mode for static screens
- Immediate mode for dynamic widgets
- Screen manager for navigation and state
---
## Documentation
Detailed documentation for the project is available in the `/docs` directory:
- [UI Framework Guide](docs/UI_Framework_Guide.md): Comprehensive guide to the UI system architecture
- [UI Framework Example](docs/UI_Framework_Example.md): Code examples demonstrating UI component usage
---
## Configuration & Build Workflow
### Project Structure
- `/src/hal/` - Hardware abstraction modules
- `/src/services/` - Data, network, and system services
- `/src/apps/` - Application modules
- `/src/ui/` - UI framework and widgets
- `/config/` - Configuration files
- `/tests/` - Unit and hardware-in-the-loop tests
### Build Tools
- PlatformIO or Arduino IDE for building and flashing
- CI/CD pipeline for automated builds and tests
### Memory Optimization
- Use custom allocators and object pools
- Profile stack and heap usage
- Optimize for low-latency and low-power operation
### Quality Assurance
- Static analysis tools (e.g., cppcheck)
- Automated unit and integration tests
- Performance monitoring and logging
---
## Getting Started
1. **Set up development environment:** Install PlatformIO or Arduino IDE, Clone the project repository
2. **Configure hardware:** Connect peripherals as per pin mapping, Update `/config/hardware.h` for custom setups
3. **Build and flash firmware:** Use provided build scripts or IDE
4. **Run tests:** Execute unit and hardware-in-the-loop tests
5. **Monitor and maintain:** Use logging and diagnostics tools, Update firmware via OTA as needed
---
## References
- [ESP32 LIVE MINI KIT Documentation](https://doc.riot-os.org/group__boards__esp32__mh-et-live-minikit.html)
- [PlatformIO](https://platformio.org/)
- [Arduino IDE](https://www.arduino.cc/en/software)
---
## Notes
- The project is designed for extensibility; new applications and services can be added as plugins.
- All hardware interfaces are abstracted for easy replacement or upgrade.
- Documentation and code comments are provided for maintainability.
---
## License
MIT License
