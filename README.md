# CampBuilder

The game is simple, you have to fill a camp with some buildings.
There are few buildings (take a look at the var `t_building builds[]` in campbuider.c):
        - foundation
        - wall
        - roof
        - gold_mine
        - statue
        - stone_wall

You can add a custom building by follow the `t_building buids[]` in campbuilder.c

To add building(s), you must write a query with this schematic:

`[building name]: [first abs] [operator] [other num]`

`[building name]` is the name of the building you want to place.
`[first abs]` is the first number you have to give. It also can be the last of a query.
`[operator]` represent the operator you want to use in this list : '->', ',', 'x'
`[other num]` is the other number needed for the query, according to the operator choosen


## How to use operators

### No operator
When there is no operator, you don't need to give an `[other num]`. It will just place a `[building nane]` at given `[first abs]`
Exemple:
    - foundation:1 (will place a foundation at 1)
    - stone_wall:8 (will place a stone_wall at 8)

### '->'
The arrow operator allow you to place `[building name]` from `[first abs]` to `[other num]` included.
Exemple:
    - wall:0->10 (will place a line of wall from 0 to 10 included)
    - wall:4->8  (will place a line of wall from 4 to 8 included)

### ','
The comma operator allow you to give multiple abs in the same query, comma-separrated
Exemple:
    - wall:0,3,4,5 (will place a wall at 0 and 3 and 4 and 5)
    - foundation:0,9 (will place a foundation at 0 and 9)

### 'x'
The time operator allow you to place `[other num]` builds at the same abs (given in `[first abs]`)
Exemple:
    - wall:0x10 (will place 10 wall at 0)
    - wall:5x5 (will place 5 wall at 5)

## Launch the game

If you want to play at CampBuilder, you have to give you permision and exec `./campbuilder [x_max]`.
Where `[x_max]` represent the max abs you can fill with your camp. You cannot change this value during the game.