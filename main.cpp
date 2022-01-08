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
    CellType cell_type = CellType::None;
    bool has_queen = false;
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

    [[nodiscard]] static auto QueenHitArea(const int row, const int col) {
        std::vector<std::pair<std::size_t, std::size_t>> hit_area;

        for (auto i = 0; i < m_board_size; i++) {

            if (i != col) hit_area.emplace_back(row, i);
            if (i != row) hit_area.emplace_back(i, col);

            if (i > 0) {

                auto is_inside_board = [](auto i, auto j) {
                    if (i >= 0 && i < m_board_size && j >= 0 && j < m_board_size) return true;
                    else return false;
                };

                if (is_inside_board(row + i, col + i)) hit_area.emplace_back(row + i, col + i);
                if (is_inside_board(row + i, col - i)) hit_area.emplace_back(row + i, col - i);
                if (is_inside_board(row - i, col + i)) hit_area.emplace_back(row - i, col + i);
                if (is_inside_board(row - i, col - i)) hit_area.emplace_back(row - i, col - i);
            }
        }
        return hit_area;
    }

    [[nodiscard]] bool CanPlace(const std::size_t row, const std::size_t col) {

        auto queen_hit_area = QueenHitArea((int) row, (int) col);

        auto coord_has_queen = [this](std::pair<std::size_t, std::size_t> coord) {
            return this->operator()(coord.first, coord.second).has_queen;
        };

        if (std::ranges::any_of(queen_hit_area, coord_has_queen)) {
            return false;
        }
        return true;
    }
};

int main() {
    ChessBoard table;

    for (auto row = 0; row < ChessBoard::rows(); ++row) {
        for (auto line_num = 0; line_num < 3; line_num++) {
            for (auto col = 0; col < ChessBoard::cols(); ++col) {

                const auto draw_line = [&]() {
                    switch (table(row, col).cell_type) {
                        case CellType::EmptyWhite: return "\033[30m██████\033[0m";
                        case CellType::EmptyBlack: return "\033[37m██████\033[0m";
                        case CellType::Queen: return "\033[31m██████\033[0m";
                        default: return " ";
                    }
                }();

                std::cout << draw_line;
            }
            std::cout << '\n';
        }
    }

    return 0;
}