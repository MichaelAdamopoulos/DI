:- lib(ic).
:- lib(branch_and_bound).

games_csp(Ps, T, K, Gs, P) :- 
	length(Ps, L),
	length(Gs, L),
	Gs #:: 1..T,
	constrain(Ps, T, T, K, Gs),
	inn_prod(Ps, Gs, P1),		% inn_prod calculates the pleasure
	P2 #= -P1, 			% we need the negative value to search for the minimum
	bb_min(search(Gs, 0, input_order, indomain, complete, []), 
		P2, bb_options{strategy:restart, solutions:all}),
	P is -P2.			% restore the negative value

constrain([], _, _, _, []).
constrain(_, 0, _, _, []).
constrain(_, _, 0, _, []).
constrain([Ps|PsR], CT, TT, K, [Gs|GsR]) :-	% CT = CurrentTokens, TT = TotalTokens
	Gs #=< CT,
	CT1 #= min(CT-Gs+K, TT),
	constrain(PsR, CT1, TT, K, GsR).
	
inn_prod([], [], 0).
inn_prod([X1|R1], [X2|R2], IP1) :-
   	inn_prod(R1, R2, IP2),
   	IP1 #= IP2 + X1 * X2.
	
