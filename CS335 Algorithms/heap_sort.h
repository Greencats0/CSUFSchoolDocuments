#include "utils.h"
#include <algorithm>
#include <cassert>
#include "random.h"
#include "array.h"
template <typename T>
class heap_sort {
public:
  static void sort(T* a, size_t n, const comparator<T>& comp=fwd_comparator<T>() )
{
 for (int k = n/2; k >= 1; k--)
 sink(a, k, n, comp);
 while (n > 1)
 {
 exchange(a, 0, (n--)-1);
 sink(a, 1, n, comp);
 }
}
private:
 static void sink(T* pq, size_t k, size_t n, const comparator<T>& comp=fwd_comparator<T>()) {
        while (2*k <= n) {
            size_t j = 2*k;
            if (j < n && less(pq[j-1],pq[j], comp)) j++;
            if (!less(pq[k-1], pq[j-1], comp)) break;
            exchange(pq, k-1, j-1);
            k = j;
        }
    }
};

template <typename T>
class max_pq_heap {
public:
 max_pq_heap() : max_pq_heap(MIN_CAPACITY_) { }
 max_pq_heap(size_t capacity) : pq_(capacity+1){ }

 bool empty() const { return pq_.empty();}

 void insert(const T& value, const comparator<T>& comp){
     pq_.push_back(value);
     swin(pq_.szie(), comp);
 }

 T delMax(){
     T& maximum = pq_[1];
     size_t n = pq_.size();

     exchange(1,n);
     pq_.pop_back();
     sink(1);
     pq_[n+1]= T();
     return maximum;
 }

 void swim(size_t k, const comparator <T>& comp){
     while(k> 1 && less(k/2, k, comp)) {
         exchange(k, k/2);
         k /= 2;
     }
 }

 void sink(size_t k, const comparator<T>& comp){
     size_t n = pq_.size();

     while(2*k <= n){
         size_t j= 2*k;
         if(j < n && less( j, j+1, comp)){ ++j;}
         if(!less(k,j,comp)) { break;}
         exchange(k,j);
         k=j;
     }
 }

private:
 static const size_t MIN_CAPACITY_;
 void exchange(size_t i, size_t j){
     T& temp = pq_[i]; pq_[i]= pq_[j]; pq_[j]= temp;
 }
 bool less(size_t i, size_t j, const comparator<T>& comp){
     return less(pq_[i], pq_[j], comp);
 }
 array_<T> pq_;
};

template <typename T>
const size_t max_pq_heap<T>::MIN_CAPACITY_ =10;
