/*
NEVER FORGET TO:
    Look at the problem's constraints before coding.
How to cheese cf:
    Find a lower bound or upper bound for the problem. Have faith that it is the answer of the problem.
    If it isn't the answer, have more faith or change to another bound god by looking for a better bound.

    Trust guesses. Who has time to think? If people in div2 AC the problem it requires no proof since people don't prove things.

    You must draw cases. Thinking gets you nowhere, so draw cases and reach illogical conclusions from them.
    Sometimes drawing cases is bad because it takes too much time. Faster is to not think at all and just code a bruteforce solution.
    This is called "law of small numbers". If something works for small numbers, surely it works for big numbers.
    https://en.wikipedia.org/wiki/Faulty_generalization#Hasty_generalization don't mind the "faulty" part of it, in competitive programming mistakes are lightly punished
    Don't think about them being right or not, cf is a battle of intuition only.

    Be as stupid as possible in implementation. Trying to be smart is an easy way to get WA.

    Think about 2x2 cases for matrix problems and hope that everything works for the general case.

    Find a necessary condition and trust it to be sufficient. They're basically the same thing.

    Heuristics might speed up your code. Forget about complexity, it's only about ACing and not proving that your solution is good.

    For paths in a grid starting at (1, i) or something like that, assume that they never cross and do D&C

    Consider doing problems in reverse order of queries/updates

    For combinatorics problems, consider symmetry

General strategy (MUST DO):
    Try to solve the problem with more restricted constraints.

About testing:
    Test n=1, a[i]=1, a[i]=n, etc. Basically, test low values. No need to test if pretests are strong, but if you get WA it's good.

This isn't a joke. Do it if you get stuck. It's shit practice in my opinion, but do it if you want AC.
*/
