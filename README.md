# NotAJSONParser
A JSON generator written in C compatible with C++.  
I was going to write a JSON parser to go along with it, but I ended up just giving up.

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
Output for both (with better spacing, GitHub formatting is weird 😔 ):

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
