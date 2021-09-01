#ifndef _ZSY_VECTOR_H_
#define _ZSY_VECTOR_H_
#include "zsyMarco.h"
#include <vector>
#include <algorithm>
NS_ZSY_BEGIN

template<class T>
class Vector {
public:

    using iterator = typename std::vector<T>::iterator;
    using const_iterator = typename std::vector<T>::const_iterator;

    using reverse_iterator = typename std::vector<T>::reverse_iterator;
    using const_reverse_iterator = typename std::vector<T>::const_reverse_iterator;

    iterator begin() { return _data.begin(); }
    const_iterator begin() const { return _data.begin(); }

    iterator end() { return _data.end(); }
    const_iterator end() const { return _data.end(); }


    const_iterator cbegin() const { return _data.cbegin(); }
    const_iterator cend() const { return _data.cend(); }

    reverse_iterator rbegin() { return _data.rbegin(); }
    const_reverse_iterator rbegin() const { return _data.rbegin(); }

    reverse_iterator rend() { return _data.rend(); }
    const_reverse_iterator rend() const { return _data.rend(); }

    const_reverse_iterator crbegin() const { return _data.crbegin(); }
    const_reverse_iterator crend() const { return _data.crend(); }

    const_iterator find(T object) const {
        return std::find(_data.begin(), _data.end(), object);
    }

    iterator find(T object) {
        return std::find(_data.begin(), _data.end(), object);
    }

    iterator erase(iterator pos) {
        (*pos)->release();
        return _data.erase(pos);
    }

    iterator erase(iterator first, iterator last) {
        for(auto it = first; it != last; ++it)  {
            (*it)->release();
        }
        return _data.erase(first, last);
    }
    iterator erase(ssize_t index) {
        auto it = std::next(begin(), index);
        (*it)->release();
        return _data.erase(it);
    }

    Vector<T>():_data() {

    }
    Vector<T>(ssize_t capacity) : _data() {
        reserve(capacity);
    }
    Vector<T>(std::initializer_list<T> list) {
        for(auto &e : list) {
            pushBack(e);
        }
    }
    virtual ~Vector<T>() {
        clear();
    }
    // copy constructor
    Vector<T>(const Vector<T> &other): _data(other._data) {
        addRefForAllObjects();
    }
    // move constructor
    Vector<T>(Vector<T> &&other): _data(std::move(other._data)) {

    }
    Vector<T> &operator=(const Vector<T> &other) {
        if(this != &other) {
            clear();
            _data = other._data;
            addRefForAllObjects();
        }
        return *this;
    }
    Vector<T> &operator=(Vector<T> &&other) {
        if(this != &other) {
            clear();
            _data = std::move(other._data);
        }
        return *this;
    }
    void reserve(ssize_t t) {
        _data.reserve(t);
    }
    ssize_t capacity() const {
        return _data.capacity();
    }
    ssize_t size() {
        return _data.size();
    }
    bool empty() {
        return _data.empty();
    }
    ssize_t max_size() {
        return _data.max_zise();
    }
    T at(ssize_t index) const {
        return _data[index];
    }
    T front() {
        return _data.front();
    }
    T back() {
        return _data.back();
    }
    bool contains(T object) {
        return (std::find(_data.begin(), _data.end(), object) != _data.end());
    }
    bool equals(const Vector<T> &other) {
        ssize_t s = this->size();
        for(ssize_t i = 0; i < s; i++) {
            if(this->at(i) != other.at(i)) {
                return false;
            }
        }
        return true;
    }
    void push_back(T object) {
        _data.push_back(object);
        object->retain();
    }
    void push_back(const Vector<T> &other) {
        for(const auto &obj : other) {
            _data.push_back(obj);
            obj->retain();
        }
    }
    void insert(ssize_t index, T object) {
        _data.insert((std::begin(_data) + index), object);
        object->retain();
    }
    void pop_back() {
        auto last = _data.back();
        _data.pop_back();
        last->release();
    }
    void eraseObject(T object, bool removeAll = false) {
        if (removeAll) {
            for(auto it = _data.begin(); it != _data.end();) {
                if ((*it) == object) {
                    it = _data.erase(it);
                    object->release();
                }else {
                    ++it;
                }
            }
        }else{
            auto it = std::find(_data.begin(), _data.end(), object);
            if(it != _data.end()) {
                _data.erase(it);
                object->release();
            }
        }
    }

    void clear() {
        for(auto it : _data) {
            it->release();
        }
        _data.clear();
    }

    ssize_t getIndex(T object) {
        auto it = std::find(_data.begin(), _data.end(), object) ;
        if(it != _data.end()) {
            return it - _data.begin();
        }
        return -1;
    }
    void swap(T object1, T object2) {
        ssize_t idx1 = getIndex(object1);
        ssize_t idx2 = getIndex(object2);
        std::swap(_data[idx1], _data[idx2]);
    }
    void swap(ssize_t idx1, ssize_t idx2) {
        std::swap(_data[idx1], _data[idx2]);
    }
    void replace(ssize_t index, T object) {
        ZSYASSERT(index >= 0 && index < size(), "Invalid index!");
        ZSYASSERT(object != nullptr, "The object should not be nullptr");

        _data[index]->release();
        _data[index] = object;
        object->retain();
    }

    // Reverse the Vector
    void reverse() {
        std::reverse(std::begin(_data), std::end(_data));
    }
protected:
    void addRefForAllObjects() {
        for(const auto &obj : _data) {
            obj->retain();
        }
    }
    std::vector<T> _data;
};

NS_ZSY_END

#endif