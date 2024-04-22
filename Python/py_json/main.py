

import json

with open('prize.json', 'r') as json_file:
    json_data = json.load(json_file)
    
for i in [4, 6, 8, 10]:
    print(f'({i:02d}):',json_data['prizes'][i]['year'])
    for lau in json_data['prizes'][i]['laureates']:
        firstname = lau["firstname"]
        surname   = lau["surname"]
        print(f'\t{firstname} {surname}')

