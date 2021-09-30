# Events

## Receiving Events (EventDispatcher)

The helper object responsible for reading and dispatching an event is the `EventDispatcher`.

### Declaration

* Declared in `Keg/src/Core/Event/Event.h`

```clike
class EventDispatcher
	{
	public:
		EventDispatcher(Event& e) // The event recieved in the OnEvent() method.

        /**
        * @input: F& func (The boolean function that should be called when the event type is encountered).
        * @output: bool (Did this method invoktion caused the function invoktion).
        **/
		bool Dispatch(const F& func);
```

### Usage

In this example we will use an EventDispatcher to capture an event of type `KeyPressedEvent`.

In our class:
```clike
class DispatcherExample
{
    bool OnKeyPressedEvent(KeyPressedEvent &e)
    {
        std::cout << `A key was pressed!` << std::endl;
    }

}
void OnEvent(Event &e)
{
    // Step 1: Initialize dispatcher with the desired type and pass the recieved event to it.
    EventDispatcher<KeyPressedEvent> dispatcher(e);

    // Step 2: Call the Dispatch() method and pass a binded function to it, that should be activated iif the event is of type KeyPressedEvent.
    dispatcher.Dispatch(std::bind(&DispatcherExample::OnKeyPressedEvent, this, std::placeholders::_1)); 

}
```

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

    bool IsMinimized() 
}
```
