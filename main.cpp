#include <array>
#include <bitset>
#include <iostream>
#include <vector>

/**
 *    col   0   1   2
 * row
 * 0      x00  x01 x02
 * 1      x10  x11 x12
 * 2      x20  x21 x22
*/

template <std::size_t sz = 0>
class chessboard {
private:
	std::array<std::bitset<sz>, sz> board;
	static constexpr std::size_t dim = sz;

public:
	inline void set(uint32_t row, uint32_t col) {
		board[row].set(col);
	}

	inline void reset(uint32_t row, uint32_t col) {
		board[row].reset(col);
	}

	inline bool is_set(uint32_t row, uint32_t col) const {
		return board[row].test(col);
	}

	inline std::size_t size(void) {
		return dim;
	}

	inline bool is_valid(int32_t row, int32_t col) const {
		if (row < 0 || col < 0) {
			return false;
		}
		if (row < dim && col < dim) {
			return true;
		}
		return false;
	}

	inline bool is_valid_col(uint32_t col) const {
		if (col < 0 || col >= dim) {
			return false;
		}
		return true;
	}

	inline bool is_valid_row(uint32_t row) const {
		if (row < 0 || row >= dim) {
			return false;
		}
		return true;
	}

	void print() const {
		for (std::size_t i = 0; i < dim + 4; i++) {
			std::cout << "*";
		}
		std::cout << "\n";

		for (std::size_t i = 0; i < dim; i++) {
			std::cout << "* " << board[i] << " *\n";
		}

		for (std::size_t i = 0; i < dim + 4; i++) {
			std::cout << "*";
		}
		std::cout << "\n";
	}
};

template <std::size_t sz = 0>
class n_queens {
private:
	chessboard<sz> board;
	static constexpr std::size_t dim = sz;

public:
	bool solve(void) {
		return solve(0);
	}

	bool is_valid_pos(uint32_t row, uint32_t col) const {
		if (!is_empty_row(row)) {
			return false;
		}
		if (!is_empty_col(col)) {
			return false;
		}
		if (!is_empty_k_diag(row, col)) {
			return false;
		}
		if (!is_empty_skew_diag(row, col)) {
			return false;
		}
		return true;
	}

private:
	bool solve(uint32_t queen) {
		if (queen == dim) {
			board.print();
			return true;
		}
		for (std::size_t i = 0; i < dim; i++) {
			if (is_valid_pos(i, queen)) {
				board.set(i, queen);
				if (solve(queen + 1)) {
					return true;
				}
				board.reset(i, queen);
			}
		}
		return false;
	}
	inline bool is_empty_row(uint32_t row) const {
		for (std::size_t j = 0; j < dim; j++) {
			if (board.is_set(row, j)) {
				return false;
			}
		}
		return true;
	}

	inline bool is_empty_col(uint32_t col) const {
		for (std::size_t i = 0; i < col; i++) {
			if (board.is_set(i, col)) {
				return false;
			}
		}
		return true;
	}

	bool is_empty_k_diag(uint32_t row, uint32_t col) const {
		int32_t row_it = row;
		int32_t col_it = col;
		while (board.is_valid(row_it, col_it)) {
			if (board.is_set(row_it, col_it)) {
				return false;
			}
			row_it++;
			col_it++;
		}
		row_it = row - 1;
		col_it = col - 1;
		while (board.is_valid(row_it, col_it)) {
			if (board.is_set(row_it, col_it)) {
				return false;
			}
			row_it--;
			col_it--;
		}
		return true;
	}

	bool is_empty_skew_diag(uint32_t row, uint32_t col) const {
		int32_t row_it = row;
		int32_t col_it = col;
		while (board.is_valid(row_it, col_it)) {
			if (board.is_set(row_it, col_it)) {
				return false;
			}
			row_it++;
			col_it--;
		}
		row_it = row - 1;
		col_it = col + 1;
		while (board.is_valid(row_it, col_it)) {
			if (board.is_set(row_it, col_it)) {
				return false;
			}
			row_it--;
			col_it++;
		}
		return true;
	}
};

int main() {
	n_queens<5> queens;
	if (!queens.solve()) {
		std::cout << "NOT possible\n";
	}
	return 0;
}
