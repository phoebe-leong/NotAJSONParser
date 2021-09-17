#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#pragma once

#define NAJP_OK 0
#define NAJP_TITLE_ALREADY_IN_USE -1
#define NAJP_ELEMENT_LIMIT_REACHED -2

#define NAJP_LIMIT 10000

struct najp_data {
    bool comma, isubclass, isubclasstart;
    int objects, parentsubclasses;
    const char* titles[NAJP_LIMIT + 1];
};

typedef struct {
    FILE* json;
    struct najp_data d;
} najp;

typedef struct {
    const char value[101];
    bool valueistring;
} najp_array;

void najp_open(const char file[], najp* object) {
    object->json = fopen(file, "w");

    fprintf(object->json, "{\n");
    object->d.comma = false;
    object->d.objects = 0;
    object->d.parentsubclasses = 0;
}

#ifdef __cplusplus
    int najp_addelement(const char title[], const char value[], najp* object) {
        if (object->d.objects >= NAJP_LIMIT)
            return NAJP_ELEMENT_LIMIT_REACHED;
        for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
            if (title == object->d.titles[i])
                return NAJP_TITLE_ALREADY_IN_USE;
        }
        object->d.titles[object->d.objects] = title;
        object->d.objects++;
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses; i++)
                fprintf(object->json, "\t");
        }

        fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);
        return NAJP_OK;
    }

    int najp_addelement(const char title[], int value, najp* object) {
        if (object->d.objects >= NAJP_LIMIT - 1)
            return NAJP_ELEMENT_LIMIT_REACHED;
        for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
            if (title == object->d.titles[i])
                return NAJP_TITLE_ALREADY_IN_USE;
        }
        object->d.titles[object->d.objects] = title;
        object->d.objects++;
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses + 1; i++)
                fprintf(object->json, "\t");
        }

            fprintf(object->json, "\t\"%s\" : %d", title, value);
        return NAJP_OK;
    }

        int najp_addelement(const char title[], bool value, najp* object) {
        if (object->d.objects >= NAJP_LIMIT)
            return NAJP_ELEMENT_LIMIT_REACHED;
        for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
            if (title == object->d.titles[i])
                return NAJP_TITLE_ALREADY_IN_USE;
        }
        object->d.titles[object->d.objects] = title;
        object->d.objects++;
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses; i++)
                fprintf(object->json, "\t");
        }

            fprintf(object->json, "\t\"%s\" : ", title);
            fprintf(object->json, value ? "true" : "false");
        return NAJP_OK;
    }
#else
    int najp_addstrelement(const char title[], const char value[], najp* object) {
        if (object->d.objects >= NAJP_LIMIT)
            return NAJP_ELEMENT_LIMIT_REACHED;
        for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
            if (title == object->d.titles[i])
                return NAJP_TITLE_ALREADY_IN_USE;
        }
        object->d.titles[object->d.objects] = title;
        object->d.objects++;
        if (object->d.comma)
            fprintf(object->json, ",\n");
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses; i++)
                fprintf(object->json, "\t");
        }

        if (!object->d.comma)
            object->d.comma = true;

        fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);
        return NAJP_OK;
    }

    int najp_addnumelement(const char title[], const int value, najp* object) {
        if (object->d.objects >= NAJP_LIMIT)
            return NAJP_ELEMENT_LIMIT_REACHED;
        for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
            if (title == object->d.titles[i])
                return NAJP_TITLE_ALREADY_IN_USE;
        }
        object->d.titles[object->d.objects] = title;
        object->d.objects++;
        if (object->d.comma)
            fprintf(object->json, ",\n");
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses; i++)
                fprintf(object->json, "\t");
        }

        if (!object->d.comma)
            object->d.comma = true;

        fprintf(object->json, "\t\"%s\" : %d", title, value);
        return NAJP_OK;
    }

    int najp_addboolelement(const char title[], const bool value, najp* object) {
        if (object->d.objects >= NAJP_LIMIT)
            return NAJP_ELEMENT_LIMIT_REACHED;
        for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
            if (title == object->d.titles[i])
                return NAJP_TITLE_ALREADY_IN_USE;
        }
        object->d.titles[object->d.objects] = title;
        object->d.objects++;
        if (object->d.comma)
            fprintf(object->json, ",\n");
        if (object->d.isubclass) {
            object->d.isubclasstart = false;
            for (int i = 0; i != object->d.parentsubclasses; i++)
                fprintf(object->json, "\t");
        }

        if (!object->d.comma)
            object->d.comma = true;

        fprintf(object->json, "\t\"%s\" : ", title);
        fprintf(object->json, value ? "true" : "false");
        return NAJP_OK;
    }
#endif

int najp_addarray(const char title[], najp_array values[], const size_t valuesamt, najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i])
            return NAJP_TITLE_ALREADY_IN_USE;
    }
    object->d.titles[object->d.objects] = title;
    object->d.objects++;

    if (!object->d.comma) {
        object->d.comma = true;
    } else {
        fprintf(object->json, ",\n");
    }
    if (object->d.isubclass) {
        object->d.isubclasstart = false;
        fprintf(object->json, "\t");
    }
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

int najp_addsubclass(const char title[], najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++)
        if (title == object->d.titles[i])
            return NAJP_TITLE_ALREADY_IN_USE;
    if (object->d.comma)
        fprintf(object->json, ",\n");
    if (object->d.parentsubclasses != 0)
        for (int i = 0; i < object->d.parentsubclasses; i++)
            fprintf(object->json, "\t");
    fprintf(object->json, "\t\"%s\" : {\n", title);

    object->d.parentsubclasses++;
    object->d.isubclass = true;
    object->d.isubclasstart = true;
    object->d.comma = false;
    return NAJP_OK;
}

void najp_closesubclass(najp* object) {
    if (!object->d.isubclasstart)
        fprintf(object->json, "\n");
    for (int i = 0; i < object->d.parentsubclasses - 1; i++)
        fprintf(object->json, "\t");
    fprintf(object->json, "\t}");
    object->d.isubclass = false;
    object->d.isubclasstart = false;
    object->d.parentsubclasses--;
}

void najp_close(const najp* object) {
    fprintf(object->json, "\n}");
    fclose(object->json);
}
