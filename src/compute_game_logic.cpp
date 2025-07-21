#include "cells.cpp"
#include "compute_game_logic.h"
#include "space.h"

static void spawn_fruit(Cells &cells);
static GameState check_for_game_end(
    const Cells &cells,
    const std::vector<Pos> &one_segments,
    const std::vector<Pos> &two_segments,
    const Direction one_dir,
    const Direction two_dir
);
static void compute_new_snake_positions(
    Cells &cells,
    std::vector<Pos> &segments,
    Cell player_cell,
    Direction dir,
    bool is_eating_fruit
);

// First element of segments is the head
GameState compute_game_logic(
    Cells &cells,
    const unsigned int game_ticks,
    const Direction player_one_dir,
    const Direction player_two_dir,
    std::vector<Pos> &player_one_segments,
    std::vector<Pos> &player_two_segments
) {
    GameState game_state = check_for_game_end(
        cells,
        player_one_segments,
        player_two_segments,
        player_one_dir,
        player_two_dir
    );

    if (game_state != ON_GOING) {
        return game_state;
    }

    Pos player_one_head = player_one_segments.front();
    bool player_one_eating_fruit =
        cells.get(player_one_head.with_dir(player_one_dir))
        == Cell::FRUIT;

    Pos player_two_head = player_two_segments.front();
    bool player_two_eating_fruit =
        cells.get(player_two_head.with_dir(player_two_dir))
        == Cell::FRUIT;

    compute_new_snake_positions(
        cells,
        player_one_segments,
        Cell::PLAYER_ONE,
        player_one_dir,
        player_one_eating_fruit
    );

    compute_new_snake_positions(
        cells,
        player_two_segments,
        Cell::PLAYER_TWO,
        player_two_dir,
        player_two_eating_fruit
    );

    // spawn_fruit happens last because we don't want to spawn a fruit
    // and then have it immediately eaten
    if (game_ticks % 10 == 0) {
        spawn_fruit(cells);
    }

    return GameState::ON_GOING;
}

static GameState check_for_game_end(
    const Cells &cells,
    const std::vector<Pos> &one_segments,
    const std::vector<Pos> &two_segments,
    const Direction one_dir,
    const Direction two_dir
) {
    Pos one_head_moved = one_segments.front().with_dir(one_dir);
    Pos two_head_moved = two_segments.front().with_dir(two_dir);

    // Heads moved into each other
    if (one_head_moved == two_head_moved) {
        return GameState::DRAW;
    }

    auto hit_wall = [&cells](Pos head) {
        return (head.x >= cells.width() || head.x < 0 || head.y >= cells.height() || head.y < 0);
    };

    auto hit_segment = [&cells, &one_segments, &two_segments](Pos head_moved){
        bool collided = false;

        Cell head_cell = cells.get(head_moved.x, head_moved.y);
        if (
            head_cell == Cell::PLAYER_ONE ||
            head_cell == Cell::PLAYER_ONE_HEAD ||
            head_cell == Cell::PLAYER_TWO ||
            head_cell == Cell::PLAYER_TWO_HEAD
        ) {
            collided = true;
        }

        if (collided) { 
            bool is_tail = head_moved == one_segments.back() || head_moved == two_segments.back();

            // If is tail, would be gone the next frame, so it hasn't
            // actually hit anything
            return !is_tail;
        } else {
            return false;
        }
    };

    // Short circuit important because no bounds checking happens in
    // hit_segment when accessing cells
    bool one_dead = hit_wall(one_head_moved) || hit_segment(one_head_moved);
    bool two_dead = hit_wall(two_head_moved) || hit_segment(two_head_moved);

    if (one_dead && two_dead) {
        return GameState::DRAW;
    } else if (one_dead) {
        return GameState::PLAYER_TWO_WON;
    } else if (two_dead) {
        return GameState::PLAYER_ONE_WON;
    } else {
        return GameState::ON_GOING;
    }
}

// Precondition: New snake positions will not result in a game end
static void compute_new_snake_positions(
    Cells &cells,
    std::vector<Pos> &segments,
    Cell player_cell,
    Direction dir,
    bool is_eating_fruit
) {
    assert(segments.size() > 0); // There exists at least a head
    assert(player_cell == Cell::PLAYER_ONE  || player_cell == Cell::PLAYER_TWO);

    auto head_cell = [](Cell cell) {
        if (cell == Cell::PLAYER_ONE) {
            return Cell::PLAYER_ONE_HEAD;
        } else {
            return Cell::PLAYER_TWO_HEAD;
        }
    };

    Pos prev = segments.at(0).with_dir(dir);
    for (int i = 0; i < segments.size(); i++) {
        Pos new_pos = prev;
        prev = segments.at(i);

        segments.at(i) = new_pos;

        cells.set(new_pos, i != 0 ? player_cell : head_cell(player_cell));
        cells.set(prev, Cell::EMPTY);
    }

    if (is_eating_fruit) {
        cells.set(prev, player_cell);
        segments.push_back(prev);
    }
}

// Spawn a fruit if there is an empty space, else do nothing
static void spawn_fruit(Cells &cells) {
    bool has_empty = false;

    for (int y = 0; y < cells.height(); y++) {
        for (int x = 0; x < cells.width(); x++) {
            if (cells.get(x, y) == Cell::EMPTY) {
                has_empty = true;
                break;
            }
        }
        if (has_empty) {
            break;
        }
    }

    if (!has_empty) {
        return;
    }

    unsigned int random_x;
    unsigned int random_y;
    do {
        random_x = std::rand() % cells.width();
        random_y = std::rand() % cells.height();
    } while (cells.get(random_x, random_y) != Cell::EMPTY);

    cells.set(random_x, random_y, Cell::FRUIT);
}
