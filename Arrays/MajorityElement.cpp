#include <iostream>
#include <array>

/* Problem statement:
* An element is a majority element if it occurs more than n / 2 times, where n is the number of elements.
*/

/*
 * Finds majority element via sorting.
 * Time Complexity: O(n * log(n)
 */
template <typename RandomAccessIterator>
RandomAccessIterator
find_majority_element_sort(RandomAccessIterator begin, RandomAccessIterator end);

/*
* Finds majority element using the Boyer-Moore vote algorithm.
* Time Complexity: O(n)
*/
template <typename RandomAccessIterator>
RandomAccessIterator
find_majority_element_bmv(RandomAccessIterator begin, RandomAccessIterator end);

/*
 * Runs the algorithms and prints results on a given array.
 */
template <typename RandomAccessIterator>
void
run_test(RandomAccessIterator begin, RandomAccessIterator end)
{
	auto majority_sort = find_majority_element_sort(begin, end);
	auto majority_bmv = find_majority_element_bmv(begin, end);

	if (majority_sort == end) {
		std::cout << "None";
	} else {
		std::cout << *majority_sort;
	}
	std::cout << "\t";
	if (majority_bmv == end) {
		std::cout << "None";
	} else {
		std::cout << *majority_bmv;
	}
	std::cout << std::endl;
}

int main()
{
	std::array<int, 0> no_elements{};
	std::array<int, 1> one_element{ 15 };
	std::array<int, 3> three_majority{ 10, 10, 10 };
	std::array<int, 3> three_no_majority{ 10, 15, 20};
	std::array<int, 4> four_no_majority{ 10, 15, 20, 20 };
	std::array<int, 100> many_majority{
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 4, 37, 12, 40, 80, 70, 26, 38, 66, 46,
		17, 43, 42, 83, 74, 49, 53, 7, 93, 42, 27, 69, 63, 72, 85, 45, 65, 43, 23, 33,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10,
		64, 79, 68, 57, 96, 10, 99, 85, 84, 26, 83, 74, 25, 5, 61, 58, 29, 56, 54 };
	std::array<int, 100> many_no_majority{
		11, 23, 99, 10, 23, 46, 43, 96, 8, 61, 15, 74, 65, 35, 49, 52, 70, 12, 37, 24, 85,
		19, 26, 65, 39, 93, 19, 42, 28, 28, 38, 27, 74, 93, 7, 35, 41, 24, 19, 96, 19,
		10, 27, 29, 19, 67, 66, 5, 87, 43, 81, 4, 37, 12, 40, 80, 70, 26, 38, 66, 46,
		17, 43, 42, 83, 74, 49, 53, 7, 93, 42, 27, 69, 63, 72, 85, 45, 65, 43, 23, 33,
		64, 79, 68, 57, 96, 10, 99, 85, 84, 26, 83, 74, 25, 5, 61, 58, 29, 56, 54 };

	std::cout << "Sorting\tBMV\n";
	run_test(no_elements.begin(), no_elements.end());
	run_test(one_element.begin(), one_element.end());
	run_test(three_majority.begin(), three_majority.end());
	run_test(three_no_majority.begin(), three_no_majority.end());
	run_test(four_no_majority.begin(), four_no_majority.end());
	run_test(many_majority.begin(), many_majority.end());
	run_test(many_no_majority.begin(), many_no_majority.end());

	getchar();
	return 0;
}

template <typename RandomAccessIterator>
RandomAccessIterator
find_majority_element_sort(RandomAccessIterator begin, RandomAccessIterator end)
{
	if (end == begin)
		return end;
	if (end - begin == 1)
		return begin;

	/* sorted  in O(n * log(n)) */
	using value_type = std::iterator_traits<RandomAccessIterator>::value_type;
	std::sort(begin, end);

	/* counting in O(n) because elements are sorted */
	size_t count = 1, halfsize = (end - begin) / 2;
	value_type crt = *begin;
	for (auto it = begin + 1; it != end; it++) {
		if (*it == crt) {
			count++;
			/* found a majority element, done */
			if (count > halfsize) {
				return it;
			}
		} else {
			count = 1;
			crt = *it;
		}
	}

	return end;
}

template <typename RandomAccessIterator>
RandomAccessIterator
find_majority_element_bmv(RandomAccessIterator begin, RandomAccessIterator end)
{
	if (end == begin)
		return end;
	if (end - begin == 1)
		return begin;

	/* find a candidate, initial does not matter because it will be set immediately inside the loop */
	auto candidate = begin;
	size_t count = 0;
	for (auto it = begin; it != end; it++) {
		/* if count gets back to zero, we change the candidate */
		if (count == 0) {
			candidate = it;
			count = 1;
		}
		else {
			if (*candidate == *it) {
				count++; // same
			} else {
				count--; // different
			}
		}
	}

	/* every time our candidate was found, we found a different element to pair it with
	   it is definitely not a majority */
	if (count == 0)
		return end;

	/* count > 0 means the candidate may or may not be a majority, therefore we count it */
	count = 0;
	for (auto it = begin; it != end; it++) {
		if (*candidate == *it) {
			count++;
		}
	}

	/* count > halfsize means that the candidate is a majority */
	size_t halfsize = (end - begin) / 2;
	return (count > halfsize) ? candidate : end;
}