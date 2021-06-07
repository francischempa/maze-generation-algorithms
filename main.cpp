/**
 * @file    main.cpp
 * @author  Ferenc Nemeth
 * @date    18 Nov 2018
 * @brief   Generates a maze with a selected width, height and algorithm, then saves it.
 *
 *          Copyright (c) 2018 Ferenc Nemeth - https://github.com/ferenc-nemeth/
 */ 

#include "aldous_broder.h"
#include "binary_tree.h"
#include "kruskal.h"
#include "prim.h"
#include "recursive_backtracking.h"
#include "recursive_division.h"

#include "solver.h"

#include <iostream>
#include <stdexcept>
#include <ctime>

/**
 * @brief   Main function.
 * @param   void
 * @return  0
 */
int32_t main(void)
{
  uint32_t width        = 0u;
  uint32_t height       = 0u;
  uint32_t algorithm    = 0u;
  std::string filename  = "output/";
  time_t current_time   = 0u;
  maze::solver m_solver;
  std::vector<std::vector<uint32_t>> maze;
  
  std::cout << "\n--------------------------------\n";
  std::cout << "   Maze generation algorithms\n";
  std::cout << "https://github.com/ferenc-nemeth\n";
  std::cout << "--------------------------------\n\n";
  std::cout << "Width of the maze (must be odd number): ";
  std::cin  >> width;
  std::cout << "Height of the maze (must be odd number): ";
  std::cin  >> height;
  std::cout << "\n";
  std::cout << "Aldous-Broder ------------ 1\n";
  std::cout << "Binary tree -------------- 2\n";
  std::cout << "Kruskal's ---------------- 3\n";
  std::cout << "Prim's ------------------- 4\n";
  std::cout << "Recursive backtracking --- 5\n";
  std::cout << "Recursive division ------- 6\n";
  std::cout << "Select an algorithm: ";
  std::cin  >> algorithm;

  /* Save the image with the current Unix-time, */
  /* so it is possible to run the software multiple times without overwriting the outputs. */
  time(&current_time);
  filename += std::to_string(current_time);

  /* Generate the empty area, put entrance and exit on it, then generate the actual maze. */
  if (1u == algorithm)
  {
    maze::aldous_broder m_maze(height, width);            /**< Initialize. */
    m_maze.set_cell(0u,1u, m_maze.hole);                  /**< Entrance point at top-left. */
    m_maze.set_cell(height-1u, width-2u, m_maze.hole);    /**< Exit point at bottom-right. */
    m_maze.generate();                                    /**< The actual generation. */
    filename += "_Aldous_Broder.png";                     /**< Add the name of the algorithm into the filename. */
    maze = m_maze.get_maze();                             /**< Get the maze. */
    m_solver.dijkstra(maze, 0u, 1u, height-1u, width-2u); /**< Solve it. */
    filename.insert(filename.size()-4u, "_Solved");       /**< Rename the filename. */
  }
  else if (2u == algorithm)
  {
    maze::binary_tree m_maze(height, width);
    m_maze.set_cell(0u,1u, m_maze.hole);
    m_maze.set_cell(height-1u, width-2u, m_maze.hole);
    m_maze.generate();
    filename += "_Binary_tree.png";
    maze = m_maze.get_maze();
    m_solver.dijkstra(maze, 0u, 1u, height-1u, width-2u);
    filename.insert(filename.size()-4u, "_Solved");
  }
  else if (3u == algorithm)
  {
    maze::kruskal m_maze(height, width);
    m_maze.set_cell(0u,1u, m_maze.hole);
    m_maze.set_cell(height-1u, width-2u, m_maze.hole);
    m_maze.generate();
    filename += "_Kruskal.png";
    maze = m_maze.get_maze();
    m_solver.dijkstra(maze, 0u, 1u, height-1u, width-2u);
    filename.insert(filename.size()-4u, "_Solved");
  }
  else if (4u == algorithm)
  {
    maze::prim m_maze(height, width);
    m_maze.set_cell(0u,1u, m_maze.hole);
    m_maze.set_cell(height-1u, width-2u, m_maze.hole);
    m_maze.generate();
    filename += "_Prim.png";
    maze = m_maze.get_maze();
    m_solver.dijkstra(maze, 0u, 1u, height-1u, width-2u);
    filename.insert(filename.size()-4u, "_Solved");
  }
  else if (5u == algorithm)
  {
    maze::recursive_backtracking m_maze(height, width);
    m_maze.set_cell(0u,1u, m_maze.hole);
    m_maze.set_cell(height-1u, width-2u, m_maze.hole);
    m_maze.generate();
    filename += "_Recursive_backtracking.png";
    maze = m_maze.get_maze();
    m_solver.dijkstra(maze, 0u, 1u, height-1u, width-2u);
    filename.insert(filename.size()-4u, "_Solved");
  }
  else if (6u == algorithm)
  {
    maze::recursive_division m_maze(height, width);
    m_maze.set_cell(0u,1u, m_maze.hole);
    m_maze.set_cell(height-1u, width-2u, m_maze.hole);
    m_maze.generate();
    filename += "_Recursive_division.png";
    maze = m_maze.get_maze();
    m_solver.dijkstra(maze, 0u, 1u, height-1u, width-2u);
    filename.insert(filename.size()-4u, "_Solved");
  }
  else
  {
    throw std::invalid_argument("Wrong algorithm number!");
  }

  std::cout << "\nMaze generated and saved!\n\n";

  for(int i=0; i<maze.size(); i++)
  {
    for(int j=0; j<maze[i].size(); j++)
    {
      std::cout << maze[i][j] << " ";
    }
    std::cout << "\n";
  }

  return 0;
}

