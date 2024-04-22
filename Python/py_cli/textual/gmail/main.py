from textual import on
from textual.app import App, ComposeResult
from textual.containers import ScrollableContainer
from textual.reactive import reactive
from textual.widgets import Button,Footer, Header, Static, SelectionList
from textual.widgets.selection_list import Selection

list_emails = [
    "MasterClass <support@email.masterclass.com> | Subject: Coming soon: Leadership lessons from an award-winning director",
    "LinkedIn <messages-noreply@linkedin.com> | Subject: 💬 Add Siloana Ouverney, Structural Analysis Engineer",
    "adidas arena <movethelines@adidasarena.com> | Subject: La Reine des Neiges & Encanto à l'adidas arena ! ",
    "LinkedIn Job Alerts <jobalerts-noreply@linkedin.com> | Subject: “system engineer”: ConSol Partners - System Engineer and more",
    "LinkedIn Job Alerts <jobalerts-noreply@linkedin.com> | Subject: “software designer”: GoPro - Staff C++ Software Engineer and more",
    "Inter <no-reply@inter.co> | Subject: Nota de Corretagem de Aluguel",
    "trivago <newsletter@email.trivago.com> | Subject: Conheça o nosso novo logotipo 👋",
    "Tom Crosshill <news@crosshilltraining.com> | Subject: The best steak I never ate",
    "Medium Weekly Digest <noreply@medium.com> | Subject: Native Apps Are Dead — Get Over It | Andrew Zuo",
    "Club Paris 2024 <club@contact.paris2024.org> | Subject: Give a unique gift for Christmas",
    "MasterClass <support@email.masterclass.com> | Subject: Launched last month: Become a mogul by breaking the mold",
    "DHL eCommerce <noreply@dhlparcel.nl> | Subject: Je pakket is bezorgd in de brievenbus (JJD000090254011013098142)",
    "DHL eCommerce <noreply@dhlparcel.nl> | Subject: Je pakket is bezorgd in de brievenbus (JJD000090254011013103975)",
    "RENPHO <hello@mail.renpho.com> | Subject: Last Chance to Order Your Gift! 🚦🎁",
    "The Browser Company <members@arc.net> | Subject: Arc Update | One big step for Arc",
    "Grammarly Updates <info@send.grammarly.com> | Subject: 🚀 Grammarly product updates have arrived",
    "LinkedIn Job Alerts <jobalerts-noreply@linkedin.com> | Subject: “software designer”: ESRF - The European Synchrotron - Software Developer for Data Automation and more",
    "DHL eCommerce <noreply@dhlparcel.nl> | Subject: We staan vandaag voor de deur tussen 18.00 - 20.30 uur (JJD000090254011013098142)",
    "DHL eCommerce <noreply@dhlparcel.nl> | Subject: We staan vandaag voor de deur tussen 18.00 - 20.30 uur (JJD000090254011013103975)",
    "LinkedIn Job Alerts <jobalerts-noreply@linkedin.com> | Subject: “system engineer”: Capgemini Engineering - Senior System Engineer  / Grenoble and more",
    "Twitch <no-reply@twitch.tv> | Subject: Your Twitch Account - Successful Log-in",
    "Twitch <account@twitch.tv> | Subject: Your Twitch Login Verification Code",
    "SHAPING NEW TOMORROW <info@shapingnewtomorrow.eu> | Subject: Order your gifts with free shipping 🎄",
    "Nomad <hello@getnomad.app> | Subject: Daniel Your early Christmas gift just got better! 20% off eSIM data plans!",
    "The NordVPN team <support@nordvpn.com> | Subject: Special price for a password manager",
    "Todoist Mensal <no-reply@todoist.com> | Subject: Dezembro: seu bônus de fim de ano do esquadrão de cortadores de papel 🎁",
    "conseil.client@votreassistance.fr | Subject: email de confirmation",
    "Diego Collector <email@diegocollector.info> | Subject: 2024 será um ano caótico…",
    "Diego Collector <email@diegocollector.info> | Subject: 🛑[Aula Ao vivo] - Agora",
    "Diego Collector <email@diegocollector.info> | Subject: Você tem certeza que está pronto?",
]

# print(lines)

class GmailApp(App):
    CSS_PATH = "style.css"
    
    BINDINGS = [
        ("j", "cursor_down", "Down"),
        ("k", "cursor_up", "Up"),
        ("d", "item_toggle", "Toggle"),
        ("q", "quit", "Quit")
    ]
    
    def compose(self) -> ComposeResult:
        yield Header()
        # yield SelectionList[int](
        #     Selection("falkers maze", 0, True),
        # )

        selection_list = SelectionList[int]()
        for i,e in enumerate(list_emails):
            selection_list.add_option(Selection(e, i, True))
        yield selection_list

        yield Footer()
        
    def on_mount(self) -> None:
        self.query_one(SelectionList).border_title = "Mark the emails to remove:"

    def action_cursor_down(self):
        self.query_one(SelectionList).action_cursor_down()

    def action_cursor_up(self):
        self.query_one(SelectionList).action_cursor_up()

    def action_item_toggle(self):
        self.query_one(SelectionList).action_select()

    def action_quit(self):
        self.exit()

if __name__ == "__main__":
    GmailApp().run()