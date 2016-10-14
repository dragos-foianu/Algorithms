#include <iostream>
#include <vector>
#include <array>

/* Problem statement:
* Given an array, find the length of the minimum subarray which sums to a given sum.
*/

/*
* Iterate through each element and for each of them look at subsequent elements.
* Time Complexity: O(n^2)
*/
template <typename RandomAccessIterator>
size_t
minlen_sum_n2(RandomAccessIterator begin, RandomAccessIterator end,
	typename std::iterator_traits<RandomAccessIterator>::value_type sum);

/*
* Iterate through each element and if we went over the sum, remove elements from the beginning.
* Time Complexity: O(n)
*/
template <typename RandomAccessIterator>
size_t
minlen_sum_n(RandomAccessIterator begin, RandomAccessIterator end,
	typename std::iterator_traits<RandomAccessIterator>::value_type sum);

/*
* Runs the algorithms and prints results on a given array.
*/
template <typename RandomAccessIterator>
void
run_test(RandomAccessIterator begin, RandomAccessIterator end, typename std::iterator_traits<RandomAccessIterator>::value_type sum)
{
	auto n2 = minlen_sum_n2(begin, end, sum);
	auto n = minlen_sum_n(begin, end, sum);

	if (n2 == std::numeric_limits<size_t>::max()) {
		std::cout << "None";
	} else {
		std::cout << n2;
	}
	std::cout << "\t";
	if (n == std::numeric_limits<size_t>::max()) {
		std::cout << "None";
	} else {
		std::cout << n;
	}
	std::cout << "\n";
}

int main()
{
	int const sum = 15;
	std::vector<int> empty{};
	std::vector<int> one_element{ 5 };
	std::vector<int> one_element_s{ 15 };
	std::vector<int> two_elements{ 5, 7 };
	std::vector<int> two_elements_s{ 10, 5 };
	std::vector<int> some_elements{ 7, 2, 5, 11, 6, 3 };
	std::vector<int> some_elements_s{ 5, 1, 4, 5, 10, 15 };
	std::vector<int> no_update_elements{ 15, 5, 1, 4, 5, 10 };

	std::cout << "O(n^2)\tO(n)\n---\t---\n";
	run_test(empty.begin(), empty.end(), sum);
	run_test(one_element.begin(), one_element.end(), sum);
	run_test(one_element_s.begin(), one_element_s.end(), sum);
	run_test(two_elements.begin(), two_elements.end(), sum);
	run_test(two_elements_s.begin(), two_elements_s.end(), sum);
	run_test(some_elements.begin(), some_elements.end(), sum);
	run_test(some_elements_s.begin(), some_elements_s.end(), sum);
	run_test(no_update_elements.begin(), no_update_elements.end(), sum);

	getchar();
	return 0;
}

template <typename RandomAccessIterator>
size_t
minlen_sum_n2(RandomAccessIterator begin, RandomAccessIterator end,
	typename std::iterator_traits<RandomAccessIterator>::value_type sum)
{
	typename std::iterator_traits<RandomAccessIterator>::value_type current = 0;
	size_t len = std::numeric_limits<size_t>::max();

	for (auto it1 = begin; it1 != end; it1++) {
		current = *it1;

		for (auto it2 = it1 + 1;; it2++) {
			if (current == sum && (it2 - it1) < len) {
				len = it2 - it1;
			}
			if (current > sum || it2 == end) break;
			current += *it2;
		}
	}

	return len;
}

template <typename RandomAccessIterator>
size_t
minlen_sum_n(RandomAccessIterator begin, RandomAccessIterator end,
	typename std::iterator_traits<RandomAccessIterator>::value_type sum)
{
	if (begin == end)
		return std::numeric_limits<size_t>::max();

	typename std::iterator_traits<RandomAccessIterator>::value_type current = *begin;
	size_t len = std::numeric_limits<size_t>::max();

	auto itstart = begin;
	for (auto it = begin + 1;; it++) {
		while (current > sum && itstart != it)
			current -= *(itstart++);

		if (current == sum && (it - itstart) < len) {
			len = it - itstart;
		}

		if (it == end) break;
		current += *it;
	}

	return len;
}