:- compile(listpr).
:- compile(diags).

:- lib(ic).

decode([], _, _, _).
decode(_, [], _, _).
decode(_, _, [], _).
decode(_, _, _, []).
decode(Lines, Columns, DiagsDown, DiagsUp) :-
	length(Lines, M),
	length(Columns, N),
	make_matrix(M, N, Matrix),
	Matrix #:: [0,1],
	diags(Matrix, DD, DU),
	restrict_lines(DD, DiagsDown),		% restrict the descending diagonals
	restrict_lines(DU, DiagsUp),		% restrict the ascending diagonals
	restrict_lines(Matrix, Lines),		% restrict the lines
	matr_transp(Matrix, Matrix1),		% transpose the matrix so the columns become the lines
	restrict_lines(Matrix1, Columns),	% in order to restrict them using the previous function	
	matr_transp(Matrix1, Matrix2),		% revert the transposition
	search(Matrix2, 0, input_order, indomain, complete, []),
	prints(Matrix2).

restrict_lines([], _).
restrict_lines(_, []).
restrict_lines([L1|R1], [L2|R2]) :-
	sum(L1) #= L2,
	restrict_lines(R1,R2).

prints([]).
prints([M|R]) :-
	prints_line(M),
	print('\n'),
	prints(R).

prints_line([]).
prints_line([F|R]) :-
	prints_var(F),
	prints_line(R).

prints_var(1) :-
	print(*).
prints_var(0) :-
	print(.).
	