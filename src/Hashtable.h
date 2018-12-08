//
// Created by garri1105 on 12/7/18.
//

#ifndef PAC_SPHERE_HASHTABLE_H
#define PAC_SPHERE_HASHTABLE_H

#include <stdio.h>

class Hashtable {

public:
    std::unordered_map<const void *, const void *> htmap;

    void put(const void *key, const void *value) {
        htmap[key] = value;
    }

    const void *get(const void *key) {
        return htmap[key];
    }

};
#endif //PAC_SPHERE_HASHTABLE_H
