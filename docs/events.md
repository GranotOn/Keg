# Events

## Key Events

### KeyPressedEvent

```cpp
class KeyPressedEvent
{
    KeyCode GetKey(); // Get the keycode
    bool IsRepeated(); // Is press in repeat mode
}
```
### KeyReleasedEvent
```cpp
class KeyPressedEvent
{
    KeyCode GetKey(); // Get the keycode
}
```


## Mouse Events

### CursorMovedEvent
```cpp
class CursorMovedEvent
{
    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```
### MousePressedEvent
```cpp
class MousePressedEvent
{
    MouseCode GetButton(); // Get the mousecode

    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```
### MouseReleasedEvent
```cpp
class MouseReleasedEvent
{
    MouseCode GetButton(); // Get the mousecode

    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```
### MouseScrolledEvent
```cpp
class MouseScrolledEvent
{
    // Offset
    double GetXOffset();
    double GetYOffset();
    std::pair<double, double> GetOffset();

    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```
### CursorEnteredEvent
```cpp
class CursorEnteredEvent
{
    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```
### CursorLeftEvent
```cpp
class CursorLeftEvent
{
    // Last known position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```

## Window Events

### WindowCloseEvent
```cpp
class WindowCloseEvent
{
    // There aren't any methods here.
    // Generally this will be handled by the engine.
}
```
### WindowResizeEvent
```cpp
class WindowResizeEvent
{
    // Measurements
    int GetWidth();
    int GetHeight();
    std::pair<int, int> GetSize();
}
```
