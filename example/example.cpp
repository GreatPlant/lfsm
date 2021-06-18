#include <iostream>
#include <thread>

#include "IFSM.hpp"
#include "FSM.hpp"
#include "ternarFSM.hpp"



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


using STATE(green_s);
using STATE(yellow_s);
using STATE(red_s);

using EVENT(green_e);
using EVENT(yellow_e);
using EVENT(red_e);

using fsm_table = TransitionTable
    <
    /*source state |   event   | target state |   action   |    guard           |*/
    Tr<green_s,      yellow_e,     yellow_s,     yellow_on,   Guard::NO_GUARD>,
    Tr<yellow_s,      red_e,        red_s,        red_on,     Guard::NO_GUARD>,
    Tr<red_s,        green_e,      green_s,      green_on,    Guard::NO_GUARD>
    >;


struct enter_observer {
    enter_observer() {
        counter = 0;
    };

    int counter;
    void operator()() {
        std::cout << "I'm enter observer" << " counter: "<< counter++ << "\n";
    }
};


struct exit_observer {
    void operator()() {
        std::cout << "I'm exit observer\n"
                     "------------------------\n";
    }
};

template <class derivedFSM>
void get_state(lfsm::IFSM<derivedFSM> const& fsm) {
    std::cout << fsm.get_state() << '\n';
}

int main() {

    lfsm::StateMachine<fsm_table, enter_observer, exit_observer> fsm;

    fsm.process(yellow_e{});
    fsm.process(red_e{});
    fsm.process(green_e{});

    get_state(fsm);

    return std::cout.rdstate();

}

