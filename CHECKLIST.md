# Design Patterns — Practical Projects Checklist

Check a box (`- [x]`) when you finish a project and ask for a review.
Each project lives in `<Category>/<Pattern>/<Level>/` (e.g. `Behavioral/Observer/Easy/`).

---

## Behavioral

### Observer

- [x] **Weather Station** / Easy
  A `WeatherStation` subject holds temperature, humidity and pressure. Create three observers — `CurrentConditionsDisplay`, `StatisticsDisplay` (min/avg/max), and `ForecastDisplay` (rising/falling pressure). Observers can subscribe and unsubscribe at runtime; every `setMeasurements()` call notifies all current subscribers.
  *Focus:* the basic `attach / detach / notify` contract, a clean `IObserver` / `ISubject` interface.

- [ ] **Stock Market Ticker with Filtered Subscriptions** / Medium
  A `StockExchange` publishes price updates for many symbols (`AAPL`, `GOOG`, ...). Observers subscribe to *specific* symbols only, and some observers only want to be notified when the price changes by more than X%. Implement a `Trader` that buys/sells on thresholds and a `PriceLogger` that writes every update.
  *Focus:* topic-based subscriptions, push vs. pull model, safely unsubscribing **during** a notification (don't break iteration), using `std::weak_ptr` so a destroyed observer doesn't leave a dangling pointer.

- [ ] **Generic Type-Safe Event Bus** / Hard
  Build a reusable `EventBus` where any type can be an event (`struct PlayerDied {...}`, `struct ScoreChanged {...}`). `subscribe<T>(callback)` returns a RAII `Subscription` handle that auto-unsubscribes when destroyed. Support priorities (higher priority handlers run first) and handlers that subscribe/unsubscribe other handlers while an event is being dispatched. Bonus: thread-safe publishing.
  *Focus:* templates + type erasure (`std::type_index`, `std::function`), RAII lifetime management, re-entrancy, thread safety.

### State

- [ ] **Traffic Light** / Easy
  A `TrafficLight` cycles `Red → Green → Yellow → Red` on each `next()` call, and each state prints its own behaviour and duration. Add a `PedestrianButton` press that shortens the Green state.
  *Focus:* one class per state, the context delegating to the current state, states triggering transitions.

- [ ] **Vending Machine** / Medium
  States: `Idle`, `HasMoney`, `Dispensing`, `OutOfStock`, `Maintenance`. Actions: `insertCoin(amount)`, `selectProduct(id)`, `refund()`, `restock()`, `enterMaintenance()`. Every action must do something sensible in every state (e.g. inserting coins while `OutOfStock` returns them). Track inventory and change.
  *Focus:* handling *all* actions in *all* states, who owns the transitions, avoiding a giant `switch`, state objects with shared data in the context.

- [ ] **TCP Connection State Machine** / Hard
  Model a TCP connection: `Closed`, `Listen`, `SynSent`, `SynReceived`, `Established`, `FinWait`, `CloseWait`, `TimeWait`. Events: `open`, `close`, `send`, `receive(packet)`, `timeout`. Invalid events in a state must be reported, not crash. Keep a **transition log** and support state `enter()` / `exit()` hooks. Bonus: hierarchical states (e.g. all "connected" sub-states share a common `close()` handling).
  *Focus:* many states and events, entry/exit actions, shared/flyweight state objects vs. per-context state objects, hierarchical state machines.

---

## Creational

### Singleton

- [ ] **Application Logger** / Easy
  A `Logger` with `info()`, `warning()`, `error()` that writes to the console and has a configurable log level. Only one instance may exist; copying and moving must be impossible.
  *Focus:* Meyers singleton (`static` local), deleted copy/move constructors and assignment, private constructor.

- [ ] **Configuration Manager** / Medium
  A `ConfigManager` loads `key=value` pairs from a `config.ini` file once, and offers typed getters (`getInt`, `getString`, `getBool` with defaults). Must be thread-safe when accessed from multiple threads at startup. Then write a class that *depends* on the config and make it testable — show how you would inject a fake config in a test.
  *Focus:* thread-safe lazy init (`std::call_once` or static local), why singletons hurt testability and how to mitigate it (interface + accessor, dependency injection).

- [ ] **Generic Singleton Template + Dependent Singletons** / Hard
  Write a reusable `Singleton<T>` template (CRTP) that any class can inherit to become a singleton. Then create three singletons — `Logger`, `Config`, `DatabasePool` — where `DatabasePool` uses `Config` and `Logger` in its constructor and destructor. Solve the **static initialization/destruction order** problem (e.g. Logger destroyed before DatabasePool logs in its destructor). Bonus: a `DatabasePool` that holds N connections (a "multiton").
  *Focus:* CRTP, friend access to private constructors, initialization order fiasco, destruction order ("Phoenix singleton" or explicit lifetime control).

### Factory Method

- [ ] **Shape Creator** / Easy
  An abstract `ShapeCreator` with a factory method `createShape()` and a `render()` method that uses it. Concrete creators: `CircleCreator`, `SquareCreator`, `TriangleCreator`. The client code only works with `ShapeCreator` and `Shape` interfaces.
  *Focus:* the classic GoF structure — creator uses its own factory method; returning `std::unique_ptr<Shape>`.

- [ ] **Cross-Platform Notification Sender** / Medium
  A `NotificationService` base class with `send(message)` that calls the factory method `createNotifier()`. Concrete services: `EmailService`, `SmsService`, `PushService`, each with its own config (address, phone number, device token). Choose which service to use at runtime from user input or a config string.
  *Focus:* factory method that takes parameters, separating "which product" from "how it's used", picking the creator at runtime without `if/else` spreading throughout the code.

- [ ] **Plugin-Style Self-Registering Factory** / Hard
  Build a document editor that can open files by extension (`.txt`, `.md`, `.csv`, `.json`). Each `Document` type registers itself in a `DocumentFactory` registry **automatically** (static registration in its own `.cpp`) — adding a new format must not require editing the factory. Creators are stored as `std::function<std::unique_ptr<Document>(const std::string& path)>`. Handle unknown extensions gracefully.
  *Focus:* registry-based factories, self-registration and its pitfalls (static init order, linker stripping unused objects), Open/Closed principle.

---

## Structural

### Adapter

- [ ] **Temperature Sensor Adapter** / Easy
  Your app expects an `ITemperatureSensor` with `double getCelsius()`. You get a third-party `FahrenheitSensor` class with `float readF()` that you can't modify. Write an adapter so the app works with it unchanged.
  *Focus:* object adapter (composition), the target / adaptee / adapter roles.

- [ ] **Unified Payment Gateway** / Medium
  Your shop uses an `IPaymentProcessor` interface: `pay(amountInCents, currency)`, `refund(transactionId)`. Adapt three "third-party SDKs" with different APIs: `PayPalApi` (amounts in dollars as `double`, returns `bool`), `StripeClient` (takes a `ChargeRequest` struct, returns a result object, throws on error), `LegacyBankGateway` (uses error codes and C-style strings). Normalize errors into one exception type or result type.
  *Focus:* adapting different data formats and error-handling styles, object adapter vs. class adapter (implement one of them with private inheritance and compare).

- [ ] **Legacy C Library + Two-Way Adapter** / Hard
  Wrap a C-style API (write it yourself to simulate it): `lib_open()`, `lib_read(handle, buffer, size)`, `lib_close(handle)`, with error codes and manual memory. Expose it as a modern C++ interface (`std::unique_ptr` with custom deleter, `std::string`/`std::vector` returns, exceptions). Then build a **two-way adapter** so a new C++ `IStream` implementation can also be passed *back* into old code that expects the C function-pointer callback interface (`void* user_data` + callbacks).
  *Focus:* RAII wrappers for C resources, function pointers + `void*` context trampolines, two-way adapters, exception safety at the boundary (no exceptions escaping into C).
