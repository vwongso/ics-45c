#include "BacktrackMazeGenerator.hpp"
#include "Maze.hpp"
#include <ics46/factory/DynamicFactory.hpp>
#include <iostream>
#include <vector>
#include <random>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, BacktrackMazeGenerator, "Depth-First Search (Required)");

void BacktrackMazeGenerator::generateMaze(Maze& maze)
{

    maze.addAllWalls();

    std::vector<std::vector<bool>> twoD;
    for(int x = 0; x < maze.getWidth(); x++){
        twoD.push_back(std::vector<bool>{});
        for(int y = 0; y < maze.getHeight(); y++){
            twoD[x].push_back(false);
        }
    }

    int x = 0;
    int y = 0;

    generateMyMaze(x,y,twoD,maze);

}


void BacktrackMazeGenerator::generateMyMaze(int x,int y, std::vector<std::vector<bool>> twoD, Maze& maze)
{
    std::default_random_engine engine(std::random_device{}());
    std::uniform_int_distribution<int> distribution{0,3};

    twoD[x][y] = true;

   /* std::vector<int> move;
 
    move.clear();

    if( y > 0 && (twoD[x][y-1] == false)){
        if( maze.wallExists(x, y-1, Direction::up) && maze.wallExists(x, y-1, Direction::down) && maze.wallExists(x, y-1, Direction::left) && maze.wallExists(x, y-1, Direction::right)){
             move.push_back(0);
        }
     }

    if( y < maze.getHeight() && (twoD[x][y+1] == false)){
        if( maze.wallExists(x, y+1, Direction::up) && maze.wallExists(x, y+1, Direction::down) && maze.wallExists(x, y+1, Direction::left) && maze.wallExists(x, y+1, Direction::right)){
             move.push_back(1);
        }
    }

    if( x > 0 && (twoD[x-1][y] == false)){
        if( maze.wallExists(x-1, y, Direction::up) && maze.wallExists(x-1, y, Direction::down) && maze.wallExists(x-1, y, Direction::left) && maze.wallExists(x-1, y, Direction::right)){             
            move.push_back(2);
         }                                                                      }

     if( x < maze.getWidth() && (twoD[x+1][y] == false)){
        if( maze.wallExists(x+1, y, Direction::up) && maze.wallExists(x+1, y, Direction::down) && maze.wallExists(x+1, y, Direction::left) && maze.wallExists(x+1, y, Direction::left) ){
            move.push_back(3);
        }
    }*/

        int randVal = distribution(engine);
        
     //       while((std::find(move.begin(), move.end(), randVal)) != move.end()){
   //             randVal = distribution(engine);
 //           }
    
                switch(randVal){
        
                    case 0:
                            if( y > 0 && (twoD[x][y-1] == false)){
                                    if( maze.wallExists(x, y-1, Direction::up) && maze.wallExists(x, y-1, Direction::down) && maze.wallExists(x, y-1, Direction::left) && maze.wallExists(x, y-1, Direction::right)){
                                                 
                                                     
                        maze.removeWall(x,y,Direction::up);
                        y--;
                        break;
                        }
                        }
                    case 1:
                        if( y < maze.getHeight() && (twoD[x][y+1] == false)){
                                if( maze.wallExists(x, y+1, Direction::up) && maze.wallExists(x, y+1, Direction::down) && maze.wallExists(x, y+1, Direction::left) && maze.wallExists(x, y+1, Direction::right)){

                        maze.removeWall(x,y,Direction::down);
                        y++;
                        break;
                        }
                        }
                    case 2:
                            if( x > 0 && (twoD[x-1][y] == false)){
                                    if( maze.wallExists(x-1, y, Direction::up) && maze.wallExists(x-1, y, Direction::down) && maze.wallExists(x-1, y, Direction::left) && maze.wallExists(x-1, y, Direction::right)){

                        maze.removeWall(x,y,Direction::left);
                        x--;
                        break;
                        }
                        }
                    case 3:
                        if( x < maze.getWidth() && (twoD[x+1][y] == false)){
                            if( maze.wallExists(x+1, y, Direction::up) && maze.wallExists(x+1, y, Direction::down) && maze.wallExists(x+1, y, Direction::left) && maze.wallExists(x+1, y, Direction::left) ){

                        maze.removeWall(x,y,Direction::right);
                        x++;
                        break;
                        }
                        }
                }
            
    

    generateMyMaze(x,y,twoD,maze);
}

