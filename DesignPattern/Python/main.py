from abc import ABC, abstractmethod

class State(ABC):
    @abstractmethod
    def receive_payment(self):
        '''method :: receive_payment'''
        
    @abstractmethod
    def ship(self):
        '''method :: ship'''

    @abstractmethod
    def mark_delivered(self):
        '''method :: mark_delivered'''
    
class Order:
    def __init__(self) -> None:
        self.unpaid_state = UnpaidState(self)
        self.paid_state = PaidState(self)
        self.shipped_state = ShippedState(self)
        self.delivered_state = DeliveredState(self)
        
        self.state = self.unpaid_state
        
    def set_state(self, state: State):
        self.state = state
        
    def receive_payment(self):
        self.state.receive_payment()

    def ship(self):
        self.state.ship()
    
    def mark_delivered(self):
        self.state.mark_delivered()

class UnpaidState(State):
    def __init__(self, context: Order):
        self.context = context

    def receive_payment(self):
        self.context.set_state(self.context.paid_state)
        print("Your payment was accepted")

    def ship(self):
        print("Can't ship unpaid orders")

    def mark_delivered(self):
        print("Can't deliver unshipped orders")
    
class PaidState(State):
    def __init__(self, context: Order):
        self.context = context

    def receive_payment(self):
        print("The order has already been paid for!")

    def ship(self):
        self.context.set_state(self.context.shipped_state)
        print("The order has been shipped!")

    def mark_delivered(self):
        print("Only shipped orders can be delivered")

class ShippedState(State):
    def __init__(self, context: Order):
        self.context = context

    def receive_payment(self):
        print("The order has already been paid for!")

    def ship(self):
        print("The order has been shipped!")

    def mark_delivered(self):
        self.context.set_state(self.context.delivered_state)
        print("The order has been delivered!")

class DeliveredState(State):
    def __init__(self, context: Order):
        self.context = context

    def receive_payment(self):
        self.context.set_state(self.context.paid_state)
        print("The order has already been paid for!")

    def ship(self):
        print("The order has already been delivered! Check the front door")

    def mark_delivered(self):
        print("Only shipped orders can be delivered! chack the front door")

if __name__ == "__main__":
    order = Order()
    print(order.state)
    order.receive_payment()
    print(order.state)
    order.ship()
    print(order.state)
    order.mark_delivered()
    print(order.state)