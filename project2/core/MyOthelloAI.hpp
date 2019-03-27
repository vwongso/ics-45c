#include "OthelloAI.hpp"


namespace vwongso
{
    class MyOthelloAI : public OthelloAI
    {
    public:
        virtual std::pair<int,int> chooseMove(const OthelloGameState& state);
        int findMove(const OthelloGameState& state, int depth, bool myTurn);
        int functionEvaluation(const OthelloGameState& state, bool myTurn);
    };
}
