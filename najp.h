#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "termcolor-c/termcolor-c.h"
#include <unistd.h>

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

    system("clear");

    fputs("  ", stdout);
    fprintf(text_underline(stdout), "File \"%s\" opened ..\n", file);
    reset_colors(stdout);
}

#ifdef __cplusplus
    int najp_addelement(const char title[], const char value[], najp* object) {
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
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses; i++)
                fprintf(object->json, "\t");
        }

        fprintf(object->json, "\t\"%s\" : \"%s\"", title, value);

        sleep(1);
        fprintf(text_green(stdout), "✓ String element \"%s\" finished with no errors\n", title);
        reset_colors(stdout);
        return NAJP_OK;
    }

    int najp_addelement(const char title[], int value, najp* object) {
        if (object->d.objects >= NAJP_LIMIT - 1) {
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
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
        if (object->d.isubclass) {
            object->d.isubclasstart = false;

            for (int i = 0; i != object->d.parentsubclasses + 1; i++)
                fprintf(object->json, "\t");
        }

            fprintf(object->json, "\t\"%s\" : %d", title, value);

        sleep(1);
        fprintf(text_green(stdout), "✓ Integer element \"%s\" finished with no errors\n", title);
        reset_colors(stdout);
        return NAJP_OK;
    }

        int najp_addelement(const char title[], bool value, najp* object) {
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

        sleep(1);
        fprintf(text_green(stdout), "✓ Boolean element \"%s\" finished with no errors\n", title);
        reset_colors(stdout);
        return NAJP_OK;
    }

    int najp_addelement(const char title[], najp* object) {
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
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
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
#else
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

        sleep(1);
        fprintf(text_green(stdout), "✓ String element \"%s\" finished with no errors\n", title);
        reset_colors(stdout);
        return NAJP_OK;
    }

    int najp_addnumelement(const char title[], const int value, najp* object) {
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
        if (object->d.comma)
            fprintf(object->json, ",\n");
        else object->d.comma = true;
        if (object->d.isubclass) {
            object->d.isubclasstart = false;
            for (int i = 0; i != object->d.parentsubclasses; i++) {
                fprintf(object->json, "\t");
            }
        }
        fprintf(object->json, "\"%s\" : null", title);

        sleep(1);
        fprintf(text_green(stdout), "✓ Null element \"%s\" finished with no errors\n", title);
        reset_colors(stdout);

        return NAJP_OK;
    }
#endif

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

    sleep(1);
    fprintf(text_green(stdout), "✓ Array \"%s\" finished with no errors\n", title);
    reset_colors(stdout);
    return NAJP_OK;
}

int najp_addsubclass(const char title[], najp* object) {
    for (int i = 0; i != sizeof(object->d.titles) / sizeof(object->d.titles[0]); i++)
        if (title == object->d.titles[i]) {
            sleep(1);
            fprintf(text_red(stdout), "✗ Subclass \"%s\" finished with one error: NAJP_TITLE_ALREADY_IN_USE\n", title);
            reset_colors(stdout);

            return NAJP_TITLE_ALREADY_IN_USE;
        }
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

    sleep(1);
    fprintf(text_green(stdout), "✓ Subclass \"%s\" opened with no errors\n", title);
    reset_colors(stdout);
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

    sleep(1);
    fputs("  ", stdout);
    fputs("File closed ..\n", text_underline(stdout));
    reset_colors(stdout);
    sleep(1);
}
