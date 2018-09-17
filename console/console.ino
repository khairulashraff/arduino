#include <Console.h>

void setup() {
  Bridge.begin();
  Console.begin();

  while (!Console) {
    ; // wait for Console port to connect.
  }

  Console.println("ASCII Table ~ Character Map");
}

int thisByte = 33;
void loop() {
  // prints value unaltered, i.e. the raw binary version of the
  // byte. The Console monitor interprets all bytes as
  // ASCII, so 33, the first number,  will show up as '!'
  Console.write(thisByte);

  Console.print(", dec: ");
  // prints value as string as an ASCII-encoded decimal (base 10).
  // Decimal is the  default format for Console.print() and Console.println(),
  // so no modifier is needed:
  Console.print(thisByte);
  // But you can declare the modifier for decimal if you want to.
  //this also works if you uncomment it:

  // Console.print(thisByte, DEC);

  Console.print(", hex: ");
  // prints value as string in hexadecimal (base 16):
  Console.print(thisByte, HEX);

  Console.print(", oct: ");
  // prints value as string in octal (base 8);
  Console.print(thisByte, OCT);

  Console.print(", bin: ");
  // prints value as string in binary (base 2)
  // also prints ending line break:
  Console.println(thisByte, BIN);

  // if printed last visible character '~' or 126, stop:
  if (thisByte == 126) {    // you could also use if (thisByte == '~') {
    // ensure the latest bit of data is sent
    Console.flush();

    // This loop loops forever and does nothing
    while (true) {
      continue;
    }
  }
  // go on to the next character
  thisByte++;
}
