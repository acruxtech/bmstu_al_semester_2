#include "../source/Sorts.cpp"
#include <iostream>


int main() {
    std::vector<int> v1 = {1, 3, 5, 7};
    std::vector<int> v2 = {2, 4, 6, 8};
    std::vector<int> merged;
    merge(v1.begin(), v1.end(), v2.begin(), v2.end(), std::back_inserter(merged));
    std::cout << "Merge test: ";
    for (int x : merged) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> unsorted = {5, 3, 1, 4, 2};
    std::vector<int> sorted;
    merge_sort(unsorted.begin(), unsorted.end(), std::back_inserter(sorted));
    std::cout << "Merge sort test: ";
    for (int x : sorted) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> inplace = {5, 3, 1, 4, 2};
    inplace_merge_sort(inplace.begin(), inplace.end());
    std::cout << "Inplace merge sort test: ";
    for (int x : inplace) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> heap = {5, 3, 1, 4, 2};
    heap_sort(heap.begin(), heap.end());
    std::cout << "Heap sort test: ";
    for (int x : heap) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> quick = {5, 3, 1, 4, 2};
    quick_sort(quick.begin(), quick.end());
    std::cout << "Quick sort test: ";
    for (int x : quick) std::cout << x << " ";
    std::cout << "\n";

    std::vector<int> insertion = {5, 3, 1, 4, 2};
    insertion_sort(insertion.begin(), insertion.end());
    std::cout << "Insertion sort test: ";
    for (int x : insertion) std::cout << x << " ";
    std::cout << "\n";

    return 0;
}
