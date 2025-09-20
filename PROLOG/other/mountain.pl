/* True if a list has strictly ascending elements */
ascending([X,Y]) :-
    X < Y.
ascending([X,Y|R]) :-
    X < Y,
    ascending([Y|R]).

/* True if a list has strictly descending elements */
descending([X,Y]) :-
    X > Y.
descending([X,Y|R]) :-
    X > Y,
    descending([Y|R]).

/* For a given list L with size > 2, split it in S - X - R, where X is the possible peak  */
/* If S - X is ascending and X - R is descending, then L is a mountain */
mountain(L) :-
    length(L, Len),
    Len > 2,
    append(S, [X|R], L),
    append(S, [X], Asc),
    ascending(Asc),
    descending([X|R]).