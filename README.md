My personal collection of useful stuff.

There is no packaging yet. Just copy the files.

Kyrylo, please don't spend another two years on it. Implement only the stuff you really need.

How to use buffers:
```
//The element
struct Entity
{
    int property;
};

//Declare buffer
//Arguments are: actual type, name to use in structures, name to use in function
DECLARE_BUFFER(struct Entity, EntityBuffer, entity_);

//Declare buffer function (in header)
DECLARE_BUFFER_GROW(struct Entity, EntityBuffer, entity_);

//Implement buffer function (in source file)
IMPLEMENT_BUFFER_GROW(struct Entity, EntityBuffer, entity_);
```