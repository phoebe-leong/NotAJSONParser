# NotAJSONParser - with handy output to the console
A JSON generator (with console output) written in C compatible with C++.  
I was going to write a JSON parser to go along with it, but I ended up just giving up.

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

#### Note: The console output will only work on POSIX machines.

## Examples

C code:
```c
#include "najp.h"

najp n;
int main() {
  najp_open("test.json", &n);
  najp_addstrelement("Name", "Phoebe", &n);
  najp_addnumelement("Age", 13, &n); /* This also works with booleans */
  
  najp_array languages[] = {{"HTML", true}, {"CSS", true}, {"C++", true}, {"C", true}};
  najp_addarray("Programming Languages Learnt", languages, sizeof(languages) / sizeof(languages[0]), &n);
  
  najp_close(&n);
}
```
C++ code:
```cpp
#include "najp.h"

najp n;
int main() {
  najp_open("test.json", &n);
  najp_addelement("Name", "Phoebe", &n);
  najp_addelement("Age", 13, &n); /* Making use of overloaded functions */
  
  najp_array languages[] = {{"HTML", true}, {"CSS", true}, {"C++", true}, {"C", true}};
  najp_addarray("Programming Languages Learnt", languages, sizeof(languages) / sizeof(languages[0]), &n);
  
  najp_close(&n);
}
```
JSON Output for both:

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
$   F͟i͟l͟e͟ ͟"͟t͟e͟s͟t͟.͟j͟s͟o͟n͟"͟ ͟o͟p͟e͟n͟e͟d͟ ͟.͟.͟
$ ✓ String element "Name" finished with no errors
$ ✓ Integer element "Age" finished with no errors
$ ✓ Array "Programming Languages Learnt" finished with no errors
$   F͟i͟l͟e͟ ͟c͟l͟o͟s͟e͟d͟ ͟.͟.͟
```

Errors will be displayed in red, and successes will be displayed in green.  
Opening and closing of files is coloured normally and underlined.
