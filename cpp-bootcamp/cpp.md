---
marp: true
paginate: false
backgroundImage: linear-gradient(135deg, white, white 50%, lightblue)
style: 'section{padding-left: 110px}'
---
<!-- 
This presentation is written in markdown, and should be formatted using marp
-->

# C++ Bootcamp 2020

![width:400px](Ocient_logo_1333x304.png)

Dave Boutcher

---
<!-- These settings take effect for the remainder of the slides -->
<!-- header: '![](Ocient_symbol_75x75.png)' -->
<!-- footer: 'C++ Bootcamp 2020' -->
<!-- paginate: true -->

# C++ at Ocient

For

- performance
- composability
- standard library
- third party libraries

---

# This class...

...is designed to be a fast romp through C++ as we use it at Ocient

Ask lots of questions!!!!!!!!

![bg right width:600px](questions.png)

---

# Modern C++

We use current compilers (soon to upgrade to GCC 10)
Use modern C++ patterns

- auto where appropriate
- range based loops
- smart pointers (shared_ptr/unique_ptr)
- exploit containers (vectors, sets maps)
- references
- lambdas
- exploit 'algorithms' library
- templates

---

# Auto and Ranged Based Loops

```c++
std::vector<int> primes{2, 3, 5, 7, 11, 13};

for (const auto &p: primes) {
    // ... do something clever
}
```

Older C++ would have used iterators...

---

# Use of ```std::```

Most C++ courses teach you to do...

```c++
using namespace std;
```

...at the top of your code.

We **don't** do that. We prefer to be explicit about things coming from the standard library  

```c++
std::vector<int> primes;
```

---

# Smart Pointers

You will almost never see malloc/free or new/delete in our code

```std::shared_ptr``` and ```std::unique_ptr```

```c++
#include <memory>

class MyComplexClass {
public:
    MyComplexClass(std::string a, float b){}
};

int myfunc() {

    std::shared_ptr<MyComplexClass> dog = std::make_shared<MyComplexClass>("Dog", 2.0);

    // ... lots of code ...

} // dog goes out of scope and gets automatically deleted
```

---

# auto keyword

This is slightly better. We don't pedantically repeat the class type

```c++
class MyComplexClass {
public:
    MyComplexClass(std::string a, float b){}
};

int myfunc() {

    auto dog = std::make_shared<MyComplexClass>("Dog", 2.0);

    // ... lots of code ...m_fd = open(m_fname.c_str(), 0);

} // dog goes out of scope and gets automatically deleted
```

---

# Use of ```auto```

The ```auto``` keyaword can make code simpler.

It can also make it more confusing 

```c++
auto i = makeBomb();

i.destruct();
```

What the heck type is ```i``` and what can I do with it and what does ```destruct()``` mean in this context?

That can be a religious discussion...

---

# Containers

Use appropriately:

- map vs unordered_map
- vector
- set vs unordered_set
- deque

---

# References

What is wrong with this picture?

```c++
// A position in 3D space
using pos3D = std::tuple<float, float, float>;

// Map of every star we know about to its position
using starMap = std::map<std::string, pos3D>;

// Get me a star based on its characteristics
pos3D findStar(std::string characteristics, starMap map) {
    ///...
}
```

---

# References 2

Much better

```c++
// A position in 3D space
using pos3D = std::tuple<float, float, float>;

// Map of every star we know about to its position
using starMap = std::map<std::string, pos3D>;

// Get me a star based on its characteristics
pos3D findStar(const std::string &characteristics, const starMap &map) {
    ///...
}
```

---

# References 3

This *may* be better, depending on the context.  What are the concerns?

```c++
// A position in 3D space
using pos3D = std::tuple<float, float, float>;

// Map of every star we know about to its position
using starMap = std::map<std::string, pos3D>;

// Get me a star based on its characteristics
const &pos3D findStar(const std::string &characteristics, const starMap &map) {
    ///...
}
```

---

# References 4

What's wrong with this code?

```c++
// A position in 3D space
using pos3D = std::tuple<float, float, float>;

// Map of every star we know about to its position
using starMap = std::map<std::string, pos3D>;

starMap map;

// Note the "structured binding"...
for (auto [name, location]: map) {
    // ...
}

```

---

# References 5

Better...

```c++
// A position in 3D space
using pos3D = std::tuple<float, float, float>;

// Map of every star we know about to its position
using starMap = std::map<std::string, pos3D>;

starMap map;

// ...
for (auto &[name, location]: map) {
    // ...
}

```

---

# Lambdas

```c++
auto add = [](int a, int b) {
    return a+b;
};

printf("result: %d\n", add(3,5));
```

---

# Lambdas and captures

What does it print?

```c++
int a = 3;

// lambda with capture
auto add = [a](int b) {
    return a+b;
};

a = 1000;

printf("result: %d\n", add(5));
```

---

# Lambdas and captures part 2

What does it print?

```c++
int a = 3;

// lambda with capture
auto add = [&a](int b) {
    return a+b;
};

a = 1000;

printf("result: %d\n", add(5));
```

What happens if ```a``` goes out of scope before the lambda runs?

---

# Algorithms

If you find yourself searching or aggregating a container manually, think about std::algorithms

```c++
#include <algorithm>

// Count all entries in a vector divisible by a value
int countDivisible(const std::vector<int> &v, int divisor) {
    // use a lambda expression to count elements divisible by divisor
    return std::count_if(v.begin(), v.end(), [divisor](int i){return i % divisor == 0;});
}
```

---

# C++ templates

```c++
#include <algorithm>

// Count all entries in a vector greater than a value
template<typename T>
int countGreaterThan(const std::vector<T> &v, const T &val) {
    // use a lambda expression to count elements greater than
    return std::count_if(v.begin(), v.end(), [&val](T &i){return i > val;});
}
```

Note that you could do this via dynamic polymorphism (virtual methods that get checked at run time), but templates will generally perform much better.

Our code sometimes does crazy things to move polymorphism to compile time

---

# C++ Things We Don't Use

- exceptions (with some exceptions)
- objects for the sake of objects

---

Miscellaneous C++ Topics

---

# ```class``` vs ```struct```

What's the difference between a class and a struct?

```c++
struct Foo {
    Foo(); // constructor
    ~Foo(); // destructor
    void foobaby(); // do something

    int m_foo;
};
```

---

# C++ Overloading

Can have different functions/methods with the same name, distinguishable by their parameters

```c++
class Number {
    double fuzz(double a, double b) { ... }
    double fuzz(int a, int b) { ... }

    double &someInternal() { .... }
    const double &someInternal() const { ... }
}
```

**Cannot** have methods that differ only by their return value

---

# C++ Operator Overloading

```c++
class Dog {
    Puppy operator+(const Dog &other) { ... }
}

Dog a, b;

Puppy c = a + b;
```

Use this when it makes sense.

---

# constexpr

Things that are known at compile time

```c++
class Parrot {
    constexpr bool IS_BIRD = true;
};

for (const auto &p:parrots) {
    if constexpr Parrot::IS_BIRD {
        // do something
    }
}
```

---

# <!-- fit --> Copy Constructors, Assignment Operators, Destructors

By default, C++ *Does The Right Thing*&trade; for copy, assignment, destruct

```c++
class Foo {
public:
    Foo(std::string fooname) : m_fooname(fooname) {}
private:
    std::string m_fooname;
    std::vector<std::string> m_otherstuff;
};

// ...
{
   Foo a("bisket");  // construct

   Foo b(a); // copy constructor

   Foo c;
   c = b;  // assignment
} // a, b, c all beautifully destroyed
```

---

# <!-- fit --> Copy Constructors, Assignment Operators, Destructors cont

Sometimes you DO need to write your own operators. What is wrong here?

```c++
class File {
public:
    File(const std::string &fname) : m_fname(fname) {
        m_fd = open(m_fname.c_str(), 0);
    }

    void write(std::string s) {
        write(m_fd, s.c_str(), s.length());
    }

    ~File() {
        close(m_fd);
    }

private:
    std::string m_fname;
    int m_fd;
};
```

---

# <!-- fit --> Copy Constructors, Assignment Operators, Destructors cont

Think about this case:

```c++
void printFunc(File f) {
    f.write("Hello world");
}
```

---

# <!-- fit --> Copy Constructors, Assignment Operators, Destructors cont

This **should** be:

```c++
void printFunc(File &f) {
    f.write("Hello world");
}
```

... but the compiler won't warn you about that.

---

# The Rule of Three

If you need any of a copy constructor, assignment operator, or destructor, you probably need all three

```c++
class File {                                                                                                       .
public:
    File(const std::string &fname) : m_fname(fname) {
        m_fd = open(m_fname.c_str(), 0);
    }

    File(const File &other) : m_fname(other.m_fname) {
        m_fd = open(m_fname.c_str(), 0);
    }

    File& operator=(File other) {
        close(m_fd);
        m_fname = other.m_fname;
        m_fd = open(m_fname.c_str(), 0);
    }

    ~File() {
        close(m_fd);
    }

private:
    std::string m_fname;
    int m_fd;
};
```

*Note:* What will happen with self-assignment? (a = a)

---

# The Rule of Three cont

A better solution in this case is likely:

```c++
class File {                                                                                                       .
public:
    File(const std::string &fname) : m_fname(fname) {
        m_fd = open(m_fname.c_str(), 0);
    }

    File(const File &other) = delete; // prevent copying

    File& operator=(File other) = delete; // prevent assignment

    ~File() {
        close(m_fd);
    }

private:
    std::string m_fname;
    int m_fd;
};
```

The principle of least surprise is important

---

# Move Semantics

A gnarly, game changing feature introduced in C++11

```c++

void myfunc(std::vector<int> v); // Make a copy of v

void myfunc(std::vector<int> &v); // Give myfunc direct write access to v

void myfunc(const std::vector<int> &v); // give myfunc read-only access to v

void myfunc(std::vector<int> &&v); // transfer ownership of the contents of v to myfunc!
```

---

# Move implementation

```c++
class File {
public:
    File(const std::string &fname) : m_fname(fname) {
        m_fd = open(m_fname.c_str(), 0);
    }

    File(const File &other) = delete; // prevent copying
    File& operator=(File other) = delete; // prevent assignment

    File(File &&other) : m_fname(std::move(other.m_fname)) {
        close(m_fd);
        m_fd = other.m_fd;
        other.m_fd = -1;
    }

    File& operator=(File &&other) {
        close(m_fd);
        m_fname = std::move(other.m_fname);
        m_fd = m_other.m_fd;
        other.m_fd = -1;
    }

    ~File() {
        close(m_fd);
    }

private:
    std::string m_fname;
    int m_fd;
};
```

---

# Callers of move semantics need to play along

```c++
std::vector<int> data(1'000'000); // construct a vector with 1 million entries

void func(std::vector<int> &&v);

{
    func(data);
}
```

```plain
movetest.cpp:8:12: error: cannot bind rvalue reference of type ‘std::vector<int>&&’ to lvalue of type ‘std::vector<int>’
    8 |     func(data);
      |          ^~~~
movetest.cpp:3:32: note:   initializing argument 1 of ‘void func(std::vector<int>&&)’
    3 | void func(std::vector<int> &&v);
      |           ~~~~~~~~~~~~~~~~~~~^
```

---

# Callers of move semantics need to play along

```c++
std::vector<int> data(1'000'000); // construct a vector with 1 million entries

void func(std::vector<int> &&v);

{
    func(std::move(data));
}
```

```std::move()``` does **nothing** functionally. It just indicates to the compiler that this data can be moved

---

# Return Value Optimization (RVO)

C++ automatically uses move when returning a value:

```c++
std::vector<std::string> getWords() {
    std::vector<std::string> ret;

    // add lots of stuff to the ret vector

    return ret; // This will be moved!
}
```

Counterintuitively if you add ```return std::move(ret);``` it will do the wrong thing

---

# Do as much at compile time as possible

- prefer ```constexpr int MY_VALUE = 100;``` to ```#define MY_VALUE 100```
-- stronger type and semantic checking
- use ```static_assert``` to check things at compile time
- avoid ```void *``` pointers
- avoid functions like ```void myfunc(int a, int b, int c)```
-- someone is guaranteed to mess up the order of parameters

---

# Sanitizer library

GCC (and Clang) have sanitizer libraries that wrap memory allocations and detect

- memory leaks
- accessing memory outside of allocations
- use after free

We build with those to detect problems in our code.

---

# Modern C++ Book

![bg right width:300px](meyers.jpg)

- a little old (was published in 2014)
- hard to read
- full of useful nuggets
- if you actually understand the things in this book it will make you a very solid C++ programmer

---

C++ Advanced terminology and topics

- rvalue references vs lvalue references
- universal references
- variadic templates

Useful to wow your next C++ interviewer

---

# C++ Core Guidelines

Another excellent (if dry) source for learning good C++ practices

[https://isocpp.github.io/CppCoreGuidelines/](https://isocpp.github.io/CppCoreGuidelines/)

---

# Ocient C++ Internal Standards

Search for "C++ Coding Standards" on confluence
