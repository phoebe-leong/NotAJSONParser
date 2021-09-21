# NotAJSONParser - with handy output to the console
A JSON generator (with console output) written in C.  

This branch would be good for developing, but is not actually intended to be used in production.   
Having the console output to analyse is much more handy in comparison to this:
```c
if (najp_addelement("ElementTitle", "ElementValue", &n) != NAJP_OK) {
	printf("Didn't work\n");
} else {
	printf("Worked\n");
}
```
The two branches function the same, one simply outputs its status to the console, and the other doesn't.

#### Note: This branch will only work on POSIX machines.

## Example

```c
#include "najp.h"

najp n;
int main() {
  najp_open("test.json", &n);
  najp_addstrelement("Name", "Phoebe", &n);
  najp_addnumelement("Age", 13, &n); /* This also works with booleans */
  najp_addnumelement("Age", 14, &n);
  
  najp_array languages[] = {{"HTML", true}, {"CSS", true}, {"C++", true}, {"C", true}};
  najp_addarray("Programming Languages Learnt", languages, sizeof(languages) / sizeof(languages[0]), &n);
  
  najp_close(&n);
}
```

JSON Output:

```json
{
	"Name" : "Phoebe",
	"Age" : 13,
	"Programming Languages Learnt" : [
		"HTML",
		"CSS",
		"C++",
		"C"
	]
}
```
Console output:
```
$   File "test.json" opened ..
$ ✓ String element "Name" finished with no errors
$ ✓ Integer element "Age" finished with no errors
$ ✗ Integer element "Age" finished with one error: NAJP_TITLE_ALREADY_IN_USE
$ ✓ Array "Programming Languages Learnt" finished with no errors
$   File closed ..
```

Errors will be displayed in red, and successes will be displayed in green.  
Opening and closing of files is coloured normally and underlined.
