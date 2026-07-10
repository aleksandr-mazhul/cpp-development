#!/usr/bin/env python3
"""Render terminal-style PNG screenshots from ANSI-colored program logs."""

from __future__ import annotations

import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path
from typing import Iterable, List, Tuple

from PIL import Image, ImageDraw, ImageFont

ROOT = Path(__file__).resolve().parent.parent
ASSETS = ROOT / "tmp" / "report_assets"
ASSETS.mkdir(parents=True, exist_ok=True)
LOGS = ROOT / "tmp" / "test_logs"
LOGS.mkdir(parents=True, exist_ok=True)


COLORS_STD = {
    30: "#3c3c3c", 31: "#f4787a", 32: "#8fce8f", 33: "#f0c674",
    34: "#7aa6da", 35: "#c397d8", 36: "#8abeb7", 37: "#c5c8c6",
    90: "#666666", 91: "#ff6b6b", 92: "#b5e07f", 93: "#f7d874",
    94: "#8fb3ff", 95: "#d8a0e6", 96: "#7ed3ce", 97: "#ffffff",
}
DEFAULT_FG = "#e8e8e8"
BG = "#1e1e1e"
TITLE_BG = "#2d2d2d"
BORDER = "#3c3c3c"

ANSI_RE = re.compile(r"\x1b\[(\d+(?:;\d+)*)m")


@dataclass
class Segment:
    text: str
    color: str
    bold: bool


def _sanitize(line: str) -> str:
    """Replace glyphs that most monospace fonts render as tofu boxes."""
    return (line
            .replace("━", "-")
            .replace("═", "=")
            .replace("─", "-")
            .replace("→", "->")
            .replace("▸", ">"))


def parse_ansi(line: str) -> List[Segment]:
    """Convert a line with ANSI escapes into a list of (text, color, bold) segments."""
    line = _sanitize(line)
    segments: List[Segment] = []
    color = DEFAULT_FG
    bold = False
    pos = 0
    for m in ANSI_RE.finditer(line):
        if m.start() > pos:
            segments.append(Segment(line[pos : m.start()], color, bold))
        codes = [int(c) for c in m.group(1).split(";") if c]
        for c in codes:
            if c == 0:
                color = DEFAULT_FG
                bold = False
            elif c == 1:
                bold = True
            elif c == 22:
                bold = False
            elif c in COLORS_STD:
                color = COLORS_STD[c]
        pos = m.end()
    if pos < len(line):
        segments.append(Segment(line[pos:], color, bold))
    return segments


def _load_font(size: int, bold: bool = False):
    candidates_bold = [
        "/System/Library/Fonts/Menlo.ttc",
        "/Library/Fonts/MonacoB.ttf",
        "/System/Library/Fonts/Supplemental/Andale Mono.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono-Bold.ttf",
    ]
    candidates_regular = [
        "/System/Library/Fonts/Menlo.ttc",
        "/System/Library/Fonts/Monaco.ttf",
        "/System/Library/Fonts/Supplemental/Andale Mono.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSansMono.ttf",
    ]
    for path in (candidates_bold if bold else candidates_regular):
        p = Path(path)
        if p.exists():
            try:
                if p.suffix == ".ttc":
                    return ImageFont.truetype(str(p), size, index=(1 if bold else 0))
                return ImageFont.truetype(str(p), size)
            except OSError:
                continue
    return ImageFont.load_default()


def render_lines(
    lines: List[str],
    output: Path,
    title: str = "Terminal",
    font_size: int = 14,
    padding: int = 14,
    max_width_chars: int | None = None,
):
    font = _load_font(font_size)
    font_bold = _load_font(font_size, bold=True)

    dummy = Image.new("RGB", (10, 10))
    d = ImageDraw.Draw(dummy)
    char_w = d.textlength("M", font=font)
    ascent, descent = font.getmetrics()
    line_h = ascent + descent + 2

    plain_lines = [ANSI_RE.sub("", line) for line in lines]
    if max_width_chars is None:
        max_len = max((len(pl) for pl in plain_lines), default=1)
    else:
        max_len = max_width_chars
        plain_lines = [pl[:max_len] for pl in plain_lines]
        lines = [line for line in lines]

    title_h = font_size + 12
    content_w = int(max_len * char_w) + padding * 2
    content_h = title_h + len(lines) * line_h + padding * 2
    img_w = max(content_w, 320)
    img_h = max(content_h, title_h + 40)

    img = Image.new("RGB", (img_w, img_h), BG)
    draw = ImageDraw.Draw(img)

    draw.rectangle([(0, 0), (img_w, title_h)], fill=TITLE_BG)
    draw.line([(0, title_h), (img_w, title_h)], fill=BORDER, width=1)
    for i, color in enumerate(["#ff5f56", "#ffbd2e", "#27c93f"]):
        cx = 14 + i * 18
        cy = title_h // 2
        draw.ellipse((cx - 6, cy - 6, cx + 6, cy + 6), fill=color)
    title_font = _load_font(font_size - 2, bold=True)
    tw = draw.textlength(title, font=title_font)
    draw.text(((img_w - tw) / 2, (title_h - font_size + 2) / 2), title, fill="#c5c8c6", font=title_font)

    y = title_h + padding
    for raw in lines:
        segments = parse_ansi(raw)
        x = padding
        for seg in segments:
            f = font_bold if seg.bold else font
            draw.text((x, y), seg.text, fill=seg.color, font=f)
            x += draw.textlength(seg.text, font=f)
        y += line_h

    draw.rectangle([(0, 0), (img_w - 1, img_h - 1)], outline=BORDER, width=1)
    img.save(output)
    return output


def slice_log(log_path: Path, start_marker: str, end_marker: str | None = None) -> List[str]:
    text = log_path.read_text(encoding="utf-8", errors="replace")
    lines = text.splitlines()
    result: List[str] = []
    in_block = False
    for line in lines:
        plain = ANSI_RE.sub("", line)
        if not in_block:
            if start_marker in plain:
                in_block = True
                result.append(line)
        else:
            if end_marker and end_marker in plain:
                result.append(line)
                break
            result.append(line)
    return result


def render_from_log(
    log_path: Path,
    output_name: str,
    title: str,
    start: str,
    end: str | None = None,
    max_lines: int | None = None,
    max_width_chars: int | None = None,
):
    lines = slice_log(log_path, start, end)
    if max_lines and len(lines) > max_lines:
        lines = lines[:max_lines] + ["...  (обрезано для наглядности)"]
    if not lines:
        print(f"  WARN: empty slice for {output_name} ({start!r})")
        return None
    return render_lines(lines, ASSETS / output_name, title=title, max_width_chars=max_width_chars)


def run_manual(exe: Path, stdin: str, log_out: Path, extra_env: dict[str, str] | None = None):
    env = None
    if extra_env:
        import os
        env = os.environ.copy()
        env.update(extra_env)
    result = subprocess.run(
        [str(exe)],
        input=stdin,
        capture_output=True,
        text=True,
        env=env,
        timeout=30,
    )
    log_out.write_text(result.stdout, encoding="utf-8")
    return result.stdout


def main():
    # --- lab1 manual runs ---
    lab1_exe = ROOT / "integerArithmetic" / "build" / "semester_2_practice_integerarithmetic"
    if lab1_exe.exists():
        test1 = run_manual(lab1_exe, "5\n12 45 88 23 71\n", LOGS / "lab1_test1.txt")
        render_lines(test1.splitlines(), ASSETS / "lab1_test1.png",
                     title="lab1 test 1: max suitable")
        test2 = run_manual(lab1_exe, "3\n13 17 19\n", LOGS / "lab1_test2.txt")
        render_lines(test2.splitlines(), ASSETS / "lab1_test2.png",
                     title="lab1 test 2: not found")
        test3 = run_manual(lab1_exe, "1\n246\n", LOGS / "lab1_test3.txt")
        render_lines(test3.splitlines(), ASSETS / "lab1_test3.png",
                     title="lab1 test 3: single element")

    # --- lab2 all tests ---
    lab2_log = LOGS / "lab2_tests.txt"
    if lab2_log.exists():
        for idx, name in enumerate([
            ("Тест 1", "lab2_test1.png", "Тест 1", "Тест 2"),
            ("Тест 2", "lab2_test2.png", "Тест 2", "Тест 3"),
            ("Тест 3", "lab2_test3.png", "Тест 3", "Тест 4"),
            ("Тест 4", "lab2_test4.png", "Тест 4", "Все тесты завершены"),
        ], start=1):
            _, out, start, end = name
            render_from_log(lab2_log, out, f"lab2 {_}", start, end, max_lines=45)

    # --- lab3 all tests ---
    lab3_log = LOGS / "lab3_tests.txt"
    if lab3_log.exists():
        for label, out, start, end in [
            ("Тест 1", "lab3_test1.png", "Тест 1 / 5", "Тест 2 / 5"),
            ("Тест 2", "lab3_test2.png", "Тест 2 / 5", "Тест 3 / 5"),
            ("Тест 3", "lab3_test3.png", "Тест 3 / 5", "Тест 4 / 5"),
            ("Тест 4", "lab3_test4.png", "Тест 4 / 5", "Тест 5 / 5"),
            ("Тест 5", "lab3_test5.png", "Тест 5 / 5", None),
        ]:
            render_from_log(lab3_log, out, f"lab3 {label}", start, end, max_lines=45)

    # --- lab5 gauss autotests ---
    lab5_log = LOGS / "lab5_tests.txt"
    if lab5_log.exists():
        for label, out, start, end in [
            ("Тест 1", "lab5_test1.png", "Тест 1 из 5", "Тест 2 из 5"),
            ("Тест 2", "lab5_test2.png", "Тест 2 из 5", "Тест 3 из 5"),
            ("Тест 3", "lab5_test3.png", "Тест 3 из 5", "Тест 4 из 5"),
            ("Тест 4", "lab5_test4.png", "Тест 4 из 5", "Тест 5 из 5"),
            ("Тест 5", "lab5_test5.png", "Тест 5 из 5", "Итог:"),
        ]:
            render_from_log(lab5_log, out, f"lab5 {label}", start, end, max_lines=32)

    # --- lab6 autotests and variant 5 table ---
    lab6_log = LOGS / "lab6_tests.txt"
    if lab6_log.exists():
        for label, out, start, end in [
            ("Тест 1", "lab6_test1.png", "Тест 1.", "Тест 2."),
            ("Тест 2", "lab6_test2.png", "Тест 2.", "Тест 3."),
            ("Тест 3", "lab6_test3.png", "Тест 3.", "Тест 4."),
            ("Тест 4", "lab6_test4.png", "Тест 4.", "ИТОГ:"),
        ]:
            render_from_log(lab6_log, out, f"lab6 {label}", start, end, max_lines=20)
    lab6_v5 = LOGS / "lab6_variant5.txt"
    if lab6_v5.exists():
        render_from_log(lab6_v5, "lab6_variant5_table.png",
                        "lab6 Таблица варианта 5",
                        "Таблица результатов", "Проверка решения", max_lines=25)
        render_from_log(lab6_v5, "lab6_sqrt_check.png",
                        "lab6 Проверка sqrt через Ньютон",
                        "Проверка решения уравнения", None, max_lines=15)

    # --- lab7 ascending/descending tests ---
    lab7_asc = LOGS / "lab7_ascending_tests.txt"
    lab7_desc = LOGS / "lab7_descending_tests.txt"
    if lab7_asc.exists():
        for label, out, start, end in [
            ("Тест 1", "lab7_asc_test1.png", "  Тест 1", "  Тест 2"),
            ("Тест 3", "lab7_asc_test3.png", "  Тест 3", "  Тест 4"),
            ("Тест 4", "lab7_asc_test4.png", "  Тест 4", "  Тест 5"),
            ("Тест 5", "lab7_asc_test5.png", "  Тест 5", "ИТОГ"),
        ]:
            render_from_log(lab7_asc, out, f"lab7 {label} (по возрастанию)",
                            start, end, max_lines=35)
    if lab7_desc.exists():
        render_from_log(lab7_desc, "lab7_desc_test1.png",
                        "lab7 Тест 1 (по убыванию)",
                        "  Тест 1", "  Тест 2", max_lines=25)
        render_from_log(lab7_desc, "lab7_desc_test4.png",
                        "lab7 Тест 4 (по убыванию)",
                        "  Тест 4", "  Тест 5", max_lines=32)

    # --- lab4 recursive and iterative tests ---
    lab4_rec = LOGS / "lab4_recursive_tests.txt"
    lab4_iter = LOGS / "lab4_iterative_tests.txt"
    if lab4_rec.exists():
        render_from_log(lab4_rec, "lab4_recursive_summary.png",
                        "lab4 рекурсивные тесты (сводка)",
                        "Тесты:", "Итог:", max_lines=30)
    if lab4_iter.exists():
        render_from_log(lab4_iter, "lab4_iterative_summary.png",
                        "lab4 нерекурсивные тесты (сводка)",
                        "Тесты:", "Итог:", max_lines=30)

    print("Console screenshots generated in", ASSETS)


if __name__ == "__main__":
    main()
