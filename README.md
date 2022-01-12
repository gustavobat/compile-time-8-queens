# compile-time-8-queens
Solve the 8 queens puzzle at compile time

This program uses a backtracking algorithm to find the following solution to the 8-queens puzzle at compile time:

|  -  |    a    |    b    |    c    |    d    |    e    |    f    |    g    |    h    |
| :-: |   :-:   |   :-:   |   :-:   |   :-:   |   :-:   |   :-:   |   :-:   |   :-:   |
|**8**| :crown: |    -    |    -    |    -    |    -    |    -    |    -    |    -    |
|**7**|    -    |    -    |    -    |    -    |    -    |    -    | :crown: |    -    |
|**6**|    -    |    -    |    -    |    -    | :crown: |    -    |    -    |    -    |
|**5**|    -    |    -    |    -    |    -    |    -    |    -    |    -    | :crown: |
|**4**|    -    | :crown: |    -    |    -    |    -    |    -    |    -    |    -    |
|**3**|    -    |    -    |    -    | :crown: |    -    |    -    |    -    |    -    |
|**2**|    -    |    -    |    -    |    -    |    -    | :crown: |    -    |    -    |
|**1**|    -    |    -    | :crown: |    -    |    -    |    -    |    -    |    -    |

## TODO
- [ ] Find *all* solutions. More solutions can be found by tweaking the algorithm a little bit, but we need a fixed-size container to store them.
- [ ] Comment code
