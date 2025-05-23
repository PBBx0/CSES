n = int(input())
r = list(map(int, input().split()))
res = 0
dp = [0 for i in range(101)]
for i in range(n):
    cur = 0
    for d in range(1, r[i] + 1):
        for x in range(d + 1, 101):
            cur += dp[x]
    res += cur / r[i]
    for d in range(1, r[i] + 1):
        dp[d] += 1 / r[i]
print(f"{round(res, 8):.6f}")