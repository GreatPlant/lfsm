#ifndef TERNARFSM_HPP_
#define TERNARFSM_HPP_

#include <bitset>

#include "IFSM.hpp"
#include "types.hpp"

using std::string;
using std::bitset;

namespace lfsm {

    template <size_t S, size_t X, size_t Y>
    class TernarFSM : public IFSM<lfsm::TernarFSM<S,X,Y>> {
        friend class IFSM<lfsm::TernarFSM<S,X,Y>>;
    public:
        TernarFSM(const ternarMatrixArray& setFunctions,
                  const ternarMatrixArray& unsetFunctions,
                  const ternarMatrixArray& outputFunctions,
                  std::bitset<X>&		   inputSignals,
                  std::bitset<Y>&		   outputSignals);

        void process(void);

        std::bitset<S> get_state();

    private:
        ternarFunctions transitionFunctions;		///Функции перехода
        ternarMatrixArray outputFunctions;			///Функции возбуждения выходных сигналов

        bitset<X>& inputSignals;
        bitset<Y>& outputSignals;
        bitset<S> state;

        void activate_output_signals();

        bitset<S> calculate_next_state();

        bool calculate_next_state(ternarMatrtix funcTernarMatrix, string funcTemplate);

        bool cmpstr(std::string exampleStr, std::string controlStr);
        void before_enter();
        void before_exit();


    };
    template <size_t S, size_t X, size_t Y>
    TernarFSM<S, X, Y>::TernarFSM(const ternarMatrixArray & setFunctions,
                         const ternarMatrixArray & unsetFunctions,
                         const ternarMatrixArray & outputFunctions,
                         std::bitset<X>& inputSignals,
                         std::bitset<Y>& outputSignals) :
        inputSignals(inputSignals),
        outputSignals(outputSignals)

    {
        if (setFunctions.size() == unsetFunctions.size()) {
            this->transitionFunctions = std::make_pair(setFunctions, unsetFunctions);
            this->outputFunctions = outputFunctions;
            this->state = std::bitset<S>(0);
        }

    }
    template <size_t S, size_t X, size_t Y>
    void TernarFSM<S, X, Y>::process()
    {
        this->state = calculate_next_state();
        activate_output_signals();
    }

    template <size_t S, size_t X, size_t Y>
    std::bitset<S> TernarFSM<S, X, Y>::get_state() {
        return state;
    }

    template <size_t S, size_t X, size_t Y>
    void TernarFSM<S, X, Y>::activate_output_signals()
    {
        std::string controlString = inputSignals.to_string() + state.to_string();
        outputSignals.reset();
        for (int i = 0; i < outputFunctions.size(); i++)
        {
            if (calculate_next_state(outputFunctions[i], controlString))
            {
                outputSignals.set(i);
            }
        }
    }

    template <size_t S, size_t X, size_t Y>
    bitset<S> TernarFSM<S, X, Y>::calculate_next_state()
    {
        bitset<S> newState = this->state;

        string controlString = inputSignals.to_string() + state.to_string();

        for (size_t i = 0; i < transitionFunctions.first.size(); i++)
        {
            if (calculate_next_state(transitionFunctions.first[i], controlString))
            {
                newState.set(i, 1);
            }
            if (calculate_next_state(transitionFunctions.second[i], controlString))
            {
                newState.set(i, 0);
            }
        }
        return newState;
    }

    template <size_t S, size_t X, size_t Y>
    bool TernarFSM<S, X, Y>::calculate_next_state(ternarMatrtix funcTernarMatrix,
                                                 string funcTemplate)
    {
        bool answer = false;
        for (size_t i = 0; i < funcTernarMatrix.size() && answer == false; i++) {
            if (funcTemplate.size() != funcTernarMatrix[i].size()) {
                answer = false;
                break;
            }
            else {
                answer = cmpstr(funcTernarMatrix[i], funcTemplate);
            }
        }
        return answer;
    }

    template <size_t S, size_t X, size_t Y>
    bool TernarFSM<S, X, Y>::cmpstr(std::string exampleStr, std::string controlStr) {
        bool answer = true;
        if (exampleStr.length() != controlStr.length()) {
            answer = false;
        }
        else {
            for (int i = 0; i < exampleStr.size(); i++) {
                if (exampleStr[i] == '-') {
                    continue;
                }
                else if (exampleStr[i] != controlStr[i]) {
                    answer = false;
                    break;
                }
            }
        }
        return answer;
    }
}
#endif
