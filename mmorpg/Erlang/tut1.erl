-module(tut1).
-export([double/1,fact/1]).

double(X)->
    2 * X.

fact(N) when N > 0 ->
    N * fact(N - 1);
fact(0) ->
    1.