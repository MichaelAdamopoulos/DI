/* Remove elements of E that exist in S and call the helper function */
/* After that clear list I of elements [[], _] which are created when no Ts is found */
seq(S, E, I) :-
    remove_equals(S, E, E1),
    seq_helper(S, E1, I1),
    remove_empty(I1, I).

/* For each Te find the immediate previous Ts, remove lower Ts, insert pair and recurse */
seq_helper(_, [], []).  
seq_helper([], _, []).  
seq_helper(S, [Te|E], [[Ts, Te]|I]) :- 
    find_ts(S, Te, Ts),
    remove_le(Ts, S, SR),   
    seq_helper(SR, E, I).                  

/* Not member */
not_member(_, []).
not_member(X, [L|R]) :-
    X \= L,
    not_member(X, R).

/* For a given number X and an ascending list find the last element Y of the list that Y < X else return [] */
find_ts([], _, []).
find_ts([L|R], X, Y) :- 
    L < X, 
    find_ts_helper(R, X, L, Y).
find_ts([_|R], X, []) :-
    find_ts(R, X, []).

/* Helper function in order to maintain the last checked element */
find_ts_helper([L|R], X, _, Y) :- 
    L < X, 
    find_ts_helper(R, X, L, Y).
find_ts_helper([L|_], X, Y, Y) :- 
    L >= X.
find_ts_helper([], _, Y, Y).  

/* Remove all elements from a list [X|L1] than are less or equal than a number N */
remove_le([], _, _).
remove_le(_, [], []).
remove_le(N, [X|L1], L2) :-
    X =< N,
    remove_le(N, L1, L2).
remove_le(N, [X|L1], [X|L2]) :-
    X > N,
    remove_le(N, L1, L2).

/* Remove all elements from a list L2 that exist in L1 */
remove_equals(_, [], []).  
remove_equals(L1, [X|L2], L) :-  
    member(X, L1),  
    remove_equals(L1, L2, L).  
remove_equals(L1, [X|L2], [X|L]) :-  
    not_member(X, L1),  
    remove_equals(L1, L2, L).

/* Remove all elements of a list of type: [[], _] */
remove_empty([], []).
remove_empty([[[], _]|R], L) :-
    remove_empty(R, L).
remove_empty([X|R], [X|L]) :-
    remove_empty(R, L).


