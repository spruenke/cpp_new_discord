#include <algorithm>
#include <array>
#include <cctype>
#include <iostream>
#include <utility>

class TicTocToe
{
  std::array<std::array<char, 3>, 3> field{
      {{'-', '-', '-'}, {'-', '-', '-'}, {'-', '-', '-'}}};

  bool is_running{true};
  bool is_player_1_turn{true};
  // WON  := player 1 won
  // LOSE := player 2 won
  // RUN  := only exists because of check in is_finished
  enum status { DRAW, WON, LOSE, RUN };

public:
  auto print()
  {
    for (auto i{0L}; i < field.size(); i++) {
      for (auto j{0L}; j < field.size(); j++) {
        std::cout << field[i][j] << " ";
      }
      std::cout << '\n';
    }
  }

  auto getUserInput()
  {
    bool is_valid_input{false};
    std::pair<int, int> position;
    std::cout << "Player " << (is_player_1_turn ? "1" : "2")
              << " Choose your row and col: \n";
    while (!is_valid_input) {
      std::cout << "row: ";
      std::string tmp;
      int row;
      do {
        std::getline(std::cin, tmp);
        row = tmp[0] - '0';
        // size check to avoid 020
        if (!(row >= 0 and row <= 2) or tmp.size() > 1) {
          std::cout << "Invalid input! Type again:\n";
        }
      } while (!(row >= 0 and row <= 2) or tmp.size() > 1);
      std::cout << "col: ";
      int col;
      do {
        std::getline(std::cin, tmp);
        col = tmp[0] - '0';
        if (!(col >= 0 and col <= 2) or tmp.size() > 1) {
          std::cout << "Invalid input! Type again:\n";
        }
      } while (!(col >= 0 and col <= 2) or tmp.size() > 1);
      position = {row, col};
      if (fieldAlreadyOccupied(position)) {
        std::cout << "This field is already occupied\nChose another one.";
      } else {
        is_valid_input = true;
      }
    }

    return position;
  }

  bool fieldAlreadyOccupied(std::pair<int, int> const &pos)
  {
    return field[pos.first][pos.second] != '-';
  }

  // 0 := noone won
  // 1 := player 1 won
  // 2 := player 2 won
  auto is_finished()
  {
    bool is_dash = false;
    for (auto const &row : field) {
      if (std::any_of(row.begin(), row.end(),
                      [](auto const el) { return el == '-'; })) {
        is_dash = true;
      }
    }

    for (auto const &row : field) {
      if (std::all_of(row.begin(), row.end(),
                      [](auto const el) { return el == 'X'; })) {
        return status::WON;
      }

      if (std::all_of(row.begin(), row.end(),
                      [](auto const el) { return el == 'O'; })) {
        return status::LOSE;
      }
    }

    // vertical check
    for (auto col{0U}; col < field.size(); col++) {
      std::array<char, 3> curr_col = {field[0][col], field[1][col],
                                      field[2][col]};
      if (std::all_of(curr_col.begin(), curr_col.end(),
                      [](auto const el) { return el == 'X'; })) {
        return status::WON;
      }
      if (std::all_of(curr_col.begin(), curr_col.end(),
                      [](auto const el) { return el == 'O'; })) {
        return status::LOSE;
      }
    }

    // diagonal check
    std::array<char, 3> diagonal = {field[0][0], field[1][1], field[2][2]};
    if (std::all_of(diagonal.begin(), diagonal.end(),
                    [](auto const el) { return el == 'X'; })) {
      return status::WON;
    }
    if (std::all_of(diagonal.begin(), diagonal.end(),
                    [](auto const el) { return el == 'O'; })) {
      return status::LOSE;
    }
    diagonal = {field[2][0], field[1][1], field[0][2]};
    if (std::all_of(diagonal.begin(), diagonal.end(),
                    [](auto const el) { return el == 'X'; })) {
      return status::WON;
    }
    if (std::all_of(diagonal.begin(), diagonal.end(),
                    [](auto const el) { return el == 'O'; })) {
      return status::LOSE;
    }

    if (is_dash == false) {
      return status::DRAW;
    }

    return status::RUN;
  }

  auto doMove()
  {
    auto const [row, col] = getUserInput(); // structured binding
    if (is_player_1_turn) {
      field[row][col] = 'X';
    } else {
      field[row][col] = 'O';
    }

    is_player_1_turn = !is_player_1_turn;
  }

  void gameLoop()
  {
    print();
    while (is_running) {
      doMove();
      auto res = is_finished();
      print();
      switch (res) {
      case static_cast<int>(status::DRAW):
        std::cout << "Draw\n";
        is_running = false;
        break;
      case status::WON:
        std::cout << "Player 1 won!\n";
        is_running = false;
        break;
      case 2:
        std::cout << "Player 2 won!\n";
        is_running = false;
      default:
        break;
      }

      if (res == 1) {
        std::cout << "Player 1 won!\n";
        is_running = false;
      } else if (res == 2) {
        std::cout << "Player 2 won!\n";
        is_running = false;
      } else if (res == 0) {
        std::cout << "Draw\n";
        is_running = false;
      }
    }
  }
};

/*
 * TODO:
 * user can guess random number in [0, 10]; if correct, he can move one piece
 of opponent whereever he wants
 * allow for variable field size
 * add ai
 */
auto main() -> int
{
  TicTocToe ticTacToe{};
  ticTacToe.gameLoop();
}