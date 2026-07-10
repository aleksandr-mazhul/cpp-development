#!/usr/bin/env python3
"""Generate graphviz flowcharts and lab4 chart for the practice report."""

from __future__ import annotations

from pathlib import Path

from graphviz import Digraph, Graph

ASSETS = Path(__file__).resolve().parent.parent / "tmp" / "report_assets"
ASSETS.mkdir(parents=True, exist_ok=True)

FONT = "Arial"


def _new(name: str, rankdir: str = "TB") -> Digraph:
    g = Digraph(name=name, format="png")
    g.attr(
        rankdir=rankdir,
        bgcolor="white",
        splines="polyline",
        nodesep="0.35",
        ranksep="0.55",
        pad="0.2",
    )
    g.attr(
        "node",
        fontname=FONT,
        fontsize="11",
        color="#1f2937",
        fillcolor="#f3f4f6",
        style="filled",
    )
    g.attr("edge", fontname=FONT, fontsize="10", color="#1f2937")
    return g


def _terminator(g, name, label):
    g.node(name, label=label, shape="ellipse", fillcolor="#bbf7d0", color="#166534")


def _process(g, name, label):
    g.node(name, label=label, shape="box", fillcolor="#dbeafe", color="#1e3a8a")


def _decision(g, name, label):
    g.node(name, label=label, shape="diamond", fillcolor="#fef3c7", color="#92400e")


def _io(g, name, label):
    g.node(name, label=label, shape="parallelogram", fillcolor="#e9d5ff", color="#6b21a8")


def _render(g, filename: str) -> Path:
    out = ASSETS / filename
    g.render(str(out.with_suffix("")), cleanup=True)
    return out


def lab1_findAnswer():
    g = _new("lab1_findAnswer")
    _terminator(g, "s", "Начало findAnswer")
    _process(g, "init", "found = false\nanswer = 0\nptr = array")
    _decision(g, "cond", "ptr < array + size ?")
    _decision(g, "suit", "isSuitable(*ptr) ?")
    _decision(g, "cmp", "!found || *ptr > answer ?")
    _process(g, "upd", "answer = *ptr\nfound = true")
    _process(g, "next", "++ptr")
    _decision(g, "ret", "found ?")
    _io(g, "ret_val", "return answer")
    _io(g, "ret_none", "return -1")
    _terminator(g, "e", "Конец")

    g.edge("s", "init")
    g.edge("init", "cond")
    g.edge("cond", "suit", label=" Да")
    g.edge("cond", "ret", label=" Нет")
    g.edge("suit", "cmp", label=" Да")
    g.edge("suit", "next", label=" Нет")
    g.edge("cmp", "upd", label=" Да")
    g.edge("cmp", "next", label=" Нет")
    g.edge("upd", "next")
    g.edge("next", "cond")
    g.edge("ret", "ret_val", label=" Да")
    g.edge("ret", "ret_none", label=" Нет")
    g.edge("ret_val", "e")
    g.edge("ret_none", "e")
    return _render(g, "lab1_findAnswer")


def lab1_getMinDigit():
    g = _new("lab1_getMinDigit")
    _terminator(g, "s", "Начало getMinDigit(number)")
    _process(g, "init", "minDigit = 9")
    _decision(g, "cond", "number > 0 ?")
    _process(g, "d", "digit = number % 10")
    _decision(g, "less", "digit < minDigit ?")
    _process(g, "upd", "minDigit = digit")
    _process(g, "div", "number /= 10")
    _io(g, "ret", "return minDigit")
    _terminator(g, "e", "Конец")

    g.edge("s", "init")
    g.edge("init", "cond")
    g.edge("cond", "d", label=" Да")
    g.edge("cond", "ret", label=" Нет")
    g.edge("d", "less")
    g.edge("less", "upd", label=" Да")
    g.edge("less", "div", label=" Нет")
    g.edge("upd", "div")
    g.edge("div", "cond")
    g.edge("ret", "e")
    return _render(g, "lab1_getMinDigit")


def lab1_isSuitable():
    g = _new("lab1_isSuitable")
    _terminator(g, "s", "Начало isSuitable(number)")
    _process(g, "min", "minD = getMinDigit(number)")
    _process(g, "max", "maxD = getMaxDigit(number)")
    _decision(g, "sum", "(minD + maxD) % 2 == 0 ?")
    _io(g, "t", "return true")
    _io(g, "f", "return false")
    _terminator(g, "e", "Конец")

    g.edge("s", "min")
    g.edge("min", "max")
    g.edge("max", "sum")
    g.edge("sum", "t", label=" Да")
    g.edge("sum", "f", label=" Нет")
    g.edge("t", "e")
    g.edge("f", "e")
    return _render(g, "lab1_isSuitable")


def lab2_findTargetRow():
    g = _new("lab2_findTargetRow")
    _terminator(g, "s", "Начало findTargetRow(outCount)")
    _process(g, "init", "outCount = 0\ntarget = nullptr\nrp = rowPtrs")
    _decision(g, "cond", "rp < rowPtrs + rowCount ?")
    _decision(g, "desc", "isDescending(*rp) ?")
    _process(g, "cnt", "cnt = countEvenMinDigit(*rp)")
    _decision(g, "ok", "cnt > 0 &&\ncnt >= outCount ?")
    _process(g, "upd", "outCount = cnt\ntarget = rp")
    _process(g, "next", "++rp")
    _decision(g, "null", "target == nullptr ?")
    _process(g, "zero", "outCount = 0")
    _io(g, "ret", "return target")
    _terminator(g, "e", "Конец")

    g.edge("s", "init")
    g.edge("init", "cond")
    g.edge("cond", "desc", label=" Да")
    g.edge("cond", "null", label=" Нет")
    g.edge("desc", "cnt", label=" Да")
    g.edge("desc", "next", label=" Нет")
    g.edge("cnt", "ok")
    g.edge("ok", "upd", label=" Да")
    g.edge("ok", "next", label=" Нет")
    g.edge("upd", "next")
    g.edge("next", "cond")
    g.edge("null", "zero", label=" Да")
    g.edge("null", "ret", label=" Нет")
    g.edge("zero", "ret")
    g.edge("ret", "e")
    return _render(g, "lab2_findTargetRow")


def lab2_insertZeroRow():
    g = _new("lab2_insertZeroRow")
    _terminator(g, "s", "Начало insertZeroRowAfter(afterRow)")
    _decision(g, "full", "rowCount >= MAX_ROWS ?")
    _io(g, "f", "return false")
    _process(g, "zero", "Заполнить data[rowCount] нулями")
    _process(g, "shift", "Сдвиг rowPtrs вправо\nна одну позицию,\nначиная с конца до afterRow")
    _process(g, "link", "rowPtrs[afterIndex+1] = data[rowCount]")
    _process(g, "inc", "++rowCount")
    _io(g, "t", "return true")
    _terminator(g, "e", "Конец")

    g.edge("s", "full")
    g.edge("full", "f", label=" Да")
    g.edge("full", "zero", label=" Нет")
    g.edge("zero", "shift")
    g.edge("shift", "link")
    g.edge("link", "inc")
    g.edge("inc", "t")
    g.edge("t", "e")
    g.edge("f", "e")
    return _render(g, "lab2_insertZeroRow")


def lab2_memory():
    g = _new("lab2_memory", rankdir="LR")
    g.attr("node", shape="record", fontname="Consolas", fontsize="10")
    g.node(
        "data",
        label="data[MAX_ROWS][MAX_COLS]|{<r0> row 0: 9 7 5 3|<r1> row 1: 4 2 8 6|<r2> row 2: 8 6 4 2|<r3> row 3: 7 3 1 0}",
        fillcolor="#dbeafe",
    )
    g.node(
        "ptrs",
        label="rowPtrs[]|{<p0> [0] &#8594;|<p1> [1] &#8594;|<p2> [2] &#8594;|<p3> [3] &#8594;}",
        fillcolor="#fef3c7",
    )
    g.edge("ptrs:p0", "data:r0")
    g.edge("ptrs:p1", "data:r1")
    g.edge("ptrs:p2", "data:r2")
    g.edge("ptrs:p3", "data:r3")
    return _render(g, "lab2_memory")


def lab3_mergeSort():
    g = _new("lab3_mergeSort")
    _terminator(g, "s", "Начало mergeSortRange(left, right)")
    _decision(g, "leq", "left >= right ?")
    _io(g, "ret", "return")
    _decision(g, "adj", "left + 1 == right ?")
    _decision(g, "cmp", "compareWords(words[left],\nwords[right]) ?")
    _process(g, "swp", "swapWords(left, right)")
    _process(g, "mid", "mid = left + (right - left) / 2")
    _process(g, "l", "mergeSortRange(left, mid)")
    _process(g, "r", "mergeSortRange(mid + 1, right)")
    _process(g, "m", "mergeRanges(left, mid, right)")
    _terminator(g, "e", "Конец")

    g.edge("s", "leq")
    g.edge("leq", "ret", label=" Да")
    g.edge("leq", "adj", label=" Нет")
    g.edge("adj", "cmp", label=" Да")
    g.edge("adj", "mid", label=" Нет")
    g.edge("cmp", "e", label=" Да")
    g.edge("cmp", "swp", label=" Нет")
    g.edge("swp", "e")
    g.edge("mid", "l")
    g.edge("l", "r")
    g.edge("r", "m")
    g.edge("m", "e")
    g.edge("ret", "e")
    return _render(g, "lab3_mergeSort")


def lab3_compareWords():
    g = _new("lab3_compareWords")
    _terminator(g, "s", "Начало compareWords(a, b)")
    _process(g, "cnt", "vA = countVowels(a)\nvB = countVowels(b)")
    _decision(g, "eq1", "vA != vB ?")
    _io(g, "r1", "return vA < vB")
    _process(g, "fv", "fA = firstVowel(a)\nfB = firstVowel(b)")
    _decision(g, "eq2", "fA != fB ?")
    _io(g, "r2", "return fA < fB")
    _io(g, "r3", "return strcmp(a, b) < 0")
    _terminator(g, "e", "Конец")

    g.edge("s", "cnt")
    g.edge("cnt", "eq1")
    g.edge("eq1", "r1", label=" Да")
    g.edge("eq1", "fv", label=" Нет")
    g.edge("fv", "eq2")
    g.edge("eq2", "r2", label=" Да")
    g.edge("eq2", "r3", label=" Нет")
    g.edge("r1", "e")
    g.edge("r2", "e")
    g.edge("r3", "e")
    return _render(g, "lab3_compareWords")


def lab3_memory():
    g = _new("lab3_memory", rankdir="LR")
    g.attr("node", shape="record", fontname="Consolas", fontsize="10")
    g.node("text", label="char* text|\"Hello, world! Programming IS fun.\"", fillcolor="#e9d5ff")
    g.node(
        "words",
        label="char** words|{<w0> [0] &#8594;|<w1> [1] &#8594;|<w2> [2] &#8594;|<w3> [3] &#8594;|<w4> [4] &#8594;}",
        fillcolor="#fef3c7",
    )
    g.node("s0", label="\"is\"", shape="box", fillcolor="#dbeafe")
    g.node("s1", label="\"world\"", shape="box", fillcolor="#dbeafe")
    g.node("s2", label="\"fun\"", shape="box", fillcolor="#dbeafe")
    g.node("s3", label="\"hello\"", shape="box", fillcolor="#dbeafe")
    g.node("s4", label="\"programming\"", shape="box", fillcolor="#dbeafe")

    g.edge("words:w0", "s0")
    g.edge("words:w1", "s1")
    g.edge("words:w2", "s2")
    g.edge("words:w3", "s3")
    g.edge("words:w4", "s4")
    return _render(g, "lab3_memory")


def lab4_recursive():
    g = _new("lab4_recursive")
    _terminator(g, "s", "Начало countPathsRecursive(n, k)")
    _process(g, "val", "validateInput(n, k)")
    _decision(g, "z", "n == 0 ?")
    _io(g, "r1", "return 1")
    _process(g, "init", "total = 0\nstep = 1")
    _decision(g, "loop", "step <= k && step <= n ?")
    _process(g, "rec", "total += countPathsRecursive(n - step, k)")
    _process(g, "inc", "++step")
    _io(g, "ret", "return total")
    _terminator(g, "e", "Конец")

    g.edge("s", "val")
    g.edge("val", "z")
    g.edge("z", "r1", label=" Да")
    g.edge("z", "init", label=" Нет")
    g.edge("init", "loop")
    g.edge("loop", "rec", label=" Да")
    g.edge("loop", "ret", label=" Нет")
    g.edge("rec", "inc")
    g.edge("inc", "loop")
    g.edge("ret", "e")
    g.edge("r1", "e")
    return _render(g, "lab4_recursive")


def lab4_dp():
    g = _new("lab4_dp")
    _terminator(g, "s", "Начало countPathsIterative(n, k)")
    _process(g, "val", "validateInput(n, k)")
    _process(g, "dp", "dp[0..n] = 0\ndp[0] = 1\ni = 1")
    _decision(g, "outer", "i <= n ?")
    _process(g, "sinit", "step = 1")
    _decision(g, "inner", "step <= k && step <= i ?")
    _process(g, "acc", "dp[i] += dp[i - step]")
    _process(g, "sinc", "++step")
    _process(g, "iinc", "++i")
    _io(g, "ret", "return dp[n]")
    _terminator(g, "e", "Конец")

    g.edge("s", "val")
    g.edge("val", "dp")
    g.edge("dp", "outer")
    g.edge("outer", "sinit", label=" Да")
    g.edge("outer", "ret", label=" Нет")
    g.edge("sinit", "inner")
    g.edge("inner", "acc", label=" Да")
    g.edge("inner", "iinc", label=" Нет")
    g.edge("acc", "sinc")
    g.edge("sinc", "inner")
    g.edge("iinc", "outer")
    g.edge("ret", "e")
    return _render(g, "lab4_dp")


def lab5_solveGauss():
    g = _new("lab5_solveGauss")
    _terminator(g, "s", "Начало solveSystemGauss")
    _process(g, "sz", "n_M = readSize(matrix.bin)\nn_V = readSize(vector.bin)")
    _decision(g, "eq", "n_M == n_V && n_M в [1..MAX_N] ?")
    _io(g, "err", "Ошибка размеров → return false")
    _process(g, "kloop", "Для k = 0..n-1")
    _process(g, "pivot", "Поиск строки с max |A[i][k]|\n(i = k..n-1) через readMatrixElement")
    _decision(g, "zpiv", "max < EPS ?")
    _io(g, "sing", "Ошибка: нулевой pivot →\nreturn false")
    _process(g, "swap", "swapMatrixRows(k, pivotRow)\nswapVectorTerms(k, pivotRow)")
    _process(g, "fwd", "Прямой ход: для i = k+1..n-1\nrowB -= factor * rowA\n(запись обратно в файл)")
    _process(g, "back", "Обратный ход: x[i] =\n(b[i] - Σ A[i][j]*x[j]) / A[i][i]")
    _process(g, "wr", "Запись x[] в result.txt")
    _io(g, "ok", "return true")
    _terminator(g, "e", "Конец")

    g.edge("s", "sz")
    g.edge("sz", "eq")
    g.edge("eq", "kloop", label=" Да")
    g.edge("eq", "err", label=" Нет")
    g.edge("kloop", "pivot")
    g.edge("pivot", "zpiv")
    g.edge("zpiv", "sing", label=" Да")
    g.edge("zpiv", "swap", label=" Нет")
    g.edge("swap", "fwd")
    g.edge("fwd", "back")
    g.edge("back", "wr")
    g.edge("wr", "ok")
    g.edge("ok", "e")
    g.edge("err", "e")
    g.edge("sing", "e")
    return _render(g, "lab5_solveGauss")


def lab5_swapRows():
    g = _new("lab5_swapRows")
    _terminator(g, "s", "Начало swapMatrixRows(rowA, rowB)")
    _decision(g, "eq", "rowA == rowB ?")
    _io(g, "t1", "return true")
    _process(g, "r1", "row1 = readMatrixRow(rowA)")
    _process(g, "r2", "row2 = readMatrixRow(rowB)")
    _process(g, "w1", "writeMatrixRow(rowA, row2)")
    _process(g, "w2", "writeMatrixRow(rowB, row1)")
    _io(g, "t2", "return true")
    _terminator(g, "e", "Конец")

    g.edge("s", "eq")
    g.edge("eq", "t1", label=" Да")
    g.edge("eq", "r1", label=" Нет")
    g.edge("r1", "r2")
    g.edge("r2", "w1")
    g.edge("w1", "w2")
    g.edge("w2", "t2")
    g.edge("t1", "e")
    g.edge("t2", "e")
    return _render(g, "lab5_swapRows")


def lab5_binary_layout():
    g = _new("lab5_binary_layout", rankdir="LR")
    g.attr("node", shape="record", fontname="Consolas", fontsize="10")
    g.node(
        "matrix",
        label="matrix.bin|{<h> [0] int n = 3|<r0> [1] double[n]: 2 1 -1|<r1> [2] double[n]: -3 -1 2|<r2> [3] double[n]: -2 1 2}",
        fillcolor="#dbeafe",
    )
    g.node(
        "vector",
        label="vector.bin|{<h> [0] int n = 3|<v0> [1] double: 8|<v1> [2] double: -11|<v2> [3] double: -3}",
        fillcolor="#fef3c7",
    )
    g.node(
        "result",
        label="result.txt|{n = 3|x[0] = 2|x[1] = 3|x[2] = -1}",
        fillcolor="#e9d5ff",
    )
    g.edge("matrix:h", "vector:h", style="dashed", arrowhead="none")
    g.edge("vector:h", "result", style="dotted", label=" solveSystemGauss")
    return _render(g, "lab5_binary_layout")


def lab6_newton():
    g = _new("lab6_newton")
    _terminator(g, "s", "Начало newtonSolve(f, df, y0, eps)")
    _process(g, "init", "y_old = y0\niteration = 0")
    _decision(g, "cond", "iteration < max_iter ?")
    _process(g, "der", "d = df(y_old)")
    _decision(g, "z", "|d| < ε_machine ?")
    _io(g, "brk", "return y_new (защита)")
    _process(g, "step", "y_new = y_old - f(y_old) / d")
    _decision(g, "stop", "|y_new - y_old| < eps ?")
    _io(g, "ret", "return y_new")
    _process(g, "upd", "y_old = y_new\n++iteration")
    _io(g, "ret2", "return y_new (лимит)")
    _terminator(g, "e", "Конец")

    g.edge("s", "init")
    g.edge("init", "cond")
    g.edge("cond", "der", label=" Да")
    g.edge("cond", "ret2", label=" Нет")
    g.edge("der", "z")
    g.edge("z", "brk", label=" Да")
    g.edge("z", "step", label=" Нет")
    g.edge("step", "stop")
    g.edge("stop", "ret", label=" Да")
    g.edge("stop", "upd", label=" Нет")
    g.edge("upd", "cond")
    g.edge("ret", "e")
    g.edge("ret2", "e")
    g.edge("brk", "e")
    return _render(g, "lab6_newton")


def lab6_sqrtNewton():
    g = _new("lab6_sqrtNewton")
    _terminator(g, "s", "Начало sqrtByNewton(t, eps)")
    _decision(g, "neg", "t < 0 ?")
    _io(g, "err1", "throw invalid_argument")
    _decision(g, "zero", "t == 0 ?")
    _io(g, "ret0", "return 0.0")
    _process(g, "brack", "проверка isRootBracketed(f_sqrt, 0, t)")
    _decision(g, "ok", "корень отделён ?")
    _io(g, "err2", "throw runtime_error")
    _process(g, "call", "newtonSolve(f_sqrt, df_sqrt, y0=t, eps)")
    _io(g, "ret", "return y")
    _terminator(g, "e", "Конец")

    g.edge("s", "neg")
    g.edge("neg", "err1", label=" Да")
    g.edge("neg", "zero", label=" Нет")
    g.edge("zero", "ret0", label=" Да")
    g.edge("zero", "brack", label=" Нет")
    g.edge("brack", "ok")
    g.edge("ok", "call", label=" Да")
    g.edge("ok", "err2", label=" Нет")
    g.edge("call", "ret")
    g.edge("ret", "e")
    g.edge("ret0", "e")
    g.edge("err1", "e")
    g.edge("err2", "e")
    return _render(g, "lab6_sqrtNewton")


def lab6_trapezoid():
    g = _new("lab6_trapezoid")
    _terminator(g, "s", "Начало compositeTrapezoid(f, a, b, n)")
    _decision(g, "chk", "n > 0 && b >= a ?")
    _io(g, "err", "throw invalid_argument")
    _process(g, "h", "h = (b - a) / n\nsum = 0.5 * (f(a) + f(b))\ni = 1")
    _decision(g, "loop", "i < n ?")
    _process(g, "acc", "sum += f(a + i * h)")
    _process(g, "inc", "++i")
    _io(g, "ret", "return h * sum")
    _terminator(g, "e", "Конец")

    g.edge("s", "chk")
    g.edge("chk", "h", label=" Да")
    g.edge("chk", "err", label=" Нет")
    g.edge("h", "loop")
    g.edge("loop", "acc", label=" Да")
    g.edge("loop", "ret", label=" Нет")
    g.edge("acc", "inc")
    g.edge("inc", "loop")
    g.edge("ret", "e")
    g.edge("err", "e")
    return _render(g, "lab6_trapezoid")


def lab6_adaptive():
    g = _new("lab6_adaptive")
    _terminator(g, "s", "Начало adaptiveTrapezoid(f, a, b, n0, eps, maxRef)")
    _process(g, "init", "n = n0\ni_prev = trapezoid(f, a, b, n)\ni_curr = trapezoid(f, a, b, 2n)\nstep = 0")
    _decision(g, "loop", "step < maxRef ?")
    _process(g, "dbl", "n *= 2\ni_curr = trapezoid(f, a, b, n)\ndiff = |i_prev - i_curr|")
    _decision(g, "eps", "diff < eps ?")
    _io(g, "conv", "result.converged = true\nreturn result (I_curr, n)")
    _process(g, "shift", "i_prev = i_curr\n++step")
    _io(g, "nc", "result.converged = false\nreturn result (I_curr, n)")
    _terminator(g, "e", "Конец")

    g.edge("s", "init")
    g.edge("init", "loop")
    g.edge("loop", "dbl", label=" Да")
    g.edge("loop", "nc", label=" Нет")
    g.edge("dbl", "eps")
    g.edge("eps", "conv", label=" Да")
    g.edge("eps", "shift", label=" Нет")
    g.edge("shift", "loop")
    g.edge("conv", "e")
    g.edge("nc", "e")
    return _render(g, "lab6_adaptive")


def lab6_variant5_chart():
    """Plot integrand f(x) = sqrt(x^2 + c^2) / x on [1, 2] for c = 1, 2, 3."""
    import os
    os.environ.setdefault("MPLCONFIGDIR", str(ASSETS.parent / "mplconfig"))
    Path(os.environ["MPLCONFIGDIR"]).mkdir(parents=True, exist_ok=True)
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt
    import math

    xs = [1 + 0.005 * i for i in range(201)]
    fig, ax = plt.subplots(figsize=(7, 4.2))
    for c, color, marker in [(1.0, "#2563eb", None), (2.0, "#16a34a", None), (3.0, "#dc2626", None)]:
        ys = [math.sqrt(x * x + c * c) / x for x in xs]
        ax.plot(xs, ys, color=color, linewidth=2.0, label=f"c = {c:g}")
    ax.set_xlabel("x", fontsize=12)
    ax.set_ylabel("f(x) = √(x² + c²) / x", fontsize=12)
    ax.set_title("Подынтегральная функция варианта 5 на отрезке [1; 2]", fontsize=13)
    ax.grid(True, alpha=0.35)
    ax.legend(fontsize=11)
    fig.tight_layout()
    out = ASSETS / "lab6_variant5_chart.png"
    fig.savefig(out, dpi=180, facecolor="white")
    plt.close(fig)
    return out


def lab7_sort():
    g = _new("lab7_sort")
    _terminator(g, "s", "Начало sortByAverage(compare)")
    _process(g, "invoke", "students.sort(lambda lhs, rhs:\n    compare(lhs.averageGrade(),\n            rhs.averageGrade()))")
    _process(g, "stl", "std::list::sort — устойчивая\nсортировка слиянием (mergesort)")
    _process(g, "avg", "averageGrade():\nsum(grades) / 5")
    _io(g, "ret", "return")
    _terminator(g, "e", "Конец")

    g.edge("s", "invoke")
    g.edge("invoke", "stl")
    g.edge("stl", "avg", label=" вызов ключа")
    g.edge("avg", "ret")
    g.edge("ret", "e")
    return _render(g, "lab7_sort")


def lab7_insertSorted():
    g = _new("lab7_insertSorted")
    _terminator(g, "s", "Начало insertSorted(new, compare)")
    _process(g, "avg", "newAvg = new.averageGrade()")
    _process(g, "init", "it = students.begin()")
    _decision(g, "end", "it == students.end() ?")
    _process(g, "ins_end", "students.insert(end, new)")
    _decision(g, "cmp", "compare(newAvg,\nit->averageGrade()) ?")
    _process(g, "ins_pos", "students.insert(it, new)")
    _process(g, "next", "++it")
    _io(g, "ret", "return")
    _terminator(g, "e", "Конец")

    g.edge("s", "avg")
    g.edge("avg", "init")
    g.edge("init", "end")
    g.edge("end", "ins_end", label=" Да")
    g.edge("end", "cmp", label=" Нет")
    g.edge("cmp", "ins_pos", label=" Да")
    g.edge("cmp", "next", label=" Нет")
    g.edge("next", "end")
    g.edge("ins_pos", "ret")
    g.edge("ins_end", "ret")
    g.edge("ret", "e")
    return _render(g, "lab7_insertSorted")


def lab7_list_structure():
    g = _new("lab7_list_structure", rankdir="LR")
    g.attr("node", shape="record", fontname="Consolas", fontsize="10")
    g.node("head", label="StudentList\\l|students &#8594;", fillcolor="#e9d5ff")
    g.node(
        "n1",
        label="{Node 1|surname: Nguyen|first: Nam|grades: 6,5,6,5,6|avg: 5.6|next &#8594;}",
        fillcolor="#dbeafe",
    )
    g.node(
        "n2",
        label="{Node 2|surname: Belova|first: Daria|grades: 7,7,6,7,7|avg: 6.8|next &#8594;}",
        fillcolor="#dbeafe",
    )
    g.node(
        "n3",
        label="{Node 3|surname: Kuznetsova|first: Anna|grades: 8,7,8,8,7|avg: 7.6|next &#8594;}",
        fillcolor="#dbeafe",
    )
    g.node(
        "n4",
        label="{Node 4|surname: Orlov|first: Oleg|grades: 9,8,8,8,9|avg: 8.4|next: null}",
        fillcolor="#dbeafe",
    )
    g.edge("head", "n1")
    g.edge("n1", "n2")
    g.edge("n2", "n3")
    g.edge("n3", "n4")
    return _render(g, "lab7_list_structure")


def lab4_chart():
    """Number of paths vs N for K=2,3,4 (matplotlib)."""
    import os
    os.environ.setdefault("MPLCONFIGDIR", str(ASSETS.parent / "mplconfig"))
    Path(os.environ["MPLCONFIGDIR"]).mkdir(parents=True, exist_ok=True)
    import matplotlib
    matplotlib.use("Agg")
    import matplotlib.pyplot as plt

    def count_iter(n: int, k: int) -> int:
        dp = [0] * (n + 1)
        dp[0] = 1
        for i in range(1, n + 1):
            for step in range(1, min(k, i) + 1):
                dp[i] += dp[i - step]
        return dp[n]

    ns = list(range(0, 13))
    fig, ax = plt.subplots(figsize=(7, 4.2))
    for k, color, marker in [(2, "#2563eb", "o"), (3, "#16a34a", "s"), (4, "#dc2626", "^")]:
        ax.plot(ns, [count_iter(n, k) for n in ns], marker=marker, color=color, linewidth=2.0, markersize=6, label=f"K = {k}")
    ax.set_xlabel("N (длина поля)", fontsize=12)
    ax.set_ylabel("Число путей", fontsize=12)
    ax.set_title("Зависимость числа путей фишки от N при разных K", fontsize=13)
    ax.grid(True, alpha=0.35)
    ax.legend(fontsize=11)
    fig.tight_layout()
    out = ASSETS / "lab4_paths_chart.png"
    fig.savefig(out, dpi=180, facecolor="white")
    plt.close(fig)
    return out


def main():
    tasks = [
        lab1_findAnswer,
        lab1_getMinDigit,
        lab1_isSuitable,
        lab2_findTargetRow,
        lab2_insertZeroRow,
        lab2_memory,
        lab3_mergeSort,
        lab3_compareWords,
        lab3_memory,
        lab4_recursive,
        lab4_dp,
        lab4_chart,
        lab5_solveGauss,
        lab5_swapRows,
        lab5_binary_layout,
        lab6_newton,
        lab6_sqrtNewton,
        lab6_trapezoid,
        lab6_adaptive,
        lab6_variant5_chart,
        lab7_sort,
        lab7_insertSorted,
        lab7_list_structure,
    ]
    for t in tasks:
        p = t()
        print("  ok:", p.name)


if __name__ == "__main__":
    main()
