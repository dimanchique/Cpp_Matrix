#pragma once

#include "vector"
#include <cassert>

class ProxyVector {
private:
    std::vector<float> data{};

public:
    ProxyVector() = default;
    explicit ProxyVector(const int Size) : data(Size) {}
    explicit ProxyVector(std::vector<float> &Data) : data(Data) {}
    ~ProxyVector() = default;

    [[nodiscard]] size_t size() const { return data.size(); }

    void erase(int idx);
    ProxyVector &operator=(const std::vector<float> &new_data);
    bool operator==(const ProxyVector &InVector) const;
    bool operator!=(const ProxyVector &InVector) const;
    bool operator==(const std::vector<float> &InVector) const;
    bool operator!=(const std::vector<float> &InVector) const;
    float &operator[](int idx);
    float operator[](int idx) const;
};
