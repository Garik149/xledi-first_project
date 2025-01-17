#ifndef DEFINES_H
#define DEFINES_H

#include <qdebug.h>

#define RESULT_ERROR 1
#define RESULT_SUCCESS 0
#define GRID_SZ 20

#define DARK_BLUE 20,40,120
#define BLUE 40,100,200
#define LIGHT_BLUE 70,160,240
#define DARK_RED 130,40,10
#define RED 230,90,80
#define DARK_GREEN 15,80,10
#define GREEN 50,210,20
#define WHITE 255,255,255
#define CYAN 20,150,180

#define DELETE(a) {delete(a); a = NULL;}

class LEData;
class LEShape;
struct PortData;
class PortShape;
struct WireData;
class WireShape;
class WireSeg;
class WireNode;
class LEdiScene;
class LEdiView;
class Locale;
enum State {Default, Bolded, Moved, DrawingWire, PlacingLE};

#endif // DEFINES_H
