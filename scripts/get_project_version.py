import re
from pathlib import Path
from typing import Final, Optional

PROJECT_VERSION_EXPR: Final[re.Pattern[str]] = re.compile(r'^PROJECT\([a-zA-Z\-]+\s+VERSION\s+([0-9.]+)')

# pylint: disable=missing-function-docstring


def get_project_root() -> Path:
    return Path(__file__).resolve().parent.parent


def print_project_version() -> None:
    project_root = get_project_root()
    version: Optional[str] = None
    with open(project_root / 'CMakeLists.txt', 'rt', encoding='UTF-8') as fh:
        for line in fh:
            match = PROJECT_VERSION_EXPR.match(line)
            if match:
                version = match.group(1)
                break
    if version is None:
        raise ValueError('Could not find project version in CMakeLists.txt')
    print(version)


if __name__ == '__main__':
    print_project_version()
