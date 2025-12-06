from random import randrange, choice

letters = ["A", "B", "C", "D", "E", "F"]
numbers = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]

for i in range(100):
    V = letters[0: randrange(2, 7)]
    V.append("S")
    T = numbers[0: randrange(2, 11)]
    P2 = {}
    P1 = {}
    for v in V:
        P2[v] = set()
        P1[v] = set()
    for j in range(randrange(4, 16)):
        a = choice(V)
        b = choice(V)
        P2["S"].add(a + b)
        print(f"S->{a}{b}")
    for j in range(randrange(16, 64)):
        v = choice(V)
        a = choice(V)
        b = choice(V)
        P2[v].add(a + b)
        print(f"{v}->{a}{b}")

    print(f"={i}=")
    for c in V:
        x = choice(T)
        P1[c].add(x)
        print(f"{c}->{x}")
    for j in range(randrange(4, 16)):
        v = choice(V)
        x = choice(T)
        P1[v].add(x)
        print(f"{v}->{x}")
    print(f"={i}=")
    for j in range(20):
        s = "S"
        for k in range(randrange(4, 16)):
            pos = randrange(len(s))
            if len(P2[s[pos]]) == 0:
                continue
            s = s[:pos] + choice(list(P2[s[pos]])) + s[pos + 1:]
        ss = ""
        for c in s:
            ss += choice(list(P1[c]))
        print(ss)
    print(f"={i}=")
