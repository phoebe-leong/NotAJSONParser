#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma once

#define NAJP_OK 0
#define NAJP_TITLE_ALREADY_IN_USE -1
#define NAJP_ELEMENT_LIMIT_REACHED -2

struct najp_data {
    bool istart, isubclass, isubclasstart; 
    int amountofeverything, parentsubclasses;
    const char* titles[1000];
};

typedef struct {
    FILE* json;
    struct najp_data d;
} najp;

typedef struct {
    const char value[101];
    bool valueistring;
} najp_array;

void open(const char file[], najp* object) {
    object->json = fopen(file, "w");

    fprintf(object->json, "{\n");
    object->d.istart = true;
    object->d.amountofeverything = -1;
    object->d.parentsubclasses = -1;
}

/* *cries* Dennis what were you thinking?? Not adding overloaded functions to C!! :0 */
#ifdef __cplusplus
    int addelement(const char title[], const char value[], najp* object) {
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

        fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);
        return NAJP_OK;
    }

    int addelement(const char title[], int value, najp* object) {
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

            fprintf(object->json, "\t\"%s\" : %d", title, value);
        return NAJP_OK;
    }

        int addelement(const char title[], bool value, najp* object) {
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

            fprintf(object->json, "\t\"%s\" : ", title);
            fprintf(object->json, value ? "true" : "false");
        return NAJP_OK;
    }
#else
    int addstrelement(const char title[], const char value[], najp* object) {
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

        fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);
        return NAJP_OK;
    }

    int addnumelement(const char title[], const int value, najp* object) {
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

        fprintf(object->json, "\t\"%s\" : %d", title, value);
        return NAJP_OK;
    }

    int addboolelement(const char title[], const bool value, najp* object) {
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

        fprintf(object->json, "\t\"%s\" : ", title);
        fprintf(object->json, value ? "true" : "false");
        return NAJP_OK;
    }
#endif

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
