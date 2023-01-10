---
marp: true
paginate: false
backgroundImage: linear-gradient(135deg, white, white 50%, lightgreen)
style: 'section{padding-left: 110px}'
---
<!--
This presentation is written in markdown, and should be formatted using marp
-->

# Type Erasure 
## Simpler Code and Faster Compile Times

---
<!-- These settings take effect for the remainder of the slides -->
<!-- header: '![](Ocient_symbol_75x75.png)' -->
<!-- footer: 'Logging' -->
<!-- paginate: true -->

# Topics

There will always be dependencies

We want to avoid *artificial* dependencies

"The goal of software architecture is to minimize the human resources required to build and maintain the required system" . Robert Martin

"The most flexible systems are those in which source code dependencies refer only to abstractions, not to concretions." Robert Martin

”Dependency is the key problem in software development at all scales.”
(Kent Beck, TDD by Example)
---

# Forward Declarations

Greatly reduce the need for transitive header files

Can only be used in places where you don't care about things like size

Ocient doesn't use them enough....

---

# Classic Forward Declaration Example

## `myThing.h`
```c++
#pragma once

class MyComplicatedThing; // Forward declare

class MyThing {
    MyComplicatedThing *makeThing();
    bool useThing(MyComplicatedThing *thing);
};
```

**No caller ever cares about the contents of `MyComplicatedThing`**

---

# Classic Forward Declaration Example

## `myThing.cpp`
```c++
// This has 100 transitive includes
#include "myComplicatedThingDeclaration.h"

MyComplicatedThing MyThing::makeThing() {
    return new MyComplicatedThing();
}

bool MyThing::useThing(MyComplicaedThing *thing) {
    return thing->doSomething();
}
```

---

# Forward Declarations and Data Members

This doesn't work:

```c++
class Duck;

class FooDuck {
  public:
    void quack();
  private:
    Duck m_duck;
};
```

```c++
#include "fooduck.h"
int main(int argc, char **argv) {
    FooDuck fd;
    fd.quack();
    return 0;
}
```

---

```c++
class Duck;

class FooDuck {
  public:
    void quack();
  private:
    Duck m_duck;
};

int main(int argc, char **argv) {
    FooDuck fd;
    fd.quack();
    return 0;
}
```

```
test1.cpp:7:10: error: field has incomplete type 'Duck'
    Duck m_duck;
         ^
test1.cpp:1:7: note: forward declaration of 'Duck'
class Duck;
      ^
1 error generated.
```

---

# Forward Declarations and Data Members

This works

```c++
class Duck;

class FooDuck {
  public:
    FooDuck();
    void quack();
  private:
    Duck *m_duck;
};

int main(int argc, char **argv) {
    FooDuck fd;
    fd.quack();
    return 0;
}
```

---

# Forward Declarations and Smart Pointers

We would never use naked pointers, of course

```c++
#include <memory>
class Duck;

class FooDuck {
  public:
    FooDuck();
    void quack();
  private:
    std::unique_ptr<Duck> m_duck;
};
```

---

# Forward Declarations and Smart Pointers

```
In file included from test1.cpp:1:
In file included from ./fooduck.h:1:
In file included from memory:682:
In file included from shared_ptr.h:25:
unique_ptr.h:53:19: error: invalid application of 'sizeof' to an incomplete type 'Duck'
    static_assert(sizeof(_Tp) > 0,
                  ^~~~~~~~~~~
unique_ptr.h:318:7: note: in instantiation of member function 'std::default_delete<Duck>::operator()' requested here
      __ptr_.second()(__tmp);
      ^
unique_ptr.h:272:19: note: in instantiation of member function 'std::unique_ptr<Duck>::reset' requested here
  ~unique_ptr() { reset(); }
                  ^
./fooduck.h:4:7: note: in instantiation of member function 'std::unique_ptr<Duck>::~unique_ptr' requested here
class FooDuck {
      ^
./fooduck.h:2:7: note: forward declaration of 'Duck'
class Duck;
      ^
1 error generated.
```

---

# Forward Declarations and Smart Pointers

Make sure you declare a destructor...

```c++
#include <memory>
class Duck;

class FooDuck {
  public:
    FooDuck();
    ~FooDuck();   // <========>
    void quack();
  private:
    std::unique_ptr<Duck> m_duck;
};
```

---

# Forward Declarations and Smart Pointers

```c++
#include "duck.h"

FooDuck::FooDuck() { m_duck = std::make_unique<Duck>(); }
FooDuck::~FooDuck() = default;
```

The syntax for nested namespaces is ugly

---
quote: 

std::unique_ptr may be constructed for an incomplete type T, such as to facilitate the use as a handle in the Pimpl idiom. If the default deleter is used, T must be complete at the point in code where the deleter is invoked, which happens in the destructor, move assignment operator, and reset member function of std::unique_ptr. (Conversely, std::shared_ptr can’t be constructed from a raw pointer to incomplete type, but can be destroyed where T is incomplete).

---

# PIMPL

An ugly pattern (IMHO)

--- 

Forward declarations and virtual functions????
Forward declarations and templates?????
https://climbtheladder.com/10-forward-declaration-best-practices/

Google style guide recomments **against** forward declarations
https://gieseanw.wordpress.com/2018/02/25/the-joys-of-forward-declarations-results-from-the-real-world/

Upcoming `modules` support in C++ will make all this redundant.....

include what you use is supposed to suggest forward declarations

having a dedicated "...fwd.h" file is not usually useful.  Quickly gets stale, and nothing will detect unused forward declarations.

talk about forward declarations and templates.  Like:

```c++
template <typename T>
class Foo {
public
    Foo();
    ~Foo();
private:
    std::unique_ptr<T> m_obj;
}
```

---

iosfwd header file provides forward declarations for iostream stuff

```c++
// in MyStruct.h 
#include <iosfwd> // contains forward declaration of std::ostream
 
struct MyStruct
{
    int value;
    friend std::ostream& operator<<(std::ostream& os, const S& s);
    // definition provided in MyStruct.cpp file which uses #include <ostream>
};
```



