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
find_any_peak_element(RandomAccessIterator begin, RandomAccessIterator end);

/*
* Runs the algorithms and prints results on a given array.
*/
template <typename RandomAccessIterator>
void
run_test(RandomAccessIterator begin, RandomAccessIterator end)
{
	auto all = find_all_peak_elements(begin, end);
	auto any = find_any_peak_element(begin, end);

	if (any == end) {
		std::cout << "None";
	} else {
		std::cout << *any;
	}
	std::cout << "\t[ ";
	for (auto peak : all) {
		std::cout << peak << " ";
	}
	std::cout << "]\n";
}

int main()
{
	const std::array<int, 0> no_elements{};
	const std::array<int, 1> one_element{ 5 };
	const std::array<int, 2> two_elements{ 20, 55 };
	const std::array<int, 3> three_elements_t1{ 25, 18, 15 }; /* peak at start */
	const std::array<int, 3> three_elements_t2{ 12, 14, 16 }; /* peak at end */
	const std::array<int, 3> three_elements_t3{ 8, 15, 10 }; /* peak in the middle */
	const std::array<int, 3> three_elements_eq{ 9, 9, 9 }; /* equal elements */
	const std::array<int, 6> two_peaks{ 10, 15, 11, 29, 33, 11 }; /* equal elements */
	const std::array<int, 100> many_elements{
		/* Generated randomly using 'http://www.psychicscience.org/random.aspx' */
		11, 23, 99, 10, 23, 46, 43, 96, 8, 61, 15, 74, 65, 35, 49, 52, 70, 12, 37, 24, 85,
		19, 26, 65, 39, 93, 19, 42, 28, 28, 38, 27, 74, 93, 7, 35, 41, 24, 19, 96, 19,
		10, 27, 29, 19, 67, 66, 5, 87, 43, 81, 4, 37, 12, 40, 80, 70, 26, 38, 66, 46,
		17, 43, 42, 83, 74, 49, 53, 7, 93, 42, 27, 69, 63, 72, 85, 45, 65, 43, 23, 33,
		64, 79, 68, 57, 96, 10, 99, 85, 84, 26, 83, 74, 25, 5, 61, 58, 29, 56, 54 };

	std::cout << "Any\tAll\n---\t---\n";
	run_test(no_elements.begin(), no_elements.end());
	run_test(one_element.begin(), one_element.end());
	run_test(two_elements.begin(), two_elements.end());
	run_test(three_elements_t1.begin(), three_elements_t1.end());
	run_test(three_elements_t2.begin(), three_elements_t2.end());
	run_test(three_elements_t3.begin(), three_elements_t3.end());
	run_test(three_elements_eq.begin(), three_elements_eq.end());
	run_test(two_peaks.begin(), two_peaks.end());
	run_test(many_elements.begin(), many_elements.end());

	getchar();
	return 0;
}

template <typename RandomAccessIterator>
std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type>
find_all_peak_elements(RandomAccessIterator begin, RandomAccessIterator end)
{
	std::vector<typename std::iterator_traits<RandomAccessIterator>::value_type> results;
	if (end == begin) return results;
	if (end - begin == 1) {
		results.push_back(*begin);
		return results;
	}

	auto first = begin, last = end - 1;
	if (*first >= *(first + 1)) results.push_back(*first);
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
find_any_peak_element(RandomAccessIterator begin, RandomAccessIterator end)
{
	if (end == begin)
		return end;

	/* array has one element */
	if (end - begin == 1)
		return begin;

	/* look at first and last */
	auto first = begin, last = end - 1;
	if (*first >= *(begin + 1)) return first;
	if (*last >= *(last - 1)) return last;

	/* look in the middle*/
	while (begin < end) {
		auto middle = begin + (end - begin) / 2;
		auto prev = middle - 1, next = middle + 1;
		if (*middle >= *prev && *middle >= *next) {
			return middle;
		} else if (*middle < *prev) {
			end = prev;
		} else {
			begin = next;
		}
	}

	/* cannot happen */
	return end;
}