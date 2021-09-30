# Layers

Layers are objects that have engine life-cycle hooks such as `OnEvent(Event &e)` and `OnUpdate()`.

## LayerStack

* Defined in `Keg/src/Core/Layer/LayerStack.h`

The `LayerStack` is a std::vector-like data structure containing `Layer*` objects. An `Application` object holds a `LayerStack` as a protected field.

The `LayerStack` differntiats between a layer and an overlay. A layer gets his `OnUpdate()` method called first (The lowest layers should be the more responsive layers), but an overlay gets events first (A UI button should get precedence over the actual game).

```clike
class LayerStack
{
    void AddLayer(Layer *layer);
    void RemoveLayer(Layer *layer);
    void AddOverlay(Layer *layer);
    void RemoveOverlay(); // Always pops the back layer.

    // LayerStack also supports ranged-based for loops.
}
```

## Layer

* Defined in `Keg/src/Core/Layer/Layer.h`

The `Layer` object is an object that has life-cycle hooks. Examples for a layer: `EditorLayer`, `UILayer`, `ProfilerLayer` and more.

```clike
class Layer
{
        void OnAttach() // When added to a LayerStack object.
		void OnDetach() // When removed from a layerstack object.
		void OnUpdate() // Every frame.
		void OnEvent(Event &e) // Every event.

        std::string GetDebugName(); // Only in DEBUG mode (macro: KEG_DEBUG).
}
```


 