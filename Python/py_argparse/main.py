import argparse

parser = argparse.ArgumentParser(description="process two integers")


def power2(x):
    return x**2


parser.add_argument(
    "integers", metavar="N", type=int, nargs="+", help="integers for the accumulator"
)

parser.add_argument(
    "--sum",
    dest="accumulate",
    action="store_const",
    const=sum,
    default=max,
    help="sum the integers (default: find the max)",
)

parser.add_argument(
    "--min",
    dest="accumulate",
    action="store_const",
    const=min,
    default=max,
    help="get the min value",
)

parser.add_argument("--power2", action="store_true", help="square each integer")

parser.add_argument("--o", default=0, type=int, help="optimization level")

args = parser.parse_args()

values = []
print(args)
if args.power2:
    values = [x**2 for x in args.integers]

if values:
    print(values)
else:
    print(args.accumulate(args.integers))
