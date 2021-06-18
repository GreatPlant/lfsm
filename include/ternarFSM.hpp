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

        std::bitset<S> getState();

    private:
        ternarFunctions transitionFunctions;		///Функции перехода
        ternarMatrixArray outputFunctions;			///Функции возбуждения выходных сигналов

        bitset<X>& inputSignals;
        bitset<Y>& outputSignals;
        bitset<S> state;

        void activateOutputSignals();

        bitset<S> calculateNextState();

        bool calculateTernarFunc(ternarMatrtix funcTernarMatrix, string funcTemplate);

        bool cmpstr(std::string exampleStr, std::string controlStr);
        void beforeEnter();
        void beforeExit();


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
        this->state = calculateNextState();
        activateOutputSignals();
    }

    template <size_t S, size_t X, size_t Y>
    std::bitset<S> TernarFSM<S, X, Y>::getState() {
        return state;
    }

    template <size_t S, size_t X, size_t Y>
    void TernarFSM<S, X, Y>::activateOutputSignals()
    {
        std::string controlString = inputSignals.to_string() + state.to_string();
        outputSignals.reset();
        for (int i = 0; i < outputFunctions.size(); i++)
        {
            if (calculateTernarFunc(outputFunctions[i], controlString))
            {
                outputSignals.set(i);
            }
        }
    }

    template <size_t S, size_t X, size_t Y>
    bitset<S> TernarFSM<S, X, Y>::calculateNextState()
    {
        bitset<S> newState = this->state;

        string controlString = inputSignals.to_string() + state.to_string();

        for (size_t i = 0; i < transitionFunctions.first.size(); i++)
        {
            if (calculateTernarFunc(transitionFunctions.first[i], controlString))
            {
                newState.set(i, 1);
            }
            if (calculateTernarFunc(transitionFunctions.second[i], controlString))
            {
                newState.set(i, 0);
            }
        }
        return newState;
    }

    template <size_t S, size_t X, size_t Y>
    bool TernarFSM<S, X, Y>::calculateTernarFunc(ternarMatrtix funcTernarMatrix,
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
