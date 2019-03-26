#pragma once

enum mode
{
  bfs,
  dfs,
  iterative,
  greedy,
  a_star
};

enum heuristic
{
  none,
  distance,
  manhattan_distance,
  euclidian_distance
};