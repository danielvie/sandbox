from rich.console import Console
from rich.panel import Panel


console = Console()

def display_greeting():
    console.print("Hello, welcome to the TUI example!")

def main():

    console.fullscreen()
    while True:
        # console.clear()
        console.width = console.height = None  # Set console to fullscreen

        options = [
            {"name": "Display Greeting", "callback": display_greeting},
            {"name": "Exit", "callback": lambda: exit()},
        ]

        menu_text = "\n".join([f"{index + 1}. {option['name']}" for index, option in enumerate(options)])
        menu_panel = Panel(menu_text, title="Menu", border_style="blue", padding=(1, 2))

        console.print(menu_panel)

        try:
            choice = int(console.input("Enter your choice: "))
            if 1 <= choice <= len(options):
                options[choice - 1]["callback"]()
            else:
                console.print("Invalid choice. Please try again.")
        except ValueError:
            console.print("Invalid input. Please enter a number.")

if __name__ == "__main__":
    main()
