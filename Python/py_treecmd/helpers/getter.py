from pathlib import Path

def DummyDataFromFile(file:str):
    path = Path(file)
    if path.exists():
        with open(path, 'r') as f:
            params = f.readlines()
        return params
    else:
        print("error, file not found")
        return []


def DummyData():
    params = [
        'M       main.py', 
        'M       Makefile', 
        'A       lib/lib1.h', 
        'A       lib/lib2.h', 
        'A       lib/sub/l3.h', 
        'A       lib/sub/l4.h', 
        'A       lib/sub/l5.h', 
        'A       lib/sub/subsub/l7.h', 
        'A       lib/sub/subsub/l8.h', 
        'A       lib/sub/subsub/l9.h', 
        'A       lib/sub/subsub/l10.h', 
        'A       src/bla.txt', 
        'A       src/ble.txt', 
    ]
    return params

def DummyParamsGit():

    params = [
        "A	py_automate/Makefile",
        "A	py_automate/main.py",
        "A	py_automate/py_pathlib/Makefile",
        "A	py_automate/py_pathlib/bla/ble/newfile.txt",
        "A	py_automate/py_pathlib/main.py",
        "A	py_automate/py_pathlib/newfile.txt",
        "A	py_compare_list/Makefile",
        "A	py_compare_list/main.py",
        "A	py_design_patterns/py_factory/Makefile",
        "A	py_design_patterns/py_factory/main.py",
        "A	py_events/Makefile",
        "A	py_events/api/__init__.py",
        "A	py_events/api/events.py",
        "A	py_events/api/runners.py",
        "A	py_events/api/workers.py",
        "A	py_events/main.py",
        "A	py_fortran/Makefile",
        "A	py_fortran/main.py",
        "A	py_grpc/README.md",
        "A	py_jupyter_pg/Untitled.ipynb",
        "A	py_quadprog/Makefile",
        "A	py_quadprog/main.py",
        "A	py_quadprog/requirements.txt",
        "A	py_read_monitor_text/Makefile",
        "A	py_read_monitor_text/README.md",
        "A	py_read_monitor_text/goto.png",
        "A	py_read_monitor_text/goto2.png",
        "A	py_read_monitor_text/img1.png",
        "A	py_read_monitor_text/img2.png",
        "A	py_read_monitor_text/img3.png",
        "A	py_read_monitor_text/main.py",
        "A	py_read_monitor_text/requirements.txt",
        "A	py_read_monitor_text/shot.png",
        "A	py_spotipy/Makefile",
        "A	py_spotipy/main.py",
        "A	py_treecmd/.gitignore",
        "A	py_treecmd/Makefile",
        "A	py_treecmd/lib/lib1.h",
        "A	py_treecmd/lib/lib2.h",
        "A	py_treecmd/lib/sub/l3.h",
        "A	py_treecmd/lib/sub/l4.h",
        "A	py_treecmd/lib/sub/l5.h",
        "A	py_treecmd/main.py",
        "A	py_treecmd/src/bla.txt",
        "A	py_treecmd/src/ble.txt",
        "A	py_walrus/Makefile",
        "A	py_walrus/main.py",
        "A	py_websocket/Makefile",
        "A	py_websocket/client.py",
        "A	py_websocket/index.html",
        "A	py_websocket/server.py",
        "A	py_websocket/server_browser.py",
        "A	py_youtube/.gitignore",
        "A	py_youtube/main.py",
        "A	py_youtube/requirements.txt",
    ]
    return params