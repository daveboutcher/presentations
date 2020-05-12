---
marp: true
paginate: false
backgroundImage: linear-gradient(135deg, white, white 50%, lightblue)
style: 'section{padding-left: 110px}'
---

# Smartpointer exercise

---
<!-- These settings take effect for the remainder of the slides -->
<!-- header: '![](Ocient_symbol_75x75.png)' -->
<!-- footer: 'Smartpointer exercise' -->
<!-- paginate: true -->

# Smart Pointers

Two main smartpointer types:

*std::shared_ptr*

- a reference counted pointer to memory/object
- when the last reference drops, the memory is freed

*std::unique_ptr*

- A wrapped pointer that **cannot be copied**
-- copy and assignment are ```deleted```

---

# The Exercise

Git repository with a skeleton implementation of smart pointers

- smart_pointers.h

```c++
/*
 * My Super Cool Shared Ptr Class
 */
template <typename T>
class shared_ptr {
};

/*
 * Create a shared pointer
 */
template<class T, class ... Args>
shared_ptr<T> make_shared(Args && ... args) {
	dout << "Hey, some fool just made one of my shared objects...." << std::endl;
	return shared_ptr<T>(new T(std::forward<Args>(args)...));
}
```

---

# main.cpp exercises the classes

