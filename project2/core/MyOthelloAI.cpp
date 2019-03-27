#include <ics46/factory/DynamicFactory.hpp>
#include "MyOthelloAI.hpp"
#include <iostream>
#include <ostream>

ICS46_DYNAMIC_FACTORY_REGISTER(OthelloAI, vwongso::MyOthelloAI, "Project AI (Required)");

std::pair<int,int> vwongso::MyOthelloAI::chooseMove(const OthelloGameState& state)
{   
    std::vector<std::pair<int,int>> validMoves;
    std::pair<int,int> bestMove;
    int depth = 4;
    bool myTurn;

    if(state.isBlackTurn() == true)
        myTurn = state.isBlackTurn();
    else
        myTurn = state.isWhiteTurn();

    for(int x = 0; x < 8; x++){
      for(int y = 0; y < 8; y++){
         if(state.isValidMove(x,y) == true){
           validMoves.push_back(std::make_pair(x,y));
         }
      }
    }

    int bestScore = -999999;
    if(validMoves.empty() == false){
    bestMove = validMoves.front();
    }

    for(std::vector<std::pair<int,int>>::const_iterator it = validMoves.begin(); it != validMoves.end(); it++){
        std::unique_ptr<OthelloGameState> cloneState = state.clone();
        
        cloneState->makeMove(it->first, it->second);
        int score = findMove(*cloneState,depth,myTurn);

        if(score > bestScore){
            bestMove = *it;
            bestScore = score;
        }
    }

    return bestMove;
    

}

int vwongso::MyOthelloAI::findMove(const OthelloGameState& state, int depth, bool myTurn)
{
    int score;
    
    if( depth == 0 )
        return functionEvaluation(state, myTurn);
    
    else{
        if( myTurn == true){
            score = -2*999999;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(state.isValidMove(i,j) == true){
                        std::unique_ptr<OthelloGameState> copyState = state.clone();
                        copyState->makeMove(i,j);
                        int maxVal = findMove(*copyState,depth-1,myTurn);
                        if( score < maxVal){
                            score = maxVal;
                        }
                    }
                }
            }
        }
        
        else{
            score = 2*999999;
            for(int i = 0; i < 8; i++){
                for(int j = 0; j < 8; j++){
                    if(state.isValidMove(i,j) == true){
                        std::unique_ptr<OthelloGameState> stateCopy = state.clone();
                        stateCopy->makeMove(i,j);
                        int minVal = findMove(*stateCopy,depth-1,myTurn);
                        if(score > minVal){
                            score = minVal;
                        }
                            
                    }
                }
            }

        }
        
        return score;
    }
}


int vwongso::MyOthelloAI::functionEvaluation(const OthelloGameState& state, bool myTurn)
{
    int eval;

    if(myTurn == state.isBlackTurn())
        eval = state.blackScore() - state.whiteScore();
    else
        eval = state.whiteScore() - state.blackScore();

    return eval;
}


