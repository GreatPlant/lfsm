#ifndef IFSM_
#define IFSM_

namespace lfsm {

    template <class FSM>
    class IFSM {
    public:
        template <typename Arg>
        void process(Arg& arg) {
            const_cast<FSM*>(static_cast<const FSM*>(this))->process(arg);
        }

        decltype (auto) get_state() const {
            return const_cast<FSM*>(static_cast<const FSM*>(this))->get_state();
        }
    private:
        void before_enter() {
            const_cast<FSM*>(static_cast<const FSM*>(this))->before_enter();
        };

        void before_exit() {
            const_cast<FSM*>(static_cast<const FSM*>(this))->before_exit();
        };

    };
}
#endif
