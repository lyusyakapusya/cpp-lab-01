#!/usr/bin/env bash
# Прогоняет тесты шаблона. Аргумент: all | types | branches | loops | journal
set -uo pipefail

root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$root"
mkdir -p build

if ! command -v g++ >/dev/null 2>&1; then
    echo "Не найден компилятор g++. Проект собирается этой командой, не кнопкой в редакторе."
    echo "Проверка: g++ --version"
    echo "Linux:   sudo apt install build-essential"
    echo "macOS:   xcode-select --install"
    echo "Windows: терминал MSYS2 UCRT64, затем pacman -S --needed mingw-w64-ucrt-x86_64-gcc make"
    echo "Подробности в README, раздел «Сборка»."
    exit 1
fi

cxx=(g++ -std=c++20 -Wall -Wextra)
only="${1:-all}"
failed=0

want() {
    [[ "$only" == "all" || "$only" == "$1" ]]
}

run_bin() {
    local name="$1"
    shift
    echo "== $name =="
    if ! "${cxx[@]}" -o "build/$name" "$@"; then
        echo "FAIL $name: compile"
        failed=1
        return
    fi
    if ! "./build/$name"; then
        echo "FAIL $name"
        failed=1
        return
    fi
    echo "ok $name"
}

run_io() {
    local name="$1"
    local bin="$2"
    local dir="$3"
    local any=0
    local local_fail=0

    for input in "$dir"/*.in; do
        [[ -e "$input" ]] || continue
        any=1
        local base="${input%.in}"
        local case_name
        case_name="$(basename "$base")"
        local actual="build/${name}_${case_name}.actual"
        local expected_code=0
        if [[ -f "${base}.exit" ]]; then
            expected_code="$(tr -d '[:space:]' < "${base}.exit")"
        fi

        "./build/$bin" < "$input" > "$actual"
        local code=$?
        local bad=0
        if [[ "$code" != "$expected_code" ]]; then
            echo "FAIL $case_name: exit code $code, expected $expected_code"
            bad=1
        fi
        if ! diff -u "${base}.out" "$actual"; then
            bad=1
        fi
        if [[ "$bad" -eq 0 ]]; then
            echo "ok $case_name"
        else
            local_fail=1
        fi
    done

    if [[ "$any" -eq 0 ]]; then
        echo "FAIL $name: no tests"
        failed=1
        return
    fi
    if [[ "$local_fail" -ne 0 ]]; then
        failed=1
    fi
}

if want types; then
    run_bin check_types tasks/01_types/types.cpp tasks/01_types/check.cpp
fi

if want branches; then
    run_bin check_labels tasks/02_branches/labels.cpp tasks/02_branches/check.cpp
fi

if want loops; then
    echo "== loops =="
    if ! "${cxx[@]}" -o build/loops tasks/03_loops/main.cpp; then
        echo "FAIL loops: compile"
        failed=1
    else
        run_io loops loops tasks/03_loops/tests
    fi
fi

if want journal; then
    run_bin check_journal tasks/04_journal/journal.cpp tasks/04_journal/check.cpp
    echo "== journal program =="
    if ! "${cxx[@]}" -o build/journal tasks/04_journal/journal.cpp tasks/04_journal/main.cpp; then
        echo "FAIL journal: compile"
        failed=1
    else
        run_io journal journal tasks/04_journal/tests
    fi
fi

if [[ "$failed" -ne 0 ]]; then
    echo "FAILED"
    exit 1
fi

echo "ALL OK"
exit 0
