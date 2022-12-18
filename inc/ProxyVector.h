#pragma once

#include "vector"
#include <cassert>

template<typename Type>
class ProxyVector {
private:
    std::vector<Type> data{};

public:
    ProxyVector() = default;
    explicit ProxyVector(const int Size) : data(Size) {}
    explicit ProxyVector(std::vector<Type> &Data) : data(Data) {}
    ~ProxyVector() = default;

    [[nodiscard]] size_t size() const { return data.size(); }

    void erase(int idx){
        data.erase(data.begin() + idx);
    }

    ProxyVector &operator=(const std::vector<Type> &new_data){
        data = new_data;
        return *this;
    }

    bool operator==(const ProxyVector &InVector) const{
        bool SizeEquality = size() == InVector.size();
        bool ValuesEquality = true;
        for (int i = 0; i < size(); i++)
            if (data[i] != InVector[i]) {
                ValuesEquality = false;
                break;
            }
        return SizeEquality && ValuesEquality;
    }

    bool operator!=(const ProxyVector &InVector) const{
        return *this != InVector;
    }

    bool operator==(const std::vector<Type> &InVector) const{
        bool SizeEquality = size() == InVector.size();
        bool ValuesEquality = true;
        for (int i = 0; i < size(); i++)
            if (data[i] != InVector[i]) {
                ValuesEquality = false;
                break;
            }
        return SizeEquality && ValuesEquality;
    }

    bool operator!=(const std::vector<Type> &InVector) const{
        return *this != InVector;
    }

    Type &operator[](const int idx){
        assert(idx < data.size());
        return data[idx];
    }

    Type operator[](const int idx) const{
        assert(idx < data.size());
        return data[idx];
    }
};
