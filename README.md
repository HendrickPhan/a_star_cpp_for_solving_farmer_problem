# How To build:
```
mkdir build
cd build
cmake ..
make
```

# How to run:
`./main`

# Prolog Code:
```
/* DFS algo */
dfs(X, P, [X|P]) :- goal(X),!.
dfs(X, P, Path) :- edge(X, Y), X\=Y, \+member(Y,P), dfs(Y, [X|P], Path).

/* goal */
goal([1,1,1,1]).

/* actions */
moveGoatRight([_, X, Y, _], [1, X, Y, 1]).
moveGoatLeft([_, X, Y, _], [0, X, Y, 0]).
moveWolfRight([X, _, Y, _], [X, 1, Y, 1]).
moveWolfLeft([X, _, Y, _], [X, 0, Y, 0]).
moveCabbageRight([X, Y, _, _], [X, Y, 1, 1]).
moveCabbageLeft([X, Y, _, _], [X, Y, 0, 0]).
moveBoatRight([X, Y, Z, _], [X, Y, Z, 1]).
moveBoatLeft([X, Y, Z, _], [X, Y, Z, 0]).

/* checkers */
wolfEatGoat([A, B, _, D]) :- A=:=B, D\=A.
goatEatCabbage([A, _, C, D]) :- A=:=C, D\=A.

boatAtRight([_,_,_,1]).
boatAtLeft([_,_,_,0]).

goatAtRight([1,_,_,_]).
goatAtLeft([0,_,_,_]).

wolfAtRight([_,1,_,_]).
wolfAtLeft([_,0,_,_]).

cabbageAtRight([_,_,1,_]).
cabbageAtLeft([_,_,0,_]).

/* edge */
edge(X, Y) :- transit(X, Y).

transit(X, Y) :- moveGoatRight(X, Y), goatAtLeft(X), boatAtLeft(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveGoatLeft(X, Y), goatAtRight(X), boatAtRight(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveWolfRight(X, Y), wolfAtLeft(X), boatAtLeft(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveWolfLeft(X, Y), wolfAtRight(X), boatAtRight(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveCabbageRight(X, Y), cabbageAtLeft(X), boatAtLeft(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveCabbageLeft(X, Y), cabbageAtRight(X), boatAtRight(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveBoatRight(X, Y), boatAtLeft(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
transit(X, Y) :- moveBoatLeft(X, Y), boatAtRight(X),\+wolfEatGoat(Y), \+goatEatCabbage(Y).
```

# Prolog Query:
`dfs([0,0,0,0], [], P).`