from time import monotonic

from textual import on
from textual.app import App
from textual.containers import ScrollableContainer
from textual.reactive import reactive
from textual.widgets import Button,Footer, Header, Static

class TimeDisplay(Static):
    
    accumulated_time = 0
    start_time = monotonic()
    time_elapsed = reactive(0)
    
    def on_mount(self):
        self.update_timer = self.set_interval(
            1 / 60, 
            self.update_time_elapsed,
            pause=True
        )
    
    def update_time_elapsed(self):
        self.time_elapsed = monotonic() + self.accumulated_time - self.start_time
    
    def watch_time_elapsed(self):
        time = self.time_elapsed
        time, seconds = divmod(time, 60)
        hours, minutes = divmod(time, 60)
        time_string = f"{hours:02.0f}:{minutes:02.0f}:{seconds:05.2f}"
        self.update(time_string)
        
    def start(self):
        """ Start keeping track of the time elapsed. """
        self.start_time = monotonic()
        self.update_timer.resume()

    def stop(self):
        """ Stop keeping track of the time elapsed. """
        # self.time_elapsed = monotonic() + self.accumulated_time - self.start_time
        self.accumulated_time = self.time_elapsed
        self.update_timer.pause()


    def reset(self):
        """ Reset the time elapsed. """
        self.accumulated_time = 0
        self.time_elapsed = 0
        self.start_time = monotonic()

class Stopwatch(Static):
    """ custom stopwatch widget """

    def on_button_pressed(self, event: Button.Pressed) -> None:
        button_id = event.button.id
        time_display = self.query_one(TimeDisplay)
        if button_id == "start":
            time_display.start()
            self.add_class("started")
        elif button_id == "stop":
            time_display.stop()
            self.remove_class("started")
        elif button_id == "reset":
            time_display.reset()


    def compose(self):
        yield Button("Start", variant="success", id="start")
        yield Button(
            "Stop", 
            variant="error", 
            id="stop",
            classes="hidden"
        )
        yield Button("Reset", id="reset")
        yield TimeDisplay("00:00:00.00")


class StopwatchApp(App):
    BINDINGS = [
        ("d", "toggle_dark_mode", "Toggle dark mode"),
        ("a", "add_stopwatch", "Add"),
        ("r", "remove_stopwatch", "Remove"),
    ]
    
    CSS_PATH = "stopwatch.css"

    def compose(self):
        """what widgets is this app composed off?"""
        yield Header(show_clock=True)
        yield Footer()
        with ScrollableContainer(id="stopwatches"):
            yield Stopwatch()
            yield Stopwatch()
    
    def action_toggle_dark_mode(self):
        self.dark = not self.dark

    def action_add_stopwatch(self):
        new_stopwatch = Stopwatch()
        self.query_one("#stopwatches").mount(new_stopwatch)
        new_stopwatch.scroll_visible()

    def action_remove_stopwatch(self):
        stopwatches = self.query(Stopwatch)
        if stopwatches:
            stopwatches.last().remove()



if __name__ == "__main__":
    StopwatchApp().run()