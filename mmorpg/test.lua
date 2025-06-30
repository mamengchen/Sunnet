local tb = {
    sss = 1,
    zzz = 2
}


local tb2 = {
    ccc = 4,
}

local tb3 = table.merge(tb, tb2)

print(tb)
print(tb3)