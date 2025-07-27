import decimal

n = int(input())
r = list(map(int, input().split()))
total = decimal.Decimal(0)

for i in range(n):
    for j in range(i + 1, n):
        ra = r[i]
        rb = r[j]
        if ra <= rb:
            prob = decimal.Decimal(ra - 1) / decimal.Decimal(2 * rb)
        else:
            prob = decimal.Decimal(1) - (decimal.Decimal(rb + 1) / decimal.Decimal(2 * ra))
        total += prob


rounded_total = total.quantize(decimal.Decimal('0.000000'), rounding=decimal.ROUND_HALF_EVEN)
print("{0:.6f}".format(float(rounded_total)))