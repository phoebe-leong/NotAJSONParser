#pragma once
#include <stdio.h>
#include <stdbool.h>

#ifdef __cplusplus
    #warning "Use of the C++ variant of NAJP, located at https://github.com/phoebe-leong/NotAJSONParser_cpp, is recommended
#endif

#define NAJP_OK 0
#define NAJP_TITLE_ALREADY_IN_USE -1
#define NAJP_ELEMENT_LIMIT_REACHED -2
#define NAJP_SUBCLASS_NOT_CURRENT -3

#define NAJP_LIMIT 10000

void najp_hjson() {
    #ifdef NAJP_HJSON
        #undef NAJP_HJSON
    #else
        #define NAJP_HJSON
    #endif
}

struct najp_data {
    bool comma, isubclass, isubclasstart;
    int objects, parentsubclasses;
    const char* titles[NAJP_LIMIT + 1];
};

typedef struct {
    const char value[101];
    bool valueistring;
} najp_array;

typedef struct {
    FILE* json;
    struct najp_data d;
} najp;

void najp_open(const char file[], najp* object) {
    object->json = fopen(file, "w");

    fprintf(object->json, "{\n");
    object->d.comma = false;
    object->d.objects = 0;
    object->d.parentsubclasses = 0;
}

#ifdef NAJP_HJSON
    void najp_addcomment(const char comment[], najp* object) {
        if (object->d.isubclass) {
            for (int i = 0; i != object->d.parentsubclasses; i++) {
                fprintf(object->json, "\t");
            }
        }
        fprintf(object->json, "\t# %s\n", comment);
    }
#endif

int najp_addstrelement(const char title[], const char value[], najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            return NAJP_TITLE_ALREADY_IN_USE;
        }
    }

    object->d.titles[object->d.objects] = title;
    object->d.objects++;
    if (object->d.comma) {
        #ifdef NAJP_HJSON
            fprintf(object->json, "\n");
        #else
            fprintf(object->json, ",\n");
        #endif
    }

    if (object->d.isubclass) {
        object->d.isubclasstart = false;
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }

    if (!object->d.comma) {
        object->d.comma = true;
    }
    fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);
    return NAJP_OK;
}

int najp_addnumelement(const char title[], const double value, najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            return NAJP_TITLE_ALREADY_IN_USE;
        }
    }

    object->d.titles[object->d.objects] = title;
    object->d.objects++;
    if (object->d.comma) {
        #ifdef NAJP_HJSON
            fprintf(object->json, "\n");
        #else
            fprintf(object->json, ",\n");
        #endif
    }

    if (object->d.isubclass) {
        object->d.isubclasstart = false;
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }

    if (!object->d.comma) {
        object->d.comma = true;
    }

    fprintf(object->json, "\t\"%s\" : %f", title, value);
    return NAJP_OK;
}

int najp_addboolelement(const char title[], const bool value, najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            return NAJP_TITLE_ALREADY_IN_USE;
        }
    }

    object->d.titles[object->d.objects] = title;
    object->d.objects++;
    if (object->d.comma) {
        #ifdef NAJP_HJSON
            fprintf(object->json, "\n");
        #else
            fprintf(object->json, ",\n");
        #endif
    }
    
    if (object->d.isubclass) {
        object->d.isubclasstart = false;
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }

    if (!object->d.comma) {
        object->d.comma = true;
    }

    fprintf(object->json, "\t\"%s\" : ", title);
    fprintf(object->json, value ? "true" : "false");
    return NAJP_OK;
}

int najp_addnullelement(const char title[], najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i < sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            return NAJP_TITLE_ALREADY_IN_USE;
        }
    }

    object->d.titles[object->d.objects] = title;
    object->d.objects++;
    if (object->d.comma) {
        #ifdef NAJP_HJSON
            fprintf(object->json, "\n");
        #else
            fprintf(object->json, ",\n");
        #endif
    } else {
        object->d.comma = true;
    }

    if (object->d.isubclass) {
        object->d.isubclasstart = false;
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }
    fprintf(object->json, "\t\"%s\" : null", title);
    return NAJP_OK;
}

int najp_addarray(const char title[], najp_array values[], const size_t valuesamt, najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            return NAJP_TITLE_ALREADY_IN_USE;
        }
    }

    object->d.titles[object->d.objects] = title;
    object->d.objects++;

    if (!object->d.comma) {
        object->d.comma = true;
    } else {
        #ifdef NAJP_HJSON
            fprintf(object->json, "\n");
        #else
            fprintf(object->json, ",\n");
        #endif
    }

    if (object->d.isubclass) {
        object->d.isubclasstart = false;
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }
    fprintf(object->json, "\t\"%s\" : [\n", title);

    for (int i = 0; i != valuesamt; i++) {
        if (i != 0) {
            #ifdef NAJP_HJSON
                fprintf(object->json, "\n");
            #else
                fprintf(object->json, ",\n");
            #endif
        }
        
        if (object->d.isubclass) {
            for (int j = 0; j != object->d.parentsubclasses; j++) {
                fprintf(object->json, "\t");
            }
        }
        if (!values[i].valueistring) {
            fprintf(object->json, "\t\t%s", values[i].value);
        } else {
            fprintf(object->json, "\t\t\"%s\"", values[i].value);
        }
    }
    fprintf(object->json, "\n");
    if (object->d.isubclass)
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    fprintf(object->json, "\t]");
    return NAJP_OK;
}

int najp_addsubclass(const char title[], najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            return NAJP_TITLE_ALREADY_IN_USE;
        }
    }

    if (object->d.comma) {
        #ifdef NAJP_HJSON
            fprintf(object->json, "\n");
        #else
            fprintf(object->json, ",\n");
        #endif
    }
    if (object->d.parentsubclasses != 0) {
        for (int i = 0; i < object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }
    fprintf(object->json, "\t\"%s\" : {\n", title);

    object->d.parentsubclasses++;
    object->d.isubclass = true;
    object->d.isubclasstart = true;
    object->d.comma = false;
    return NAJP_OK;
}

int najp_closesubclass(najp* object) {
    if (!object->d.isubclass) {
        return NAJP_SUBCLASS_NOT_CURRENT;
    } else if (!object->d.isubclasstart) {
        fprintf(object->json, "\n");
    }
    for (int i = 0; i < object->d.parentsubclasses - 1; i++) {
        fprintf(object->json, "\t");
    }
    fprintf(object->json, "\t}");
    if (object->d.parentsubclasses == 0) {
        object->d.isubclass = false;
    }
    object->d.isubclasstart = false;
    object->d.parentsubclasses--;

    return NAJP_OK;
}

void najp_close(const najp* object) {
    fprintf(object->json, "\n}");
    fclose(object->json);
}
