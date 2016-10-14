#include <iostream>
#include <vector>
#include <array>

/* Problem statement:
* Given two sorted arrays, find the median of the merged array.
*/

/*
* Merge the two arrays using Mergesort's merge() operation and find the median.
* Time Complexity: O(n)
*/
template <typename RandomAccessIterator>
double
median_merged(RandomAccessIterator a1begin, RandomAccessIterator a1end,
	RandomAccessIterator a2begin, RandomAccessIterator a2end);

/*
* Binary search-like algorithm for finding median of equally sized arrays.
* Time Complexity: O(log(n)) if arrays are equally sized, otherwise uses median_merged for O(n)
*/
template <typename RandomAccessIterator>
double
median_binary(RandomAccessIterator a1begin, RandomAccessIterator a1end,
	RandomAccessIterator a2begin, RandomAccessIterator a2end);

/*
* Runs the algorithms and prints results on a given array.
*/
template <typename RandomAccessIterator>
void
run_test(RandomAccessIterator a1begin, RandomAccessIterator a1end, RandomAccessIterator a2begin, RandomAccessIterator a2end)
{
	auto merged = median_merged(a1begin, a1end, a2begin, a2end);
	auto binary = median_binary(a1begin, a1end, a2begin, a2end);

	std::cout << merged << "\t " << binary << "\n";
}

int main()
{
	std::vector<int> empty{};
	std::vector<int> one_element{ 5 };
	std::vector<int> two_elements{ 20, 55 };
	std::vector<int> two_elements_other{ 35, 66 };
	std::vector<int> some_elements{ 10, 15, 11, 29, 33, 11 }; /* equal elements */
	std::vector<int> some_elements_other{ 7, 32, 55, 19, 23, 66 }; /* equal elements */
	std::vector<int> many_elements{
		/* Generated randomly using 'http://www.psychicscience.org/random.aspx' */
		11, 23, 99, 10, 23, 46, 43, 96, 8, 61, 15, 74, 65, 35, 49, 52, 70, 12, 37, 24, 85,
		19, 26, 65, 39, 93, 19, 42, 28, 28, 38, 27, 74, 93, 7, 35, 41, 24, 19, 96, 19,
		10, 27, 29, 19, 67, 66, 5, 87, 43, 81, 4, 37, 12, 40, 80, 70, 26, 38, 66, 46,
		17, 43, 42, 83, 74, 49, 53, 7, 93, 42, 27, 69, 63, 72, 85, 45, 65, 43, 23, 33,
		64, 79, 68, 57, 96, 10, 99, 85, 84, 26, 83, 74, 25, 5, 61, 58, 29, 56, 54 };

	std::sort(some_elements.begin(), some_elements.end());
	std::sort(many_elements.begin(), many_elements.end());

	std::cout << "Merged\tBinary\n---\t---\n";
	run_test(empty.begin(), empty.end(), empty.begin(), empty.end());
	run_test(empty.begin(), empty.end(), one_element.begin(), one_element.end());
	run_test(one_element.begin(), one_element.end(), one_element.begin(), one_element.end());
	run_test(two_elements.begin(), two_elements.end(), one_element.begin(), one_element.end());
	run_test(two_elements.begin(), two_elements.end(), some_elements.begin(), some_elements.end());
	run_test(two_elements.begin(), two_elements.end(), one_element.begin(), one_element.end());
	run_test(two_elements.begin(), two_elements.end(), two_elements_other.begin(), two_elements_other.end());
	run_test(some_elements.begin(), some_elements.end(), some_elements_other.begin(), some_elements_other.end());

	getchar();
	return 0;
}

template <typename RandomAccessIterator>
double
median_merged(RandomAccessIterator a1begin, RandomAccessIterator a1end,
	RandomAccessIterator a2begin, RandomAccessIterator a2end)
{
	using value_type = typename std::iterator_traits<RandomAccessIterator>::value_type;

	/* merge */
	std::vector<value_type> merged;
	for (; a1begin != a1end && a2begin != a2end;) {
		if (*a1begin < *a2begin) {
			merged.push_back(*(a1begin++));
		} else {
			merged.push_back(*(a2begin++));
		}
	}

	/* leftovers */
	while (a1begin != a1end) {
		merged.push_back(*(a1begin++));
	}
	while (a2begin != a2end) {
		merged.push_back(*(a2begin++));
	}

	/* calculate median */
	if (merged.size() == 0) return 0;
	if (merged.size() % 2 == 0)
		return (merged[merged.size() / 2 - 1] + merged[merged.size() / 2]) / 2.0f;
	else
		return merged[merged.size() / 2];
}

template <typename RandomAccessIterator>
double
median_binary(RandomAccessIterator a1begin, RandomAccessIterator a1end,
	RandomAccessIterator a2begin, RandomAccessIterator a2end)
{
	size_t size1 = a1end - a1begin, size2 = a2end - a2begin;

	/* if the arrays are not equally sized, use the merge algorithm */
	if (size1 == 0 && size2 == 0)
		return 0;
	if (size1 != size2)
		return median_merged(a1begin, a1end, a2begin, a2end);

	while (true) {
		size1 = a1end - a1begin;
		size2 = a2end - a2begin;

		/* special cases:
		* sizes == 1
		*	=> a1 = [5], a2 = [7] => median = (5 + 7) / 2;
		* sizes == 2
		*   => a1 = [5 9], a2 = [6 8] => median = (max(5 6) + min(8 9)) / 2;
		*/
		if (size1 == 1 && size2 == 1) {
			return (a1begin[0] + a2begin[0]) / 2.0f;
		}
		if (size1 == 2 && size2 == 2) {
			return (std::max(a1begin[0], a2begin[0]) + std::min(a1begin[1], a2begin[1])) / 2.0f;
		}

		/* calculate medians */
		double m1, m2;
		if (size1 % 2 == 0)
			m1 = (a1begin[size1 / 2 - 1] + a1begin[size1 / 2]) / 2.0f;
		else
			m1 = a1begin[size1 / 2];
		if (size2 % 2 == 0)
			m2 = (a2begin[size2 / 2 - 1] + a2begin[size2 / 2]) / 2.0f;
		else
			m2 = a2begin[size2 / 2];

		/* knowing medians:
		* a1 = [x1 x2 m1 x3 x4]
		* a2 = [y1 y2 m2 y3 y4]
		*
		* if m1 < m2, sorted would be: [x1 x2 {} m1 {others} m2 {} y3 y4]
		*	=> we can discard the left side of a1 (x1 x2) and the right side of a2 (y3 y4)
		* if m2 < m1, sorted would be: [y1 y2 {} m2 {others} m1 {} x3 x4]
		*	=> we can discard the right side of a1 (x3 x4) and the left side of a2 (y1 y2)
		*
		* the reason we can discard these elements is because we know for sure they cannot be between
		* our two medians in the sorted array
		*/
		if (m1 < m2) {
			a1begin += (size1) / 2;
			a2end -= (size2) / 2;
		} else {
			a2begin += (size2) / 2;
			a1end -= (size1) / 2;
		}
	}
}