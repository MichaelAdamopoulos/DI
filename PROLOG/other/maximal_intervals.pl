/* Find the first Te bigger than Ts that is not in list of Ts(S) and remove all Ts less than Te before recursing */ 
maximal_intervals([], [], []).
maximal_intervals([X|_], [], [[X,inf]]).
maximal_intervals([], _, []).
maximal_intervals([Ts|S], E, [[Ts, Te]|I]) :-
    find_te(Ts, E, Te),
    not_member(Te, S),
    remove_lt(Te, S, SR),    
    maximal_intervals(SR, E, I).

/* Find the first element Te bigger than Ts or else return inf */
find_te(_, [], inf).
find_te(Ts, [Te|_], Te) :-
    Te > Ts.
find_te(Ts, [_|Es], Te) :-
    find_te(Ts, Es, Te).

/* Not member */
not_member(_, []).
not_member(X, [L|R]) :-
    X \= L,
    not_member(X, R).

/* Remove all elements from a list [X|L1] than are less than a number N */
remove_lt(_, [], []).
remove_lt(N, [X|L1], [X|L2]) :-
    X >= N,
    remove_lt(N, L1, L2).
remove_lt(N, [X|L1], L2) :-
    X < N,
    remove_lt(N, L1, L2).
