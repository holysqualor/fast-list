#ifndef FAST_LIST_H
#define FAST_LIST_H

#include <iostream>
#include <vector>

template <class T>
class fast_list {
    static const size_t null = (size_t)-1;
    
    struct Node {
        size_t prev, next;
        T object;
    };
    
    std::vector<Node> nodes;
    size_t head, tail, free;
    
public:
    class iterator {
        friend class fast_list;
        
        fast_list *owner;
        size_t index;
        
        iterator(fast_list *owner, size_t index) : owner{owner}, index{index} {}
        
    public:
        T &operator *() {
            return owner->nodes[index].object;
        }
        
        iterator &operator --() {
            index = index == null ? owner->tail : owner->nodes[index].prev;
            return *this;
        }
        
        iterator operator --(int) {
            iterator temp = *this;
            --(*this);
            return temp;
        }
        
        iterator &operator ++() {
            index = index == null ? null : owner->nodes[index].next;
            return *this;
        }
        
        iterator operator ++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator ==(const iterator &other) {
            return owner == other.owner && index == other.index;
        }
        
        bool operator !=(const iterator &other) {
            return !(*this == other);
        }
        
        operator bool() {
            return index != null;
        }
    };
    
    fast_list() : head{null}, tail{null}, free{null} {}
    
    fast_list(std::initializer_list<T> init) : fast_list() {
        for(const T &object : init)
            push_back(object);
    }
    
    iterator begin() {
        return {this, head};
    }
    
    iterator end() {
        return {this, null};
    }
    
    T &front() {
        return nodes[head].object;
    }
    
    T &back() {
        return nodes[tail].object;
    }
    
    size_t size() {
        size_t count = 0;
        for(iterator it = begin(); it; ++it)
            ++count;
        return count;
    }
    
    bool empty() {
        return head == null;
    }
    
    void insert(const iterator &pos, const T &object) {
        size_t place = free == null ? nodes.size() : free;
        if(free != null) {
            free = nodes[free].next;
            nodes[place].object = object;
        } else nodes.push_back({null, null, object});
        nodes[place].prev = pos.index == null ? tail : nodes[pos.index].prev;
        nodes[place].next = pos.index;
        if(nodes[place].prev == null)
            head = place;
        else nodes[nodes[place].prev].next = place;
        if(nodes[place].next == null)
            tail = place;
        else nodes[nodes[place].next].prev = place;
    }
    
    void push_back(const T &object) {
        insert(end(), object);
    }
    
    void push_front(const T &object) {
        insert(begin(), object);
    }
    
    void erase(const iterator &pos) {
        if(pos.index == null)
            return;
        if(nodes[pos.index].prev == null)
            head = nodes[pos.index].next;
        else nodes[nodes[pos.index].prev].next = nodes[pos.index].next;
        if(nodes[pos.index].next == null)
            tail = nodes[pos.index].prev;
        else nodes[nodes[pos.index].next].prev = nodes[pos.index].prev;
        nodes[pos.index].next = free;
        free = pos.index;
    }
    
    void erase(const iterator &first, const iterator &last) {
        auto it = last;
        nodes[(--it).index].next = free;
        free = first.index;
        if(nodes[first.index].prev == null)
            head = last.index;
        else nodes[nodes[first.index].prev].next = last.index;
        if(last.index == null)
            tail = nodes[first.index].prev;
        else nodes[last.index].prev = nodes[first.index].prev;
    }
    
    void clear() {
        if(tail == null)
            return;
        nodes[tail].next = free;
        free = head;
        head = null;
        tail = null;
    }
    
    void deep_clear() {
        nodes.clear();
        head = null;
        tail = null;
        free = null;
    }
};

#endif