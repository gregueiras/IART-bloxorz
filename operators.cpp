#include "operators.h"
#include <algorithm>
#include <stdexcept>

node roll_up(node state, const cost_function cost) {
  auto pos = state.pos;

  if (pos.size() == 2) {
    const auto x1 = pos.at(0).x;
    const auto y1 = pos.at(0).y;

    const auto x2 = pos.at(1).x;
    const auto y2 = pos.at(1).y;

    const auto sideways = y1 == y2;   // "Horizontal"
    const auto forewards = x1 == x2;  // "Vertical"
    const auto min_y = std::min(y1, y2);

    if (sideways && y1 > 0) {
      return sideways_up(state, cost, x1, y1, x2, y2);
    }
    if (forewards && min_y > 0) {
      return forewards_up(state, cost, x1, y1, x2, y2, min_y);
    }

  } else if (pos.size() == 1) {
    const auto x = pos.at(0).x;
    const auto y = pos.at(0).y;

    if (y > 1) {
      return standing_up(state, cost, x, y);
    }
    // Would go off the map
    throw std::logic_error("Invalid Move");

  } else {
    throw std::invalid_argument("invalid position");
  }

  throw std::logic_error("Invalid Move");
}

node roll_down(node state, cost_function cost) {
	auto pos = state.pos;

	if (pos.size() == 2) {
		const auto x1 = pos.at(0).x;
		const auto y1 = pos.at(0).y;
	
		const auto x2 = pos.at(1).x;
		const auto y2 = pos.at(1).y;

		const auto sideways = y1 == y2;   // "Horizontal"
		const auto forewards = x1 == x2;  // "Vertical"
		const auto max_y = std::max(y1, y2);

		if (sideways && y1 < state.rows -1) {
			return sideways_down(state, cost, x1, y1, x2, y2);
		}
		if (forewards /*acho que nao precisa de nada aqui?*/) {
			return forewards_down(state, cost, x1, y1, x2, y2, max_y);
		}

	}
	else if (pos.size() == 1) {
		const auto x = pos.at(0).x;
		const auto y = pos.at(0).y;

		if (y < state.rows -1) {
			return standing_down(state, cost, x, y);
		}
		// Would go off the map
		throw std::logic_error("Invalid Move");

	}
	else {
		throw std::invalid_argument("invalid position");
	}

	throw std::logic_error("Invalid Move");


}

node roll_left(node state, cost_function cost) { return state; }

node roll_right(node state, cost_function cost) { return state; }


node sideways_up(node& state, const cost_function cost, const int x1,
                 const int y1, const int x2, const int y2) {
  // Calculate new position
  const auto new_x1 = x1;
  const auto new_y1 = y1 - 1;
  const auto new_x2 = x2;
  const auto new_y2 = y2 - 1;

  // Update map
  const auto index1 = get_index(x1, y1, state.cols);
  const auto index2 = get_index(x2, y2, state.cols);

  const auto new_index1 = get_index(new_x1, new_y1, state.cols);
  const auto new_index2 = get_index(new_x2, new_y2, state.cols);

  std::swap(state.map[index1], state.map[new_index1]);
  std::swap(state.map[index2], state.map[new_index2]);

  // Update position
  state.pos = {point(new_x1, new_y1), point(new_x2, new_y2)};

  // Update cost
  state.cost = cost(state);

  return state;
}

node forewards_up(node& state, const cost_function cost, const int x1,
                  const int y1, const int x2, const int y2, const int min_y) {
  // Calculate new position
  const auto new_x = x1;
  const auto new_y = min_y - 1;

  // Update Map
  const auto index1 = get_index(x1, y1, state.cols);
  const auto index2 = get_index(x2, y2, state.cols);

  const auto new_index = get_index(new_x, new_y, state.cols);

  state.map[index1] = empty_tile;  // TODO: Restore original tile
  state.map[index2] = empty_tile;
  state.map[new_index] = block_tile;

  // Update position
  state.pos = {point(new_x, new_y)};

  // Update cost
  state.cost = cost(state);

  return state;
}

node standing_up(node& state, const cost_function cost, const int x,
	const int y) {
	// Calculate new position
	const auto new_x1 = x;
	const auto new_y1 = y - 2;
	const auto new_x2 = x;
	const auto new_y2 = y - 1;

	// Update map
	const auto index = get_index(x, y, state.cols);

	const auto new_index1 = get_index(new_x1, new_y1, state.cols);
	const auto new_index2 = get_index(new_x2, new_y2, state.cols);

	state.map[index] = empty_tile;  // TODO: Restore original tile
	state.map[new_index1] = block_tile;
	state.map[new_index2] = block_tile;

	// Update position
	state.pos = { point(new_x1, new_y1), point(new_x2, new_y2) };

	// Update cost
	state.cost = cost(state);

	return state;
}


node sideways_down(node& state, const cost_function cost, const int x1,
	const int y1, const int x2, const int y2) {
	// Calculate new position
	const auto new_x1 = x1;
	const auto new_y1 = y1 + 1;
	const auto new_x2 = x2;
	const auto new_y2 = y2 + 1;

	// Update map
	const auto index1 = get_index(x1, y1, state.cols);
	const auto index2 = get_index(x2, y2, state.cols);

	const auto new_index1 = get_index(new_x1, new_y1, state.cols);
	const auto new_index2 = get_index(new_x2, new_y2, state.cols);

	std::swap(state.map[index1], state.map[new_index1]);
	std::swap(state.map[index2], state.map[new_index2]);

	// Update position
	state.pos = { point(new_x1, new_y1), point(new_x2, new_y2) };

	// Update cost
	state.cost = cost(state);

	return state;
}

node forewards_down(node& state, const cost_function cost, const int x1,
	const int y1, const int x2, const int y2, const int max_y) {
	// Calculate new position
	const auto new_x = x1;
	const auto new_y = max_y;

	// Update Map
	const auto index1 = get_index(x1, y1, state.cols);
	const auto index2 = get_index(x2, y2, state.cols);

	const auto new_index = get_index(new_x, new_y, state.cols);

	state.map[index1] = empty_tile;  // TODO: Restore original tile
	state.map[index2] = empty_tile;
	state.map[new_index] = block_tile;

	// Update position
	state.pos = { point(new_x, new_y) };

	// Update cost
	state.cost = cost(state);

	return state;
}



node standing_down(node& state, const cost_function cost, const int x,
                 const int y) {
  // Calculate new position
  const auto new_x1 = x;
  const auto new_y1 = y + 1;
  const auto new_x2 = x;
  const auto new_y2 = y;

  // Update map
  const auto index = get_index(x, y, state.cols);

  const auto new_index1 = get_index(new_x1, new_y1, state.cols);
  const auto new_index2 = get_index(new_x2, new_y2, state.cols);

  state.map[index] = empty_tile;  // TODO: Restore original tile
  state.map[new_index1] = block_tile;
  state.map[new_index2] = block_tile;

  // Update position
  state.pos = {point(new_x1, new_y1), point(new_x2, new_y2)};

  // Update cost
  state.cost = cost(state);

  return state;
}