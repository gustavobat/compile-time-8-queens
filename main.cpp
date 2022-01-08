#include <iostream>
#include <limits>
#include <utility>
#include <map>
#include <vector>
#include <algorithm>

enum class CellType {
    Empty,
    Queen,
};

struct Cell {
    CellType cell_type = CellType::Empty;
};

struct ChessBoard {

    // Member variables
    constexpr const static std::size_t m_board_size = 8;
    Cell m_data[m_board_size * m_board_size];

    // Member functions
    constexpr static auto rows() { return m_board_size; }

    constexpr static auto cols() { return m_board_size; }

    constexpr Cell &operator()(const std::size_t row, const std::size_t col) {
        return m_data[col + (row * cols())];
    }

    constexpr const Cell &operator()(const std::size_t row, const std::size_t col) const {
        return m_data[col + (row * cols())];
    }

    constexpr bool HasQueen(const std::size_t row, const std::size_t col) {
        return this->operator()(row, col).cell_type == CellType::Queen;
    }

    constexpr void InsertQueen(const std::size_t row, const std::size_t col) {
        this->operator()(row, col).cell_type = CellType::Queen;
    }

    constexpr void RemoveQueen(const std::size_t row, const std::size_t col) {
        this->operator()(row, col).cell_type = CellType::Empty;
    }

    [[nodiscard]] constexpr bool CanPlace(const std::size_t row, const std::size_t col) {

        auto hits_another_queen = [&]() {
            for (auto i = 0; i < m_board_size; i++) {

                if (i != col) if (HasQueen(row, i)) return true;
                if (i != row) if (HasQueen(i, col)) return true;

                if (i > 0) {

                    auto is_inside_board = [](auto i, auto j) {
                        if (i >= 0 && i < m_board_size && j >= 0 && j < m_board_size) return true;
                        else return false;
                    };

                    if (is_inside_board(row + i, col + i)) if (HasQueen(row + i, col + i)) return true;
                    if (is_inside_board(row + i, col - i)) if (HasQueen(row + i, col - i)) return true;
                    if (is_inside_board(row - i, col + i)) if (HasQueen(row - i, col + i)) return true;
                    if (is_inside_board(row - i, col - i)) if (HasQueen(row - i, col - i)) return true;
                }
            }
            return false;
        };


        if (hits_another_queen()) return false;
        return true;
    }


    constexpr bool Solve(std::size_t col = 0) {
        auto board_size = ChessBoard::m_board_size;

        if (col >= board_size)
            return true;

        for (auto row = 0; row < board_size; row++) {
            if (this->CanPlace(row, col)) {
                InsertQueen(row, col);

                if (Solve(col + 1))
                    return true;

                RemoveQueen(row, col);
            }
        }

        return false;
    }

    void PrintSolution() {
        for (auto row = 0; row < ChessBoard::rows(); ++row) {
            for (auto line_num = 0; line_num < 3; line_num++) {
                for (auto col = 0; col < ChessBoard::cols(); ++col) {
                    const auto draw_line = [&]() {
                        switch (this->operator()(row, col).cell_type) {
                            case CellType::Empty:
                                return (row + col) % 2 == 0 ? "\033[37m██████\033[0m" : "\033[30m██████\033[0m";
                            case CellType::Queen:
                                return "\033[31m██████\033[0m";
                            default:
                                return " ";
                        }
                    }();

                    std::cout << draw_line;
                }
                std::cout << '\n';
            }
        }

    }

};

int main() {

    ChessBoard board;
    board.Solve();
    board.PrintSolution();

    return 0;
}