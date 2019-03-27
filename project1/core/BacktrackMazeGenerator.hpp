#ifndef BACKTRACKMAZEGENERATOR_HPP
#define BACKTRACKMAZEGENERATOR_HPP

#include "Maze.hpp"
#include "MazeGenerator.hpp"
#include <iostream>
#include <random>

class BacktrackMazeGenerator : public MazeGenerator
{
public:
  virtual void generateMaze(Maze& maze);
  void generateMyMaze(int x , int y , std::vector<std::vector<bool>> twoD, Maze& maze);
};

#endif // BACKTRACKMAZEGENERATOR_HPP
