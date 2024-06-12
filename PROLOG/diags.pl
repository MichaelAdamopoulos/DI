diags(Matrix, DiagsDown, DiagsUp) :-
	diagsDown(Matrix, TempDiagsDown),
	diagsUp(Matrix, TempDiagsUp),
	delete_dummies(TempDiagsDown, DiagsDown),
	delete_dummies(TempDiagsUp, DiagsUp).

diagsDown(Matrix, DiagsDown) :-
	length(Matrix, L),
	Front is L-1,
	Back is 0,
	append_dummies(Matrix, TempDiagsDown, Front, Back),
	matr_transp(TempDiagsDown, DiagsDown).

diagsUp(Matrix, DiagsUp) :-
	reverse(Matrix, RevMatrix),
	diagsDown(RevMatrix, DiagsDown),
	reverseMatrix(DiagsDown, DiagsUp).

reverseMatrix([],[]).
reverseMatrix([FirstLine|RestLines], [RevFirstLine|RevRestLines]) :-
	reverse(FirstLine, RevFirstLine),
	reverseMatrix(RestLines, RevRestLines).

append_dummies([], [], _, _).
append_dummies([FirstLine|RestLines], [NewNewFirstLine|NewRestLines], Front, Back) :-
	append_front(FirstLine, Front, NewFirstLine),
	append_back(NewFirstLine, Back, NewNewFirstLine),
	NewFront is Front-1,
	NewBack is Back+1,
	append_dummies(RestLines, NewRestLines, NewFront, NewBack).

append_front(List, Front, NewList) :-
	Front =:= 0, NewList = List.
append_front(List, Front, NewNewList) :-
	Front =\= 0,
	append([*], List, NewList),
	NewFront is Front-1,
	append_front(NewList, NewFront, NewNewList).

append_back(List, Back, NewList) :-
	Back =:= 0, NewList = List.
append_back(List, Back, NewNewList) :-
	Back =\= 0,
	append(List, [*],NewList),
	NewBack is Back-1,
	append_back(NewList, NewBack, NewNewList).
	
del_first([], [], []).
del_first([[X|L]|R], [X|RX], [L|RL]) :-
   del_first(R, RX, RL).

matr_transp(M, []) :-
   	empty_lists(M).
matr_transp(M, [C|TM]) :-
   	del_first(M, C, RM),
   	matr_transp(RM, TM).

empty_lists([]).
empty_lists([[]|M]) :-
  	empty_lists(M).

delete_dummies([],[]).
delete_dummies([FirstLine|RestLines],[NewFirstLine|NewRestLines]) :-
	delete_all(*, FirstLine, NewFirstLine),
	delete_dummies(RestLines, NewRestLines).

delete_all(_, [], []).
delete_all(Item, [Head|Tail], [Head|NewTail]) :-
	Item \= Head,
	delete_all(Item, Tail, NewTail).
delete_all(Item, [Item|Tail], NewTail) :-
 	delete_all(Item, Tail, NewTail).








	