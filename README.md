# Design Patterns — Practical Examples in C++

An educational repository for learning classic design patterns by **building small, practical projects** instead of only reading about them.

Each pattern has three projects of increasing difficulty: **Easy**, **Medium** and **Hard**. Easy covers the core structure of the pattern. Medium adds real-world complications. Hard pushes into the edge cases and modern C++ techniques you need to use the pattern in production code.

> This is a learning repo. The code favours clarity over cleverness, and each solution is reviewed for correctness against the "Focus" points listed in the checklist.

---

## Patterns covered

24 patterns in three categories, with 72 projects in total.

### Behavioral: how objects communicate

| Pattern | What it solves |
|---|---|
| **Chain of Responsibility** | Passes a request along a chain of handlers until one of them handles it. |
| **Command** | Turns a request into an object, enabling undo/redo, queuing and logging. |
| **Iterator** | Traverses a collection without exposing its internal representation. |
| **Mediator** | Centralizes communication between objects so they don't refer to each other directly. |
| **Memento** | Captures and restores an object's state without breaking encapsulation. |
| **Observer** | Lets many objects react to changes in one object without the object knowing who is listening. |
| **State** | Lets an object change its behaviour when its internal state changes, without a giant `switch`. |
| **Strategy** | Makes algorithms interchangeable behind a common interface, selectable at runtime. |
| **Template Method** | Defines an algorithm's skeleton in a base class and lets subclasses fill in specific steps. |
| **Visitor** | Adds new operations to a class hierarchy without modifying the classes. |

### Creational: how objects are created

| Pattern | What it solves |
|---|---|
| **Abstract Factory** | Creates *families* of related objects that must be used together, without naming their concrete classes. |
| **Builder** | Constructs a complex object step by step, separating construction from the final representation. |
| **Factory Method** | Lets subclasses decide which concrete object to create, so client code depends only on interfaces. |
| **Lazy Initialization** | Delays creating an expensive object until it is actually needed. |
| **Object Pool** | Reuses expensive objects (connections, buffers, bullets) instead of creating and destroying them repeatedly. |
| **Prototype** | Creates new objects by cloning existing ones, without depending on their concrete classes. |
| **Singleton** | Guarantees exactly one instance of a class with a global access point (and teaches why to use it sparingly). |

### Structural: how objects are composed

| Pattern | What it solves |
|---|---|
| **Adapter** | Makes an existing class with an incompatible interface work with the interface your code expects. |
| **Bridge** | Splits an abstraction from its implementation so both can vary independently. |
| **Composite** | Treats individual objects and trees of objects uniformly (part-whole hierarchies). |
| **Decorator** | Adds behaviour to an object dynamically by wrapping it, without subclassing. |
| **Facade** | Provides one simple interface to a complex subsystem. |
| **Flyweight** | Shares common state between many objects to save memory. |
| **Proxy** | Stands in for another object to control access, add caching or lazy loading, or manage lifetime. |

---

## Progress

**4 / 72 projects completed.** Full project descriptions and what each one focuses on are in **[CHECKLIST.md](CHECKLIST.md)**.

### Behavioral

| Pattern | Easy | Medium | Hard |
|---|---|---|---|
| Chain of Responsibility | ⬜ Ticket Escalation | ⬜ HTTP Middleware | ⬜ GUI Event Bubbling |
| Command | ⬜ Smart Home Remote | ⬜ Undo/Redo Text Editor | ⬜ Persistent Job Queue |
| Iterator | ⬜ Playlist Iterator | ⬜ Binary Tree Traversals | ⬜ Lazy Range Adapters |
| Mediator | ⬜ Chat Room | ⬜ Registration Dialog | ⬜ Air Traffic Control |
| Memento | ⬜ Text Editor Snapshots | ⬜ Game Save System | ⬜ Incremental Snapshots |
| Observer | ✅ Weather Station | ⬜ Stock Market Ticker | ⬜ Type-Safe Event Bus |
| State | ✅ Traffic Light | ⬜ Vending Machine | ⬜ TCP Connection |
| Strategy | ⬜ Route Planner | ⬜ Discount Pricing Engine | ⬜ Cache Eviction Policies |
| Template Method | ⬜ Hot Beverages | ⬜ Report Generator (NVI) | ⬜ Mini Unit-Test Framework |
| Visitor | ⬜ Shape Calculations | ⬜ Document Exporter | ⬜ AST: Visitor vs. `std::variant` |

### Creational

| Pattern | Easy | Medium | Hard |
|---|---|---|---|
| Abstract Factory | ⬜ Cross-Platform GUI Widgets | ⬜ Database Access Layer | ⬜ Themed Game World Generator |
| Builder | ⬜ Pizza Builder | ⬜ HTTP Request Builder | ⬜ Compile-Time Checked SQL Builder |
| Factory Method | ✅ Shape Creator | ⬜ Notification Sender | ⬜ Self-Registering Factory |
| Lazy Initialization | ⬜ Lazy Image Gallery | ⬜ Generic `Lazy<T>` | ⬜ Lazy Service Container |
| Object Pool | ⬜ Bullet Pool | ⬜ Connection Pool with RAII | ⬜ Generic Thread-Safe Pool |
| Prototype | ⬜ Shape Cloning | ⬜ Enemy Spawner Registry | ⬜ Drawing Editor Copy/Paste |
| Singleton | ✅ Application Logger | ⬜ Configuration Manager | ⬜ Generic Singleton Template |

### Structural

| Pattern | Easy | Medium | Hard |
|---|---|---|---|
| Adapter | ⬜ Temperature Sensor | ⬜ Payment Gateway | ⬜ Legacy C Library |
| Bridge | ⬜ Shapes × Renderers | ⬜ Remotes × Devices | ⬜ Logging Library with Sinks |
| Composite | ⬜ File System Tree | ⬜ Organization Chart | ⬜ Expression Tree Calculator |
| Decorator | ⬜ Coffee Shop | ⬜ Data Stream Pipeline | ⬜ Middleware: Dynamic vs. Static |
| Facade | ⬜ Home Theater | ⬜ Video Conversion | ⬜ Tiny Compiler |
| Flyweight | ⬜ Forest Rendering | ⬜ Text Editor Styles | ⬜ String Interning |
| Proxy | ⬜ Protected Bank Account | ⬜ Caching Proxy | ⬜ Your Own Smart Pointers |

---

## Repository structure

Patterns are grouped by their GoF category. Each project lives in its own folder:

```
<Category>/<Pattern>/<Level>/
```

```
.
├── Behavioral/
│   ├── Observer/
│   │   ├── Easy/          # Weather Station
│   │   │   ├── Subject.hpp / Subject.cpp
│   │   │   ├── Observer.hpp / Observer.cpp
│   │   │   └── main.cpp
│   │   ├── Medium/
│   │   │   └── ...
│   │   └── Hard/
│   │       └── ...
│   └── ...                # other Behavioral patterns
├── Creational/
│   ├── Singleton/
│   │   ├── Easy/          # Application Logger
│   │   │   ├── Singleton.hpp / Singleton.cpp
│   │   │   └── main.cpp
│   │   ├── Medium/
│   │   │   └── ...
│   │   └── Hard/
│   │       └── ...
│   └── ...                # other Creational patterns
├── Structural/
│   ├── <Pattern>/
│   │   ├── Easy/
│   │   │   └── ...
│   │   ├── Medium/
│   │   │   └── ...
│   │   └── Hard/
│   │       └── ...
│   └── ...                # other Structural patterns
├── CHECKLIST.md           # All 72 projects, levels and focus points
└── README.md
```

---

## Building and running

Every project is self-contained, with no external dependencies. You only need a C++17 compiler (a few Hard projects have optional C++20 bonuses).

```bash
cd Behavioral/Observer/Easy
g++ -std=c++17 -Wall -Wextra *.cpp -o weather_station
./weather_station
```

With MSVC (Developer Command Prompt):

```bat
cd Behavioral\Observer\Easy
cl /std:c++17 /W4 /EHsc *.cpp /Fe:weather_station.exe
weather_station.exe
```

---

## Completed examples

### Observer: Weather Station (Easy)

`Behavioral/Observer/Easy/`

A `WeatherStation` (the subject) publishes temperature, humidity and pressure readings. Three independent displays (the observers) react to each update:

- **CurrentConditionsDisplay** shows the latest readings.
- **StatisticsDisplay** tracks the min, max and average temperature.
- **ForecastDisplay** compares pressure with the previous reading and predicts rising, dropping or stable weather.

Key ideas demonstrated:

- A generic `ISubject` interface (`attach` / `detach` / `notify`) that knows nothing about concrete observers.
- The **push model**: the subject sends a `const WeatherData&` snapshot to every observer.
- Subscribing and unsubscribing at runtime, shown in `main.cpp` by detaching and re-attaching the forecast display.

Known limitations, which the Medium project addresses: observers are held as raw pointers, so destroying one without detaching it leaves a dangling pointer, and detaching from inside `update()` would invalidate the iteration.

### State: Traffic Light (Easy)

`Behavioral/State/Easy/`

A `TrafficLightContext` cycles through `Red → Green → Yellow → Red`. Each light is its own state class (`RedLightState`, `GreenLightState`, `YellowLightState`) that shows its colour, waits for its duration, and then chooses the next state itself.

Key ideas demonstrated:

- **Transitions owned by the states** (classic GoF style). Each state calls `ctx.updateState(...)` with its successor, so neither `main` nor the context contains any `if` / `switch` on the current state.
- **The context only delegates**: `next()` and `pressPedestrianButton()` forward to the current state.
- **State-dependent behaviour for the same action.** Pressing the pedestrian button shortens Green (once per cycle), while Red and Yellow ignore it.
- **Safe ownership with `std::unique_ptr`.** The state is replaced as the last step of `handle()`, so the old state object is never used after it is destroyed.

### Factory Method: Shape Creator (Easy)

`Creational/Factory/Easy/`

An abstract `ShapeCreator` declares the factory method `createShape()`, and the concrete creators `CircleCreator`, `TriangleCreator` and `SquareCreator` decide which `Shape` is created. Each shape draws itself as ASCII art.

Key ideas demonstrated:

- **The creator uses its own factory method.** `ShapeCreator::render()` calls `createShape()` and then `draw()` on the result, without knowing the concrete shape. This is what makes it Factory Method rather than a simple factory.
- **Subclasses decide what is created** by overriding the private `createShape()`, so the client never names `Circle`, `Triangle` or `Square`.
- **The client depends only on abstractions.** `run(const ShapeCreator&)` works with any creator.
- **Ownership is explicit**: products are returned as `std::unique_ptr<Shape>`, and both base classes have virtual destructors.

### Singleton: Application Logger (Easy)

`Creational/Singleton/Easy/`

A `Logger` with `info()`, `warning()` and `error()` and a configurable log level. Exactly one instance exists, and every part of the program reaches it through `Logger::getInstance()`.

Key ideas demonstrated:

- **Meyers singleton**: a function-local `static Logger instance` inside `getInstance()`, which is thread-safe to initialize since C++11.
- **No other way to create a logger**: the constructor is private, and the copy/move constructors and assignments are `= delete`.
- **Log level as a threshold**: the three public functions forward to one private `log(level, msg)`, which prints only messages at or above the current level. `setLevel()` changes it once for the whole program.
- `main.cpp` shows level filtering, that `getInstance()` always returns the same address, and that a level set in `main` also applies inside other functions.

---

## How this repo is used for learning

1. Pick the next unchecked project in [CHECKLIST.md](CHECKLIST.md).
2. Implement it in `<Category>/<Pattern>/<Level>/`.
3. Check its box and get the solution reviewed against the project's **Focus** points: correct pattern structure, object lifetimes, RAII and const-correctness.
4. Fix the issues found, then move on to the next level.

## References

- *Design Patterns: Elements of Reusable Object-Oriented Software* by Gamma, Helm, Johnson and Vlissides (the "Gang of Four").
- *Head First Design Patterns* by Freeman and Robson. The Weather Station example is based on this book.
- [GeeksforGeeks — Software Design Patterns](https://www.geeksforgeeks.org/system-design/software-design-patterns/)
- [refactoring.guru/design-patterns](https://refactoring.guru/design-patterns)
