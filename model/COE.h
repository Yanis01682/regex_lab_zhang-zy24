#ifndef REGEX_LAB_COE_H
#define REGEX_LAB_COE_H

// character or epsilon
struct COE {
    // character when this is not epsilon
    char ch;
    // is this epsilon
    bool ep;

    COE() = default;

    constexpr COE(const char c, const bool b) : ch(c), ep(b) {}

    explicit COE(const char c) : ch(c), ep(false) {}

    COE(const COE &coe) = default;

    COE &operator=(const COE &rhs) = default;

    bool operator==(const COE &other) const {
        if (other.ep) return ep;
        if (ep) return other.ep;
        return ch == other.ch;
    }

    bool operator!=(const COE &other) const {
        if (other.ep) return !ep;
        if (ep) return true;
        return ch != other.ch;
    }

    bool operator<(const COE &other) const {
        if (other.ep) return false;
        if (ep) return true;
        return ch < other.ch;
    }
};

#endif //REGEX_LAB_COE_H
