#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "termcolor-c/termcolor-c.h"

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

    system("clear");

    fputs("  ", stdout);
    fprintf(text_underline(stdout), "File \"%s\" opened ..\n", file);
    reset_colors(stdout);
}

#ifdef NAJP_HJSON
    void najp_addcomment(const char comment[], najp* object) {
        if (object->d.isubclass) {
            for (int i = 0; i != object->d.parentsubclasses; i++) {
                fprintf(object->json, "\t");
            }
            fprintf(object->json, "\t# %s\n", comment);
        }

        sleep(1);
        fprintf(text_green(stdout), "✓ Comment \"%s\" finished with no errors\n", comment);
        reset_colors(stdout);
    }
#endif

int najp_addstrelement(const char title[], const char value[], najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        sleep(1);
        fprintf(text_red(stdout), "✗ String element \"%s\" finished with one error: NAJP_ELEMENT_LIMIT_REACHED\n", title);
        reset_colors(stdout);

        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ String element \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);
                
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

    if (!object->d.comma) { object->d.comma = true; }
    fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);

    sleep(1);
    fprintf(text_green(stdout), "✓ String element \"%s\" finished with no errors\n", title);
    reset_colors(stdout);
    return NAJP_OK;
}

int najp_addnumelement(const char title[], const double value, najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        sleep(1);
        fprintf(text_red(stdout), "✗ Integer element \"%s\" finished with one error: NAJP_ELEMENT_LIMIT_REACHED\n", title);
        reset_colors(stdout);

        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ Integer element \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);

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

    if (!object->d.comma) { object->d.comma = true; }
    fprintf(object->json, "\t\"%s\" : %f", title, value);

    sleep(1);
    fprintf(text_green(stdout), "✓ Integer element \"%s\" finished with no errors\n", title);
    reset_colors(stdout);
    return NAJP_OK;
}

int najp_addboolelement(const char title[], const bool value, najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        sleep(1);
        fprintf(text_red(stdout), "✗ Boolean element \"%s\" finished with one error: NAJP_ELEMENT_LIMIT_REACHED\n", title);
        reset_colors(stdout);

        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ Boolean element \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);

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

    if (!object->d.comma) { object->d.comma = true; }
    fprintf(object->json, "\t\"%s\" : ", title);
    fprintf(object->json, value ? "true" : "false");

    sleep(1);
    fprintf(text_green(stdout), "✓ Boolean element \"%s\" finished with no errors\n", title);
    reset_colors(stdout);
    return NAJP_OK;
}

int najp_addnullelement(const char title[], najp* object) {
    if (object->d.objects >= NAJP_LIMIT) {
        sleep(1);
        fprintf(text_red(stdout), "✗ Null element \"%s\" finished with one error: NAJP_ELEMENT_LIMIT_REACHED\n", title);
        reset_colors(stdout);

        return NAJP_ELEMENT_LIMIT_REACHED;
    }
    for (int i = 0; i < sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ Null element \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);

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

    sleep(1);
    fprintf(text_green(stdout), "✓ Null element \"%s\" finished with no errors\n", title);
    reset_colors(stdout);

    return NAJP_OK;
}

int najp_addarray(const char title[], najp_array values[], const size_t valuesamt, najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ Array \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);

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
            for (int i = 0; i != object->d.parentsubclasses; i++) {
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
    if (object->d.isubclass) {
        for (int i = 0; i != object->d.parentsubclasses; i++) {
            fprintf(object->json, "\t");
        }
    }
    fprintf(object->json, "\t]");

    sleep(1);
    fprintf(text_green(stdout), "✓ Array \"%s\" finished with no errors\n", title);
    reset_colors(stdout);
    return NAJP_OK;
}

int najp_addsubclass(const char title[], najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++) {
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ Subclass \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);

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
        for (int i = 0; i < object->d.parentsubclasses; i++)
            fprintf(object->json, "\t");
    }

    fprintf(object->json, "\t\"%s\" : {\n", title);
    object->d.parentsubclasses++;
    object->d.isubclass = true;
    object->d.isubclasstart = true;
    object->d.comma = false;

    sleep(1);
    fprintf(text_green(stdout), "✓ Subclass \"%s\" opened with no errors\n", title);
    reset_colors(stdout);
    return NAJP_OK;
}

int najp_closesubclass(najp* object) {
    if (!object->d.isubclass) {
        sleep(1);
        fprintf(text_red(stdout), "✗ Subclass closure finished with one error: NAJP_SUBCLASS_NOT_CURRENT\n");
        reset_colors(stdout);

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

    sleep(1);
    fputs("  ", stdout);
    fputs("File closed ..\n", text_underline(stdout));
    reset_colors(stdout);
    sleep(1);
}
