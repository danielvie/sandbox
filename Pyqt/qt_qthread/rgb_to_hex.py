
sky = []
sky.append(['50', (240, 249, 255)])
sky.append(['100', (224, 242, 254)])
sky.append(['200', (186, 230, 253)])
sky.append(['300', (125, 211, 252)])
sky.append(['400', (56, 189, 248)])
sky.append(['500', (14, 165, 233)])
sky.append(['600', (2, 132, 199)])
sky.append(['700', (3, 105, 161)])
sky.append(['800', (7, 89, 133)])
sky.append(['900', (12, 74, 110)])
sky.append(['950', (8, 47, 73)])

def rgb_to_hex(r, g, b):
    return '#{:02x}{:02x}{:02x}'.format(r, g, b)

for name, rgb in sky:
    print(f"{name:3s}: {rgb_to_hex(*rgb)}")