#include <iostream>
#include <vector>
#include <array>

/* Problem statement:
 * An element is a peak element if it is greater than the adjacent elements to its left and right.
 */

/*
 * Linear search to find a list of peak elements.
 * Time Complexity: O(n)
 */
template <typename RandomAccessIterator>
std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type>
find_all_peak_elements(RandomAccessIterator begin, RandomAccessIterator end);

/*
 * Binary search to find any one peak element.
 * Time Complexity: O(log(n)
 */
template <typename RandomAccessIterator>
RandomAccessIterator
find_one_peak_element(RandomAccessIterator begin, RandomAccessIterator end);

int main()
{
	/* Generated randomly using 'http://www.psychicscience.org/random.aspx' */
	const std::array<int, 100> arr{
		11, 23, 99, 10, 23, 46, 43, 96, 8, 61, 15, 74, 65, 35, 49, 52, 70, 12, 37, 24, 85,
		19, 26, 65, 39, 93, 19, 42, 28, 28, 38, 27, 74, 93, 7, 35, 41, 24, 19, 96, 19,
		10, 27, 29, 19, 67, 66, 5, 87, 43, 81, 4, 37, 12, 40, 80, 70, 26, 38, 66, 46,
		17, 43, 42, 83, 74, 49, 53, 7, 93, 42, 27, 69, 63, 72, 85, 45, 65, 43, 23, 33,
		64, 79, 68, 57, 96, 10, 99, 85, 84, 26, 83, 74, 25, 5, 61, 58, 29, 56, 54 };

	/* Find all peak elements.
	 * Produces:
	 * [ 99 46 96 61 74 70 37 85 65 93 42 38 93 41 96 29 67 87 81 37 80 66 43 83 53 93 69 85 65 79 96 99 83 61 56 ]
	 */

	std::cout << "All Peak Elements:\n[ ";
	auto peaks = find_all_peak_elements(arr.begin(), arr.end());
	for (auto peak : peaks) {
		std::cout << peak << " ";
	}
	std::cout << "]\n";

	/* Find any one peak element.
	 * Produces: 65
	 */
	auto peak_element = find_one_peak_element(arr.begin(), arr.end());
	if (peak_element != arr.end()) {
		std::cout << "One Peak Element: " << *peak_element << std::endl;
	}

	getchar();
	return 0;
}

template <typename RandomAccessIterator>
std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type>
find_all_peak_elements(RandomAccessIterator begin, RandomAccessIterator end)
{
	std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> results;
	if (end - begin == 1) {
		results.push_back(*begin);
		return results;
	}

	auto first = begin, last = end - 1;
	if (*first >= *(begin + 1)) results.push_back(*first);
	if (*last >= *(last - 1)) results.push_back(*last);

	for (auto it = first + 1; it != last; it++) {
		auto prev = it - 1, next = it + 1;
		if (*it >= *prev && *it >= *next)
			results.push_back(*it);
	}

	return results;
}

template <typename RandomAccessIterator>
RandomAccessIterator
find_one_peak_element(RandomAccessIterator begin, RandomAccessIterator end)
{
	/* array has one element */
	if (end - begin == 1)
		return begin;

	/* look at first and last */
	auto first = begin, last = end - 1;
	if (*first >= *(begin + 1)) return first;
	if (*last >= *(last - 1)) return last;

	/* look in the middle*/
	while (first <= last) {
		auto middle = first + (last - first - 1) / 2;
		auto prev = middle - 1, next = middle + 1;
		if (*middle >= *prev && *middle >= *next) {
			return middle;
		}
		else if (*middle < *prev) {
			last = prev;
		}
		else {
			first = next;
		}
	}

	/* cannot happen */
	return end;
}