#ifndef BACKTRACKMAZESOLVER_HPP
#define BACKTRACKMAZESOLVER_HPP

#include "Maze.hpp"
#include "MazeSolver.hpp"
#include "MazeSolution.hpp"

class BacktrackMazeSolver : public MazeSolver
{
public:
  virtual void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
  void findPath(int x, int y, std::vector<std::vector<bool>> matrix, const Maze& maze, MazeSolution& mazeSolution);
};


#endif // BACKTRACKMAZESOLVER_HPP
