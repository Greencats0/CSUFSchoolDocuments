#include "utils.h"
#include <algorithm>
#include <cassert>
template <typename T>
class merge_sort {
public:
 static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()){
    T* aux = new T[n]; // Allocate space just once.
    assert(aux != nullptr);
    sort(arr, aux, 0, n-1, comp);
    delete[] aux;
 }
private:
 static const int CUTOFF = 7;
 static void sort(T* arr, T* aux, size_t low, size_t high, const comparator<T>& comp){
     if (high <= low) return;
    int mid = low + (high - low)/2;
    sort(arr,aux, low, mid, comp); // Sort left half.
    sort(arr,aux, mid+1, high,comp); // Sort right half.
    merge(arr, aux, low, mid, high,comp);     
 }
 static void merge(T* arr, T* aux, size_t low, size_t mid, size_t high, const comparator<T>& comp){
    assert(is_sorted(arr, low, mid, comp));
    assert(is_sorted(arr, mid+1, high, comp));
    int i = low, j = mid+1;
    for (int k = low; k <= high; k++){ // Copy a[lo..hi] to aux[lo..hi].
        aux[k] = arr[k];
    }
    for (int k = low; k <= high; k++){ // Merge back to a[lo..hi].
        if (i > mid) arr[k] = aux[j++];
        else if (j > high ) arr[k] = aux[i++];
        else if (less(aux[j], aux[i],comp)) arr[k] = aux[j++];
        else arr[k] = aux[i++]; 
    }
    assert(is_sorted(arr, low, high, comp));
 }
};
template <typename T>
class merge_bu_sort {
public:
// merge_bu_sort() = delete;
 static void sort(T* arr, size_t n, const comparator<T>& comp=fwd_comparator<T>()){
    int N = n;
    T* aux = new T[N];
    for (int sz = 1; sz < N; sz = sz+sz){ // sz: subarray size
        for (int lo = 0; lo < N-sz; lo += sz+sz){ // lo: subarray index
            merge(arr, aux, lo, lo+sz-1, std::min(lo+sz+sz-1, N-1), comp);
        }
    }
    assert(is_sorted(arr,n,comp));
 }
private:
 static void merge(T* arr, T* aux, size_t low, size_t mid, size_t high, const comparator<T>& comp){
    assert(is_sorted(arr, low, mid, comp));
    assert(is_sorted(arr, mid+1, high, comp));
    int i = low, j = mid+1;
    for (int k = low; k <= high; k++){ // Copy a[lo..hi] to aux[lo..hi].
        aux[k] = arr[k];
    }
    for (int k = low; k <= high; k++){ // Merge back to a[lo..hi].
        if (i > mid) arr[k] = aux[j++];
        else if (j > high ) arr[k] = aux[i++];
        else if (less(aux[j], aux[i],comp)) arr[k] = aux[j++];
        else arr[k] = aux[i++]; 
    }
    assert(is_sorted(arr,low, high,comp));
 }
};





