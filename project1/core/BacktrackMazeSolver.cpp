#include "BacktrackMazeSolver.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, BacktrackMazeSolver, "Recursive Backtracking (Required)");

void BacktrackMazeSolver::solveMaze(const Maze&maze, MazeSolution& mazeSolution)
{
    std::vector<std::vector<bool>> matrix;
    for(int x = 0; x < mazeSolution.getWidth(); x++){
        matrix.push_back(std::vector<bool>{});
        for(int y = 0; y < mazeSolution.getHeight(); y++){
            matrix[x].push_back(false);
        }
    }

    int x = 0;
    int y = 0;
    findPath(x,y,matrix,maze,mazeSolution);

}

void BacktrackMazeSolver::findPath(int x, int y, std::vector<std::vector<bool>> matrix, const Maze& maze, MazeSolution& mazeSolution)
{   
    
   /* Direction go;
    int x = mazeSolution.getCurrentCell().first;
    int y = mazeSolution.getCurrentCell().second;
    int move = 0;

    matrix[x][y] = true;

    while(mazeSolution.isComplete() == false){
        while( move < 4 ){
            switch(move){
                case 0:
                    go = Direction::up;
                    break;
                case 1:
                    go = Direction::down;
                    break;
                case 2:
                    go = Direction::left;
                    break;
                case 3:
                    go = Direction::right;
                    break;
            }
            if(!maze.wallExists(x,y,go)){
                switch(move){
                    case 0:
                        if(y!=0)
                            y--;
                    case 1:
                        if(y!=mazeSolution.getHeight()-1)
                            y++;
                    case 2:
                        if(x!=0)
                            x--;
                    case 3:
                        if(x!=mazeSolution.getWidth()-1)
                            x++;
                }
            }
            if(matrix[x][y] == false){
                mazeSolution.extend(go);
                findPath(matrix,maze,mazeSolution);
            }

            else{
                x = mazeSolution.getCurrentCell().first;
                y = mazeSolution.getCurrentCell().second;
            }

            move++;

            if( move == 4 && !mazeSolution.isComplete() ){
                mazeSolution.backUp();
                findPath(matrix,maze,mazeSolution);
            }
        }  
                    
    }*/
    //std::pair<int,int>(x,y) = mazeSolution.getCurrentCell();
    matrix[x][y] = true;

    while(mazeSolution.getCurrentCell() != mazeSolution.getEndingCell()){

    if(!maze.wallExists(x,y,Direction::right) && matrix[x+1][y] == false){
        mazeSolution.extend(Direction::right);
        mazeSolution.getCurrentCell();
        x++;
        std::cout << "going right" << std::endl;
        findPath(x,y,matrix,maze, mazeSolution);
      
    }

    if (!maze.wallExists(x,y,Direction::down) && matrix[x][y+1] == false){
        mazeSolution.extend(Direction::down);
        mazeSolution.getCurrentCell();
        y++;
        std::cout << "going down" << std::endl;
        findPath(x,y,matrix,maze, mazeSolution);
    }

    if (!maze.wallExists(x,y,Direction::left) && matrix[x-1][y] == false){
        mazeSolution.extend(Direction::left);
        mazeSolution.getCurrentCell();
        //std::pair<int,int> prev = maze
        x--;
        std::cout << "left" << std::endl;
        findPath(x,y,matrix,maze, mazeSolution);
    }

    if (!maze.wallExists(x,y,Direction::up) && matrix[x][y-1] == false){
        mazeSolution.extend(Direction::up);
        //std::pair<int,int> prev = mazeSolution.getCurrentCell();
        y--;
        std::cout << "up" << std::endl;
        findPath(x,y,matrix,maze, mazeSolution);
    }

    else{
        mazeSolution.backUp();
        //prev;
        //std::pair<int,int>(x,y) = mazeSolution.getCurrentCell();
        findPath(x,y,matrix,maze,mazeSolution);
    }
}
}

