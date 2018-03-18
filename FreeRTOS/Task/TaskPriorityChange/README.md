# TaskPriorityChange Example

> Example 08

Dynamically Changes the priority of Tasks (itself or others)

`vTask1` raises the priority of `vTask2`

`vTask2` reduces its priority by 2 times

```
vTask1 (5) --> vTask2 (6)

vTask2 (4) --> vTask2 (2)

vTask1 (runs again)
```

### Functions Used

`uxTaskPriorityGet() API`

`vTaskPrioritySet() API`

# Important

NOTE: Make sure that you add function calls on top of the C Program otherwise program will be glitchy
