#include "ProxyVector.h"

void ProxyVector::erase(const int idx) {
    data.erase(data.begin() + idx);
}

ProxyVector &ProxyVector::operator=(const std::vector<float> &new_data) {
    data = new_data;
    return *this;
}

bool ProxyVector::operator==(const ProxyVector &InVector) const {
    bool SizeEquality = size() == InVector.size();
    bool ValuesEquality = true;
    for (int i = 0; i < size(); i++)
        if (data[i] != InVector[i]) {
            ValuesEquality = false;
            break;
        }
    return SizeEquality && ValuesEquality;
};

bool ProxyVector::operator!=(const ProxyVector &InVector) const {
    return !(*this == InVector);
};

bool ProxyVector::operator==(const std::vector<float> &InVector) const {
    bool SizeEquality = size() == InVector.size();
    bool ValuesEquality = true;
    for (int i = 0; i < size(); i++)
        if (data[i] != InVector[i]) {
            ValuesEquality = false;
            break;
        }
    return SizeEquality && ValuesEquality;
};

bool ProxyVector::operator!=(const std::vector<float> &InVector) const {
    return !(*this == InVector);
};

float &ProxyVector::operator[](const int idx) {
    assert(idx < data.size());
    return *&data.at(idx);
}

float ProxyVector::operator[](const int idx) const {
    assert(idx < data.size());
    return data.at(idx);
}