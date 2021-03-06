#include <iterator>
#include <iostream>
#include <string>
#include <cstddef>

struct line_iterator {

	using iterator_category = std::input_iterator_tag;
	using value_type = std::string;
	using difference_type = std::ptrdiff_t;
	using pointer = value_type *;
	using reference = value_type &;

	line_iterator() = default;
	explicit line_iterator(std::istream& in) : in { &in } {
	}

	bool operator==(line_iterator const & other) const {
		return is_not_good() && other.is_not_good();
	}

	bool operator!=(line_iterator const & other) const {
		return !(*this == other);
	}

	line_iterator & operator++() {
		std::getline(*in, current_line);
		return *this;
	}

	line_iterator operator++(int) {
		auto copy = *this;
		++*this;
		return copy;
	}

	value_type operator*() const {
		return current_line;
	}

private:
	std::istream * in{nullptr};
	value_type current_line{};

	bool is_not_good() const {
		return in == nullptr || (in->peek(), !in->good());
	}
};


int main(){
	line_iterator input_iter{std::cin};
	line_iterator eof{};
	std::cout << std::distance(input_iter, eof);
}


