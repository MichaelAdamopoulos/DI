
max(X,Y,X):-X>=Y,!.
max(_,Y,Y).

all_between(Min,Max,L):- findall(X, between(Min, Max, X), L).

assert_if_not_exists(X):-
    X-> true ; assertz(X).
