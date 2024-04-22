import re

txt = '"aa":"bb", "cc":"dd", "ee":"ff", "gg":"hh", "ii":"jj", "ll":"mm", "nn":"oo", "pp":"qq", "rr":"ss", "tt":"uu", "vv":"xx"'
regex = re.compile('"(?P<name>\w\w)":"(?P<value>\w\w)"')

txt_ = txt
res = regex.search(txt_)
V = []

while res:
    # processing result
    r = res.groupdict()
    msg = f'{r.get("name")}, {r.get("value")}\n'
    V.append(msg)
    
    # new strng
    txt_ = txt_[res.span()[1]::]
    res = regex.search(txt_)

# writing on a file
with open("bla.txt", "w") as f:
    f.writelines(V)

print(txt_)
print(txt)