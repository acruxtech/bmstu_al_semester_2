#include <vector>
#include <algorithm>
#include <iterator>


template <class It, class Out, class Compare = std::less<>>
Out merge(It first1, It last1, It first2, It last2, Out out, Compare cmp = Compare{}) {
    while (first1 != last1 && first2 != last2) {
        if (cmp(*first1, *first2)) {
            *out++ = *first1++;
        } else {
            *out++ = *first2++;
        }
    }
    return std::copy(first2, last2, std::copy(first1, last1, out));
}


template <class It, class Out, class Compare = std::less<>>
Out merge_sort(It first, It last, Out out, Compare cmp = Compare{}) {
    const auto size = std::distance(first, last);
    if (size <= 1) {
        return std::copy(first, last, out);
    }
    
    const auto middle = std::next(first, size / 2);
    std::vector<typename std::iterator_traits<It>::value_type> left(first, middle);
    std::vector<typename std::iterator_traits<It>::value_type> right(middle, last);
    
    std::vector<typename std::iterator_traits<It>::value_type> left_sorted, right_sorted;
    
    merge_sort(left.begin(), left.end(), std::back_inserter(left_sorted), cmp);
    merge_sort(right.begin(), right.end(), std::back_inserter(right_sorted), cmp);
    
    return merge(left_sorted.begin(), left_sorted.end(), 
               right_sorted.begin(), right_sorted.end(), 
               out, cmp);
}


template <class It, class Compare = std::less<>>
void inplace_merge_sort(It first, It last, Compare cmp = Compare{}) {
    const auto size = std::distance(first, last);
    if (size <= 1) return;
    
    const auto middle = std::next(first, size / 2);
    inplace_merge_sort(first, middle, cmp);
    inplace_merge_sort(middle, last, cmp);
    
    auto first1 = first;
    auto last1 = middle;
    auto first2 = middle;
    auto last2 = last;
    
    while (first1 != last1 && first2 != last2) {
        if (cmp(*first1, *first2)) {
            ++first1;
        } else {
            auto value = std::move(*first2);
            auto it = first2;
            
            while (it != first1) {
                *it = std::move(*std::prev(it));
                --it;
            }
            
            *first1 = std::move(value);
            ++first1;
            ++last1;
            ++first2;
        }
    }
}


template <class It, class Compare = std::less<>>
void heap_sort(It first, It last, Compare cmp = Compare{}) {
    std::make_heap(first, last, cmp);
    std::sort_heap(first, last, cmp);
}


template <class It, class Compare = std::less<>>
void quick_sort(It first, It last, Compare cmp = Compare{}) {
    if (std::distance(first, last) <= 1) return;
    
    const auto pivot = *std::next(first, std::distance(first, last) / 2);
    auto middle1 = std::partition(first, last, [&](const auto& elem) { 
        return cmp(elem, pivot); 
    });
    auto middle2 = std::partition(middle1, last, [&](const auto& elem) { 
        return !cmp(pivot, elem); 
    });
    
    quick_sort(first, middle1, cmp);
    quick_sort(middle2, last, cmp);
}


template <class It, class Compare = std::less<>>
void insertion_sort(It first, It last, Compare cmp = Compare{}) {
    for (auto it = first; it != last; ++it) {
        auto insertion_point = std::upper_bound(first, it, *it, cmp);
        std::rotate(insertion_point, it, std::next(it));
    }
}
