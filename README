LFSM
==============================================================================
simple header-only fsm library for construction fsm models

Installation
--------
  1. Get source code
  1. Project lib directory
  1. In your CmakeList.txt add `target_include_directories(test_lib PUBLIC
    "${PROJECT_BINARY_DIR}"
    "${PROJECT_SOURCE_DIR}/lfsm/include")`

It contains
-------------
- basic CRTP interface for fsm classes (IFSM)
- class for event based fsm (FSM),
- class for ternar matrix based fsm (TernarFSM)
- each class can accept an observer at the entrance and exit

Usage
--------------------------
**create actions**
```cpp

struct green_on {
  void operator()() {
      std::cout << "--GREEN COLOR--" << "\n";

}
};

struct yellow_on {
  void operator()() {
      std::cout << "--YELLOW COLOR--" << "\n";
      }
};

struct red_on {
  void operator()() {
      std::cout << "--RED COLOR--" << "\n";

  }
};
```
**create states**
```cpp

using STATE(green_s);
using STATE(yellow_s);
using STATE(red_s);

using EVENT(green_e);
using EVENT(yellow_e);
using EVENT(red_e);
```
**create observers (if you needed)**
```cpp
struct enter_observer {
    void operator()() {
        std::cout << "I'm exit observer\n"
    }
};
```
**create transtion table**
```cpp
using fsm_table = TransitionTable
                  <
                  /*source state |   event   | target state |   action   |    guard           |*/
                  Tr<green_s,      yellow_e,     yellow_s,     yellow_on,   Guard::NO_GUARD>,
                  Tr<yellow_s,      red_e,        red_s,        red_on,     Guard::NO_GUARD>,
                  Tr<red_s,        green_e,      green_s,      green_on,    Guard::NO_GUARD>
                  >;
```
**run this!**
```cpp
int main() {
    lfsm::StateMachine<fsm_table, enter_observer> fsm;
    fsm.process(yellow_e{});
}
```
License
-------

The project is licensed under the GPLv2.
