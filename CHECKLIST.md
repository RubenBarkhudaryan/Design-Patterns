# Design Patterns — Practical Projects Checklist

Check a box (`- [x]`) when you finish a project and ask for a review.
Each project lives in `<Category>/<Pattern>/<Level>/` (e.g. `Behavioral/Observer/Easy/`).

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

### Abstract Factory

- [ ] **Cross-Platform GUI Widgets** / Easy
  A `GUIFactory` interface creates `Button` and `Checkbox`. Concrete factories: `WindowsFactory` and `MacFactory`, each producing its own look (`render()` prints e.g. `[Windows Button]`). The `Application` receives a factory and builds its UI without knowing the platform.
  *Focus:* families of related products, the difference from Factory Method (one factory object creating *many* product types), client depends only on abstract interfaces.

- [ ] **Database Access Layer** / Medium
  A `DatabaseFactory` creates `Connection`, `Command` and `Transaction` objects. Implement simulated `MySqlFactory`, `PostgresFactory` and `SqliteFactory` (print the SQL dialect they would use). The factory is chosen at runtime from a config string. Make it impossible (or at least detected) to mix a `MySqlCommand` with a `PostgresConnection`.
  *Focus:* guaranteeing product compatibility within a family, choosing the concrete factory once at startup, ownership of created objects.

- [ ] **Themed Game World Generator** / Hard
  Themes `Medieval`, `SciFi`, `Horror` each produce `Enemy`, `Weapon`, `Terrain` and `Music`. The theme can be swapped mid-game. Then add a new product type (`Vehicle`) and note what you had to change. Finally, reduce the boilerplate with a **generic** abstract factory built from variadic templates (`AbstractFactory<Enemy, Weapon, Terrain, Music>` with `create<T>()`).
  *Focus:* the "adding a new product type is expensive" weakness of the pattern, variadic templates / type lists, keeping the API type-safe.

### Builder

- [ ] **Pizza Builder** / Easy
  A `PizzaBuilder` with a fluent interface: `PizzaBuilder().size(Large).crust(Thin).addTopping("cheese").addTopping("olives").build()`. `Pizza` itself has no public setters.
  *Focus:* fluent interface (returning `*this` by reference), separating construction from the final immutable object.

- [ ] **HTTP Request Builder with Validation** / Medium
  Build immutable `HttpRequest` objects (method, URL, headers, query params, body, timeout). `build()` validates the request (URL required, `GET` must not have a body, timeout > 0) and reports errors clearly. Add a `Director` with presets like `jsonPost(url, body)` and `authorizedGet(url, token)`.
  *Focus:* validation at `build()` time, error reporting (exceptions vs. result type), the role of a Director, keeping the product immutable.

- [ ] **Compile-Time Checked SQL Query Builder** / Hard
  A query builder where the **compiler** enforces the order of steps: `select(...)` → `from(...)` → optional `where(...)` → optional `orderBy(...)` → `build()`. Calling `build()` before `from()`, or `where()` twice, must not compile. Output a parameterized query (`WHERE age > ?`) plus its bound values.
  *Focus:* step builder / type-state pattern (each step returns a different type), templates, `&&`-qualified member functions and move semantics.

### Prototype

- [ ] **Shape Cloning** / Easy
  `Shape` has a virtual `clone()` returning `std::unique_ptr<Shape>`. Implement `Circle`, `Rectangle`, `Triangle`. Fill a "palette" with configured shapes and create copies from it without knowing their concrete types.
  *Focus:* virtual copy constructor idiom, why you can't just copy through a base-class pointer (slicing).

- [ ] **Enemy Spawner with Prototype Registry** / Medium
  A `PrototypeRegistry` maps names (`"goblin"`, `"orc_archer"`) to pre-configured `Enemy` prototypes. Each `Enemy` owns components (`std::unique_ptr<Weapon>`, `std::vector<std::unique_ptr<Ability>>`). Spawning clones a prototype; modifying a spawned enemy must never affect the prototype.
  *Focus:* deep copy vs. shallow copy, cloning objects that own other polymorphic objects, registry of prototypes.

- [ ] **Copy/Paste in a Drawing Editor** / Hard
  Clone whole object trees: groups that contain shapes and other groups, where children hold a raw `parent` pointer. Shared resources (`std::shared_ptr<Texture>`) must be **shared**, not duplicated. Parent pointers in the copy must point into the copy. Remove the repetitive `clone()` code with a CRTP helper (`Cloneable<Derived, Base>`).
  *Focus:* deep-cloning graphs with back-pointers, deciding what to share vs. copy, CRTP to remove boilerplate, covariant return types vs. smart pointers.

### Object Pool

- [ ] **Bullet Pool** / Easy
  A shooter fires bullets constantly. Instead of `new`/`delete` for every shot, use a `BulletPool` with a fixed number of bullets (e.g. 100). `acquire()` returns a free bullet (or none if exhausted), `release()` returns it. Bullets are reset when reused.
  *Focus:* reuse instead of allocation, resetting state on reuse, handling an exhausted pool.

- [ ] **Database Connection Pool with RAII Handles** / Medium
  A `ConnectionPool` with a maximum size. `acquire()` returns a handle (`std::unique_ptr` with a custom deleter) that **automatically** returns the connection to the pool when it goes out of scope. Connections are reset/validated on return; broken connections are replaced.
  *Focus:* RAII to make "forgetting to release" impossible, custom deleters, validating returned objects.

- [ ] **Generic Thread-Safe Object Pool** / Hard
  Write `ObjectPool<T>` usable from many threads: `acquire()` blocks with a timeout when the pool is empty (`std::condition_variable`), the pool can grow up to a limit and shrink when idle. Handles must stay safe even if the pool is destroyed before them. Benchmark pool vs. plain `new`/`delete`.
  *Focus:* synchronization (`mutex` + `condition_variable`), lifetime of handles vs. pool (`shared_ptr`/`weak_ptr`), measuring whether pooling actually helps.

### Lazy Initialization

- [ ] **Lazy Image Gallery** / Easy
  A gallery holds 1000 `Image` objects. An image only knows its file name until someone calls `getPixels()` — only then is the (simulated, slow) loading done, and only once. Print when loading actually happens.
  *Focus:* deferring expensive work until first use, caching the result, `mutable` members in `const` getters.

- [ ] **Generic `Lazy<T>` Wrapper** / Medium
  Write `Lazy<T>` that takes a factory function and creates the value on the first `get()`. Make it thread-safe (`std::call_once`) so two threads calling `get()` at the same time initialize it only once. Compare with `std::optional<T>` and a function-local `static`.
  *Focus:* templates + `std::function`, thread-safe one-time initialization, when each lazy technique is appropriate.

- [ ] **Lazy Service Container** / Hard
  A `ServiceContainer` where services are registered with factories and created only when first requested. Services can depend on other services (resolved recursively). Detect **circular dependencies** and report them clearly. Define what happens when a factory throws (can the next call retry?). Must be thread-safe.
  *Focus:* lazy dependency graphs, cycle detection, exception safety during initialization, thread safety with re-entrant creation.

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

### Decorator

- [ ] **Coffee Shop** / Easy
  A `Beverage` interface with `cost()` and `description()`. Concrete drinks: `Espresso`, `Tea`. Decorators: `Milk`, `Sugar`, `WhippedCream`, `ExtraShot` — each adds to the price and description. Build e.g. "Espresso + Milk + Milk + Sugar" at runtime.
  *Focus:* decorator *is-a* and *has-a* the component at the same time, stacking decorators, owning the wrapped object with `std::unique_ptr`.

- [ ] **Data Stream Pipeline** / Medium
  An `IDataSource` with `write(data)` / `read()`. `FileDataSource` stores data in a file. Decorators: `CompressionDecorator` (simple RLE) and `EncryptionDecorator` (XOR or Caesar). Writing with `Encryption(Compression(File))` and reading back must return the original data. Show what happens if the order of decorators differs between write and read.
  *Focus:* decorators that transform data both ways, order of decorators matters, composing behaviour without subclass explosion.

- [ ] **Request Handler Middleware: Dynamic vs. Static Decorators** / Hard
  Wrap a request handler (`std::function<Response(const Request&)>`) with `Logging`, `Timing`, `Retry(n)`, `Cache` and `RateLimit` decorators. Implement it twice: once with runtime (virtual) decorators, once with compile-time mixins (`Logging<Timing<Retry<Handler>>>`). Compare flexibility, performance and error messages.
  *Focus:* decorating callables, perfect forwarding, runtime vs. compile-time composition, CRTP/mixin decorators.

### Facade

- [ ] **Home Theater** / Easy
  Subsystems: `Amplifier`, `Projector`, `StreamingPlayer`, `Lights`, `Screen`, each with several methods. A `HomeTheaterFacade` offers `watchMovie(title)` and `endMovie()` that call the subsystems in the right order.
  *Focus:* simplifying a complex subsystem behind one class, the subsystems stay usable directly.

- [ ] **Video Conversion Facade** / Medium
  `VideoConverter::convert(file, format)` hides fake subsystems: `CodecFactory`, `BitrateReader`, `AudioMixer`, `VideoFile`. If any step fails, clean up what was already done and report a clear error. Add a second, lower-level facade for advanced users.
  *Focus:* error handling and cleanup across subsystems, layered facades, not turning the facade into a "god object".

- [ ] **Tiny Compiler Facade** / Hard
  Build a mini compiler for arithmetic expressions with `Lexer`, `Parser`, `SemanticAnalyzer` (undefined variables) and `CodeGenerator` (stack-machine instructions). `Compiler::compile(source)` returns the instructions or a list of diagnostics with line/column. Hide all subsystem headers from users with the **Pimpl** idiom.
  *Focus:* facade over a real pipeline, Pimpl as a compilation firewall, collecting diagnostics instead of stopping at the first error.

### Composite

- [ ] **File System Tree** / Easy
  `FileSystemItem` with `getSize()` and `print(indent)`. `File` is a leaf, `Directory` contains files and other directories. Directory size is the sum of its children. Print the tree with indentation.
  *Focus:* treating leaves and containers uniformly, recursion, owning children with `std::unique_ptr`.

- [ ] **Organization Chart** / Medium
  Employees and departments in a hierarchy. Support: total salary budget of any subtree, find an employee by name, move an employee/department to another department, remove a subtree. Each node keeps a parent pointer. Moving a department into its own sub-department must be rejected.
  *Focus:* parent pointers and ownership transfer, preventing cycles, mutating a tree safely.

- [ ] **Expression Tree Calculator** / Hard
  Parse expressions like `(2 + x) * sin(y) - 3` into a composite of `Number`, `Variable`, `BinaryOp` and `Function` nodes. Support `evaluate(variables)`, `toString()`, `simplify()` (e.g. `x * 1 → x`, `0 + x → x`) and `derivative("x")`, which return **new** trees.
  *Focus:* recursive composite with immutable nodes, transformations that build new trees, structural sharing. (Reused later in Visitor / Hard.)

### Proxy

- [ ] **Protected Bank Account** / Easy
  An `IBankAccount` with `deposit`, `withdraw`, `getBalance`. A `BankAccountProxy` checks the current user's role before forwarding: tellers can deposit, only managers can withdraw large amounts, auditors can only read.
  *Focus:* protection proxy, proxy and real subject sharing one interface, the client not noticing the proxy.

- [ ] **Caching Proxy for a Slow Service** / Medium
  A `WeatherApi` that "takes 2 seconds" per request (simulate with `sleep`). A `CachingWeatherProxy` caches results per city with a time-to-live, supports manual invalidation, and logs hits/misses. Measure the speed-up.
  *Focus:* caching proxy, cache invalidation and TTL, separating the cross-cutting concern from the real service.

- [ ] **Your Own Smart Pointers** / Hard
  Implement `SharedPtr<T>` and `WeakPtr<T>` — the smart pointer is the classic "smart reference" proxy. Support `operator->`, `operator*`, copy/move, a control block with strong and weak counts, `WeakPtr::lock()`, custom deleters, and thread-safe counting with `std::atomic`.
  *Focus:* operator overloading for proxies, control blocks, atomic reference counting, exception safety, rule of five.

### Bridge

- [ ] **Shapes × Renderers** / Easy
  Shapes (`Circle`, `Square`) and renderers (`VectorRenderer`, `RasterRenderer`). Without Bridge you'd need 4 classes (`VectorCircle`, `RasterCircle`, ...). With Bridge each `Shape` holds a reference to a `Renderer`. Add a third shape and a third renderer and count the classes.
  *Focus:* separating abstraction from implementation, avoiding the "class explosion" of inheritance.

- [ ] **Remote Controls × Devices** / Medium
  Devices: `TV`, `Radio`, `SmartSpeaker` (power, volume, channel). Remotes: `BasicRemote` (power, volume) and `AdvancedRemote` (adds mute, favourite channels). Any remote works with any device, and a remote can switch to another device at runtime.
  *Focus:* both hierarchies extended independently, the abstraction delegating to the implementor, runtime switching.

- [ ] **Logging Library with Pluggable Sinks** / Hard
  Abstraction: `SyncLogger` and `AsyncLogger` (background thread + queue). Implementation: sinks `ConsoleSink`, `FileSink`, `RotatingFileSink`. Any logger works with any sink. Shut down the async logger cleanly (flush the queue, join the thread). Hide the implementation behind **Pimpl** for ABI stability.
  *Focus:* Bridge in a realistic library, thread lifecycle and clean shutdown, Pimpl as a form of Bridge.

### Flyweight

- [ ] **Forest Rendering** / Easy
  Draw 1,000,000 trees. Each `Tree` stores only `x`, `y` and a pointer to a shared `TreeType` (name, colour, texture data). A `TreeFactory` returns existing `TreeType`s. Print the memory used with and without flyweights.
  *Focus:* intrinsic (shared) vs. extrinsic (per-object) state, flyweight factory, measuring memory savings.

- [ ] **Text Editor Character Styles** / Medium
  A document of characters where each character references a shared `Style` (font, size, bold, italic, colour) obtained from a `StyleFactory`. Support applying a style to a range of text. Styles are immutable — changing a style of a range means pointing to another flyweight.
  *Focus:* immutable flyweights, hashing compound keys for the factory, keeping extrinsic state outside.

- [ ] **Thread-Safe String Interning with Eviction** / Hard
  An `InternedString` type: equal strings share one storage, and comparison is a pointer comparison. The intern pool must be thread-safe, and strings no longer used anywhere must be removed (`std::weak_ptr` in the pool). Benchmark comparisons and memory against `std::string`.
  *Focus:* flyweight pool with automatic eviction, `shared_ptr`/`weak_ptr` interplay, concurrency, benchmarking.

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

### Strategy

- [ ] **Navigation Route Planner** / Easy
  A `Navigator` computes a route between two points using a `RouteStrategy`: `CarStrategy`, `WalkingStrategy`, `PublicTransportStrategy`, each giving a different time and path description. The user can switch strategy at runtime.
  *Focus:* encapsulating interchangeable algorithms behind one interface, the context delegating to the strategy.

- [ ] **Discount Pricing Engine** / Medium
  A shopping cart applies discounts: `PercentageOff`, `BuyXGetYFree`, `SeasonalDiscount`, `LoyaltyDiscount`. Strategies are chosen at runtime and can be combined. Implement the strategy three ways — virtual interface, `std::function`, template parameter — and write down the trade-offs.
  *Focus:* classic OOP strategy vs. lambdas vs. compile-time strategy, combining strategies.

- [ ] **Cache with Eviction Policies** / Hard
  `Cache<Key, Value, EvictionPolicy>` with policies `LRU`, `LFU` and `FIFO` as **template policies** (policy-based design), all with O(1) operations. Then add a runtime-switchable version and benchmark both.
  *Focus:* policy-based design, compile-time vs. runtime strategy, designing a policy interface, efficient data structures (`std::list` + `std::unordered_map`).

### Command

- [ ] **Smart Home Remote** / Easy
  A `RemoteControl` with 5 slots. Each slot holds a `Command` (`LightOnCommand`, `LightOffCommand`, `FanSpeedCommand`, `MusicPlayCommand`). Pressing a button executes the command; an `Undo` button reverts the last one.
  *Focus:* encapsulating a request as an object, invoker / command / receiver roles, simple undo.

- [ ] **Text Editor with Undo/Redo** / Medium
  Commands `Insert`, `Delete`, `Replace` on a text buffer, with unlimited undo and redo stacks. A new command after an undo clears the redo stack. Add `MacroCommand` that groups several commands and undoes them as one.
  *Focus:* storing enough state to undo, undo/redo stacks, composite commands.

- [ ] **Persistent Job Queue** / Hard
  Commands are queued and executed by a pool of worker threads. Commands can be serialized to a text file and replayed after a "crash". Support cancellation of pending jobs and transactional macros: if one sub-command fails, the already-executed ones are rolled back.
  *Focus:* command serialization and replay, thread pool + queue, cancellation, transactional rollback.

### Chain of Responsibility

- [ ] **Support Ticket Escalation** / Easy
  Tickets have a severity (1–5). Handlers: `Bot` (≤1), `SupportAgent` (≤3), `Engineer` (≤4), `Manager` (everything else). Each handler either resolves the ticket or passes it to the next one.
  *Focus:* linking handlers, each handler deciding to handle or forward, the client only knowing the first handler.

- [ ] **HTTP Middleware Pipeline** / Medium
  Handlers: `Authentication`, `RateLimiter`, `Validation`, `Logging`, then the final request handler. Any handler can stop the chain with an error response. The order is configurable when building the pipeline, and some handlers also run code *after* the next handler returns (e.g. timing).
  *Focus:* stopping vs. continuing the chain, pre- and post-processing, building the chain from configuration.

- [ ] **GUI Event Bubbling** / Hard
  A widget tree (`Window` → `Panel` → `Button`). A click is delivered to the deepest widget, then **bubbles up** through its parents until a handler consumes it. Add a *capture* phase (top-down before bubbling) like the browser DOM, and allow handlers to add/remove other handlers while an event is being processed.
  *Focus:* chain formed by a tree's parent links, capture vs. bubble phases, safe modification during dispatch.

### Template Method

- [ ] **Hot Beverages** / Easy
  `CaffeineBeverage::prepareRecipe()` runs fixed steps: `boilWater()`, `brew()`, `pourInCup()`, `addCondiments()`. `Tea` and `Coffee` override only `brew()` and `addCondiments()`. Add a hook `customerWantsCondiments()` that subclasses may override.
  *Focus:* fixed algorithm skeleton in the base class, abstract steps vs. hooks, preventing subclasses from changing the skeleton.

- [ ] **Data Report Generator** / Medium
  `ReportGenerator::generate(path)` runs: open → read raw data → parse → analyze → format report → close. Implement `CsvReport` and `JsonLikeReport` (simple key-value format). Use the **Non-Virtual Interface (NVI)** idiom: public non-virtual `generate()`, private virtual steps. `close()` must run even if a step throws.
  *Focus:* NVI idiom, exception safety in the template method, deciding which steps are required vs. optional.

- [ ] **Mini Unit-Test Framework** / Hard
  A `TestCase` base runs `setUp()` → `run()` → `tearDown()`, catches failures, and reports results. Add fixtures, test registration, and a summary. Then implement a second version with a **static** template method (CRTP) and compare it with the virtual one.
  *Focus:* template method in a real framework, exception-safe teardown, CRTP static polymorphism vs. virtual dispatch.

### Iterator

- [ ] **Playlist Iterator** / Easy
  A `Playlist` class stores songs internally (your choice of container). Give it `begin()`/`end()` with a custom iterator so it works in a range-based `for` loop, without exposing the internal container.
  *Focus:* hiding the internal representation, the minimal iterator operations (`*`, `++`, `!=`).

- [ ] **Binary Tree Traversals** / Medium
  A binary search tree with in-order, pre-order, post-order and level-order iterators. Iterators must be STL-compatible (`iterator_traits`, works with `std::find`, `std::count_if`) and have `const` versions.
  *Focus:* iterator categories and traits, keeping traversal state (stack/queue) inside the iterator, const-correct iterators.

- [ ] **Lazy Range Adapters** / Hard
  Implement composable lazy adapters: `filter`, `map`, `take`, and an infinite `iota` sequence, so `iota(1) | filter(isPrime) | map(square) | take(10)` works without computing anything until iterated. Bonus: a C++20 coroutine-based `Generator<T>`.
  *Focus:* iterator adaptors, sentinels, lazy evaluation, operator overloading for pipes, (bonus) coroutines.

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

### Mediator

- [ ] **Chat Room** / Easy
  `User`s don't talk to each other directly; they send messages through a `ChatRoom` mediator, which delivers them to everyone else (or one user for private messages). Users can join and leave.
  *Focus:* replacing many-to-many communication with one-to-many, colleagues knowing only the mediator.

- [ ] **Registration Dialog** / Medium
  A form with `TextField`s (username, password, confirm password), a `Checkbox` ("I accept the terms") and a `Button` (Submit). Rules: Submit is enabled only when all fields are valid, passwords match and the box is checked; checking "Show password" changes the password fields. Components only notify the `DialogMediator`.
  *Focus:* moving interaction logic out of components, reusable components, keeping the mediator from becoming a god object.

- [ ] **Air Traffic Control Simulation** / Hard
  Planes request landing and take-off from a `ControlTower`. The tower manages several runways, priorities (emergencies first, low fuel next), and holding patterns. Simulate time in ticks with many planes. Split the tower's responsibilities (scheduling, runway assignment, communication) so it stays maintainable.
  *Focus:* a mediator with real coordination logic, priority scheduling, avoiding the god-object trap by decomposition.

### Memento

- [ ] **Text Editor Snapshots** / Easy
  An `Editor` with text and cursor position. `save()` returns a `Memento`, `restore(memento)` brings the state back. A `History` caretaker keeps a list of snapshots.
  *Focus:* originator / memento / caretaker roles, the caretaker never looking inside the memento.

- [ ] **Game Save System** / Medium
  Player state: position, health, inventory, quest progress. Create checkpoints, list them, load any of them. The memento must be **opaque**: only `Player` can read its contents (nested class with private members and `friend`, or similar).
  *Focus:* enforcing encapsulation of the memento in C++, deep copying complex state, managing many saves.

- [ ] **Incremental Snapshots for a Large Document** / Hard
  The document is large, so full snapshots are too expensive. Store **diffs** between snapshots, with a full snapshot every N changes. Limit memory usage by dropping the oldest history. Save and load history to/from a file, including a version number in the format.
  *Focus:* memory-efficient mementos, diff-based state, serialization and format versioning, combining Memento with Command.

### Visitor

- [ ] **Shape Calculations** / Easy
  Shapes `Circle`, `Rectangle`, `Triangle` with an `accept(Visitor&)` method. Visitors: `AreaVisitor`, `PerimeterVisitor`, `DrawVisitor`. Adding a new operation must not require changing the shapes.
  *Focus:* double dispatch, adding operations without modifying the element classes.

- [ ] **Document Exporter** / Medium
  A document made of `Heading`, `Paragraph`, `Image`, `List` and `Table` elements (nested). Visitors export it to HTML, Markdown and plain text. Exporters keep state while visiting (indentation, list numbering).
  *Focus:* visitors with internal state, traversing nested structures (who drives the traversal — the visitor or the elements?).

- [ ] **Expression AST: Classic Visitor vs. `std::variant`** / Hard
  Reuse the expression tree from Composite / Hard. Visitors: `Evaluator`, `PrettyPrinter`, `TypeChecker`, `ConstantFolder` (returns a new tree). Then reimplement the nodes as a `std::variant` and the operations with `std::visit` + the overloaded-lambdas trick. Compare: what is easy to add in each version — a new operation or a new node type?
  *Focus:* the expression problem, classic double dispatch vs. `std::variant`/`std::visit`, visitors that return values.
