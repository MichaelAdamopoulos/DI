#!/bin/bash

swipl -q <<EOF

% clean old data
retractall(event(_, _)).
retractall(state(_, _)).
retractall(t_entity(_, _, _)).

% load
['src/cerldi.prolog'].

% run
er('samples/beers/beers.input',
   'output.txt',
   'samples/beers/definitions.prolog',
   10,
   4).

halt.
EOF
