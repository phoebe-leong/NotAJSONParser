#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma once

#ifdef __cplusplus
    extern "C" {
#endif

#define NAJP_OK 0
#define NAJP_TITLE_ALREADY_IN_USE -1
#define NAJP_ELEMENT_LIMIT_REACHED -2

struct najp_data {
    bool istart, isubclass, isubclasstart; 
    int amountofeverything, parentsubclasses;
    const char* titles[1000];
};
struct najp {
    FILE* json;
    struct najp_data d;
};
struct najp_array {
    const char value[101];
    bool valueistring;
};

typedef struct najp najp;
typedef struct najp_array najp_array;

void open(const char file[], najp* object) {
    object->json = fopen(file, "w");

    fprintf(object->json, "{\n");
    object->d.istart = true;
    object->d.amountofeverything = -1;
    object->d.parentsubclasses = -1;
}

int addelement(const char title[], const char value[], bool valueistring, najp* object) {
    if (object->d.amountofeverything >= 999)
        return NAJP_ELEMENT_LIMIT_REACHED;
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i])
            return NAJP_TITLE_ALREADY_IN_USE;
    }
    object->d.titles[object->d.amountofeverything + 1] = title;
    object->d.amountofeverything++;
    if (!object->d.istart && !object->d.isubclasstart)
        fprintf(object->json, ",\n");
    if (object->d.isubclass)
        for (int i = 0; i != object->d.parentsubclasses + 1; i++)
            fprintf(object->json, "\t");

    if (object->d.istart)
        object->d.istart = false;
    if (object->d.isubclass && object->d.isubclasstart)
        object->d.isubclasstart = false;

    if (!valueistring)
        fprintf(object->json, "\t\"%s\" : %s", title, value);
    else
        fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);
    return NAJP_OK;
}

int addarray(const char title[], najp_array values[], const size_t valuesamt, najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i])
            return NAJP_TITLE_ALREADY_IN_USE;
    }
    object->d.titles[object->d.amountofeverything + 1] = title;
    object->d.amountofeverything++;

    if (object->d.istart || object->d.isubclasstart) {
        if (object->d.istart)
            object->d.istart = false;
        else
            object->d.isubclasstart = false;
    } else {
        fprintf(object->json, ",\n");
    }
    if (object->d.isubclass)
        fprintf(object->json, "\t");
    fprintf(object->json, "\t\"%s\" : [\n", title);

    for (int i = 0; i != valuesamt; i++) {
        if (i != 0)
            fprintf(object->json, ",\n");
        if (object->d.isubclass)
            fprintf(object->json, "\t");
        if (!values[i].valueistring) {
            fprintf(object->json, "\t\t%s", values[i].value);
        } else {
            fprintf(object->json, "\t\t\"%s\"", values[i].value);
        }
    }
    if (object->d.isubclass)
        fprintf(object->json, "\n\t\t]");
    else
        fprintf(object->json, "\n\t]");
    return NAJP_OK;
}

int addsubclass(const char title[], najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++)
        if (title == object->d.titles[i])
            return NAJP_TITLE_ALREADY_IN_USE;
    if (!object->d.istart && !object->d.isubclasstart)
        fprintf(object->json, ",\n");
    if (object->d.parentsubclasses != -1)
        for (int i = -1; i < object->d.parentsubclasses; i++)
            fprintf(object->json, "\t");
    fprintf(object->json, "\t\"%s\" : {\n", title);

    object->d.parentsubclasses++;
    if (!object->d.isubclass)
        object->d.isubclass = true;
    if (!object->d.isubclasstart)
        object->d.isubclasstart = true;
    return NAJP_OK;
}

void closesubclass(najp* object) {
    fprintf(object->json, "\n");
    for (int i = 0; i != object->d.parentsubclasses; i++)
        fprintf(object->json, "\t");
    fprintf(object->json, "\t}");
    object->d.isubclass = false;
    object->d.parentsubclasses--;
}

void close(const najp* object) {
    fprintf(object->json, "\n}");
    fclose(object->json);
}

#ifdef __cplusplus
    }
#endif