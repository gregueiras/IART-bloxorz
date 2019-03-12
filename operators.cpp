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
      return sideways_move(state, cost, x1, y1, x2, y2, 0,-1);
    }
    if (forewards && min_y > 0) {
      return forewards_move(state, cost, x1, y1, x2, y2, x1, min_y,0, -1);
    }

  } else if (pos.size() == 1) {
    const auto x = pos.at(0).x;
    const auto y = pos.at(0).y;

    if (y > 1) {
      return standing_move(state, cost, x, y, 0,-1);
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

		if (sideways && y1 < state.rows-1) {
			return sideways_move(state, cost, x1, y1, x2, y2,0, 1);
		}
		if (forewards && max_y < state.rows -2) {
			return forewards_move(state, cost, x1, y1, x2, y2, x1, max_y,0,1);
		}
	}
	else if (pos.size() == 1) {
		const auto x = pos.at(0).x;
		const auto y = pos.at(0).y;

		if (y < state.rows - 2) {
			return standing_move(state, cost, x, y,0, 1);
		}
		// Would go off the map
		throw std::logic_error("Invalid Move");
	}
	else {
		throw std::invalid_argument("invalid position");
	}

	throw std::logic_error("Invalid Move");
}

node roll_left(node state, cost_function cost) {
	auto pos = state.pos;

	if (pos.size() == 2) {
		const auto x1 = pos.at(0).x;
		const auto y1 = pos.at(0).y;

		const auto x2 = pos.at(1).x;
		const auto y2 = pos.at(1).y;

		const auto sideways = y1 == y2;   // "Horizontal"
		const auto forewards = x1 == x2;  // "Vertical"
		const auto min_x = std::min(x1, x2);

		if (sideways && x1 > 0) {
			return forewards_move(state, cost, x1, y1, x2, y2, min_x, y1, -1, 0);
		}
		if (forewards && min_x > 0) {
			return sideways_move(state, cost, x1, y1, x2, y2, -1, 0);
		}
	}
	else if (pos.size() == 1) {
		const auto x = pos.at(0).x;
		const auto y = pos.at(0).y;

		if (x > 1) {
			return standing_move(state, cost, x, y, -1, 0);
		}
		// Would go off the map
		throw std::logic_error("Invalid Move");
	}
	else {
		throw std::invalid_argument("invalid position");
	}

	throw std::logic_error("Invalid Move");
}

node roll_right(node state, cost_function cost) {
	auto pos = state.pos;

	if (pos.size() == 2) {
		const auto x1 = pos.at(0).x;
		const auto y1 = pos.at(0).y;

		const auto x2 = pos.at(1).x;
		const auto y2 = pos.at(1).y;

		const auto sideways = y1 == y2;   // "Horizontal"
		const auto forewards = x1 == x2;  // "Vertical"
		const auto max_x = std::max(x1, x2);

		if (sideways && x1 < state.cols - 1) {
			return forewards_move(state, cost, x1, y1, x2, y2, max_x, y1, 1, 0);
		}
		if (forewards && max_x < state.cols - 1) {
			return sideways_move(state, cost, x1, y1, x2, y2, 1, 0);
		}
	}
	else if (pos.size() == 1) {
		const auto x = pos.at(0).x;
		const auto y = pos.at(0).y;

		if (y < state.cols - 2) {
			return standing_move(state, cost, x, y, 1,0);
		}
		// Would go off the map
		throw std::logic_error("Invalid Move");
	}
	else {
		throw std::invalid_argument("invalid position");
	}

	throw std::logic_error("Invalid Move");
}



node standing_move(node& state, const cost_function cost, const int x,
                 const int y, const int direction_x, const int direction_y) {
  // Calculate new position
  const auto new_x1 = x + 2*direction_x;
  const auto new_y1 = y + 2*direction_y;
  const auto new_x2 = x + 1*direction_x;
  const auto new_y2 = y + 1*direction_y;

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

node sideways_move(node& state, const cost_function cost, const int x1,
	const int y1, const int x2, const int y2, const int direction_x, const int direction_y) {
	// Calculate new position
	const auto new_x1 = x1 + 1*direction_x;
	const auto new_y1 = y1 + 1*direction_y;
	const auto new_x2 = x2 + 1*direction_x;
	const auto new_y2 = y2 + 1*direction_y;

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


node forewards_move(node& state, const cost_function cost, const int x1,
	const int y1, const int x2, const int y2, const int m_x, const int m_y, const int direction_x, const int direction_y) {
	// Calculate new position
	const auto new_x = m_x + 1 * direction_x;  // x1
	const auto new_y = m_y + 1*direction_y;  //y1

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