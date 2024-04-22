from datetime import datetime
from colorama import init as init_colorama, Fore, Style
from enum import Enum, auto
import platform

# fix for windows cmd
if platform.system().lower() == 'windows':
    init_colorama()

class Type(Enum):
    INFO = 0
    WARNING = auto()
    ERROR = auto()

class Logger:

    def __init__(self, origin:str) -> None:
        self.origin = origin

    def __get_time_now(self, ):
        now = datetime.now().strftime("%H:%M:%S")
        return now
        
    def __get_color(self, type:Type):
        Map = {
            Type.INFO: [Fore.WHITE, Fore.LIGHTCYAN_EX],
            Type.WARNING: [Fore.LIGHTWHITE_EX, Fore.YELLOW],
            Type.ERROR: [Fore.LIGHTWHITE_EX, Fore.RED]
        }

        return Map[type]

    def __report_console(self, type:Type, msg:str):
        color = self.__get_color(type)
        now = self.__get_time_now()

        msg_console = f'{color[0]}{now} :: {type.name} :: {color[1]}{self.origin} :: {msg}{Style.RESET_ALL}'
        
        # writing in console
        print(msg_console)
        
    def info(self, msg):
        self.__report_console(Type.INFO, msg = msg)

    def warning(self, msg):
        self.__report_console(Type.WARNING, msg = msg)

    def error(self, msg):
        self.__report_console(Type.ERROR, msg = msg)