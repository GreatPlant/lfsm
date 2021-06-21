#ifndef STATE_MACHINE_HPP_
#define STATE_MACHINE_HPP_

#include <unordered_map>
#include <algorithm>
#include <typeinfo>

#include "IFSM.hpp"
#include "transition_table.hpp"
#include "key.hpp"

struct empty_action {
    void operator()() {
        return;
    }
};

using lfsm::IFSM;

namespace lfsm {

    template<typename Table,
             typename BeforeObs = empty_action,
             typename AfterObs  = empty_action>
    class StateMachine : public IFSM<StateMachine<Table, BeforeObs, AfterObs>>
    {
        friend class IFSM<StateMachine<Table, BeforeObs, AfterObs>>;

    public:

        using transition_pack = typename Table::transition_p;
        using transition_v = typename Table::transition_v;
        using state_v = typename Table::state_v;
        using event_v = typename Table::event_v;

        StateMachine()
        {
            set(transition_pack{});
        }


        template <typename... Args>
        void state_action (const Args&... args){

            state_v temp_v{current_state};

            auto l = [&](const auto& arg) {

                using state_t =  std::decay_t<decltype(arg)>;
                using functor_t = typename state_t::action_t;

                if constexpr (!std::is_same_v<functor_t, void>){

                    functor_t{}(args...);
                }
            };

            std::visit(l, temp_v);
        }

        template <typename Event,
                  class = std::enable_if_t<std::is_base_of_v<EventBase, Event>>>
        void process(const Event& e){

            Key k;
            k.event_idx = e.idx;
            k.state_idx = key.state_idx;

            on_event_impl(k);
        }

        void set_guard (const Guard& g){
            guard = g;
        }

        unsigned get_state() {
            return key.state_idx;
        }

    private:

        template <class... Ts>
        void set (type_pack<Ts...>){

            (set_impl(just_type<Ts>{}), ...);
        };

        void before_enter() {
            before();
        }

        void before_exit() {
            exit();
        }

        template <typename T>
        void set_impl (just_type<T> t){

            using transition = typename decltype(t)::type;

            using state_t = typename transition::source_t;
            using event_t = typename transition::event_t;
            Guard g = transition::guard;

            Key k;
            k.state_idx = state_t::idx;
            k.event_idx = event_t::idx;

            transitions.insert( {k, transition{}} );

            if (0 == key.state_idx) {

                key.state_idx = k.state_idx;
                guard = g;
                current_state = state_t{};
            }
        }

        void on_event_impl (Key& k){
            before_exit();

            transition_v tr_var = transitions[k];

            Key &ref_k = key;
            Guard &ref_g = guard;
            state_v &ref_state = current_state;

            auto l = [&](const auto& arg) {

                using tr_t =  std::decay_t<decltype(arg)>;
                using functor_t = typename tr_t::action_t;

                if ( GuardEqual{}(ref_g, tr_t::guard) ){

                    using target_t = typename tr_t::target_t;

                    ref_k.state_idx = target_t::idx;
                    ref_state = target_t{};

                    before_enter();

                    state_action();
                    functor_t{}();
                }
            };

            std::visit(l, tr_var);
        }

        using map_type = std::unordered_map<Key, transition_v, KeyHash, KeyEqual>;

        Key key;
        map_type transitions;
        BeforeObs before;
        AfterObs exit;
        state_v current_state;
        Guard guard = Guard::NO_GUARD;
    };
}
#endif
