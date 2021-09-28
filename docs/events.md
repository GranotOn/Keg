# Events

## Key Events

### KeyPressedEvent

```clike
class KeyPressedEvent
{
    KeyCode GetKey(); // Get the keycode
    bool IsRepeated(); // Is press in repeat mode
}
```

### KeyReleasedEvent

```clike
class KeyPressedEvent
{
    KeyCode GetKey(); // Get the keycode
}
```

## Mouse Events

### CursorMovedEvent

```clike
class CursorMovedEvent
{
    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```

### MousePressedEvent

```clike
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

```clike
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

```clike
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

```clike
class CursorEnteredEvent
{
    // Position
    double GetXPosition();
    double GetYPosition();
    std::pair<double, double> GetPosition();
}
```

### CursorLeftEvent

```clike
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

```clike
class WindowCloseEvent
{
    // There aren't any methods here.
    // Generally this will be handled by the engine.
}
```

### WindowResizeEvent

```clike
class WindowResizeEvent
{
    // Measurements
    int GetWidth();
    int GetHeight();
    std::pair<int, int> GetSize();
}
```
