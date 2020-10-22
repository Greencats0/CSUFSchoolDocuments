#include "utils.h"
#include <algorithm>
#include <cassert>
#include "random.h"
template <typename T>
class quick_sort {
public:
static void sort(T* a, size_t n, const comparator<T>& comp=fwd_comparator<T>())
 {
    std_random<T>::shuffle(a,n); // Eliminate dependence on input.
    sort(a, 0, n - 1, comp);
 }
private:
 static void sort(T* a, int lo, int hi, const comparator<T>& comp=fwd_comparator<T>())
 {
    if (hi <= lo) return;
    int j = partition(a, lo, hi, comp); // Partition (see page 291).
    sort(a, lo, j-1, comp); // Sort left part a[lo .. j-1].
    sort(a, j+1, hi, comp); // Sort right part a[j+1 .. hi].
 } 
 static int partition(T* a, int lo, int hi, const comparator<T>& comp=fwd_comparator<T>())
 { // Partition into a[lo..i-1], a[i], a[i+1..hi].
    int i = lo, j = hi+1; // left and right scan indices
    T v = a[lo]; // partitioning item
    while (true)
    { // Scan right, scan left, check for scan complete, and exchange.
    while (less(a[++i], v, comp)) if (i == hi) break;
    while (less(v, a[--j], comp)) if (j == lo) break;
    if (i >= j) break;
    swap(a[i], a[j]);
    }
    swap(a[lo], a[j]); // Put v = a[j] into position
    return j; // with a[lo..j-1] <= a[j] <= a[j+1..hi].
}
};
template <typename T>
class quick_sort_3way {
public:
 static void sort(T* a, size_t n ,const comparator<T>& comp=fwd_comparator<T>())
 {
    std_random<T>::shuffle(a,n); // Eliminate dependence on input.
    sort(a, 0, n, comp);
 }
private:
 static void sort(T* a, int lo, int hi, const comparator<T>& comp=fwd_comparator<T>())
 { // See page 289 for public sort() that calls this method.
   if (hi <= lo) return;
   int lt = lo, i = lo+1, gt = hi;
   T v = a[lo];
   while (i <= gt)
   {
   int cmp = compare(a[i], v,comp);
   if (cmp < 0) swap(a[lt++],a[i++]);
   else if (cmp > 0) swap(a[i], a[gt--]);
   else i++;
   } // Now a[lo..lt-1] < v = a[lt..gt] < a[gt+1..hi].
   sort(a, lo, lt - 1);
   sort(a, gt + 1, hi);
 }
};
