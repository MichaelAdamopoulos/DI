 % given the name of an event/state (X), 
% level should return the level of X
% e.g. an event that depends only on 
% input events should have level 0

% user
level(X, L):-
    t_entity(X, _, user),
    definition_conditions(X, XL),
    formula_level(XL, L).

% input
formula_level(X, L):-
    t_entity(X, _, input),
    L is 0.

% and
formula_level(and(X,Y), L):-
    formula_level(X, L1),
    formula_level(Y, L2),
    max(L1, L2, L3),
    L is L3 + 1.

% or
formula_level(or(X,Y), L):-
    formula_level(X, L1),
    formula_level(Y, L2),
    max(L1, L2, L3),
    L is L3 + 1.

% tnot
formula_level(tnot(X), L):-
    formula_level(X, L1),
    L is L1 + 1.

% start
formula_level(start(X), L):-
    level(X, L1),
    L is L1 + 1.

% end
formula_level(end(X), L):-
    level(X, L1),
    L is L1 + 1.

% ~>
formula_level(~>(X,Y), L):-
    formula_level(X, L1),
    formula_level(Y, L2),
    max(L1, L2, L3),
    L is L3 + 1.

% union
formula_level(union(X,Y), L):-
    level(X, L1),
    level(Y, L2),
    max(L1, L2, L3),
    L is L3 + 1.

% intersection
formula_level(intersection(X,Y), L):-
    level(X, L1),
    level(Y, L2),
    max(L1, L2, L3),
    L is L3 + 1.

% minus
formula_level(minus(X,Y), L):-
    level(X, L1),
    level(Y, L2),
    max(L1, L2, L3),
    L is L3 + 1.




