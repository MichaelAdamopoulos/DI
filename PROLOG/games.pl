solve([], _, _, _, [], 0).
solve(_, 0, _, _, [], 0).
solve(_, _, 0, _, [], 0).
solve([Ps|PsR], CT, TT, K, [Gs|GsR], P) :-	% CT = Current Tokens, TT = Total Tokens
	between(1, CT, Gs),
	CT1 is CT-Gs+K,
	minnum(CT1, TT, CT2),
	solve(PsR, CT2, TT, K, GsR, P1),
	P is P1 + Ps*Gs.
	

games(Ps, T, K, Gs, P) :-
	findall(p(Gs, P), solve(Ps, T, T, K, Gs, P), L),
	findmax(L, P),
	member(p(Gs, P), L).
	
minnum(X, Y, X) :- X =< Y.
minnum(X, Y, Y) :- Y < X.

between(LBound, RBound, LBound) :-
    LBound =< RBound. 
between(LBound, RBound, Result) :-
    LBound < RBound,
    NextLBound is LBound + 1,
    between(NextLBound, RBound, Result).

findmax([p(_, P)], P).
findmax([p(_, P1)|L], MaxP) :-
	findmax(L, MaxL),
	maxnum(P1, MaxL, MaxP).

maxnum(X, Y, X) :- X >= Y.
maxnum(X, Y, Y) :- Y > X.
