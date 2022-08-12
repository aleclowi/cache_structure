#ifndef _CACHE_
#define _CACHE_
#include <iostream>
#include <stdexcept>
#include <list>
/**
 @namespace pic10b defines 4 classes and several nonmember friend functions to create/modify/access/and display a LinkedList of integers
 */
namespace pic10b {
    /**
     @class cache stores a list of templated values and a user-defined ordering boolean variable, otherwise set by deafult
     @tparam T stores the data type
     @tparam N stores the number of elements the container can stores
     @tparam ORD defines ordering, given the default
     */
    template<typename T, std::size_t N, typename ORD = std::less<T>>
    class cache {
    private:
        /**
         constant pointers to the first and last elements
         highest and lowest values of the list (copies because pointers may be released when popped)
         high and low will only be determined at insertion process
         */
        const T* first, * last;
        T high, low;
        /**
         member variable of size <N> containig typename <T> values
         */
        std::list<T>list;
        /**
         stores the boolean (could be user-defined) that determines the sorting of the values in the list
         */
        ORD order;
    public:
        /**
         typedef typename const_iterator to substitude for the const_iterator class
         */
        using const_iterator = typename std::list<T>::const_iterator;
        /**
         default constructor sets all pointers to null and creates an empty list
         */
        constexpr cache() noexcept : first(nullptr), last(nullptr), high(), low(), list{}{}
        /**
         user-defined constructor accepts an ORD parameter and sets the memebr variable order to it
         @param ord user-defined boolean variable to initialize the order in which the list will be sorted
         */
        constexpr cache(ORD ord) noexcept : cache() {
            order = ord;
        }
        /**
         @return const_iterator referencing the first element of the list
         */
        const_iterator begin() const {
            return list.begin();
        }
        /**
         @return const_iterator referencing past the last element of the list
         */
        const_iterator end() const {
            return list.end();
        }
        /**
         function is capable of handling both lvalues an rvalues as efficiently as possible, inserts object of type T into the list, possibly at the cost of removing the odlerst stored object
         @param data the data type T
         */
        void insert(const T& data)& {
            //check if the list is full and pop
            if (size() == N) {
                pop();
            }
            list.push_front(data); //insert the new data

            //if the list only has one element, set all pointers to point at it. set high and low to equal the data
            if (size() == 1) {
                high = data;
                low = data;
                first = &data;
                last = &data;
            }
            else { //more than one element the new element is now first in the list
                first = &data;
            }
            //check if the new data is (by the rules of ordering) higher or lower than the highest and lowest variable
            if (order(high, data)) {
                high = data;
            }
            else if (order(data, low)) {
                low = data;
            }
        }
        /**
         variadic function that can accept an arbitrary number of arguments of arbitrary type to construct an object and add it to the list;
         @param data can be any number of data with arbitrary type Tvals
         */
        template<typename ... Tvals>
        constexpr void emplace(const Tvals& ...data) {
            //pass each argument of the variadic parameter list into the insert function
            insert(T(data...));
        }
        /**
         function removes the oldest element and changes the "last" pointer to point to the previous element
         */
        void pop() {
            if (!last) { // list is empty if last null
                throw std::logic_error("pop nothing");
            }
            else if (size() == 1) { // if just one element
                list.remove(*first); // free heap memory
                first = last = nullptr; // make both null because empty again
            }
            else { // many elements
                list.remove(*last); // delete the element and free the heap memory
                last = &list.back(); // update the last value
            }
        }
        /**
         counts the number of elements that are currently in the list (size cannot be larger than the given size_t N)
         @return int the size of the storage
         */
        constexpr size_t size() noexcept {
            size_t count = 0; // track the amount of elements
            const_iterator it = list.begin(); // pointer at the first element
            while (it != list.end()) { // until the end of the list
                count++;
                ++it; // move to the next element
            }
            return count; //return number of elements
        }
        /**
         function to derefrence the member pointer to the lowest value ever inserted
         @return T the lowest value
         */
        const T& get_low() {
            return low;
        }

        /**
         function to derefrence the member pointer to the highest value ever inserted
         @return T the highest value
         */
        const T& get_high() {
            return high;
        }

        /**
         friend operator defined outside of cache class
         */
        template<typename t, std::size_t n, typename ord>
        friend bool operator==(const const_iterator&, const const_iterator&);
        /**
         friend operator defined outside of cache class
         */
        template<typename t, std::size_t n, typename ord>
        friend bool operator!=(const const_iterator&, const const_iterator&);
        /**
         friend print function defined outside of cache class
         */
        template<typename t, std::size_t n, typename ord>
        friend void print(const cache<t, n, ord>&);

    };
    /**
     namespace pic10b comparison operator to determine if two const_iterators are pointing to the same value
     @param left first iterator considered
     @param right second iterator considered
     */
    template<typename t, std::size_t n, typename ord>
    bool operator==(const typename cache<t, n, ord>::const_iterator& left, const typename cache<t, n, ord>::const_iterator& right) {
        return (*left == *right);
    }
    /**
     namespace pic10b comparison operator to determine if two const_ iterators are pointing to different values.
     @param left first iterator considered
     @param right second iterator considered
    */
    template<typename t, std::size_t n, typename ord>
    bool operator!=(const typename cache<t, n, ord>::const_iterator& left, const typename cache<t, n, ord>::const_iterator& right) {
        return (*left != *right);
    }
    /**
     prints a cache object of any type, printing all the elements separated by spaces to the console.
     @param obj the class object (containing std::list) to be printed
     */
    template<typename t, std::size_t n, typename ord>
    void print(const cache<t, n, ord>& obj) {
        using const_iterator = typename std::list<t>::const_iterator;
        const_iterator it = obj.list.begin();
        while (it != obj.list.end()) {
            std::cout << *it << " ";
            ++it;
        }
    }

}//end of the namespace

#endif