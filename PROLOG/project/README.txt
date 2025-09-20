Για την εκτέλεση τρέχουμε μέσα στο cerldi directory το bash script που δέχεται σαν όρισμα το beers.input, εκτελεί το er* και αποθηκεύει τα αποτελέσματα στο output.txt:

./run.sh

* er('samples/beers/beers.input',
   'output.txt',
   'samples/beers/definitions.prolog',
   10,
   4).