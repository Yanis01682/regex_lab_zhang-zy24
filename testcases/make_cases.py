from random import randrange, shuffle, choice


def make_expression(s: list[str]) -> str:
    exps = []
    for _ in range(0, randrange(1, 15)):
        exps.append([choice(s), "*"])
    while True:
        exp = exps.pop()
        act = choice(["-", "-", "+", "*"])
        if act == "*":
            if exp[1] == "*":
                exp[0] += "*"
            else:
                exp[0] = "(" + exp[0] + ")" + "*"
            exp[1] = "*"
        elif act == "-":
            if len(exps) == 0:
                return exp[0]
            other = exps.pop()
            if exp[1] == "+":
                exp[0] = "(" + exp[0] + ")"
            if other[1] == "+":
                other[0] = "(" + other[0] + ")"
            exp[0] = choice([exp[0] + other[0], other[0] + exp[0]])
            exp[1] = "-"
        elif act == "+":
            if len(exps) == 0:
                return exp[0]
            other = exps.pop()
            exp[0] = choice([exp[0] + "+" + other[0], other[0] + "+" + exp[0]])
            exp[1] = "+"
        exps.append(exp)
        shuffle(exps)


numbers = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "0"]

for i in range(100):
    sigma = numbers[0 : randrange(2, 11)]
    e = make_expression(sigma)
    while "**" in e:
        e = e.replace("**", "*")
    print(e)
    for j in range(100):
        c = ""
        for k in range(randrange(1, 50)):
            c += choice(sigma)
        print(c)
